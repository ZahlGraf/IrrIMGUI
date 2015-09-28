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

// module includes
#include "CIrrlichtIMGUIDriver.h"
#include "CGUITexture.h"
#include "IrrIMGUIDebug_priv.h"

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
  CIrrlichtIMGUIDriver::CIrrlichtIMGUIDriver(irr::IrrlichtDevice * const pDevice):
    IIMGUIDriver(pDevice)
  {
    setupFunctionPointer();
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
    return;
  }

  void CIrrlichtIMGUIDriver::drawCommandList(ImDrawList * pCommandList)
  {
    return;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height)
  {
    return nullptr;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::IImage * pImage)
  {
    return nullptr;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createTexture(irr::video::ITexture * pTexture)
  {
    return nullptr;
  }

  IGUITexture *CIrrlichtIMGUIDriver::createFontTexture(void)
  {
    mTextureInstances++;
    CGUITexture * const pGUITexture = new CGUITexture();

    pGUITexture->mIsUsingOwnMemory = true;
    pGUITexture->mSourceType       = ETST_GUIFONT;
    pGUITexture->mSource.GUIFontID = 0;
    pGUITexture->mIsValid          = true;
    pGUITexture->mGPUTextureID     = copyTextureIDFromGUIFont();

    void * const pFontTexture = reinterpret_cast<void *>(pGUITexture);
    ImGui::GetIO().Fonts->TexID = pFontTexture;

    return pGUITexture;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * pGUITexture, EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height)
  {
    return;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * pGUITexture, irr::video::IImage * pImage)
  {
    return;
  }

  void CIrrlichtIMGUIDriver::updateTexture(IGUITexture * pGUITexture, irr::video::ITexture * pTexture)
  {
    return;
  }

  void CIrrlichtIMGUIDriver::updateFontTexture(IGUITexture * pGUITexture)
  {
    return;
  }

  void CIrrlichtIMGUIDriver::deleteTexture(IGUITexture * pGUITexture)
  {
    CGUITexture * const pRealTexture = dynamic_cast<CGUITexture * const>(pGUITexture);

    FASSERT(pRealTexture->mIsValid);

    deleteTextureID(pRealTexture);
    delete pRealTexture;

    mTextureInstances--;
    return;
  }

  ImTextureID CIrrlichtIMGUIDriver::copyTextureIDFromGUIFont(void)
  {
    irr::video::IVideoDriver * pIrrDriver = getIrrDevice()->getVideoDriver();

    // Get Font Texture from IMGUI system.
    irr::u8 * pPixelData;
    int Width, Height;
    ImGui::GetIO().Fonts->GetTexDataAsAlpha8(&pPixelData, &Width, &Height);

    irr::u32 * pImageData = new irr::u32[Width * Height];

    for (int X = 0; X < (Width * Height); X++)
    {
      // set only Alpha
      irr::video::SColor Color(pPixelData[X], 255, 255, 255);
      Color.getData(&pImageData[X], irr::video::ECF_A8R8G8B8);
    }

    // do not generate mipmaps for font textures
    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    // create image object from raw data
    irr::core::dimension2d<irr::u32> const Size(Width, Height);
    irr::video::IImage * const pImage = pIrrDriver->createImageFromData(irr::video::ECF_A8R8G8B8, Size, pImageData);

    // create texture object
    irr::video::ITexture * const pTexture = pIrrDriver->addTexture("DefaultIMGUITexture", pImage);
    ImTextureID const FontTexture = static_cast<ImTextureID>(static_cast<void * const>(pTexture));

    pIrrDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    // delete image object
    pImage->drop();
    delete[] pImageData;

    // delete temporary texture memory in IMGUI
    ImGui::GetIO().Fonts->ClearTexData();

    LOG_NOTE("{IrrIMGUI-Irr} Create ITexture object for font. Handle: " << std::hex << FontTexture << "\n");

    return FontTexture;
  }

  void CIrrlichtIMGUIDriver::deleteTextureID(CGUITexture * const pGUITexture)
  {

    if (pGUITexture->mIsUsingOwnMemory)
    {
      LOG_NOTE("{IrrIMGUI-Irr} Delete ITexture memory. Handle: " << std::hex << pGUITexture->mGPUTextureID << "\n");
      irr::video::ITexture * const pIrrlichtTexture = reinterpret_cast<irr::video::ITexture * const>(pGUITexture->mGPUTextureID);

      irr::video::IVideoDriver * const pIrrDriver = getIrrDevice()->getVideoDriver();
      //pIrrDriver->removeTexture(pIrrlichtTexture);

      pGUITexture->mIsUsingOwnMemory = false;
      pGUITexture->mGPUTextureID = nullptr;
    }

    pGUITexture->mIsValid = false;
    pGUITexture->mSourceType = ETST_UNKNOWN;

    return;
  }

}
}
}

/**
 * @}
 */

