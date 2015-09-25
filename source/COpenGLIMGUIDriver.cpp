/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband based on example OpenGL driver for IMGUI from Omar Cornut
 *
 * The original OpenGL implementation where this driver is based on was implemented
 * by Omar Cornut as an example how to use the IMGUI with OpenGL.
 * You can find the IMGUI here: https://github.com/ocornut/imgui
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file       COpenGLIMGUIDriver.cpp
 * @author     Andre Netzeband
 * @brief      Contains a driver that uses native OpenGL functions to render the GUI.
 * @attention  This driver is just a test- and fallback implementation. It is not officially supported by the Irrlicht IMGUI binding.
 * @addtogroup IrrIMGUIPrivate
 */

#ifdef _IRRIMGUI_NATIVE_OPENGL_

// library includes
#include <IrrIMGUI/IrrIMGUIConfig.h>
#ifdef _IRRIMGUI_WINDOWS_
#include <windows.h>
#endif // _IRRIMGUI_WINDOWS_
#include <GL/gl.h>

// module includes
#include "COpenGLIMGUIDriver.h"
#include "IrrIMGUIDebug_priv.h"
#include "CGUITexture.h"

namespace IrrIMGUI
{
namespace Private
{
namespace Driver
{

  /// @brief Helper functions for OpenGL
  namespace OpenGLHelper
  {
    /// @brief Deleted a texture from memory if it uses its own memory.
    /// @param pGUITexture Is a CGUITexture object where the GPU memory should be deleted from.
    void deleteTextureFromMemory(CGUITexture * pGUITexture);

    /// @brief Copies the current loaded GUI Fonts into the GPU memory.
    /// @return Returns a GPU memory ID.
    ImTextureID copyTextureIDFromGUIFont(void);

    /// @brief Extracts the GPU memory ID for GUI usage from the ITexture object.
    /// @param pTexture Is a pointer to a ITexture object.
    /// @return Returns a GPU memory ID.
    ImTextureID getTextureIDFromIrrlichtTexture(irr::video::ITexture * pTexture);

    /// @brief Copies the content of an ITexture object into the GPU memory.
    /// @param pTexture Is a pointer to a ITexture object.
    /// @return Returns a GPU memory ID.
    ImTextureID copyTextureIDFromIrrlichtTexture(irr::video::ITexture * pTexture);

    /// @brief Copies the content of an IImage object into the GPU memory.
    /// @param pImage Is a pointer to a IImage object.
    /// @return Returns a GPU memory ID.
    ImTextureID copyTextureIDFromIrrlichtImage(irr::video::IImage * pImage);

    /// @brief Creates an new texture from raw data inside the GPU memory.
    ///        When the color format does not fit to the OpenGL format, it will be translated automatically.
    /// @param ColorFormat Is the used Color Format inside the raw data.
    /// @param pPixelData  Is a pointer to the image array.
    /// @param Width       Is the number of X pixels.
    /// @param Height      Is the number of Y pixels.
    /// @return Returns a GPU memory ID.
    ImTextureID createTextureIDFromRawData(EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height);

    /// @brief Creates an new texture from raw data inside the GPU memory.
    ///        For this, the Color Format must be already in an OpenGL accepted format!
    /// @param OpenGLColorFormat Is the used OpenGL compatible Color Format inside the raw data.
    /// @param pPixelData        Is a pointer to the image array.
    /// @param Width             Is the number of X pixels.
    /// @param Height            Is the number of Y pixels.
    /// @return Returns a GPU memory ID.
    ImTextureID createTextureInMemory(GLint OpenGLColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height);

    /// @brief Translates an image in ARGB format (used by Irrlicht) to an image in RGBA format (used by OpenGL).
    /// @param pSource      Is a pointer to the source data array.
    /// @param pDestination Is a pointer to the destination data array.
    /// @param Width             Is the number of X pixels.
    /// @param Height            Is the number of Y pixels.
    void copyARGBImageToRGBA(irr::u32 * pSource, irr::u32 * pDestination, irr::u32 Width, irr::u32 Height);

