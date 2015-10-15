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
 * @file       CIrrlichtIMGUIDriver.cpp
 * @author     Andre Netzeband
 * @brief      Contains a driver that uses Irrlicht primitive drawing functions to render the GUI.
 * @addtogroup IrrIMGUIPrivate
 */

// library includes
#include <IrrIMGUI/IrrIMGUIConfig.h>
#ifdef _IRRIMGUI_WINDOWS_
#include <windows.h>
#endif // _IRRIMGUI_WINDOWS_
#include <GL/gl.h>

// module includes
#include "CIrrlichtIMGUIDriver.h"
#include "private/CGUITexture.h"
#include "private/IrrIMGUIDebug_priv.h"

/**
* @addtogroup IrrIMGUIPrivate
* @{
*/

namespace IrrIMGUI
{
namespace Private
{

/// @brief Contains driver classes for the IMGUI render system.
namespace Driver
{
/// @brief Functions that help adapting Irrlicht logic to IMGUI
namespace IrrlichtHelper
{
  /// @brief A magic number for the default font ID IMGUI.
  static irr::u8 * const IMGUI_FONT_ID = nullptr;

  /// @brief This is used to create an unique texture name.
  static irr::u32 TextureCreationID = 0;

  /// @brief Indicates, if trilinear filter should be enabled for textures.
  static bool IsTrilinearFilterEnabled = false;

  /// @brief Translates an IMGUI Color to an Irrlicht Color.
  /// @param ImGuiColor is the u32 Color value from IMGUI.
  /// @return Returns a SColor object for Irrlicht.
  irr::video::SColor getColorFromImGuiColor(irr::u32 ImGuiColor);

  /// @brief Copies a list of IMGUI vertices to a list of Irrlicht Vertices.
  /// @param rIMGUIVertexBuffer Is an IMGUI Vertex-Buffer object.
  /// @param pIrrlichtVertex    Is a pointer to an Irrlicht Vertex Array.
  /// @param rOffset            Is an offset that is applied to every vertex.
  void copyImGuiVertices2IrrlichtVertices(ImVector<ImDrawVert> &rIMGUIVertexBuffer, irr::video::S3DVertex * pIrrlichtVertex, irr::core::vector3df const &rOffset);

  /// @brief Creates a Texture object from the currently loaded Fonts.
  /// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
  /// @return Returns ITexture object as IMGUI Texture ID.
  ImTextureID copyTextureIDFromGUIFont(irr::video::IVideoDriver * pIrrDriver);

  /// @brief Created a Texture object from raw data.
  /// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
  /// @param ColorFormat Is the format of the Color of every Pixel.
  /// @param pPixelData  Is a pointer to the pixel array.
  /// @param Width       Is the number of Pixels in X direction.
  /// @param Height      Is the number of Pixels in Y direction.
  ImTextureID copyTextureIDFromRawData(irr::video::IVideoDriver * pIrrDriver, EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height);

  /// @brief Creates a Texture object from the currently loaded Fonts.
  /// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
  /// @param pImage      Is a pointer to an Irrlicht IImage object.
  /// @return Returns ITexture object as IMGUI Texture ID.
  ImTextureID copyTextureIDFromImage(irr::video::IVideoDriver * pIrrDriver, irr::video::IImage * pImage);

  /// @brief Deleted the memory from this texture ID.
  /// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
  /// @param pGUITexture is a pointer to the texture object.
  void deleteTextureID(irr::video::IVideoDriver * pIrrDriver, CGUITexture * pGUITexture);

  /// @brief Applies a workaround for an Irrlicht issue with moving clipping planes.
  /// @param pIrrDriver  Is a pointer to the Irrlicht driver object.
  void applyMovingClippingPlaneWorkaround(irr::video::IVideoDriver * pIrrDriver);

