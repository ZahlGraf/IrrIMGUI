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
 * @file   IrrIMGUIConfig.h
 * @author Andre Netzeband
 * @brief  Helper file for preprocessor configuration.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_SOURCE_IRRIMGUICONFIG_H_
#define IRRIMGUI_SOURCE_IRRIMGUICONFIG_H_

/**
 * @addtogroup IrrIMGUI
 * @{
 */

#ifdef DOXYGEN

/// @{
/// @name Configuration defines

/// @brief If this is defined during compilation, it will prepare the source for a static library
#define _IRRIMGUI_STATIC_LIB_

/// @brief If this is defined during compilation, it will prepare the headers to export the symbols to the DLL shared libary.
/// @note Windows only!
#define _IRRIMGUI_EXPORTS_

/// @brief If this is defined during compilation, it will include irrlicht library from with <Irrlicht/irrlicht.h> instead of <irrlicht.h>
#define _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_

/// @brief If this is defined during compilation, it will use the native OpenGL renderer for IMGUI instead of the Irrlicht renderer.
/// @attention This is only a fallback solution for testing. It is not officially supported by this lib!
#define _IRRIMGUI_NATIVE_OPENGL_

/// @brief If this define is during compilation the OpenGL driver will assume the memory location where the OpenGL texture ID is stored
///        inside an ITexture object. This is very fast, but with new Irrlicht versions this method could fail.
///        Disable it, when the Example 6 (RenderWindow) does not work correctly.
#define _IRRIMGUI_FAST_OPENGL_TEXTURE_HANDLE_

/// @}

/// @{
/// @name Automatically set defines

/// @brief Is automatically defined, if a windows target is detected at compile step.
#define _IRRIMGUI_WINDOWS_

/// @brief Helper for shared windows libraries (DLL).
/// @details
/// @li It is set to export symbols during DLL compilation.
/// @li It is set to import symbols during application compilation (where the DLL is used for linking later).
/// @li It is empty during static library compilation
#define IRRIMGUI_DLL_API

/// @brief Helper for IMGUI shared windows libraries (DLL).
/// @details
/// @li It is set to export symbols during DLL compilation.
/// @li It is set to import symbols during application compilation (where the DLL is used for linking later).
/// @li It is empty during static library compilation
#define IMGUI_API

/// @brief Not all modern compilers support the C++11 keyword noexcept. Thus this macro is empty for oder MSVC versions than 2015.
///        For MingW, GCC, CLang or MSVC2015 (or higher versions) this macro contains the keyword noexcept.
#define NOEXCEPT

/// @brief This is defined if the compiler supports a sizeof from non-static class members (C++11 feature)
#define IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER

/// @}

#endif

// detect Windows systems
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _IRRIMGUI_WINDOWS_
#endif

// windows dependent settings
#ifdef _IRRIMGUI_WINDOWS_

#if defined(_MSC_VER)
#define _IRRIMGUI_COMPILER_MSVC_

#if (_MSC_VER < 1600)
#define _IRRIMGUI_COMPILER_MSVC_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_

#elif ((_MSC_VER >= 1600) && (_MSC_VER < 1700))
#define _IRRIMGUI_COMPILER_MSVC_2010_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_

#elif ((_MSC_VER >= 1700) && (_MSC_VER < 1800))
#define _IRRIMGUI_COMPILER_MSVC_2012_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2012_

#elif ((_MSC_VER >= 1800) && (_MSC_VER < 1900))
#define _IRRIMGUI_COMPILER_MSVC_2013_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2012_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2013_

#elif ((_MSC_VER >= 1900) && (_MSC_VER < 2000))
#define _IRRIMGUI_COMPILER_MSVC_2015_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2012_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2013_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_

#elif (_MSC_VER >= 2000)
#define _IRRIMGUI_COMPILER_MSVC_UNKNOWN_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_OLD_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2010_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2012_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2013_
#define _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_

#endif // _MSC_VER
#endif // defined(_MSC_VER)

// To build this library as static library, you have to define _IRRIMGUI_STATIC_LIB_ during compilation!
#ifndef _IRRIMGUI_STATIC_LIB_
#ifdef _IRRIMGUI_EXPORTS_
#define IRRIMGUI_DLL_API __declspec(dllexport)
#else
#define IRRIMGUI_DLL_API __declspec(dllimport)
#endif // _IRRIMGUI_EXPORTS_
#else
#define IRRIMGUI_DLL_API
#endif // _IRRIMGUI_STATIC_LIB_

#else //_IRRIMGUI_WINDOWS_
// non windows settings

#define IRRIMGUI_DLL_API

#endif //_IRRIMGUI_WINDOWS_

// define NOEXCEPT depending on compiler
#ifdef _IRRIMGUI_COMPILER_MSVC_
  #ifdef _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_
    // MSVC 2015 has it
    #define NOEXCEPT noexcept

  #else  // _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_
    // older MSVC than 2015 don't have it.
    #define NOEXCEPT

  #endif // _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_

#else // GCC/MingW/Clang
  // Hopefully every modern Clang, MingW or GCC compiler has it... if not we need a similar solution like for MSVC
  #define NOEXCEPT noexcept

#endif // _IRRIMGUI_COMPILER_MSVC_

// define IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER depending on compiler
#ifdef _IRRIMGUI_COMPILER_MSVC_
  #ifdef _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_
    // MSVC 2015 has it
    #define IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER 1

  #endif // _IRRIMGUI_COMPILER_MSVC_AT_LEAST_2015_

#else // GCC/MingW/Clang
  // Hopefully every modern Clang, MingW or GCC compiler has it... if not we need a similar solution like for MSVC
    #define IRRIMGUI_CONFIG_SIZEOF_FROM_CLASSMEMBER 1

#endif // _IRRIMGUI_COMPILER_MSVC_

// os-independent settings
#ifndef IMGUI_API
#define IMGUI_API IRRIMGUI_DLL_API
#endif

/**
 * @}
 */
/**
 * @}
 */

#endif // IRRIMGUI_SOURCE_IRRIMGUICONFIG_H_

