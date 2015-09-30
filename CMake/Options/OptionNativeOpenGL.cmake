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

SET (IRRIMGUI_NATIVE_OPENGL OFF CACHE BOOL "Enables the native OpenGL Driver for IMGUI (ATTENTION: This is just a fallback solution!).")

if (IRRIMGUI_NATIVE_OPENGL)
	message(WARNING "Use native OpenGL render driver (Fallback solution, do not use it for productive work!)...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_NATIVE_OPENGL_
	)
	SET (IRRIMGUI_FAST_OPENGL_TEXTURE_CREATION ON CACHE BOOL "Enables the fast OpenGL texture creation to translate a ITexture object to an OpenGL handle instead of creating a copy. This is a very instable hack. Disable this, when the example 7 (RenderWindow) fails.")	
else ()
	message(STATUS "Use Irrlicht based render driver...")
endif ()

if (IRRIMGUI_FAST_OPENGL_TEXTURE_CREATION)
	message(STATUS "Use fast OpenGL texture ID creation (fast but risky!)...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_FAST_OPENGL_TEXTURE_HANDLE_
	)
else ()
	message(STATUS "Creaty texture copy for generating OpenGL texture IDs...")
endif ()