  /// @brief Sets the standard GUI material settings.
  /// @param rMaterial Is a reference to the material where the settings should be applied to.
  /// @param pTexture  Is the texture, that should be used.
  void setupStandardGUIMaterial(irr::video::SMaterial &rMaterial, irr::video::ITexture * pTexture);

  /// @brief Apples a clipping rectangle. Outside of this rectangle nothing is rendered.
  /// @param pIrrDriver    Is a pointer to the Irrlicht driver object.
  /// @param rClippingRect Is the IMGUI clipping rect to apply.
  void applyClippingRect(irr::video::IVideoDriver * pIrrDriver, ImVec4 &rClippingRect);

  /// @brief Disables the clipping rectangle.
  /// @param pIrrDriver    Is a pointer to the Irrlicht driver object.
  void disableClippingRect(irr::video::IVideoDriver * pIrrDriver);
}

  irr::core::vector3df CIrrlichtIMGUIDriver::mOffset(0.0f, 0.0f, 0.0f);

  CIrrlichtIMGUIDriver::CIrrlichtIMGUIDriver(irr::IrrlichtDevice * const pDevice):
    IIMGUIDriver(pDevice)
  {
    setupFunctionPointer();

    irr::video::IVideoDriver * pDriver = pDevice->getVideoDriver();
    irr::video::E_DRIVER_TYPE Type = pDriver->getDriverType();

    switch(Type)
    {
      case irr::video::EDT_OPENGL:
        mOffset = irr::core::vector3df(-0.375f, -0.375f, 0.0f);
        IrrlichtHelper::IsTrilinearFilterEnabled = false;
        LOG_NOTE("{IrrIMGUI-Irr} Start Irrlicht High Level GUI renderer in OpenGL mode.\n");
        break;

      case irr::video::EDT_DIRECT3D9:
      case irr::video::EDT_DIRECT3D8:
        mOffset = irr::core::vector3df(0.0f, 0.0f, 0.0f);
        IrrlichtHelper::IsTrilinearFilterEnabled = true;
        LOG_NOTE("{IrrIMGUI-Irr} Start Irrlicht High Level GUI renderer in DirectX mode.\n");
        break;

      case irr::video::EDT_NULL:
        mOffset = irr::core::vector3df(0.0f, 0.0f, 0.0f);
        IrrlichtHelper::IsTrilinearFilterEnabled = false;
        break;

      default:
        mOffset = irr::core::vector3df(0.0f, 0.0f, 0.0f);
        LOG_WARNING("{IrrIMGUI-Irr} Start Irrlicht High Level GUI renderer in unknown video mode, this Irrlicht renderer might not be supported!\n");
        break;
    }


    return;
  }

  CIrrlichtIMGUIDriver::~CIrrlichtIMGUIDriver(void)
  {
    return;
  }

  void CIrrlichtIMGUIDriver::setupFunctionPointer(void)
  {
    ImGuiIO &rGUIIO  = ImGui::GetIO();

    rGUIIO.RenderDrawListsFn = CIrrlichtIMGUIDriver::drawGUIList;

    return;
  }

  void CIrrlichtIMGUIDriver::drawGUIList(ImDrawData * pDrawData)
  {
    pDrawData->ScaleClipRects(ImGui::GetIO().DisplayFramebufferScale);

    irr::video::IVideoDriver * const pIrrDriver = getIrrDevice()->getVideoDriver();
    irr::video::SMaterial const CurrentMaterial = pIrrDriver->getMaterial2D();
    pIrrDriver->enableMaterial2D(true);

    IrrlichtHelper::applyMovingClippingPlaneWorkaround(pIrrDriver);

    for (int CommandListIndex = 0; CommandListIndex < pDrawData->CmdListsCount; CommandListIndex++)
    {
      drawCommandList(pDrawData->CmdLists[CommandListIndex]);
    }

    pIrrDriver->enableMaterial2D(false);
    pIrrDriver->getMaterial2D() = CurrentMaterial;

    return;
  }