    /// @return Returns the value of an OpenGL Enum Value
    /// @param Which is the enum where we want to know the value.
    GLenum getGlEnum(GLenum const Which);

    /// @brief Restores an OpenGL Bit
    /// @param WhichBit is the bit to restore.
    /// @param Value must be true or false, whether it was set or cleared.
    void restoreGLBit(GLenum const WhichBit, bool const Value);

    /// @brief Helper Class to store and restore the OpenGL state.
    class COpenGLState
    {
      public:
        /// @brief The Constructor stored the OpenGL state.
        COpenGLState(void);

        /// @brief The Destructor restores the state.
        ~COpenGLState(void);

      private:
        GLint  mOldTexture;
    };
  }

  COpenGLIMGUIDriver::COpenGLIMGUIDriver(irr::IrrlichtDevice * const pDevice):
      IIMGUIDriver(pDevice)
  {
    setupFunctionPointer();

    return;
  }

  COpenGLIMGUIDriver::~COpenGLIMGUIDriver(void)
  {
    return;
  }

  void COpenGLIMGUIDriver::setupFunctionPointer(void)
  {
    ImGuiIO &rGUIIO  = ImGui::GetIO();

    rGUIIO.RenderDrawListsFn = COpenGLIMGUIDriver::drawGUIList;

#ifdef _WIN32
    irr::video::IVideoDriver * const pDriver = getIrrDevice()->getVideoDriver();
    irr::video::SExposedVideoData const &rExposedVideoData = pDriver->getExposedVideoData();

    rGUIIO.ImeWindowHandle = reinterpret_cast<HWND>(rExposedVideoData.OpenGLWin32.HWnd);

#else
//Maybe for Linux you have to pass a X11 Window handle (rExposedVideoData.OpenGLLinux.X11Window)?
#endif

    return;
  }

  void COpenGLIMGUIDriver::drawCommandList(ImDrawList * const pCommandList)
  {
    ImGuiIO& rGUIIO = ImGui::GetIO();
    float const FrameBufferHeight = rGUIIO.DisplaySize.y * rGUIIO.DisplayFramebufferScale.y;

    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

    ImDrawVert * const pVertexBuffer = &(pCommandList->VtxBuffer.front());
    ImDrawIdx  * const pIndexBuffer  = &(pCommandList->IdxBuffer.front());
    int FirstIndexElement = 0;

    glVertexPointer(  2, GL_FLOAT,         sizeof(ImDrawVert), (void*)(((irr::u8*)pVertexBuffer) + OFFSETOF(ImDrawVert, pos)));
    glTexCoordPointer(2, GL_FLOAT,         sizeof(ImDrawVert), (void*)(((irr::u8*)pVertexBuffer) + OFFSETOF(ImDrawVert, uv)));
    glColorPointer(   4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(((irr::u8*)pVertexBuffer) + OFFSETOF(ImDrawVert, col)));

    for (int CommandIndex = 0; CommandIndex < pCommandList->CmdBuffer.size(); CommandIndex++)
    {

      ImDrawCmd * const pCommand = &pCommandList->CmdBuffer[CommandIndex];

      if (pCommand->UserCallback)
      {
        pCommand->UserCallback(pCommandList, pCommand);
      }
      else
      {
        CGUITexture * const pGUITexture = reinterpret_cast<CGUITexture*>(pCommand->TextureId);
        glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pGUITexture->mGPUTextureID);
        glScissor((int)pCommand->ClipRect.x, (int)(FrameBufferHeight - pCommand->ClipRect.w), (int)(pCommand->ClipRect.z - pCommand->ClipRect.x), (int)(pCommand->ClipRect.w - pCommand->ClipRect.y));
        glDrawElements(GL_TRIANGLES, (GLsizei)pCommand->ElemCount, GL_UNSIGNED_SHORT, &(pIndexBuffer[FirstIndexElement]));
      }

      FirstIndexElement += pCommand->ElemCount;
    }

