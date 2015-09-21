SET (IMGUI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependency/IMGUI" CACHE PATH "The source directory of IMGUI.")

IF (IRRIMGUI_INSTALL_MEDIA_FILES)
	SET(IMGUI_FONT_DIR "${CMAKE_SOURCE_DIR}/dependency/IMGUI/extra_fonts" CACHE PATH "The directory where the font files from IMGUI are stored (Cousine-Regular.ttf, DroidSans.ttf, Karla-Regular.ttf, ProggyClean.ttf).")
ENDIF ()

INCLUDE_DIRECTORIES(
  ${IMGUI_SOURCE_DIR}/..
  )

SET (IMGUI_PUBLIC_HEADER_FILES
	${IMGUI_SOURCE_DIR}/imgui.h
	${IMGUI_SOURCE_DIR}/imconfig.h	
)

SET (IMGUI_PRIVATE_HEADER_FILES
	${IMGUI_SOURCE_DIR}/imgui_internal.h
	${IMGUI_SOURCE_DIR}/stb_rect_pack.h	
	${IMGUI_SOURCE_DIR}/stb_textedit.h	
	${IMGUI_SOURCE_DIR}/stb_truetype.h	
)

SET (IMGUI_SOURCE_FILES
	${IMGUI_SOURCE_DIR}/imgui.cpp
	${IMGUI_SOURCE_DIR}/imgui_draw.cpp	
	${IMGUI_SOURCE_DIR}/imgui_demo.cpp	
)

SET (IMGUI_FONTFILES
	${IMGUI_FONT_DIR}/Cousine-Regular.ttf
	${IMGUI_FONT_DIR}/DroidSans.ttf
	${IMGUI_FONT_DIR}/Karla-Regular.ttf
	${IMGUI_FONT_DIR}/ProggyClean.ttf
)

SET (IMGUI_FOUND TRUE)	
IF (NOT EXISTS "${IMGUI_SOURCE_DIR}/imgui.h")
	message(SEND_ERROR "Cannot find file ${IMGUI_SOURCE_DIR}/imgui.h please specify a correct source directory for IMGUI!")
	SET (IMGUI_FOUND FALSE)	
ENDIF ()

IF (IRRIMGUI_INSTALL_MEDIA_FILES)
	foreach( FONT ${IMGUI_FONTFILES} )
		IF (NOT EXISTS "${FONT}")
			message(SEND_ERROR "Cannot find file ${FONT} please specify a correct IMGUI font directory!")
			SET (IMGUI_FOUND FALSE)			
		ENDIF ()		
	endforeach()
ENDIF ()

IF (NOT EXISTS "${IMGUI_SOURCE_DIR}/../IMGUI")
	message(SEND_ERROR "Cannot find directory IMGUI at location '${IMGUI_SOURCE_DIR}/..' . Thus the compiler will not able to include the IMGUI header files. Please install the IMGUI sources and headers in a subdirectory called IMGUI!")
	SET (IMGUI_FOUND FALSE)			
ENDIF ()		