  void CIrrlichtIMGUIDriver::drawCommandList(ImDrawList * pCommandList)
  {
    irr::u16 * const pIndices = &(pCommandList->IdxBuffer.front());

    irr::u32 LastUsedIndex = 0;
    irr::u32 const NumberOfVertex = pCommandList->VtxBuffer.size();

    // TODO: Workaround for incompatible Vertex datatype in IMGUI.
    //       This costs a lot of performance... nevertheless it seems
    //       that the Irrlicht driver is still faster than the
    //       native OpenGL driver.
    irr::video::S3DVertex * const pVertexArray = new irr::video::S3DVertex[NumberOfVertex];
    IrrlichtHelper::copyImGuiVertices2IrrlichtVertices(pCommandList->VtxBuffer, pVertexArray, mOffset);

    irr::video::IVideoDriver * pIrrDriver = getIrrDevice()->getVideoDriver();

    for (int CommandIndex = 0; CommandIndex < pCommandList->CmdBuffer.size(); CommandIndex++)
    {
      ImDrawCmd * const pDrawCommand = &pCommandList->CmdBuffer[CommandIndex];

      if (pDrawCommand->UserCallback != NULL)
      {
        pDrawCommand->UserCallback(pCommandList, pDrawCommand);
      }
      else
      {

        CGUITexture * const pGUITexture = static_cast<CGUITexture * const>(pDrawCommand->TextureId);

        FASSERT(pGUITexture);
        FASSERT(pGUITexture->mIsValid);

        irr::video::ITexture * const pIrrlichtTexture = static_cast<irr::video::ITexture * const>(pGUITexture->mGPUTextureID);

        irr::video::SMaterial Material;
        IrrlichtHelper::setupStandardGUIMaterial(Material, pIrrlichtTexture);
        pIrrDriver->setMaterial(Material);
        pIrrDriver->getMaterial2D() = Material;

        IrrlichtHelper::applyClippingRect(pIrrDriver, pDrawCommand->ClipRect);

        pIrrDriver->draw2DVertexPrimitiveList(
            pVertexArray,
            NumberOfVertex,
            &pIndices[LastUsedIndex],
            pDrawCommand->ElemCount / 3,
            irr::video::EVT_STANDARD,
            irr::scene::EPT_TRIANGLES,
            irr::video::EIT_16BIT
            );


        IrrlichtHelper::disableClippingRect(pIrrDriver);

        LastUsedIndex += pDrawCommand->ElemCount;

      }

    }

    delete[] pVertexArray;
    return;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(EColorFormat const ColorFormat, irr::u8 * const pPixelData, irr::u32 const Width, irr::u32 const Height)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_RAWDATA;
    pGUITexture->mSource.RawDataID = pPixelData;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromRawData(getIrrDevice()->getVideoDriver(), ColorFormat, pPixelData, Width, Height);

    return pGUITexture;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::IImage * const pImage)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_IMAGE;
    pGUITexture->mSource.ImageID   = pImage;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromImage(getIrrDevice()->getVideoDriver(), pImage);

    return pGUITexture;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::ITexture * pTexture)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = false;
    pGUITexture->mSourceType       = ETST_TEXTURE;
    pGUITexture->mSource.TextureID = pTexture;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = static_cast<ImTextureID>(static_cast<void * const>(pTexture));

    return pGUITexture;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createFontTexture(void)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_GUIFONT;
    pGUITexture->mSource.GUIFontID = IrrlichtHelper::IMGUI_FONT_ID;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromGUIFont(getIrrDevice()->getVideoDriver());

    void * const pFontTexture = reinterpret_cast<void *>(pGUITexture);
    ImGui::GetIO().Fonts->TexID = pFontTexture;

