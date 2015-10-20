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
 * @file   IrrIMGUIInject_priv.h
 * @author Andre Netzeband
 * @brief  Private definitions for dependency injection.
 * @addtogroup IrrIMGUIPriv
 */

#ifndef LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_
#define LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_

// module includes
#include <IrrIMGUI/IrrIMGUI.h>

/**
 * @addtogroup IrrIMGUIPriv
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains definitions for Dependency Injection.
namespace Private
{

  /// @brief Creates a real IMGUI object (the real factory function for it)
  /// @param pDevice       Is a pointer to an Irrlicht device.
  /// @param pEventStorage Is a pointer to an input event storage.
  /// @param pSettings     Is a pointer to a settings struct to apply.
  /// @return Returns a pointer to an IMGUI handle object.
  IRRIMGUI_DLL_API IIMGUIHandle * createRealIMGUI(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const * pSettings);

}
}

/**
 * @}
 */


#endif /* LIBS_IRRIMGUI_SOURCE_PRIVATE_IRRIMGUIINJECT_PRIV_H_ */
