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
 * @file   IIMGUIDriver.cpp
 * @author Andre Netzeband
 * @brief  Contains a driver interface for IMGUI.
 * @addtogroup IrrIMGUIPrivate
 */

// library includes
#include <iostream>

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "IIMGUIDriver.h"
#include "COpenGLIMGUIDriver.h"
#include "CIrrlichtIMGUIDriver.h"
#include "private/IrrIMGUIDebug_priv.h"
#include <IrrIMGUI/IrrIMGUIConstants.h>

/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */

namespace IrrIMGUI
{
namespace Private
{

  IIMGUIDriver *        IIMGUIDriver::mpInstance = nullptr;
  irr::u32              IIMGUIDriver::mInstances = 0;
  irr::IrrlichtDevice * IIMGUIDriver::mpDevice   = nullptr;
  SIMGUISettings        IIMGUIDriver::mSettings;
  IGUITexture         * IIMGUIDriver::mpFontTexture = nullptr;
  irr::u32              IIMGUIDriver::mTextureInstances = 0;

  IIMGUIDriver::IIMGUIDriver(irr::IrrlichtDevice * const pDevice)
  {
    LOG_NOTE("{IrrIMGUI} Create Singleton Instance of IIMGUIDriver.\n");
    mInstances++;
    mTextureInstances = 0;

    FASSERT(mInstances == 1);

    pDevice->grab();
    mpDevice = pDevice;

    setupMouseControl();
    setupKeyControl();
    updateSettings();

    return;
  }

  IIMGUIDriver::~IIMGUIDriver(void)
  {
    if (mTextureInstances != 0)
    {
      LOG_ERROR("Not all images created with CIMGUIHandle::createTextureFromImage(...) have been deleted with CIMGUIHandle::deleteTexture(...). There are " << mTextureInstances << " images left!\n");
    }

    if (mpFontTexture != nullptr)
    {
      LOG_ERROR("The Font Texture has not been deleted!\n");
    }

    ImGui::GetIO().Fonts->Clear();
    ImGui::Shutdown();

    mpDevice->drop();
    return;
  }

  IIMGUIDriver * IIMGUIDriver::getInstance(irr::IrrlichtDevice * const pDevice)
  {

    if (mpInstance == nullptr)
    {
#ifdef _IRRIMGUI_NATIVE_OPENGL_
      irr::video::IVideoDriver * pDriver = pDevice->getVideoDriver();
      irr::video::E_DRIVER_TYPE Type = pDriver->getDriverType();

      switch(Type)
      {
        case irr::video::EDT_NULL: // for unit testing
        case irr::video::EDT_OPENGL:
          mpInstance = new Driver::COpenGLIMGUIDriver(pDevice);
          mpFontTexture = mpInstance->createFontTexture();
          break;

        default:
          LOG_ERROR("Unknown driver type" << Type << "\n");
          FASSERT(false);
          break;
      }
#else

      mpInstance = new Driver::CIrrlichtIMGUIDriver(pDevice);
      mpFontTexture = mpInstance->createFontTexture();

#endif

    }

    ASSERT(mpInstance != nullptr);

    return mpInstance;
  }

  bool IIMGUIDriver::deleteInstance(void)
  {
    bool WasDeleted = false;

    if (mpInstance != nullptr)
    {
      LOG_NOTE("{IrrIMGUI} Delete Singleton Instance of IIMGUIDriver.\n");

      // delete font texture
      mpInstance->deleteTexture(mpFontTexture);
      mpFontTexture = nullptr;

      // delete instance
      delete(mpInstance);
      mpInstance = nullptr;
      mInstances = 0;
      FASSERT(ImGui::GetIO().MetricsAllocs == 0);

      WasDeleted = true;
    }

    return WasDeleted;
  }

  irr::IrrlichtDevice * IIMGUIDriver::getIrrDevice(void)
  {
    ASSERT(mpDevice != nullptr);
    return mpDevice;
  }

  SIMGUISettings const &IIMGUIDriver::getSettings(void)
  {
    return mSettings;
  }

  void IIMGUIDriver::setSettings(SIMGUISettings const &rSettings)
  {
    mSettings = rSettings;
    updateSettings();

    return;
  }