    return pGUITexture;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * const pGUITexture, EColorFormat const ColorFormat, irr::u8 * const pPixelData, irr::u32 const Width, irr::u32 const Height)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if (pRealTexture->mIsUsingOwnMemory)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSourceType != ETST_RAWDATA)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSource.RawDataID != pPixelData)
    {
      IsRecreationNecessary = true;
    }

    if (IsRecreationNecessary)
    {
      IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

      pRealTexture->mIsUsingOwnMemory = true;
      pRealTexture->mSourceType       = ETST_RAWDATA;
      pRealTexture->mSource.RawDataID = pPixelData;
      pRealTexture->mIsValid          = true;
      pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromRawData(getIrrDevice()->getVideoDriver(), ColorFormat, pPixelData, Width, Height);
    }

    return;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * const pGUITexture, irr::video::IImage * const pImage)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if (pRealTexture->mIsUsingOwnMemory)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSourceType != ETST_IMAGE)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSource.ImageID != pImage)
    {
      IsRecreationNecessary = true;
    }

    if (IsRecreationNecessary)
    {
      IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

      pRealTexture->mIsUsingOwnMemory = true;
      pRealTexture->mSourceType       = ETST_IMAGE;
      pRealTexture->mSource.ImageID   = pImage;
      pRealTexture->mIsValid          = true;
      pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromImage(getIrrDevice()->getVideoDriver(), pImage);
    }

    return;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * const pGUITexture, irr::video::ITexture * const pTexture)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if (pRealTexture->mIsUsingOwnMemory)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSourceType != ETST_TEXTURE)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSource.TextureID != pTexture)
    {
      IsRecreationNecessary = true;
    }

    if (IsRecreationNecessary)
    {
      IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

      pRealTexture->mIsUsingOwnMemory = false;
      pRealTexture->mSourceType       = ETST_TEXTURE;
      pRealTexture->mSource.TextureID = pTexture;
      pRealTexture->mIsValid          = true;
      pRealTexture->mGPUTextureID     = static_cast<ImTextureID>(static_cast<void * const>(pTexture));
    }

    return;
  }

  void CIrrlichtIMGUIDriver::updateFontTexture(IGUITexture * const pGUITexture)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);
    bool IsRecreationNecessary = false;

    FASSERT(pRealTexture->mIsValid);

    if (pRealTexture->mIsUsingOwnMemory)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSourceType != ETST_GUIFONT)
    {
      IsRecreationNecessary = true;
    }
    else if (pRealTexture->mSource.GUIFontID != IrrlichtHelper::IMGUI_FONT_ID)
    {
      IsRecreationNecessary = true;
    }

    if (IsRecreationNecessary)
    {
      IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);

      pRealTexture->mIsUsingOwnMemory = true;
      pRealTexture->mSourceType       = ETST_GUIFONT;
      pRealTexture->mSource.GUIFontID = IrrlichtHelper::IMGUI_FONT_ID;
      pRealTexture->mIsValid          = true;
      pRealTexture->mGPUTextureID     = IrrlichtHelper::copyTextureIDFromGUIFont(getIrrDevice()->getVideoDriver());

      void * const pFontTexture = reinterpret_cast<void *>(pGUITexture);
      ImGui::GetIO().Fonts->TexID = pFontTexture;
    }

    return;
  }

  void CIrrlichtIMGUIDriver::deleteTexture(IGUITexture * const pGUITexture)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);

    FASSERT(pRealTexture->mIsValid);

    IrrlichtHelper::deleteTextureID(getIrrDevice()->getVideoDriver(), pRealTexture);
    delete pRealTexture;

    mTextureInstances--;
    return;
  }


namespace IrrlichtHelper
{


  irr::video::SColor getColorFromImGuiColor(irr::u32 const ImGuiColor)
  {
    ImColor const Color(ImGuiColor);

    irr::u8 const Red   = static_cast<irr::u8>(Color.Value.x * 255);
    irr::u8 const Green = static_cast<irr::u8>(Color.Value.y * 255);
    irr::u8 const Blue  = static_cast<irr::u8>(Color.Value.z * 255);
    irr::u8 const Alpha = static_cast<irr::u8>(Color.Value.w * 255);

    return irr::video::SColor(Alpha, Red, Green, Blue);
  }

