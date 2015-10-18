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

SET (IRRIMGUI_BUILD_UNITTESTS OFF CACHE BOOL "Enables the unit-test compilation.")

if (IRRIMGUI_BUILD_UNITTESTS)
	message(STATUS "Build Unit Tests...")
	
	SET(IRRIMGUI_CPPUTEST_INCLUDE_DIR "NOT-FOUND" CACHE PATH "The include directory for CppUTest headers.")
	SET(IRRIMGUI_CPPUTEST_MAIN        "NOT-FOUND" CACHE FILEPATH "The path to the CppUTest main library.")
	SET(IRRIMGUI_CPPUTEST_EXTENSION   "NOT-FOUND" CACHE FILEPATH "The path to the CppUTest extension library.")

	ADD_DEFINITIONS(	
	-DCPPUTEST_USE_MEM_LEAK_DETECTION=0
	)			
	
else ()
	message(STATUS "Do not build Unit Tests...")
endif ()