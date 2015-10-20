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
 * @file   IrrIMGUI.h
 * @author Andre Netzeband
 * @brief  The main include file for the IMGUI bindinds.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_IRRIMGUI_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_IRRIMGUI_H_

// module includes
#include "IrrIMGUIConfig.h"
#include "IIMGUIHandle.h"
#include "CIMGUIEventReceiver.h"

/**
 * @defgroup IrrIMGUI IrrIMGUI
 * @brief An Irrlicht IMGUI binding.
 * @details
 * There are two main classes to use as an interface between Irrlicht and IMGUI:
 * @li IrrIMGUI::IIMGUIHandle        to setup, draw and render the GUI. Create an object of this class with IrrIMGUI::createIMGUI
 * @li IrrIMGUI::CIMGUIEventReceiver to capture the irrlicht events and pass them to the IMGUI system.
 *
 * If you need an own event receiver, you can simply inherit from IrrIMGUI::CIMGUIEventReceiver. In the OnEevent method you can trigger your own actions according to the events.
 * When no actions fits to the event you received, simply pass it to the OnEvent method from IrrIMGUI::CIMGUIEventReceiver class.
 *
 * @code

  bool OnEvent(const irr::SEvent & rEvent)
  {

    // do your own stuff with rEvent

    // when rEvent has not been consumed by your game logic pass it to the CIMGUIEventReceiver class
    return CIMGUIEventReceiver::OnEvent(rEvent);
  }

 @endcode
 *
 * If you need to be more flexible by programming the event receiver, you can create a completely own event receiver, that is inherited from IrrIMGUI::CIMGUIEventStorage
 * Here you need to set the attributes of IrrIMGUI::CIMGUIEventStorage manually to pass input informations to the IMGUI system.
 *
 * @{
 */

/// @brief Main namespace for Irrlicht IMGUI binding
namespace IrrIMGUI
{

  /// @brief Creates an IMGUI handle object.
  /// @param pDevice       Is a pointer to an Irrlicht device.
  /// @param pEventStorage Is a pointer to an event storage.
  /// @param pSettings     Is a pointer to a settings structure.
  /// @return Returns an IIMGUIHandle object. Destroy this object with IIMGUIHandle::drop()
  IRRIMGUI_DLL_API IIMGUIHandle * createIMGUI(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage = nullptr, SIMGUISettings const * pSettings = nullptr);
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_IRRIMGUI_H_ */