  void copyImGuiVertices2IrrlichtVertices(ImVector<ImDrawVert> &rIMGUIVertexBuffer, irr::video::S3DVertex * const pIrrlichtVertex, irr::core::vector3df const &rOffset)
  {
    irr::u32 const NumberOfVertex = rIMGUIVertexBuffer.size();

    for (irr::u32 i = 0; i < NumberOfVertex; i++)
    {
      ImDrawVert &rImGUIVertex = rIMGUIVertexBuffer[i];

      pIrrlichtVertex[i].Pos     = irr::core::vector3df(static_cast<irr::f32>(rImGUIVertex.pos.x), static_cast<irr::f32>(rImGUIVertex.pos.y), 0.0) + rOffset;
      pIrrlichtVertex[i].Normal  = irr::core::vector3df(0.0, 0.0, 1.0);
      pIrrlichtVertex[i].Color   = getColorFromImGuiColor(rImGUIVertex.col);
      pIrrlichtVertex[i].TCoords = irr::core::vector2df(static_cast<irr::f32>(rImGUIVertex.uv.x), static_cast<irr::f32>(rImGUIVertex.uv.y));
    }
  }

  ImTextureID copyTextureIDFromRawData(irr::video::IVideoDriver * const pIrrDriver, EColorFormat const ColorFormat, irr::u8 * const pPixelData, irr::u32 const Width, irr::u32 const Height)
  {

    irr::u32 * pImageData = nullptr;
    bool IsTempMemoryUsed = false;

    // decide if we need to translate the color or not
    switch (ColorFormat)
    {
      case ECF_A8R8G8B8:
        pImageData       = reinterpret_cast<irr::u32 *>(pPixelData);
        IsTempMemoryUsed = false;
        break;

      case ECF_R8G8B8A8:
        pImageData       = reinterpret_cast<irr::u32 *>(pPixelData);
        IsTempMemoryUsed = false;

        for (irr::u32 X = 0; X < (Width * Height); X++)
        {
          irr::video::SColor Color = getColorFromImGuiColor(pImageData[X]);
          Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
        }

        break;

      case ECF_A8:
        pImageData       = new irr::u32[Width * Height];
        IsTempMemoryUsed = true;

        for (irr::u32 X = 0; X < (Width * Height); X++)
        {
          // set only Alpha
          irr::video::SColor Color(pPixelData[X], 255, 255, 255);
          Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
        }

        break;

      default:
        LOG_ERROR("Unknown ColorFormat "<<ColorFormat<<"!\n");
        FASSERT(false);
        break;
    }

    // do not generate mipmaps for font textures
    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    // create image object from raw data
    irr::core::dimension2d<irr::u32> const Size(Width, Height);
    irr::video::IImage * const pImage = pIrrDriver->createImageFromData(irr::video::ECF_A8R8G8B8, Size, pImageData);

    // create unique texture name for Irrlicht
    irr::io::path const TextureName = "IrrIMGUIRaw" + TextureCreationID;
    TextureCreationID++;

    // create texture object
    irr::video::ITexture * const pTexture = pIrrDriver->addTexture(TextureName, pImage);
    ImTextureID const TextureID = static_cast<ImTextureID>(static_cast<void * const>(pTexture));

    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    // delete image object
    pImage->drop();

    if (IsTempMemoryUsed)
    {
      delete[] pImageData;
    }

    LOG_NOTE("{IrrIMGUI-Irr} Create ITexture object from Raw Data. Handle: " << std::hex << TextureID << "\n");

    return TextureID;
  }