  void IIMGUIDriver::updateSettings(void)
  {
    ImGuiIO &rGUIIO = ImGui::GetIO();
    if (mSettings.mIsGUIMouseCursorEnabled)
    {
      rGUIIO.MouseDrawCursor = true;
      mpDevice->getCursorControl()->setVisible(false);
    }
    else
    {
      rGUIIO.MouseDrawCursor = false;
      mpDevice->getCursorControl()->setVisible(true);
    }

    return;
  }

  void IIMGUIDriver::setupMouseControl(void)
  {
    // setup standard values
    ImGuiIO &rGUIIO = ImGui::GetIO();

    for (int i = 0; i < Const::NumberOfMouseButtons; i++)
    {
      rGUIIO.MouseClicked[i]          = false;
      rGUIIO.MouseDoubleClicked[i]    = false;
      rGUIIO.MouseDown[i]             = false;
      rGUIIO.MouseClickedTime[i]      = -FLT_MAX;
      rGUIIO.MouseDownDurationPrev[i] = -1.0f;
      rGUIIO.MouseDownDuration[i]     = -1.0f;
    }
    rGUIIO.MouseWheel = 0.0f;

    return;
  }

  void IIMGUIDriver::setupKeyControl(void)
  {
    ImGuiIO &rGUIIO = ImGui::GetIO();

    rGUIIO.KeyMap[ImGuiKey_Tab]        = irr::KEY_TAB;
    rGUIIO.KeyMap[ImGuiKey_LeftArrow]  = irr::KEY_LEFT;
    rGUIIO.KeyMap[ImGuiKey_RightArrow] = irr::KEY_RIGHT;
    rGUIIO.KeyMap[ImGuiKey_UpArrow]    = irr::KEY_UP;
    rGUIIO.KeyMap[ImGuiKey_DownArrow]  = irr::KEY_DOWN;
    rGUIIO.KeyMap[ImGuiKey_PageUp]     = irr::KEY_PRIOR;
    rGUIIO.KeyMap[ImGuiKey_PageDown]   = irr::KEY_NEXT;
    rGUIIO.KeyMap[ImGuiKey_Home]       = irr::KEY_HOME;
    rGUIIO.KeyMap[ImGuiKey_End]        = irr::KEY_END;
    rGUIIO.KeyMap[ImGuiKey_Delete]     = irr::KEY_DELETE;
    rGUIIO.KeyMap[ImGuiKey_Backspace]  = irr::KEY_BACK;
    rGUIIO.KeyMap[ImGuiKey_Enter]      = irr::KEY_RETURN;
    rGUIIO.KeyMap[ImGuiKey_Escape]     = irr::KEY_ESCAPE;
    rGUIIO.KeyMap[ImGuiKey_A]          = irr::KEY_KEY_A;
    rGUIIO.KeyMap[ImGuiKey_C]          = irr::KEY_KEY_C;
    rGUIIO.KeyMap[ImGuiKey_V]          = irr::KEY_KEY_V;
    rGUIIO.KeyMap[ImGuiKey_X]          = irr::KEY_KEY_X;
    rGUIIO.KeyMap[ImGuiKey_Y]          = irr::KEY_KEY_Y;
    rGUIIO.KeyMap[ImGuiKey_Z]          = irr::KEY_KEY_Z;
  }

  void IIMGUIDriver::compileFonts(void)
  {
    FASSERT(mpFontTexture != nullptr);

    updateFontTexture(mpFontTexture);

    return;
  }

  /// @brief An helper class, that deletes the CIMGUIDriver instance when the program is closed and no other source has deleted it.
  class CIMGUIDriverDeleteHelper
  {
    public:
      /// @brief Destructor tries to delete the Instance of CIMGUIDriver. If an instance was deleted, it shows a warning.
      ~CIMGUIDriverDeleteHelper(void)
      {
        if (IrrIMGUI::Private::IIMGUIDriver::deleteInstance())
        {
          LOG_WARNING("Forced deletion of Singleton Instance of IIMGUIDriver!\n");
        }
      }
  };

  // @brief Ensures that a driver is deleted at the end of program.
  static CIMGUIDriverDeleteHelper IMGUIDriverDeleteHelper;

}
}


/**
 * @}
 */

