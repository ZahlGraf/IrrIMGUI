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

INCLUDE_DIRECTORIES(
  includes
  )

SET (IRRIMGUI_PUBLIC_HEADER_FILES
	includes/IrrIMGUI/Inject/IrrIMGUIInject.h
	includes/IrrIMGUI/UnitTest/IIMGUIHandleMock.h
	includes/IrrIMGUI/UnitTest/IncludeCppUTest.h
	includes/IrrIMGUI/UnitTest/MockHelper.h
	includes/IrrIMGUI/UnitTest/UnitTest.h
	includes/IrrIMGUI/CCharFifo.h
	includes/IrrIMGUI/CIMGUIEventReceiver.h
	includes/IrrIMGUI/CIMGUIEventStorage.h
	includes/IrrIMGUI/IGUITexture.h
	includes/IrrIMGUI/IIMGUIHandle.h
	includes/IrrIMGUI/IMGUIHelper.h
	includes/IrrIMGUI/IncludeIMGUI.h
	includes/IrrIMGUI/IncludeIrrlicht.h
	includes/IrrIMGUI/IReferenceCounter.h
	includes/IrrIMGUI/IrrIMGUI.h	
	includes/IrrIMGUI/IrrIMGUIConfig.h
	includes/IrrIMGUI/IrrIMGUIConstants.h
	includes/IrrIMGUI/IrrIMGUIDebug.h
	includes/IrrIMGUI/SIMGUISettings.h
)

SET (IRRIMGUI_PRIVATE_HEADER_FILES
	source/private/CGUITexture.h
	source/private/IrrIMGUIDebug_priv.h
	source/private/IrrIMGUIInject_priv.h
	source/CIMGUIHandle.h
	source/CIrrlichtIMGUIDriver.h
	source/COpenGLIMGUIDriver.h
	source/IIMGUIDriver.h
)

SET (IRRIMGUI_SOURCE_FILES
	source/CChannelBuffer.cpp
	source/CCharFifo.cpp
	source/CGUITexture.cpp
	source/CIMGUIEventReceiver.cpp
	source/CIMGUIHandle.cpp
	source/CIrrlichtIMGUIDriver.cpp
	source/COpenGLIMGUIDriver.cpp
	source/IIMGUIDriver.cpp
	source/IMGUIHelper.cpp
	source/IReferenceCounter.cpp
	source/IrrIMGUIInject.cpp
	source/UnitTest.cpp
)
