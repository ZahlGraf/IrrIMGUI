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
 * @file   IrrIMGUIConstants.h
 * @author Andre Netzeband
 * @brief  Contains constants values for IrrIMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_

// library includes
#include "IncludeIMGUI.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{

/// @brief Contains constant values for IrrIMGUI:
namespace Const
{
  enum EConstants {
    /// @brief The number of mouse buttons supported by IMGUI.
    NumberOfMouseButtons = 5,
  };

#ifdef IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER
  static_assert(NumberOfMouseButtons == sizeof(ImGuiIO::MouseDown)/sizeof(bool), "The number of mouse buttons are different in IMGUI and IrrIMGUI!");
#endif // IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER

}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IRRIMGUICONSTANTS_H_ */
