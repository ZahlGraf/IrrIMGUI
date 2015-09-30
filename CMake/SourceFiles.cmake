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
	includes/IrrIMGUI/CCharFifo.h
	includes/IrrIMGUI/CIMGUIEventReceiver.h
	includes/IrrIMGUI/CIMGUIEventStorage.h
	includes/IrrIMGUI/CIMGUIHandle.h
	includes/IrrIMGUI/IrrIMGUI.h
	includes/IrrIMGUI/IrrIMGUIDebug.h
	includes/IrrIMGUI/SIMGUISettings.h
	includes/IrrIMGUI/IncludeIrrlicht.h
	includes/IrrIMGUI/IncludeIMGUI.h
	includes/IrrIMGUI/IrrIMGUIConfig.h
	includes/IrrIMGUI/IGUITexture.h
)

SET (IRRIMGUI_PRIVATE_HEADER_FILES
	source/COpenGLIMGUIDriver.h
	source/IIMGUIDriver.h
	source/IrrIMGUIDebug_priv.h
	source/CGUITexture.h
	source/CIrrlichtIMGUIDriver.h
)

SET (IRRIMGUI_SOURCE_FILES
	source/CChannelBuffer.cpp
	source/CCharFifo.cpp
	source/CIMGUIEventReceiver.cpp
	source/CIMGUIHandle.cpp
	source/COpenGLIMGUIDriver.cpp
	source/IIMGUIDriver.cpp
	source/CGUITexture.cpp
	source/CIrrlichtIMGUIDriver.cpp
)
