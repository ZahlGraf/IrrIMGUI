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
 * @file   IMGUIHelper.h
 * @author Andre Netzeband
 * @brief  Contains helper functions for the IMGUI handling.
 * @addtogroup IrrIMGUI
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief Updates the values for an IMGUI Frame, like delta time, input events and screen size.
  /// @param pDevice       Is a pointer to an Irrlicht device.
  /// @param pEventStorage Is a pointer to the event storage. If this pointer is NULL, no input event update is performed.
  /// @param pLastTime     Is a pointer to a variable where the time from the last update is stored (in seconds).
  IRRIMGUI_DLL_API void updateIMGUIFrameValues(irr::IrrlichtDevice * const pDevice,  CIMGUIEventStorage * const pEventStorage, irr::f32 * const pLastTime);
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_IMGUIHELPER_H_ */
