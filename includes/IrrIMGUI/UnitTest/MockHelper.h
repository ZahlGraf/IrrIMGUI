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
 * @file   MockHelper.h
 * @author Andre Netzeband
 * @brief  Contains definitions used inside IIMGUIHandleMock, but they must stay independent from the mock, to prevent a too close coupling to the unit test framework from the DLL.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>

/**
 * @addtogroup IrrIMGUIUTest
 * @{
 */

namespace IrrIMGUI
{
namespace UnitTest
{
  class IIMGUIHandleMock;

  /// @brief Creates a dummy font in IMGUI to prevent errors for unit-tests that uses the mock.
  IRRIMGUI_DLL_API void createIMGUIDummyFont(void);

  /// @return Returns a dummy texture object for unit-test cases.
  IRRIMGUI_DLL_API IGUITexture * getDummyTexture(void);

  /// @brief This helper class contains definitions, that can not be in IMGUIHandleMock, to prevent tight coupling between DLL and Unit Test Framework.
  class MockHelper
  {
    private:
      friend IIMGUIHandleMock;

      /// @brief If this variable is true, the mock will perform minimal IMGUI calls to not generate an error with IMGUI.
      IRRIMGUI_DLL_API static bool         mIsImGuiActivated;
  };
}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_UNITTEST_MOCKHELPER_H_ */
