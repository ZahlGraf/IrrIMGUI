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

message(STATUS " -> Configure all examples:")

SET(IRRIMGUI_MEDIA_DIR   "${CMAKE_SOURCE_DIR}/../media" CACHE PATH "The directory where the media files are stored in.")

ADD_SUBDIRECTORY(01.HelloWorld)
ADD_SUBDIRECTORY(02.AnotherWindow)
ADD_SUBDIRECTORY(03.DifferentFonts)
ADD_SUBDIRECTORY(04.Images)
ADD_SUBDIRECTORY(05.DragNDrop)
ADD_SUBDIRECTORY(06.RenderWindow)
ADD_SUBDIRECTORY(Demo)

message(STATUS " ")

