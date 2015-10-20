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
 * @file   CIMGUIEventReceiver.h
 * @author Andre Netzeband
 * @brief  Contains a standard Event Receiver for Irrlicht that passed inputs to IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_

// library includes
#include "CIMGUIEventStorage.h"
#include "IncludeIrrlicht.h"

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  class CIMGUIEventReceiver : public irr::IEventReceiver, public CIMGUIEventStorage
  {
    public:
      /// @brief This function is called by Irrlicht, when an Event occurs.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool OnEvent(irr::SEvent const &rEvent)
      {
        bool EventCompletelyHandled = false;

        EventCompletelyHandled = EventCompletelyHandled || checkKeyboardEvents(rEvent);
        EventCompletelyHandled = EventCompletelyHandled || checkMouseEvents(rEvent);

        return EventCompletelyHandled;
      }

    private:
      /// @brief Checks the events that are mouse related.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool IRRIMGUI_DLL_API checkMouseEvents(irr::SEvent const &rEvent);

      /// @brief Checks the events that are keyboard related.
      /// @param rEvent is a reference to that event.
      /// @return Returns true, if the event has completely been handled by that Receiver.
      bool IRRIMGUI_DLL_API checkKeyboardEvents(irr::SEvent const &rEvent);

  };
}

/**
 * @}
 */


#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIEVENTRECEIVER_H_ */
