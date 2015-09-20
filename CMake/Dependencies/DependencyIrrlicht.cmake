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

