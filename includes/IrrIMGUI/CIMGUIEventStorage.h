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
 * @file       CIMGUIEventStorage.h
 * @author     Andre Netzeband
 * @brief      A storage memory to transfer Input-Events from Irrlicht to the IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_

// module includes
#include "CCharFifo.h"
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief Stores the state of the Keyboard and Mouse input for IMGUI.
  class IRRIMGUI_DLL_API CIMGUIEventStorage
  {
    public:
      /// @brief Standard Constructor to reset all values to 0 and false.
      CIMGUIEventStorage(void):
        mIsLeftMouseButtonPressed(false),
        mIsRightMouseButtonPressed(false),
        mIsMiddleMouseButtonPressed(false),
        mMousePositionX(0),
        mMousePositionY(0),
        mMouseWheelPosition(0.0f),
        mTabPressed(false),
        mLeftPressed(false),
        mRightPressed(false),
        mUpPressed(false),
        mDownPressed(false),
        mPriorPressed(false),
        mNextPressed(false),
        mHomePressed(false),
        mEndPressed(false),
        mDeletePressed(false),
        mBackPressed(false),
        mReturnPressed(false),
        mEscapePressed(false),
        mKeyAPressed(false),
        mKeyCPressed(false),
        mKeyVPressed(false),
        mKeyXPressed(false),
        mKeyYPressed(false),
        mKeyZPressed(false),
        mCtrlPressed(false),
        mShiftPressed(false),
        mAltPressed(false)
      {}

      ///@{
      ///@name Mouse states

      bool mIsLeftMouseButtonPressed;
      bool mIsRightMouseButtonPressed;
      bool mIsMiddleMouseButtonPressed;
      irr::s32 mMousePositionX;
      irr::s32 mMousePositionY;
      irr::f32 mMouseWheelPosition;

      /// @}

      ///@{
      ///@name Special Key states

      bool mTabPressed;
      bool mLeftPressed;
      bool mRightPressed;
      bool mUpPressed;
      bool mDownPressed;
      bool mPriorPressed;
      bool mNextPressed;
      bool mHomePressed;
      bool mEndPressed;
      bool mDeletePressed;
      bool mBackPressed;
      bool mReturnPressed;
      bool mEscapePressed;
      bool mKeyAPressed;
      bool mKeyCPressed;
      bool mKeyVPressed;
      bool mKeyXPressed;
      bool mKeyYPressed;
      bool mKeyZPressed;
      bool mCtrlPressed;
      bool mShiftPressed;
      bool mAltPressed;

      /// @}

      /// @{
      /// @name Memory for all character keys

      CCharFifo mCharFifo;

      /// @}

  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTSTORAGE_H_ */