    return;
  }

  void COpenGLIMGUIDriver::drawGUIList(ImDrawData * const pDrawData)
  {
    OpenGLHelper::COpenGLState OpenGLState;

    // setup OpenGL states
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);

    // calculate framebuffe scales
    ImGuiIO& rGUIIO = ImGui::GetIO();
    pDrawData->ScaleClipRects(rGUIIO.DisplayFramebufferScale);

    // setup orthographic projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, rGUIIO.DisplaySize.x, rGUIIO.DisplaySize.y, 0.0f, -1.0f, +1.0f);

    // setup model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int CommandListIndex = 0; CommandListIndex < pDrawData->CmdListsCount; CommandListIndex++)
    {
      drawCommandList(pDrawData->CmdLists[CommandListIndex]);
    }

    // restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    return;
  }


  IGUITexture *COpenGLIMGUIDriver::createTexture(EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height)
  {
    mTextureInstances++;
    CGUITexture * const pRealGUITexture = new CGUITexture();

    pRealGUITexture->mIsUsingOwnMemory = true;
    pRealGUITexture->mSourceType       = ETST_RAWDATA;
    pRealGUITexture->mSource.RawDataID = pPixelData;
    pRealGUITexture->mIsValid          = true;

    pRealGUITexture->mGPUTextureID = OpenGLHelper::createTextureIDFromRawData(ColorFormat, pPixelData, Width, Height);

    return pRealGUITexture;
  }

  IGUITexture * COpenGLIMGUIDriver::createTexture(irr::video::ITexture * pTexture)
  {
    mTextureInstances++;
    CGUITexture * const pRealGUITexture = new CGUITexture();

#ifdef _IRRIMGUI_FAST_OPENGL_TEXTURE_HANDLE_
    pRealGUITexture->mIsUsingOwnMemory = false;
    pRealGUITexture->mSourceType       = ETST_TEXTURE;
    pRealGUITexture->mSource.TextureID = pTexture;
    pRealGUITexture->mIsValid          = true;

    pRealGUITexture->mGPUTextureID = OpenGLHelper::getTextureIDFromIrrlichtTexture(pTexture);
#else
    pRealGUITexture->mIsUsingOwnMemory = true;
    pRealGUITexture->mSourceType       = ETST_TEXTURE;
    pRealGUITexture->mSource.TextureID = pTexture;
    pRealGUITexture->mIsValid          = true;

    pRealGUITexture->mGPUTextureID = OpenGLHelper::copyTextureIDFromIrrlichtTexture(pTexture);
#endif
    return pRealGUITexture;
  }

  IGUITexture * COpenGLIMGUIDriver::createTexture(irr::video::IImage * pImage)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_IMAGE;
    pGUITexture->mSource.ImageID   = pImage;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = OpenGLHelper::copyTextureIDFromIrrlichtImage(pImage);

