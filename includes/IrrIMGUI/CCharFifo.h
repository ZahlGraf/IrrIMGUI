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
 * @file   CCharFifo.h
 * @author Andre Netzeband
 * @brief  Class definition for a Fifo Memory
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_

// library includes
#include "IncludeIMGUI.h"
#include "IncludeIrrlicht.h"

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{
  /// @brief A Fifo Memory to store character inputs from the keyboard.
  class IRRIMGUI_DLL_API CCharFifo
  {
    public:
      /// @{
      /// @name Constructor and Destructor

      /// @brief Standard Constructor
      CCharFifo(void);

      /// @brief Standard Destructor
      ~CCharFifo(void);

      /// @}

      /// @{
      /// @name Write-, Read- and Status-Methods

      /**
       *  @param C Is the input Character to add to the Fifo Memory.
       *  @note  If the Fifo is full an assertion is raised.
       */
      void addChar(ImWchar C);

      /// @return Returns a Character from the Fifo Memory.
      /// @note If the Fifo is empty an assertion is raised.
      ImWchar getChar(void);

      /// @return Returns true, when the Fifo is empty.
      bool isEmpty(void) const;

      /// @return Returns true, when the Fifo is full.
      bool isFull(void) const;

      /// @return Returns the number of characters inside the Fifo.
      irr::u8 getNumberOfElements(void) const;

      /// @}

    private:
      ImWchar mCharArray[256];
      irr::u8 mWriteIndex;
      irr::u8 mReadIndex;
  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CCHARFIFO_H_ */
