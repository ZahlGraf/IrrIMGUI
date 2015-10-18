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

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
cmake_policy(VERSION 2.6)

SET(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} 
	${CMAKE_CURRENT_SOURCE_DIR}/CMake
	${CMAKE_CURRENT_SOURCE_DIR}/../CMake
)

INCLUDE(ExampleBuild)

SET(EXAMPLE_SOURCE_FILES
	TestCharFifo.cpp
	TestEventReceiver.cpp
	TestHandleMockIMGUIDependency.cpp
	TestIIMGUIHandleMock.cpp
	TestInjection.cpp
	TestIrrIMGUIDebug.cpp
	TestIrrIMGUIHandle.cpp
	TestMemoryLeakDetection.cpp
	TestReferenceCounter.cpp
	TestSettings.cpp
	UnitTestMain.cpp
)

SET(EXAMPLE_HEADER_FILES
	stb_compress_only.h
)

SET(EXAMPLE_INSTALL_FILES	
)

SET(EXAMPLE_INSTALL_DIRS
)

# Basic settings check, in case the example is build as stand-alone
if (ZZZ_EXAMPLE_SINGLE_COMPILE)
	SET(IRRIMGUI_CPPUTEST_INCLUDE_DIR "NOT-FOUND" CACHE PATH "The include directory for CppUTest headers.")
	SET(IRRIMGUI_CPPUTEST_MAIN        "NOT-FOUND" CACHE FILEPATH "The path to the CppUTest main library.")
	SET(IRRIMGUI_CPPUTEST_EXTENSION   "NOT-FOUND" CACHE FILEPATH "The path to the CppUTest extension library.")
endif ()

SET(TEST_LIBRARIES
	${IRRIMGUI_CPPUTEST_MAIN}
	${IRRIMGUI_CPPUTEST_EXTENSION}
)

SET(TEST_INCLUDES
	${IRRIMGUI_CPPUTEST_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../source/private
)

#SET(TEST_INCLUDE_FILES
#	CppUTest/MemoryLeakDetectorNewMacros.h
#	CppUTest/MemoryLeakDetectorMallocMacros.h
#)

BUILD_UTEST("UnitTests" "${EXAMPLE_SOURCE_FILES}" "${EXAMPLE_HEADER_FILES}" "${EXAMPLE_INSTALL_FILES}" "${EXAMPLE_INSTALL_DIRS}" "${TEST_INCLUDES}" "${TEST_LIBRARIES}" "")