  ImTextureID copyTextureIDFromGUIFont(irr::video::IVideoDriver * const pIrrDriver)
  {
    // Get Font Texture from IMGUI system.
    irr::u8 * pPixelData;
    int Width, Height;
    ImGui::GetIO().Fonts->GetTexDataAsAlpha8(&pPixelData, &Width, &Height);

    ImTextureID const FontTexture = copyTextureIDFromRawData(pIrrDriver, ECF_A8, pPixelData, Width, Height);

    // delete temporary texture memory in IMGUI
    ImGui::GetIO().Fonts->ClearTexData();

    return FontTexture;
  }

  ImTextureID copyTextureIDFromImage(irr::video::IVideoDriver * const pIrrDriver, irr::video::IImage * const pImage)
  {
    // do not generate mipmaps for font textures
    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    // create unique texture name for Irrlicht
    irr::io::path const TextureName = "IrrIMGUIImage" + TextureCreationID;
    TextureCreationID++;

    // create texture object
    irr::video::ITexture * const pTexture = pIrrDriver->addTexture(TextureName, pImage);
    ImTextureID const TextureID = static_cast<ImTextureID>(static_cast<void * const>(pTexture));

    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    return TextureID;
  }

  void deleteTextureID(irr::video::IVideoDriver * const pIrrDriver, CGUITexture * const pGUITexture)
  {
    if (pGUITexture->mIsUsingOwnMemory)
    {
      LOG_NOTE("{IrrIMGUI-Irr} Delete ITexture memory. Handle: " << std::hex << pGUITexture->mGPUTextureID << "\n");
      irr::video::ITexture * const pIrrlichtTexture = reinterpret_cast<irr::video::ITexture * const>(pGUITexture->mGPUTextureID);

      pIrrDriver->removeTexture(pIrrlichtTexture);

      pGUITexture->mIsUsingOwnMemory = false;
      pGUITexture->mGPUTextureID = nullptr;
    }

    pGUITexture->mIsValid = false;
    pGUITexture->mSourceType = ETST_UNKNOWN;

    return;
  }

  void applyMovingClippingPlaneWorkaround(irr::video::IVideoDriver * const pIrrDriver)
  {
    // TODO: Workaround for the wrong clipping plane issue in Irrlicht.
    //       See: http://irrlicht.sourceforge.net/forum/viewtopic.php?f=7&t=50992
    //
    //       Clipping planes are applied with matrix settings of the last rendered object.
    //       This could be a rotating 3D object, so the clipping plane will rotative with
    //       this object.
    //       To prevent this error, we can draw a very simple and invisible 2D object to the
    //       screen before applying the first clipping plane. Thus the matrix settings are
    //       prepared for 2D and the clipping plane error disappears.

    irr::u32 const NumberOfVertex = 3;
    irr::video::S3DVertex * const pDummyVertices = new irr::video::S3DVertex[NumberOfVertex];
    pDummyVertices[0].Pos    = irr::core::vector3df(-20.0f,-20.0f, 0.0f);
    pDummyVertices[0].Normal = irr::core::vector3df( 0.0f,  0.0f, 1.0f);
    pDummyVertices[0].Color  = irr::video::SColor(0, 255, 0, 0);
    pDummyVertices[1].Pos    = irr::core::vector3df(-10.0f,-20.0f, 0.0f);
    pDummyVertices[1].Normal = irr::core::vector3df( 0.0f,  0.0f, 1.0f);
    pDummyVertices[1].Color  = irr::video::SColor(0, 255, 0, 0);
    pDummyVertices[2].Pos    = irr::core::vector3df(-20.0f,-10.0f, 0.0f);
    pDummyVertices[2].Normal = irr::core::vector3df( 0.0f,  0.0f, 1.0f);
    pDummyVertices[2].Color  = irr::video::SColor(0, 255, 0, 0);

    irr::u16 const pDummyIndices[3] = {0, 1, 2};

    bool const BackfaceCulling                     = pIrrDriver->getMaterial2D().BackfaceCulling;
    bool const FrontfaceCulling                    = pIrrDriver->getMaterial2D().FrontfaceCulling;
    irr::video::E_MATERIAL_TYPE const MaterialType = pIrrDriver->getMaterial2D().MaterialType;
    irr::f32 const MaterialParam                   = pIrrDriver->getMaterial2D().MaterialTypeParam;

    pIrrDriver->getMaterial2D().BackfaceCulling   = false;
    pIrrDriver->getMaterial2D().FrontfaceCulling  = false;
    pIrrDriver->getMaterial2D().MaterialType      = irr::video::EMT_ONETEXTURE_BLEND;
    pIrrDriver->getMaterial2D().MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_VERTEX_COLOR);
    pIrrDriver->setMaterial(pIrrDriver->getMaterial2D());

