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

/// @brief If this is defined during compilation, it will include irrlicht library from with <irrlicht.h> instead of <Irrlicht/irrlicht.h>
#define _IRRIMGUI_DIRECT_IRRLICHT_INCLUDE_

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

/// @}

#endif

// detect Windows systems
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _IRRIMGUI_WINDOWS_
#endif

// windows dependent settings
#ifdef _IRRIMGUI_WINDOWS_

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

#ifndef IMGUI_API
#define IMGUI_API IRRIMGUI_DLL_API
#endif

#endif //_IRRIMGUI_WINDOWS_

/**
 * @}
 */
/**
 * @}
 */

#endif // IRRIMGUI_SOURCE_IRRIMGUICONFIG_H_

