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
 * @file   IncludeIrrlicht.h
 * @author Andre Netzeband
 * @brief  Helper file for including irrlicht from the correct location.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_SOURCE_INCLUDEIRRLICHT_H_
#define IRRIMGUI_SOURCE_INCLUDEIRRLICHT_H_

// disable CPPUTEST new macro for Irrlicht library
#if CPPUTEST_USE_NEW_MACROS
   #undef new
#endif

#ifndef _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
#include <irrlicht.h>
#else  // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
#include <Irrlicht/irrlicht.h>
#endif // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_

// enable CPPUTEST new macro for further headers
#if CPPUTEST_USE_NEW_MACROS
   #include <CppUTest/MemoryLeakDetectorNewMacros.h>
#endif

#endif // _IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
