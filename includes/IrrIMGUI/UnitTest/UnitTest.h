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
 * @file   UnitTest.h
 * @author Andre Netzeband
 * @brief  Main-header for the unit test interface.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_

// library includes
#include "IncludeCppUTest.h"

/**
 * @defgroup IrrIMGUIUTest UnitTest
 * @ingroup IrrIMGUI
 * @brief Unit test related definitions.
 *
 * @{
 */

namespace IrrIMGUI
{
/// @brief Contains unit test related definitions
namespace UnitTest
{
}
}

#ifdef DOXYGEN

/// @brief Checks if two arguments are not equal.
/// @param Argument1 Is the first argument to check.
/// @param Argument2 Is the second argument to check.
#define CHECK_NOT_EQUAL(Argument1, Argument2)

/// @brief Checks if two values are equal with considering a tolerance.
/// @param ReferenceValue Is the reference value for that check.
/// @param Tolerance      Is the tolerance, where the tested value must be inside.
/// @param TestValue      Is the value to test.
#define CHECK_EQUAL_TOLERANCE(ReferenceValue, Tolerance, TestValue)

/// @brief Check a value in in range between minimum and maximum.
/// @param Minimum Is the lower border.
/// @param Maximum Is the higher border.
/// @param TestValue      Is the value to test.
#define CHECK_IN_RANGE(Minimum, Maximum, TestValue)

/// @brief Creates a mock entry into the mock database for the current function/method.
/// @param Name Is the name of the function.
#define MOCK_FUNC(Name)

/// @brief Creates a mock entry for an argument of the current function mock.
/// @param Argument Is the name of the argument.
#define MOCK_ARG(Argument)

#else // DOXYGEN

#define CHECK_NOT_EQUAL(Argument1, Argument2) \
  CHECK_NOT_EQUAL_LOCATION(Argument1, Argument2, __FILE__, __LINE__)

#define CHECK_NOT_EQUAL_LOCATION(Argument1, Argument2, file, line) \
{                                      \
  CHECK((Argument1) != (Argument2));   \
  if ((Argument1) != (Argument1)) {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Argument1\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
  if ((Argument2) != (Argument2)) {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Argument2\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
}                                      \

#define CHECK_EQUAL_TOLERANCE(ReferenceValue, Tolerance, TestValue) \
  CHECK_IN_RANGE((ReferenceValue)-(Tolerance), (ReferenceValue)+(Tolerance), (TestValue))

#define CHECK_IN_RANGE(Minimum, Maximum, TestValue) \
  CHECK_IN_RANGE_LOCATION(Minimum, Maximum, TestValue, __FILE__, __LINE__)

#define CHECK_IN_RANGE_LOCATION(Minimum, Maximum, TestValue, file, line) \
{                                                   \
  CHECK((TestValue) >= (Minimum));                  \
  CHECK((TestValue) <= (Maximum));                  \
  if ((TestValue) != (TestValue)) {UtestShell::getCurrent()->print("WARNING:\n\tThe \"TestValue\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
  if ((Minimum)   != (Minimum))   {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Minimum\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
  if ((Maximum)   != (Maximum))   {UtestShell::getCurrent()->print("WARNING:\n\tThe \"Minimum\" parameter is evaluated multiple times resulting in different values.\n\tThus the value in the error message is probably incorrect.", file, line);}   \
}                                                   \

#define MOCK_FUNC(Name)     mock().actualCall(Name)
#define MOCK_ARG(Argument)  withParameter(#Argument, Argument)

#endif // DOXYGEN


/**
 * @}
 */

#endif // IRRIMGUI_INCLUDE_IRRIMGUI_UNITTEST_H_
