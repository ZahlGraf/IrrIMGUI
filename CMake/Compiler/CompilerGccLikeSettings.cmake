#
# The MIT License (MIT)
#
# Copyright (c) 2015 André Netzeband
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
SET(GCC_LIKE_COMPILER OFF)
SET(IRRIMGUI_LINK_TO_DIRECTX OFF)

if ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
	message(STATUS "Detect CLANG compiler and handle it like GCC...")
	SET(GCC_LIKE_COMPILER ON)
elseif ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xGNU")
	message(STATUS "Detect GCC compiler...")
	SET(GCC_LIKE_COMPILER ON)
elseif ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xIntel")
	if(UNIX)
		message(STATUS "Detect Intel compiler and handle it like GCC...")
		SET(GCC_LIKE_COMPILER ON)
	endif ()
endif ()

if (GCC_LIKE_COMPILER)
	SET (CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} -std=c++11"
	)
	
	INCLUDE(CheckCSourceCompiles)
	CHECK_C_SOURCE_COMPILES("
		#ifndef __x86_64__
		#error
		#endif
		
		int main(void) { return 0; }
		" 
		WITH_64BIT
		)

	if(WITH_64BIT)
		message(STATUS "Detect 64bit GCC like compiler...")
		SET(CMAKE_CL_64 TRUE CACHE BOOL "" FORCE)
		mark_as_advanced(CMAKE_CL_64)
	else()
		message(STATUS "Detect 32bit GCC like compiler...")
		SET(CMAKE_CL_64 FALSE CACHE BOOL "" FORCE)
		mark_as_advanced(CMAKE_CL_64)
	endif()
				
endif ()

