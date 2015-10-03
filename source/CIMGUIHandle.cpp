/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband
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
 * @file   CIMGUIHandle.cpp
 * @author Andre Netzeband
 * @brief  Contains a handle to setup the IMGUI for Irrlicht.
 * @addtogroup IrrIMGUI
 */

// library includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "IIMGUIDriver.h"
#include "IrrIMGUIDebug_priv.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  using namespace Private;

  irr::u32 CIMGUIHandle::mHandleInstances = 0;

  CIMGUIHandle::CIMGUIHandle(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const &rSettings):
    CIMGUIHandle(pDevice, pEventStorage)
  {
    mpGUIDriver->setSettings(rSettings);
    return;
  }

  CIMGUIHandle::CIMGUIHandle(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage)
  {
    pDevice->grab();

    mpGUIDriver = IIMGUIDriver::getInstance(pDevice);
    mLastTime    = static_cast<float>(pDevice->getTimer()->getRealTime()) / 1000.0f;
    mpEventStorage = pEventStorage;
    mHandleInstances++;

    return;
  }

  CIMGUIHandle::~CIMGUIHandle(void)
  {
    irr::IrrlichtDevice * const pIrrDevice = mpGUIDriver->getIrrDevice();

    if (mHandleInstances == 0)
    {
      LOG_ERROR("The number of CIMGUIHandle instances is out of sync (" << mHandleInstances << " instances)!");
    }
    else
    {
      mHandleInstances--;

      if (mHandleInstances == 0)
      {
        IIMGUIDriver::deleteInstance();
      }
    }

    pIrrDevice->drop();

    return;
  }

  void CIMGUIHandle::drawAll(void)
  {

    ImGui::Render();
    return;
  }

  void CIMGUIHandle::updateScreenSize(void)
  {
    ImGuiIO& rGUIIO = ImGui::GetIO();

    irr::core::dimension2d<irr::u32> const &rRenderTargetSize = mpGUIDriver->getIrrDevice()->getVideoDriver()->getCurrentRenderTargetSize();
    rGUIIO.DisplaySize = ImVec2(static_cast<float>(rRenderTargetSize.Width), static_cast<float>(rRenderTargetSize.Height));

    return;
  }

  void CIMGUIHandle::updateTimer(void)
  {
    ImGuiIO& rGUIIO = ImGui::GetIO();

    irr::f32 const CurrentTime = static_cast<float>(mpGUIDriver->getIrrDevice()->getTimer()->getRealTime()) / 1000.0f;
    irr::f32 const DeltaTime   = CurrentTime - mLastTime;
    mLastTime = CurrentTime;

    rGUIIO.DeltaTime = ((float)(DeltaTime > 0.0f ? DeltaTime : 0.00001f));

    return;
  }

  void CIMGUIHandle::updateMouse(void)
  {
    if (mpEventStorage)
    {
      ImGuiIO& rGUIIO = ImGui::GetIO();

      enum MouseButtons
      {
        Left   = 0,
        Right  = 1,
        Middle = 2,
      };
      rGUIIO.MousePos          = ImVec2(static_cast<float>(mpEventStorage->mMousePositionX), static_cast<float>(mpEventStorage->mMousePositionY));
      rGUIIO.MouseDown[Left]   = mpEventStorage->mIsLeftMouseButtonPressed;
      rGUIIO.MouseDown[Middle] = mpEventStorage->mIsMiddleMouseButtonPressed;
      rGUIIO.MouseDown[Right]  = mpEventStorage->mIsRightMouseButtonPressed;
      rGUIIO.MouseWheel        = mpEventStorage->mMouseWheelPosition;
      mpEventStorage->mMouseWheelPosition = 0.0f;
    }

    return;
  }

  void CIMGUIHandle::updateKeyboard(void)
  {
    if (mpEventStorage)
    {
      ImGuiIO& rGUIIO = ImGui::GetIO();

      rGUIIO.KeysDown[irr::KEY_TAB]    = mpEventStorage->mTabPressed;
      rGUIIO.KeysDown[irr::KEY_LEFT]   = mpEventStorage->mLeftPressed;
      rGUIIO.KeysDown[irr::KEY_RIGHT]  = mpEventStorage->mRightPressed;
      rGUIIO.KeysDown[irr::KEY_UP]     = mpEventStorage->mUpPressed;
      rGUIIO.KeysDown[irr::KEY_DOWN]   = mpEventStorage->mDownPressed;
      rGUIIO.KeysDown[irr::KEY_PRIOR]  = mpEventStorage->mPriorPressed;
      rGUIIO.KeysDown[irr::KEY_NEXT]   = mpEventStorage->mNextPressed;
      rGUIIO.KeysDown[irr::KEY_HOME]   = mpEventStorage->mHomePressed;
      rGUIIO.KeysDown[irr::KEY_END]    = mpEventStorage->mEndPressed;
      rGUIIO.KeysDown[irr::KEY_DELETE] = mpEventStorage->mDeletePressed;
      rGUIIO.KeysDown[irr::KEY_BACK]   = mpEventStorage->mBackPressed;
      rGUIIO.KeysDown[irr::KEY_RETURN] = mpEventStorage->mReturnPressed;
      rGUIIO.KeysDown[irr::KEY_ESCAPE] = mpEventStorage->mEscapePressed;
      rGUIIO.KeysDown[irr::KEY_KEY_A]  = mpEventStorage->mKeyAPressed;
      rGUIIO.KeysDown[irr::KEY_KEY_C]  = mpEventStorage->mKeyCPressed;
      rGUIIO.KeysDown[irr::KEY_KEY_V]  = mpEventStorage->mKeyVPressed;
      rGUIIO.KeysDown[irr::KEY_KEY_X]  = mpEventStorage->mKeyXPressed;
      rGUIIO.KeysDown[irr::KEY_KEY_Y]  = mpEventStorage->mKeyYPressed;
      rGUIIO.KeysDown[irr::KEY_KEY_Z]  = mpEventStorage->mKeyZPressed;
      rGUIIO.KeyCtrl                   = mpEventStorage->mCtrlPressed;
      rGUIIO.KeyShift                  = mpEventStorage->mShiftPressed;
      rGUIIO.KeyAlt                    = mpEventStorage->mAltPressed;

      while(!mpEventStorage->mCharFifo.isEmpty())
      {
        rGUIIO.AddInputCharacter(mpEventStorage->mCharFifo.getChar());
      }
    }

    return;
  }

  void CIMGUIHandle::startGUI(void)
  {

    updateScreenSize();
    updateTimer();
    updateMouse();
    updateKeyboard();

    // start new GUI frame
    ImGui::NewFrame();

    return;
  }

  SIMGUISettings const &CIMGUIHandle::getSettings(void) const
  {
    return mpGUIDriver->getSettings();
  }

  void CIMGUIHandle::setSettings(SIMGUISettings const &rSettings)
  {
    mpGUIDriver->setSettings(rSettings);
  }

  ImFont * CIMGUIHandle::addFont(ImFontConfig const * const pFontConfig)
  {
    return ImGui::GetIO().Fonts->AddFont(pFontConfig);
  }

  ImFont * CIMGUIHandle::addDefaultFont(ImFontConfig const * const pFontConfig)
  {
    return ImGui::GetIO().Fonts->AddFontDefault(pFontConfig);
  }

  ImFont * CIMGUIHandle::addFontFromFileTTF(char const * const pFileName, float const FontSizeInPixel, ImFontConfig const * const pFontConfig, ImWchar const * const pGlyphRanges)
  {
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(pFileName, FontSizeInPixel, pFontConfig, pGlyphRanges);
  }

  ImFont * CIMGUIHandle::addFontFromMemoryTTF(void * const pTTFData, int const TTFSize, float const FontSizeInPixel, ImFontConfig const * const pFontConfig, ImWchar const * const pGlyphRanges)
  {
    return ImGui::GetIO().Fonts->AddFontFromMemoryTTF(pTTFData, TTFSize, FontSizeInPixel, pFontConfig, pGlyphRanges);
  }

  ImFont * CIMGUIHandle::addFontFromMemoryCompressedTTF(void const * const pCompressedTTFData, int const CompressedTTFSize, float const FontSizeInPixel, ImFontConfig const * const pFontConfig, ImWchar const * const pGlyphRanges)
  {
    return ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(pCompressedTTFData, CompressedTTFSize, FontSizeInPixel, pFontConfig, pGlyphRanges);
  }

  ImFont * CIMGUIHandle::addFontFromMemoryCompressedBase85TTF(char const * const pCompressedTTFDataBase85, float const FontSizeInPixel, ImFontConfig const * const pFontConfig, const ImWchar * const pGlyphRanges)
  {
    return ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(pCompressedTTFDataBase85, FontSizeInPixel, pFontConfig, pGlyphRanges);
  }

  void CIMGUIHandle::compileFonts(void)
  {
    mpGUIDriver->compileFonts();
    return;
  }

  void CIMGUIHandle::resetFonts(void)
  {
    ImGui::GetIO().Fonts->Clear();
    addDefaultFont();
    mpGUIDriver->compileFonts();
    return;
  }

  ImWchar const * CIMGUIHandle::getGlyphRangesDefault(void)
  {
    return ImGui::GetIO().Fonts->GetGlyphRangesDefault();
  }

  ImWchar const * CIMGUIHandle::getGlyphRangesJapanese(void)
  {
    return ImGui::GetIO().Fonts->GetGlyphRangesJapanese();
  }

  ImWchar const * CIMGUIHandle::getGlyphRangesChinese(void)
  {
    return ImGui::GetIO().Fonts->GetGlyphRangesChinese();
  }

  ImWchar const * CIMGUIHandle::getGlyphRangesCyrillic(void)
  {
    return ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
  }

  IGUITexture * CIMGUIHandle::createTexture(irr::video::IImage * pImage)
  {
    return mpGUIDriver->createTexture(pImage);
  }

  IGUITexture * CIMGUIHandle::createTexture(irr::video::ITexture * pTexture)
  {
    return mpGUIDriver->createTexture(pTexture);
  }

  void CIMGUIHandle::updateTexture(IGUITexture * pGUITexture, irr::video::IImage * pImage)
  {
    mpGUIDriver->updateTexture(pGUITexture, pImage);
    return;
  }

  void CIMGUIHandle::updateTexture(IGUITexture * pGUITexture, irr::video::ITexture * pTexture)
  {
    mpGUIDriver->updateTexture(pGUITexture, pTexture);
    return;
  }

  void CIMGUIHandle::deleteTexture(IGUITexture * pGUITexture)
  {
    mpGUIDriver->deleteTexture(pGUITexture);
    return;
  }


}

/**
 * @}
 */

