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

SET (IRRLICHT_INCLUDE_DIR "." CACHE PATH "The include directory of irrlicht.")
SET (IRRLICHT_LIB_DIR "." CACHE FILEPATH "The static library of irrlicht.")
SET (IRRLICHT_BIN_DIR "." CACHE FILEPATH "The shared library of irrlicht.")

INCLUDE_DIRECTORIES(
  ${IRRLICHT_INCLUDE_DIR}
  )
  
SET (IRRLICHT_FOUND TRUE)	

IF (IRRIMGUI_IRRLICHT_DIRECT_INCLUDES)
	IF (NOT EXISTS "${IRRLICHT_INCLUDE_DIR}/irrlicht.h")
		message(SEND_ERROR "Cannot find file ${IRRLICHT_INCLUDE_DIR}/irrlicht.h please specify a correct include directory for Irrlicht!")
		SET (IRRLICHT_FOUND FALSE)	
	ENDIF ()
ELSE ()
	IF (NOT EXISTS "${IRRLICHT_INCLUDE_DIR}/Irrlicht/irrlicht.h")
		message(SEND_ERROR "Cannot find file ${IRRLICHT_INCLUDE_DIR}/Irrlicht/irrlicht.h please specify a correct include directory for Irrlicht!")
		SET (IRRLICHT_FOUND FALSE)	
	ENDIF ()
ENDIF ()

if (NOT EXISTS "${IRRLICHT_LIB_DIR}")
	message(SEND_ERROR "Irrlicht library ${IRRLICHT_LIB_DIR} does not exist.")
	SET (IRRLICHT_FOUND FALSE)	
endif ()

if (NOT IRRIMGUI_STATIC_LIBRARY)
	if(NOT EXISTS "${IRRLICHT_BIN_DIR}")
		message(SEND_ERROR "Irrlicht shared library ${IRRLICHT_BIN_DIR} does not exist.")
		SET (IRRLICHT_FOUND FALSE)	
	endif ()
endif ()

SET(IRRIMGUI_DEPENDENCY_LIBRARIES
	${IRRIMGUI_DEPENDENCY_LIBRARIES}
	${IRRLICHT_LIB_DIR}
)

