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
 * @file   IrrIMGUIInject.h
 * @author Andre Netzeband
 * @brief  Functions for dependency injection.
 * @addtogroup IrrIMGUIInject
 */

#ifndef LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_
#define LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_

// module includes
#include <IrrIMGUI/IrrIMGUI.h>

/**
 * @defgroup IrrIMGUIInject Inject
 * @ingroup IrrIMGUI
 * @brief Definitions for dependency injection.
 *
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains definitions for Dependency Injection.
namespace Inject
{

  /**
   * @addtogroup IrrIMGUIInject
   * @{
   */

  /// @brief The type of the IMGUI factory function.
  typedef IrrIMGUI::IIMGUIHandle * (IMGUIFactory)(irr::IrrlichtDevice * pDevice, IrrIMGUI::CIMGUIEventStorage * pEventStorage, IrrIMGUI::SIMGUISettings const * pSettings);

  /// @param pFactoryFunction Is a function pointer to the IMGUI factory function to use.
  ///        If it is NULL, it will use the default factory function.
  IRRIMGUI_DLL_API void setIMGUIFactory(IMGUIFactory * pFactoryFunction = nullptr);

  /// @return Returns the current factory function pointer for creating an IMGUI handle instance.
  IRRIMGUI_DLL_API IMGUIFactory * getIMGUIFactory(void);

  /**
   * @}
   */

}
}

/**
 * @}
 */

#endif /* LIBS_IRRIMGUI_INCLUDES_IRRIMGUI_INJECT_IRRIMGUIINJECT_H_ */
