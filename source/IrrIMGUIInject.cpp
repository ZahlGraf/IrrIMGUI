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
 * @file   IrrIMGUIInject.cpp
 * @author Andre Netzeband
 * @brief  Contains function implementation for Dependency Injection.
 * @addtogroup IrrIMGUIInject
 */

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include "private/IrrIMGUIDebug_priv.h"
#include "CIMGUIHandle.h"
#include "private/IrrIMGUIInject_priv.h"

namespace IrrIMGUI
{
namespace Private
{
  IIMGUIHandle * createRealIMGUI(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const * pSettings)
  {
    ASSERT(pDevice);

    return new Private::CIMGUIHandle(pDevice, pEventStorage, pSettings);
  }
}

namespace Inject
{

  /// @brief Stores the factory function, that should be used for creating an IIMGUIHandle instances.
  static IMGUIFactory * pIMGUIFactoryFunction = IrrIMGUI::Private::createRealIMGUI;


  void setIMGUIFactory(IMGUIFactory * pFactoryFunction)
  {
    if (pFactoryFunction == nullptr)
    {
      pFactoryFunction = IrrIMGUI::Private::createRealIMGUI;
    }

    pIMGUIFactoryFunction = pFactoryFunction;
    return;
  }


  IMGUIFactory * getIMGUIFactory(void)
  {
    return pIMGUIFactoryFunction;
  }

}

  IIMGUIHandle * createIMGUI(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const * pSettings)
  {
    FASSERT(Inject::pIMGUIFactoryFunction);
    FASSERT(pDevice);

    return Inject::pIMGUIFactoryFunction(pDevice, pEventStorage, pSettings);
  }

}



