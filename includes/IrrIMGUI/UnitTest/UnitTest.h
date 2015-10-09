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
 * @file   UTest.h
 * @author Andre Netzeband
 * @brief  Main-header for the unit test interface.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_

// library includes
#include "IncludeCppUTest.h"

#ifndef CPPUTEST_USE_MALLOC_MACROS
#ifdef __GNUC__
#warning("Warning: CppUTest memory detection is disabled. Please include CppUTest/MemoryLeakDetectorNewMacros.h and CppUTest/MemoryLeakDetectorMallocMacros.h as first global header in your unit test project.")
#else
#pragma message ("Warning: CppUTest memory detection is disabled. Please include CppUTest/MemoryLeakDetectorNewMacros.h and CppUTest/MemoryLeakDetectorMallocMacros.h as first global header in your unit test project.")
#endif
#endif // CPPUTEST_USE_MALLOC_MACROS

#ifndef CPPUTEST_USE_NEW_MACROS
#ifdef __GNUC__
#warning("Warning: CppUTest memory detection is disabled. Please include CppUTest/MemoryLeakDetectorNewMacros.h and CppUTest/MemoryLeakDetectorMallocMacros.h as first global header in your unit test project.")
#else
#pragma message ("Warning: CppUTest memory detection is disabled. Please include CppUTest/MemoryLeakDetectorNewMacros.h and CppUTest/MemoryLeakDetectorMallocMacros.h as first global header in your unit test project.")
#endif
#endif // CPPUTEST_USE_NEW_MACROS

/**
 * @defgroup IrrIMGUIUTest UnitTest
 * @addtogroup IrrIMGUI
 * @brief Unit test related definitions.
 *
 * @{
 */

#ifdef DOXYGEN

/// @brief Checks if two arguments are not equal.
/// @param Argument1 Is the first argument to check.
/// @param Argument2 Is the second argument to check.
#define CHECK_NOT_EQUAL(Argument1, Argument2)

/// @brief Creates a mock entry into the mock database for the current function/method.
#define MOCK_FUNC()

/// @brief Creates a mock entry for an argument of the current function mock.
#define MOCK_ARG(Argument)

#else // DOXYGEN

#define CHECK_NOT_EQUAL(Argument1, Argument2) \
  CHECK_NOT_EQUAL_LOCATION(Argument1, Argument2, __FILE__, __LINE__)

#define CHECK_NOT_EQUAL_LOCATION(Argument1, Argument2, file, line) \
{                                      \
  CHECK((Argument1) != (Argument2));   \
  if ((Argument1) != (Argument1)) {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Actual Parameter\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
  if ((Argument2) != (Argument2)) {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Actual Parameter\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
}                                      \

#define MOCK_FUNC()         mock().actualCall(__FUNCTION__)
#define MOCK_ARG(Argument)  withParameter(#Argument, Argument)

#endif // DOXYGEN


/**
 * @}
 */

#endif // IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_