    return pGUITexture;
  }

  IGUITexture *COpenGLIMGUIDriver::createFontTexture(void)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_GUIFONT;
    pGUITexture->mSource.GUIFontID = 0;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = OpenGLHelper::copyTextureIDFromGUIFont();

    void * const pFontTexture = reinterpret_cast<void *>(pGUITexture);
    ImGui::GetIO().Fonts->TexID = pFontTexture;

    return pGUITexture;
  }

  void COpenGLIMGUIDriver::updateTexture(IGUITexture * pGUITexture, EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height)
  {
    CGUITexture * const pRealGUITexture = dynamic_cast<CGUITexture*>(pGUITexture);

    FASSERT(pRealGUITexture->mIsValid);

    bool IsRecreateNecessary = false;

    if (pRealGUITexture->mSourceType != ETST_RAWDATA)
    {
      IsRecreateNecessary = true;
    }
    else if (pPixelData != pRealGUITexture->mSource.RawDataID)
    {
      IsRecreateNecessary = true;
    }
    else if (pRealGUITexture->mIsUsingOwnMemory)
    {
      IsRecreateNecessary = true;
    }

    if (IsRecreateNecessary)
    {
      OpenGLHelper::deleteTextureFromMemory(pRealGUITexture);

      pRealGUITexture->mIsUsingOwnMemory = true;
      pRealGUITexture->mSourceType       = ETST_RAWDATA;
      pRealGUITexture->mSource.RawDataID = pPixelData;
      pRealGUITexture->mIsValid          = true;

      pRealGUITexture->mGPUTextureID     = OpenGLHelper::createTextureIDFromRawData(ColorFormat, pPixelData, Width, Height);
    }

    return;
  }

  void COpenGLIMGUIDriver::updateTexture(IGUITexture * pGUITexture, irr::video::ITexture * pTexture)
  {
    CGUITexture * const pRealGUITexture = dynamic_cast<CGUITexture*>(pGUITexture);

    FASSERT(pRealGUITexture->mIsValid);

    bool IsRecreateNecessary = false;

    if (pRealGUITexture->mSourceType != ETST_TEXTURE)
    {
      IsRecreateNecessary = true;
    }
    else if (pTexture != pRealGUITexture->mSource.TextureID)
    {
      IsRecreateNecessary = true;
    }
    else if (pRealGUITexture->mIsUsingOwnMemory)
    {
      IsRecreateNecessary = true;
    }

    if (IsRecreateNecessary)
    {
      OpenGLHelper::deleteTextureFromMemory(pRealGUITexture);

#ifdef _IRRIMGUI_FAST_OPENGL_TEXTURE_HANDLE_
      pRealGUITexture->mIsUsingOwnMemory = false;
      pRealGUITexture->mSourceType       = ETST_TEXTURE;
      pRealGUITexture->mSource.TextureID = pTexture;
      pRealGUITexture->mIsValid          = true;

      pRealGUITexture->mGPUTextureID = OpenGLHelper::getTextureIDFromIrrlichtTexture(pTexture);
#else
      pRealGUITexture->mIsUsingOwnMemory = true;
      pRealGUITexture->mSourceType       = ETST_TEXTURE;
      pRealGUITexture->mSource.TextureID = pTexture;
      pRealGUITexture->mIsValid          = true;

      pRealGUITexture->mGPUTextureID = OpenGLHelper::copyTextureIDFromIrrlichtTexture(pTexture);
#endif
    }

    return;
  }

  void COpenGLIMGUIDriver::updateTexture(IGUITexture * pGUITexture, irr::video::IImage * pImage)
  {
    CGUITexture * const pRealGUITexture = dynamic_cast<CGUITexture*>(pGUITexture);

    FASSERT(pRealGUITexture->mIsValid);

    bool IsRecreateNecessary = false;

    if (pRealGUITexture->mSourceType != ETST_IMAGE)
    {
      IsRecreateNecessary = true;
    }
    else if (pImage != pRealGUITexture->mSource.ImageID)
    {
      IsRecreateNecessary = true;
    }
    else if (pRealGUITexture->mIsUsingOwnMemory)
    {
      IsRecreateNecessary = true;
    }

    if (IsRecreateNecessary)
    {
      OpenGLHelper::deleteTextureFromMemory(pRealGUITexture);

      pRealGUITexture->mIsUsingOwnMemory = true;
      pRealGUITexture->mSourceType       = ETST_TEXTURE;
      pRealGUITexture->mSource.ImageID   = pImage;
      pRealGUITexture->mIsValid          = true;

      pRealGUITexture->mGPUTextureID     = OpenGLHelper::copyTextureIDFromIrrlichtImage(pImage);
    }

    return;
  }

  void COpenGLIMGUIDriver::updateFontTexture(IGUITexture * const pGUITexture)
  {
    CGUITexture * const pRealGUITexture = dynamic_cast<CGUITexture*>(pGUITexture);

    FASSERT(pRealGUITexture->mIsValid);

    OpenGLHelper::deleteTextureFromMemory(pRealGUITexture);

    pRealGUITexture->mIsUsingOwnMemory = true;
    pRealGUITexture->mSourceType       = ETST_GUIFONT;
    pRealGUITexture->mSource.GUIFontID = 0;
    pRealGUITexture->mIsValid          = true;
    pRealGUITexture->mGPUTextureID     = OpenGLHelper::copyTextureIDFromGUIFont();

    void * const pFontTexture = reinterpret_cast<void *>(pGUITexture);
    ImGui::GetIO().Fonts->TexID = pFontTexture;

    return;
  }

  void COpenGLIMGUIDriver::deleteTexture(IGUITexture * pGUITexture)
  {
    CGUITexture * const pRealGUITexture = dynamic_cast<CGUITexture*>(pGUITexture);

    FASSERT(pRealGUITexture->mIsValid);

    OpenGLHelper::deleteTextureFromMemory(pRealGUITexture);
    delete(pRealGUITexture);
    mTextureInstances--;
    return;
  }

