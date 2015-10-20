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
 * @file   IReferenceCounter.h
 * @author Andre Netzeband
 * @brief  Contains a class to count references.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_CREFERENCECOUNTER_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_CREFERENCECOUNTER_H_

// library includes
#include "IrrIMGUIConfig.h"
#include "IncludeIrrlicht.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{

  /// @brief A class to count references.
  /// @details This class can be used in the same way like the reference counter of Irrlicht:
  ///          When this class is created, it's counter is set to 1.
  ///          When this class is destroyed it will print a warning, when the counter is not equal to 1, because this means another class still uses a reference to it.
  ///          You can increase the counter by calling IReferenceCounter::grab().
  ///          By calling IReferenceCounter::drop() you can decrease the counter. If the counter reaches 0 in that way, the instance is destroyed automatically.
  ///          Thus you don't need to call destroy manually, just call IReferenceCounter::drop() and it will be destroyed automatically when no other reference is
  ///          currently in use. The big difference of the Irrlicht implementation is, that this implementation uses virtual methods. Thus you can easily mock classes
  ///          that are derived from this reference counter.
  ///          However this comes with a drawback: Creating and destroying such classes is not as fast as in the Irrlicht library.
  ///          Outside of the main-loop this is not an issue, because spending some nanoseconds more a single time is not bad, when you gain a better testability.
  ///          But when you create and destroy objects every frame, then it could become an issue. Please use in such cases the high performance inline implementation
  ///          from Irrlicht!
  class IRRIMGUI_DLL_API IReferenceCounter
  {
    public:
      /// @brief Constructor.
      IReferenceCounter(void);

      /// @brief Destructor.
      virtual ~IReferenceCounter(void);

      /// @brief Call this method to grab an instance.
      virtual void grab(void);

      /// @brief Call this method to drop an instance. If you drop the last used instance, the object is destroyed.
      virtual void drop(void);

      /// @return Returns the current reference count.
      virtual irr::u32 getReferenceCount(void) const;

    private:
      /// @brief The reference counter of this class.
      irr::u32 mReferences;
  };

}

/**
 * @}
 */

#endif // IRRIMGUI_INCLUDE_IRRIMGUI_CREFERENCECOUNTER_H_
