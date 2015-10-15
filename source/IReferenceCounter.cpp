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
 * @file   IReferenceCounter.cpp
 * @author Andre Netzeband
 * @brief  Contains a class to count references.
 * @addtogroup IrrIMGUI
 */

// library includes
#include <IrrIMGUI/IReferenceCounter.h>
#include "private/IrrIMGUIDebug_priv.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{
  IReferenceCounter::IReferenceCounter(void):
      mReferences(1)
  {
    return;
  }

  IReferenceCounter::~IReferenceCounter(void)
  {
    if (mReferences != 1)
    {
      LOG_ERROR("An object with counted references is destroyed, but there are still references in use!\n");
      LOG_ERROR(" * object address: " << std::hex << this << "\n");
      LOG_ERROR(" * object references in use: " << std::hex << (mReferences-1) << "\n");
    }

    return;
  }

  void IReferenceCounter::grab(void)
  {
    mReferences++;
    return;
  }

  void IReferenceCounter::drop(void)
  {

    if (mReferences == 1)
    {
      delete this;
    }
    else
    {
      mReferences--;
    }

    return;
  }

  irr::u32 IReferenceCounter::getReferenceCount(void) const
  {
    return mReferences;
  }

}

/**
 * @}
 */