namespace OpenGLHelper
{
  void copyARGBImageToRGBA(irr::u32 * const pSource, irr::u32 * const pDestination, irr::u32 const Width, irr::u32 const Height)
  {
    for (irr::u32 X = 0; X < Width; X++)
    {
      for (irr::u32 Y = 0; Y < Height; Y++)
      {
        irr::video::SColor PixelColor;
        PixelColor.setData(&pSource[X + Y * Width], irr::video::ECF_A8R8G8B8);
        irr::u8 * const pDestPixel = (irr::u8 *)(&pDestination[X + Y * Width]);
        PixelColor.toOpenGLColor(pDestPixel);
      }
    }

    return;
  }

  ImTextureID createTextureInMemory(GLint OpenGLColorFormat, irr::u8 * const pPixelData, irr::u32 const Width, irr::u32 const Height)
  {
    // Store current Texture handle
    GLint OldTextureID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &OldTextureID);

    // Create new texture for image
    GLuint NewTextureID;
    glGenTextures(1, &NewTextureID);
    glBindTexture(GL_TEXTURE_2D, NewTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, OpenGLColorFormat, Width, Height, 0, OpenGLColorFormat, GL_UNSIGNED_BYTE, pPixelData);

    ImTextureID pTexture = reinterpret_cast<void *>(static_cast<intptr_t>(NewTextureID));

    // Reset Texture handle
    glBindTexture(GL_TEXTURE_2D, OldTextureID);

