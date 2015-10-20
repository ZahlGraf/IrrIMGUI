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
 * @file   IrrIMGUIDebug_priv.h
 * @author Andre Netzeband
 * @brief  Contains defines for debug handling.
 * @addtogroup IrrIMGUIDebug
 */

#ifndef IRRIMGUI_SOURCE_IRRIMGUIDEBUG_PRIV_H_
#define IRRIMGUI_SOURCE_IRRIMGUIDEBUG_PRIV_H_

// module includes
#include <IrrIMGUI/IrrIMGUIConfig.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

#ifdef IRRIMGUI_UNIT_TEST
#include <IrrIMGUI/UnitTest/UnitTest.h>
#define UNIT_TEST true
#endif

/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */

/// @{
/// @name Debug level definition

/// @brief Print all messages
#define DEBUG_LEVEL_NOTE    2

/// @brief Print only Errors and Warnings
#define DEBUG_LEVEL_WARNING 1

/// @brief Print only Errors
#define DEBUG_LEVEL_ERROR   0

/// @brief Do not print anything
#define DEBUG_LEVEL_NONE   (-1)

/// @}

#if defined(DOXYGEN)

/// @{
/// @name Helper Macros

/// @brief A helper macro to create static strings out of macro expressions
/// @param x Is the expression where a string should be created from
#define TOSTR(x)

/// @}

/// @{
/// @name Assertion macros for error detection

/// @brief An assertion for detecting fatal errors. This assertion is also active in the non-debug version.
/// @param expr Is the expression to check. If it is false, an exception is thrown.
#define FASSERT(expr)

/// @brief An assertion for detecting errors. This assertion is only active in debug version.
/// @param expr Is the expression to check. If it is false, an exception is thrown.
#define ASSERT(expr)  if (!(expr)) FASSERT(expr)

/// @}

/// @{
/// @name Debug and Error logging to console

/// @brief Prints an note to std::out. It is only active for debug level 2.
/// @param string Is the stream to print.
#define LOG_NOTE(string)

/// @brief Prints an warning to std::out. It is only active for debug level 1 or higher.
/// @param string Is the stream to print.
#define LOG_WARNING(string)

/// @brief Prints an error to std::out. It is only active for debug level 0 or higher.
/// @param string Is the stream to print.
#define LOG_ERROR(string)

/// @}

#else

#define IS_DEBUG_LEVEL(LEVEL) ((DEBUG_LEVEL) >= (LEVEL))

#ifndef _DEBUG
#ifndef NDEBUG
#ifndef _NDEBUG

// Debug is default for all compiles where not _NDEBUG or NDEBUG has been defined
#define _DEBUG

#endif // _NDEBUG
#endif // NDEBUG
#endif // _DEBUG

#ifdef _DEBUG
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_LEVEL_NOTE
#endif // DEBUG_LEVEL
#else  // _DEBUG
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_LEVEL_ERROR
#endif // DEBUG_LEVEL
#endif // _DEBUG

#define _TOSTR(x) #x
#define TOSTR(x) _TOSTR(x)

#ifdef UNIT_TEST
/// in unit test case just fail a CHECK
#define FASSERT(expr) if (IrrIMGUI::Debug::AreUnitTestAssertionsEnabled) { CHECK((expr)); } else { TEST_ASSERT((expr)); }
#else
/// throw exception
#define FASSERT(expr) TEST_ASSERT((expr))
#endif

#define TEST_ASSERT(expr) if (!(expr)) { throw IrrIMGUI::Debug::ExAssert(__FILE__ "[" TOSTR(__LINE__) "] Assertion failed: \'" TOSTR(expr) "'\n"); }

#ifdef _DEBUG
#define ASSERT(expr)  if (!(expr)) FASSERT(expr)
#else  // _DEBUG
#define ASSERT(expr)
#endif // _DEBUG

#if IS_DEBUG_LEVEL(DEBUG_LEVEL_NOTE)
#define LOG_NOTE(string)    { (IrrIMGUI::Debug::NoteOutput)    << string << std::flush; }
#else  // DEBUG_LEVEL_NOTE
#define LOG_NOTE(string)
#endif // DEBUG_LEVEL_NOTE

#if IS_DEBUG_LEVEL(DEBUG_LEVEL_WARNING)
#define LOG_WARNING(string) { (IrrIMGUI::Debug::WarningOutput) << string << std::flush; }
#else  // DEBUG_LEVEL_WARNING
#define LOG_WARNING(string)
#endif // DEBUG_LEVEL_WARNING

#if IS_DEBUG_LEVEL(DEBUG_LEVEL_ERROR)
#define LOG_ERROR(string)   { (IrrIMGUI::Debug::ErrorOutput)   << string << std::flush; }
#else  // DEBUG_LEVEL_ERROR
#define LOG_ERROR(string)
#endif // DEBUG_LEVEL_ERROR

#endif

/**
 * @}
 */
/**
 * @}
 */

#endif /* IRRIMGUI_SOURCE_IRRIMGUIDEBUG_PRIV_H_ */