    pIrrDriver->draw2DVertexPrimitiveList(
        pDummyVertices,
        NumberOfVertex,
        pDummyIndices,
        1,
        irr::video::EVT_STANDARD,
        irr::scene::EPT_TRIANGLES,
        irr::video::EIT_16BIT
        );

    pIrrDriver->getMaterial2D().BackfaceCulling   = BackfaceCulling;
    pIrrDriver->getMaterial2D().FrontfaceCulling  = FrontfaceCulling;
    pIrrDriver->getMaterial2D().MaterialType      = MaterialType;
    pIrrDriver->getMaterial2D().MaterialTypeParam = MaterialParam;

    delete[] pDummyVertices;

    return;
  }

  void setupStandardGUIMaterial(irr::video::SMaterial &rMaterial, irr::video::ITexture * const pTexture)
  {
    rMaterial.setTexture(0, pTexture);
    rMaterial.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    rMaterial.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X, irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE);
    rMaterial.setFlag(irr::video::EMF_ANTI_ALIASING,      true);
    rMaterial.setFlag(irr::video::EMF_BILINEAR_FILTER,    false);
    rMaterial.setFlag(irr::video::EMF_ZBUFFER,            false);
    rMaterial.setFlag(irr::video::EMF_BLEND_OPERATION,    false);
    rMaterial.setFlag(irr::video::EMF_BACK_FACE_CULLING,  false);
    rMaterial.setFlag(irr::video::EMF_FRONT_FACE_CULLING, false);
    rMaterial.setFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
    rMaterial.setFlag(irr::video::EMF_TRILINEAR_FILTER,   IsTrilinearFilterEnabled);
    rMaterial.UseMipMaps = false;

    return;
  }

  void applyClippingRect(irr::video::IVideoDriver * const pIrrDriver, ImVec4 &rClippingRect)
  {
    irr::core::plane3df LeftPlane   (irr::core::vector3df(rClippingRect.x, 0.0f, 0.0f), irr::core::vector3df( 1.0f,  0.0f, 0.0f));
    irr::core::plane3df RightPlane  (irr::core::vector3df(rClippingRect.z, 0.0f, 0.0f), irr::core::vector3df(-1.0f,  0.0f, 0.0f));
    irr::core::plane3df TopPlane    (irr::core::vector3df(0.0f, rClippingRect.y, 0.0f), irr::core::vector3df( 0.0f,  1.0f, 0.0f));
    irr::core::plane3df BottomPlane (irr::core::vector3df(0.0f, rClippingRect.w, 0.0f), irr::core::vector3df( 0.0f, -1.0f, 0.0f));
    pIrrDriver->setClipPlane(0, LeftPlane,   true);
    pIrrDriver->setClipPlane(1, RightPlane,  true);
    pIrrDriver->setClipPlane(2, TopPlane,    true);
    pIrrDriver->setClipPlane(3, BottomPlane, true);

    return;
  }

  void disableClippingRect(irr::video::IVideoDriver * const pIrrDriver)
  {
    pIrrDriver->enableClipPlane(0, false);
    pIrrDriver->enableClipPlane(1, false);
    pIrrDriver->enableClipPlane(2, false);
    pIrrDriver->enableClipPlane(3, false);

    return;
  }
}
}
}
}

/**
 * @}
 */