    return pTexture;
  }

  ImTextureID createTextureIDFromRawData(EColorFormat const ColorFormat, irr::u8 * pPixelData, irr::u32 const Width, irr::u32 const Height)
  {
    irr::u8 * pCopyImageData = nullptr;
    GLint     OpenGLColor;

    switch(ColorFormat)
    {
      // convert color to OpenGL color format
      case ECF_A8R8G8B8:
        pCopyImageData = reinterpret_cast<irr::u8*>(new irr::u32[Width * Height]);
        copyARGBImageToRGBA(reinterpret_cast<irr::u32*>(pPixelData), reinterpret_cast<irr::u32*>(pCopyImageData), Width, Height);
        OpenGLColor = GL_RGBA;
        pPixelData = pCopyImageData;
        break;

      case ECF_R8G8B8A8:
        OpenGLColor = GL_RGBA;
        break;

      case ECF_A8:
        OpenGLColor = GL_ALPHA;
        break;

      default:
        OpenGLColor = GL_ALPHA;
        LOG_ERROR("Unknown color format: " << ColorFormat << "\n");
        FASSERT(false);
        break;
    }

    ImTextureID const pTexture = createTextureInMemory(OpenGLColor, pPixelData, Width, Height);

    if (pCopyImageData)
    {
      delete[] pCopyImageData;
    }

    LOG_NOTE("{IrrIMGUI-GL} Create texture from raw data. Handle: " << std::hex << pTexture << "\n");

    return pTexture;
  }

  ImTextureID copyTextureIDFromIrrlichtImage(irr::video::IImage * const pImage)
  {
    // Convert pImage to RGBA
    int const Width  = pImage->getDimension().Width;
    int const Height = pImage->getDimension().Height;
    irr::u32 * const pImageData = new irr::u32[Width * Height];

    for (int X = 0; X < Width; X++)
    {
      for (int Y = 0; Y < Height; Y++)
      {
        irr::video::SColor const PixelColor = pImage->getPixel(X, Y);
        irr::u8 * const pPixelPointer = (irr::u8 *)(&pImageData[X + Y * Width]);
        PixelColor.toOpenGLColor(pPixelPointer);
      }
    }

    ImTextureID const pTexture = createTextureInMemory(GL_RGBA, reinterpret_cast<irr::u8*>(pImageData), Width, Height);

    delete[] pImageData;

    LOG_NOTE("{IrrIMGUI-GL} Create texture from IImage. Handle: " << std::hex << pTexture << "\n");

    return pTexture;
  }

  ImTextureID copyTextureIDFromIrrlichtTexture(irr::video::ITexture * pTexture)
  {
    // Convert pImage to RGBA
    int const Width  = pTexture->getSize().Width;
    int const Height = pTexture->getSize().Height;
    irr::u32 * const pImageData = new irr::u32[Width * Height];

    irr::u32 const Pitch = pTexture->getPitch();
    irr::video::ECOLOR_FORMAT const ColorFormat = pTexture->getColorFormat();
    irr::u32 const Bytes = irr::video::IImage::getBitsPerPixelFromFormat(ColorFormat) / 8;
    irr::u8  * const pTextureData = reinterpret_cast<irr::u8 *>(pTexture->lock());
    FASSERT(pTextureData);

    for (int X = 0; X < Width; X++)
    {
      for (int Y = 0; Y < Height; Y++)
      {
        irr::video::SColor PixelColor = irr::video::SColor();
        PixelColor.setData((void*)(pTextureData + (Y * Pitch) + (X * Bytes)), ColorFormat);
        irr::u8 * const pPixelPointer = (irr::u8 *)(&pImageData[X + Y * Width]);
        PixelColor.toOpenGLColor(pPixelPointer);
      }
    }

    pTexture->unlock();

    ImTextureID const pNewTexture = createTextureInMemory(GL_RGBA, reinterpret_cast<irr::u8*>(pImageData), Width, Height);

    delete[] pImageData;

    LOG_NOTE("{IrrIMGUI-GL} Create texture from ITexture. Handle: " << std::hex << pNewTexture << "\n");

    return pNewTexture;
  }

  ImTextureID getTextureIDFromIrrlichtTexture(irr::video::ITexture * pTexture)
  {
    // Dirty hack to easily create an OpenGL texture out of an Irrlicht texture
    class COpenGLDriver;
    class COpenGLTexture : public irr::video::ITexture
    {
    public:
      irr::core::dimension2d<irr::u32> ImageSize;
      irr::core::dimension2d<irr::u32> TextureSize;
      irr::video::ECOLOR_FORMAT ColorFormat;
      COpenGLDriver* Driver;
      irr::video::IImage* Image;
      irr::video::IImage* MipImage;

      GLuint TextureName;
      GLint InternalFormat;
      GLenum PixelFormat;
      GLenum PixelType;

      irr::u8 MipLevelStored;
      bool HasMipMaps;
      bool MipmapLegacyMode;
      bool IsRenderTarget;
      bool AutomaticMipmapUpdate;
      bool ReadOnlyLock;
      bool KeepImage;
    };

    COpenGLTexture * const pOpenGLTexture = reinterpret_cast<COpenGLTexture * const>(pTexture);
    GLuint NewTextureID = pOpenGLTexture->TextureName;
    ImTextureID TexID = reinterpret_cast<void *>(static_cast<intptr_t>(NewTextureID));

    LOG_NOTE("{IrrIMGUI-GL} Reuse GPU memory from ITexture. Handle: " << std::hex << TexID << "\n");

    return TexID;
  }

  ImTextureID copyTextureIDFromGUIFont(void)
  {
    ImGuiIO &rGUIIO  = ImGui::GetIO();

    // Get Font Texture from IMGUI system.
    irr::u8 * pPixelData;
    int Width, Height;
    rGUIIO.Fonts->GetTexDataAsAlpha8(&pPixelData, &Width, &Height);

    ImTextureID const TextureID = createTextureIDFromRawData(ECF_A8, pPixelData, Width, Height);

    // Store Texture information in IMGUI system
    rGUIIO.Fonts->ClearTexData();

    return TextureID;
  }

  void deleteTextureFromMemory(CGUITexture * pGUITexture)
  {
    if (pGUITexture->mIsUsingOwnMemory)
    {
      LOG_NOTE("{IrrIMGUI-GL} Delete GPU memory. Handle: " << std::hex << pGUITexture->mGPUTextureID << "\n");
      GLuint TextureID = static_cast<GLuint>(reinterpret_cast<intptr_t>(pGUITexture->mGPUTextureID));
      glDeleteTextures(1, &TextureID);
    }
    pGUITexture->mIsValid = false;
    return;
  }

  GLenum getGlEnum(GLenum const Which)
  {
    GLint Vector[30];
    glGetIntegerv(Which, Vector);
    return Vector[0];
  }

  void restoreGLBit(GLenum const WhichBit, bool const Value)
  {
    if (Value)
    {
      glEnable(WhichBit);
    }
    else
    {
      glDisable(WhichBit);
    }
  }

  COpenGLState::COpenGLState(void)
  {
    // store current texture
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &mOldTexture);

    // store other settings
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);

    // store projection matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    // store view matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    return;
  }

  COpenGLState::~COpenGLState(void)
  {
    // restore view matrix
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // restore projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // restore other settings
    glPopAttrib();

    // restore texture
    glBindTexture(GL_TEXTURE_2D, mOldTexture);

    return;
  }

}

}
}
}


