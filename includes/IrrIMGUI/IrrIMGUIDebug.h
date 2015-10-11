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
 * @file   IrrIMGUIDebug.h
 * @author Andre Netzeband
 * @brief  Contains defines for debug handling.
 * @addtogroup IrrIMGUIDebug
 */

#ifndef IRRIMGUI_SOURCE_IRRIMGUIDEBUG_H_
#define IRRIMGUI_SOURCE_IRRIMGUIDEBUG_H_

// standard library includes
#include <streambuf>
#include <ostream>

// module includes
#include "IrrIMGUIConfig.h"
#include <IrrIMGUI/IrrIMGUIConfig.h>

/**
 * @defgroup IrrIMGUIDebug Debug
 * @ingroup IrrIMGUI
 * @brief Contains classes for debug purpose.
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains classes for debug purpose.
namespace Debug
{

  /// @brief Is a stream channel buffer, that adds to each new line a defined prefix.
  class IRRIMGUI_DLL_API CChannelBuffer : public std::streambuf
  {
    public:
      /**
       * @brief Constructor
       * @param pStreamBuffer Is a pointer to a stream buffer, where all input data should be written to.
       * @param pPrefix       Is a prefix string that should be added before each new line.
       */
      CChannelBuffer(std::streambuf * pStreamBuffer, char const * pPrefix);

      /// @brief Destructor.
      virtual ~CChannelBuffer(void) {};

      /// @brief Setups a new output buffer.
      /// @param pStreamBuffer       Is a pointer to a output buffer. If this pointer is NULL or nullptr, no output is generated anymore.
      /// @param NextSymbolOnNewLine Must be true, when the next symbol should start at a new line.
      void setupBuffer(std::streambuf * pStreamBuffer,  bool NextSymbolOnNewLine);

      /// @brief Setups a new prefix.
      /// @param pPrefix Is a prefix string that should be added before each new line.
      void setupPrefix(char const * pPrefix);

    private:
      /**
       * @brief Since this is not a real buffer, this method is called for each character that is written to this stream buffer.
       * @param Character Is the character that shall be written.
       * @return Returns EOF if the original buffer returns it.
       */
      virtual int overflow(int Character = EOF);

      /**
       * @brief This methods synchronizes the buffer.
       * @return Returns -1 when the buffer indicates an error, otherwise it returns 0.
       */
      virtual int sync(void);

      /// @brief Prints the prefix.
      /// @return Returns true when prefix print was successful.
      bool printPrefix(void);

      /// @brief The prefix that should be written at the beginning of each new line.
      char const * mpPrefix;

      /// @brief The stream buffer where the output should be put in.
      std::streambuf * mpBuffer;

      /// @brief Is true, when the next char should be written to a new line.
      bool mIsNewLine;
  };


  /// @brief Puts on every new line that is written to this channel a prefix.
  class IRRIMGUI_DLL_API CChannel : public std::ostream
  {
    public:
      /// @name Constructor and destructor
      /// @{

      /**
       * @brief Constructor.
       * @param rStream is the output stream to use.
       * @param pPrefix is the prefix to put at the beginning of every new line.
       */
      CChannel(std::ostream &rStream, char const * const pPrefix):
        mBuffer(rStream.rdbuf(), pPrefix),
        std::ostream(&mBuffer)
      {}

      /// @brief Copy Constructor does not exist.
      CChannel(CChannel const &rCopyChannel) = delete;

      /// @brief Setups a new stream for output.
      /// @param rStream             Is a reference to a output stream.
      /// @param NextSymbolOnNewLine Must be true, when the next symbol should start at a new line.
      void setupStream(std::ostream &rStream, bool NextSymbolOnNewLine = true) {mBuffer.setupBuffer(rStream.rdbuf(), NextSymbolOnNewLine);}

      /// @brief Setups a new prefix.
      /// @param pPrefix Is a prefix string that should be added before each new line.
      void setupPrefix(char const * const pPrefix) {mBuffer.setupPrefix(pPrefix); }

      /// @brief Disables this stream. To enable again call setup.
      void disable(void) {mBuffer.setupBuffer(nullptr, false); }

      /// @}

    private:
      /// @brief The buffer object where input data are written to.
      CChannelBuffer mBuffer;
  };

  /// @brief Standard Exception used for assertions.
  class ExAssert : public std::exception
  {
    public:
      /// @brief Constructor
      /// @param pText a static text to print.
      ExAssert(char const * pText):mpText(pText) {};

      /// @return Returns the static text.
      virtual char const *what(void) const noexcept {return mpText;}

    private:
      char const * const mpText;

  };

  /// @brief A channel for notes.
  IRRIMGUI_DLL_API extern CChannel NoteOutput;

  /// @brief A channel for warnings.
  IRRIMGUI_DLL_API extern CChannel WarningOutput;

  /// @brief A channel for errors.
  IRRIMGUI_DLL_API extern CChannel ErrorOutput;

  /// @brief If this is true, assertions do not throw exceptions, but fail a unit test check.
  IRRIMGUI_DLL_API extern bool AreUnitTestAssertionsEnabled;
}
}

/**
 * @}
 */


#endif /* IRRIMGUI_SOURCE_IRRIMGUIDEBUG_H_ */
