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
 * @file   CIMGUIEventReceiver.cpp
 * @author Andre Netzeband
 * @brief  Contains a standard Event Receiver for Irrlicht that passed inputs to IMGUI.
 * @addtogroup IrrIMGUI
 */

// module includes
#include <IrrIMGUI/CIMGUIEventReceiver.h>

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  bool CIMGUIEventReceiver::checkMouseEvents(irr::SEvent const &rEvent)
  {
    if (rEvent.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
      switch(rEvent.MouseInput.Event)
      {
        case irr::EMIE_LMOUSE_PRESSED_DOWN:
          mIsLeftMouseButtonPressed = true;
          break;

        case irr::EMIE_LMOUSE_LEFT_UP:
          mIsLeftMouseButtonPressed = false;
          break;

        case irr::EMIE_MMOUSE_PRESSED_DOWN:
          mIsMiddleMouseButtonPressed = true;
          break;

        case irr::EMIE_MMOUSE_LEFT_UP:
          mIsMiddleMouseButtonPressed = false;
          break;

        case irr::EMIE_RMOUSE_PRESSED_DOWN:
          mIsRightMouseButtonPressed = true;
          break;

        case irr::EMIE_RMOUSE_LEFT_UP:
          mIsRightMouseButtonPressed = false;
          break;

        case irr::EMIE_MOUSE_MOVED:
          mMousePositionX = rEvent.MouseInput.X;
          mMousePositionY = rEvent.MouseInput.Y;
          break;

        case irr::EMIE_MOUSE_WHEEL:
          mMouseWheelPosition = rEvent.MouseInput.Wheel;
          break;
      }
    }

    return false;
  }

  bool CIMGUIEventReceiver::checkKeyboardEvents(irr::SEvent const &rEvent)
  {
    if (rEvent.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      bool const IsKeyPressedDown = rEvent.KeyInput.PressedDown;
      switch (rEvent.KeyInput.Key)
      {
        case irr::KEY_TAB:
          mTabPressed = IsKeyPressedDown;
          break;

        case irr::KEY_LEFT:
          mLeftPressed = IsKeyPressedDown;
          break;

        case irr::KEY_RIGHT:
          mRightPressed = IsKeyPressedDown;
          break;

        case irr::KEY_UP:
          mUpPressed = IsKeyPressedDown;
          break;

        case irr::KEY_DOWN:
          mDownPressed = IsKeyPressedDown;
          break;

        case irr::KEY_PRIOR:
          mPriorPressed = IsKeyPressedDown;
          break;

        case irr::KEY_NEXT:
          mNextPressed = IsKeyPressedDown;
          break;

        case irr::KEY_HOME:
          mHomePressed = IsKeyPressedDown;
          break;

        case irr::KEY_END:
          mEndPressed = IsKeyPressedDown;
          break;

        case irr::KEY_DELETE:
          mDeletePressed = IsKeyPressedDown;
          break;

        case irr::KEY_BACK:
          mBackPressed = IsKeyPressedDown;
          break;

        case irr::KEY_RETURN:
          mReturnPressed = IsKeyPressedDown;
          break;

        case irr::KEY_ESCAPE:
          mEscapePressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_A:
          mKeyAPressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_C:
          mKeyCPressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_V:
          mKeyVPressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_X:
          mKeyXPressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_Y:
          mKeyYPressed = IsKeyPressedDown;
          break;

        case irr::KEY_KEY_Z:
          mKeyZPressed = IsKeyPressedDown;
          break;

        case irr::KEY_LSHIFT:
        case irr::KEY_RSHIFT:
        case irr::KEY_SHIFT:
          mShiftPressed = IsKeyPressedDown;
          break;

        case irr::KEY_MENU:
          mAltPressed = IsKeyPressedDown;
          break;

        case irr::KEY_LCONTROL:
        case irr::KEY_RCONTROL:
        case irr::KEY_CONTROL:
          mCtrlPressed = IsKeyPressedDown;
          break;
      }

      if ((rEvent.KeyInput.Char > 0) && IsKeyPressedDown)
      {
        if (!mCharFifo.isFull())
        {
          mCharFifo.addChar(rEvent.KeyInput.Char);
        }
      }
    }

    return false;
  }
}

/**
 * @}
 */

