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
 * @file   CCharFifo.cpp
 * @author Andre Netzeband
 * @brief  Class definition for a Fifo Memory
 * @addtogroup IrrIMGUI
 */

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "private/IrrIMGUIDebug_priv.h"

#define STATIC_ARRAY_SIZE(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))     // TODO: maybe use a template for the type

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  CCharFifo::CCharFifo(void):
    mWriteIndex(0),
    mReadIndex(0)
  {

    ASSERT(isEmpty() == true);
    ASSERT(isFull() == false);

    return;
  }

  CCharFifo::~CCharFifo(void)
  {
    return;
  }

  void CCharFifo::addChar(ImWchar C)
  {
    if (!isFull())
    {
      ASSERT(mWriteIndex < STATIC_ARRAY_SIZE(mCharArray));

      mCharArray[mWriteIndex] = C;
      mWriteIndex++;
    }

    ASSERT(isEmpty() == false);

    return;
  }

  ImWchar CCharFifo::getChar(void)
  {
    ImWchar ReturnChar = 0;

    if(!isEmpty())
    {
      ASSERT(mReadIndex < STATIC_ARRAY_SIZE(mCharArray));

      ReturnChar = mCharArray[mReadIndex];
      mReadIndex++;
    }
    else
    {
      FASSERT(false);
    }

    ASSERT(isFull() == false);

    return ReturnChar;
  }

  bool CCharFifo::isEmpty(void) const
  {
    return mWriteIndex == mReadIndex;
  }

  bool CCharFifo::isFull(void) const
  {
    return static_cast<irr::u8>(mWriteIndex+1) == mReadIndex;
  }

  irr::u8 CCharFifo::getNumberOfElements(void) const
  {
    return mWriteIndex-mReadIndex;
  }

}

/**
 * @}
 */