/* Pure Irrlicht implementation:

  irr::u32 * pImageData = new irr::u32[Width * Height];

  for (int X = 0; X < (Width * Height); X++)
  {
    // set only Alpha
    irr::video::SColor Color(PixelData[X], 255, 255, 255);
    Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
  }
  pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

  irr::core::dimension2d<irr::u32> const Size(Width, Height);
  irr::video::IImage * const pImage = pIrrDriver->createImageFromData(irr::video::ECF_A8R8G8B8, Size, pImageData);
  pTexture = pIrrDriver->addTexture("DefaultIMGUITexture", pImage);

  if (rGUIIO.RenderDrawListsFn == COpenGLIMGUIDriver::drawGUIList)
  {
    // Store Texture information in IMGUI system
    rGUIIO.Fonts->TexID = pTexture;
    rGUIIO.Fonts->ClearInputData();
    rGUIIO.Fonts->ClearTexData();
  }

  delete[] pImageData;
  */

#if 0 // Pure irrlicht implementation
void COpenGLIMGUIDriver::drawCommandList(ImDrawList * const pCommandList)
{

  /*
  const ImDrawList* cmd_list = draw_data->CmdLists[n];
  const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
  const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
  glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
  glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
  glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

  for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
  {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
      if (pcmd->UserCallback)
      {
          pcmd->UserCallback(cmd_list, pcmd);
      }
      else
      {
          glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
          glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
          glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
      }
      idx_buffer += pcmd->ElemCount;
  }
  */

  //ImDrawVert Vertex;

  irr::u16 * const pIndices = &(pCommandList->IdxBuffer.front());

  irr::u32 LastIndex = 0;
  irr::u32 NumberOfVertex = pCommandList->VtxBuffer.size();
  irr::video::S3DVertex * const pVertexArray = new irr::video::S3DVertex[NumberOfVertex];

  /*
  pIrrDriver->enableMaterial2D(true);
  pIrrDriver->getMaterial2D().TextureLayer[0].BilinearFilter=false;
  pIrrDriver->getMaterial2D().TextureLayer[0].AnisotropicFilter=false;
  pIrrDriver->getMaterial2D().TextureLayer[0].TrilinearFilter=false;
  pIrrDriver->getMaterial2D().TextureLayer[0].LODBias=-4;
  pIrrDriver->getMaterial2D().AntiAliasing=irr::video::EAAM_OFF;
  */

  for (int i = 0; i < NumberOfVertex; i++)
  {
    ImDrawVert &rImGUIVertex = pCommandList->VtxBuffer[i];

    pVertexArray[i].Pos     = irr::core::vector3df(static_cast<irr::f32>(rImGUIVertex.pos.x), static_cast<irr::f32>(rImGUIVertex.pos.y), 0.0) ;
    pVertexArray[i].Normal  = irr::core::vector3df(0.0, 0.0, 1.0);
    irr::u8 const Red   = (rImGUIVertex.col >>  0) & 0xFF;
    irr::u8 const Green = (rImGUIVertex.col >>  8) & 0xFF;
    irr::u8 const Blue  = (rImGUIVertex.col >> 16) & 0xFF;
    irr::u8 const Alpha = (rImGUIVertex.col >> 24) & 0xFF;
    pVertexArray[i].Color   = irr::video::SColor(Alpha, Red, Green, Blue);
    pVertexArray[i].TCoords = irr::core::vector2df(static_cast<irr::f32>(rImGUIVertex.uv.x), static_cast<irr::f32>(rImGUIVertex.uv.y));
  }

  pIrrDriver->enableMaterial2D(false);

  for (int CommandIndex = 0; CommandIndex < pCommandList->CmdBuffer.size(); CommandIndex++)
  {
    ImDrawCmd * const pDrawCommand = &pCommandList->CmdBuffer[CommandIndex];

    // TODO: implement user callback function!

    auto pTexture = static_cast<irr::video::ITexture*>(pDrawCommand->TextureId);
    irr::video::SMaterial Material;

    Material.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    Material.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE);
    Material.setTexture(0, pTexture);
    Material.UseMipMaps = false;
    Material.Thickness = 0.0;

    /*
    pIrrDriver->getMaterial2D().MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    pIrrDriver->getMaterial2D().MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE);
    pIrrDriver->getMaterial2D().setTexture(0, pTexture);
    pIrrDriver->getMaterial2D().Thickness = 0.0;
    */

    Material.setFlag(irr::video::EMF_ANTI_ALIASING, false);
    Material.setFlag(irr::video::EMF_BILINEAR_FILTER, false);
    Material.setFlag(irr::video::EMF_ZBUFFER, false);
    Material.setFlag(irr::video::EMF_BLEND_OPERATION, false);
    Material.setFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    Material.setFlag(irr::video::EMF_FRONT_FACE_CULLING, false);
    Material.setFlag(irr::video::EMF_ANISOTROPIC_FILTER, true);
    Material.setFlag(irr::video::EMF_TRILINEAR_FILTER, false);
    Material.TextureLayer[0].LODBias = -4;
    Material.AntiAliasing = irr::video::EAAM_OFF;

    pIrrDriver->setMaterial(Material);

    pIrrDriver->draw2DVertexPrimitiveList(
        pVertexArray,
        NumberOfVertex,
        &pIndices[LastIndex],
        pDrawCommand->ElemCount / 3,
        irr::video::EVT_STANDARD,
        irr::scene::EPT_TRIANGLES,
        irr::video::EIT_16BIT
        );

    LastIndex += pDrawCommand->ElemCount;

  }

  delete[] pVertexArray;

  return;
}
#endif

#endif // _IRRIMGUI_NATIVE_OPENGL_
