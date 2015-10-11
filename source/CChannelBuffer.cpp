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
 * @file   CChannelBuffer.cpp
 * @author Andre Netzeband
 * @brief  Contains the implementation of a channel buffer.
 * @addtogroup IrrIMGUIDebug
 */

// standard library includes
#include <iostream>

// module includes
#include <IrrIMGUI/IrrIMGUIDebug.h>

namespace IrrIMGUI
{
namespace Debug
{

  CChannelBuffer::CChannelBuffer(std::streambuf * pStreamBuffer, char const * pPrefix):
    mpPrefix(pPrefix),
    mpBuffer(pStreamBuffer),
    mIsNewLine(true)
  {
    return;
  }

  void CChannelBuffer::setupBuffer(std::streambuf * pStreamBuffer,  bool NextSymbolOnNewLine)
  {
    mpBuffer = pStreamBuffer;
    mIsNewLine = NextSymbolOnNewLine;
    return;
  }

  void CChannelBuffer::setupPrefix(char const * pPrefix)
  {
    mpPrefix = pPrefix;
    return;
  }

  int CChannelBuffer::overflow(int const Character)
  {
    int ReturnChar      = Character;

    if (mpBuffer)
    {
      bool IsPrintAllowed = true;

      if (mIsNewLine)
      {
        if (!printPrefix())
        {
          ReturnChar = EOF;
          IsPrintAllowed = false;
        }
        mIsNewLine = false;
      }

      if (IsPrintAllowed)
      {
        if (mpBuffer->sputc(Character) == EOF)
        {
          ReturnChar = EOF;
        }

        if (Character == '\n')
        {
          mIsNewLine = true;
        }
      }
    }

    return ReturnChar;
  }

  int CChannelBuffer::sync(void)
  {
    int Return = 0;

    if (mpBuffer)
    {
      if (mpBuffer->pubsync() == -1)
      {
        Return = -1;
      }
    }

    return Return;
  }

  bool CChannelBuffer::printPrefix(void)
  {
    bool IsPrintAllowed = true;

    for (int i = 0; mpPrefix[i]; i++)
    {
      if (mpBuffer->sputc(mpPrefix[i]) == EOF)
      {
        break;
        IsPrintAllowed = false;
      }
    }

    return IsPrintAllowed;
  }

  CChannel NoteOutput(std::cout,    "[Note]    ");

  CChannel WarningOutput(std::cout, "[Warning] ");

  CChannel ErrorOutput(std::cerr,   "[Error]   ");

  bool AreUnitTestAssertionsEnabled = true;
}
}

