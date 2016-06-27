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

SET(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} 
	${CMAKE_CURRENT_LIST_DIR}/Dependencies
	${CMAKE_CURRENT_LIST_DIR}/Options
	${CMAKE_CURRENT_LIST_DIR}/Compiler
	${CMAKE_CURRENT_LIST_DIR}/Packages	
	${CMAKE_CURRENT_LIST_DIR}/OperationSystems	
)

FUNCTION(BUILD_APP_GENERIC APP_NAME APP_SOURCE_FILES APP_HEADER_FILES APP_INSTALL_FILES APP_INSTALL_DIRS APP_IS_WIN32 APP_INSTALL_PATH APP_EXTRA_INCLUDES APP_EXTRA_LIBS APP_EXTRA_INCLUDE_FILES COPY_SOURCE)
	
	message(STATUS "    * Configure: ${APP_NAME}...")
	project(${APP_NAME})

	# Set variables for irrlicht and media file reference. When this CMakeList file is called from Irrlicht build as a subproject, then the Irrlicht build will overwrite them
	SET(ZZZ_EXAMPLE_SINGLE_COMPILE ON CACHE BOOL "(Do not set!) If this is enabled, cmake assumes that an example should be compiled for itself (This variable is set automatically, so do not set!).")
	mark_as_advanced(FORCE ZZZ_EXAMPLE_SINGLE_COMPILE)
	
	SET(IRRIMGUI_INSTALL_EXAMPLE_SOURCE ON CACHE BOOL "If this is enabled, cmake will install source files for the example.")
	SET(IRRIMGUI_MEDIA_DIR   "${CMAKE_SOURCE_DIR}/../../media" CACHE PATH "The directory where the media files are stored in.")
	SET(IRRIMGUI_INCLUDE_DIR "NOT-FOUND" CACHE PATH "The include directory for IrrIMGUI headers.")
	SET(IRRIMGUI_LIBRARY     "NOT-FOUND" CACHE FILEPATH "The path to the IrrIMGUI library.")
	SET(IRRIMGUI_STATIC_LIBRARY OFF CACHE BOOL "Enabled static lib for IrrIMGUI.")
	if (NOT IRRIMGUI_STATIC_LIBRARY)
		SET(IRRIMGUI_SHARED_BIN  "NOT-FOUND" CACHE FILEPATH "The path to the IrrIMGUI shared library.")
	endif ()

	# Add irrlicht include dir
	INCLUDE_DIRECTORIES(
		${IRRIMGUI_INCLUDE_DIR}
	)

	# Handle source files
	SET_SOURCE_FILES_PROPERTIES(APP_HEADER_FILES
		PROPERTIES HEADER_FILE_ONLY TRUE
	)

	SET(ALL_APP_SOURCE_FILES
		${APP_SOURCE_FILES}
		${APP_HEADER_FILES}
	)

	if (COPY_SOURCE)
		SET(APP_INSTALL_FILES
			${APP_INSTALL_FILES}
			${ALL_APP_SOURCE_FILES}
		)
	endif ()
	
	# When the examples are build without irrlicht library, we need to apply the same settings like for irrlicht
	if (ZZZ_EXAMPLE_SINGLE_COMPILE)
	
		# Compiler dependent settings
		INCLUDE(CompilerMSVCLikeSettings)
		INCLUDE(CompilerGccLikeSettings)

		# OS dependent settings
		INCLUDE(OperationSystemLinux)
		INCLUDE(OperationSystemWindows)
		
		# Option dependent settings
		INCLUDE(OptionStaticLib)
		INCLUDE(OptionBuildExamples)
		INCLUDE(OptionInstallMediaFiles)
		INCLUDE(OptionIrrlichtDirectIncludes)
		INCLUDE(OptionNativeOpenGL)

		# Dependency related settings
		INCLUDE(DependencyIrrlicht)
		INCLUDE(DependencyOpenGL)
		INCLUDE(DependencyDirectX9)
		INCLUDE(DependencyDoxygen)
		INCLUDE(DependencyX11)

		# Print all settings
		#INCLUDE(PrintSettings)
	endif ()
	
	# Cache back the flags (seems to be an error of cmake for msys makefile generator)
	if (NOT CFLAG_WRITE_BACK)
		SET(CFLAG_WRITE_BACK TRUE CACHE BOOL "(do not change!)" FORCE)
		mark_as_advanced(FORCE CFLAG_WRITE_BACK)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "compile flags" FORCE)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "compile flags" FORCE)
	endif ()
	
	# Create target
	if (APP_IS_WIN32)
		ADD_EXECUTABLE(${APP_NAME} WIN32 ${ALL_APP_SOURCE_FILES})
	else ()
		ADD_EXECUTABLE(${APP_NAME} ${ALL_APP_SOURCE_FILES})
	endif ()
    TARGET_LINK_LIBRARIES(${APP_NAME} ${IRRIMGUI_LIBRARY} ${IRRIMGUI_DEPENDENCY_LIBRARIES} ${OS_DEPENDENT_LIBRARIES} ${IRRLICHT_LIBRARY})
	
	if (NOT "${APP_EXTRA_INCLUDES}" STREQUAL "")
		TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PRIVATE ${APP_EXTRA_INCLUDES})
	endif ()
	
	if (NOT "${APP_EXTRA_LIBS}" STREQUAL "")
		TARGET_LINK_LIBRARIES(${APP_NAME} ${APP_EXTRA_LIBS})
	endif ()

	if (NOT "${APP_EXTRA_INCLUDE_FILES}" STREQUAL "")
		foreach( SINGLEINCLUDEFILE ${APP_EXTRA_INCLUDE_FILES} )
			SET_TARGET_PROPERTIES(${APP_NAME} PROPERTIES
				COMPILE_FLAGS "/FI ${SINGLEINCLUDEFILE}"
			)		
		endforeach()
	endif ()
	
#	if (GCC_LIKE_COMPILER)
#		SET_TARGET_PROPERTIES(${APP_NAME} PROPERTIES
#			COMPILE_FLAGS "-static -lpthread -static-libgcc -static-libstdc++"
#		)
#	endif ()

	# Target installation
	INSTALL(TARGETS ${APP_NAME}
		RUNTIME DESTINATION  "${APP_INSTALL_PATH}" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
	)
	
	# Install additional files
	if (NOT "${APP_INSTALL_FILES}" STREQUAL "")
		INSTALL(FILES ${APP_INSTALL_FILES} DESTINATION "${APP_INSTALL_PATH}")
	endif ()
	
	# Install additional directories
	if (NOT "${APP_INSTALL_DIRS}" STREQUAL "")
		INSTALL(DIRECTORY ${APP_INSTALL_DIRS} DESTINATION "${APP_INSTALL_PATH}")
	endif ()
	
	# Install shared library
	if (NOT IRRIMGUI_STATIC_LIBRARY)
		INSTALL(FILES ${IRRIMGUI_SHARED_BIN} DESTINATION  "${APP_INSTALL_PATH}")
		INSTALL(FILES ${IRRLICHT_BIN_DIR}    DESTINATION  "${APP_INSTALL_PATH}")
	endif()

	# Install media files
	if (ZZZ_EXAMPLE_SINGLE_COMPILE)
		if (IRRIMGUI_INSTALL_MEDIA_FILES)
			INSTALL(DIRECTORY ${IRRLICHT_MEDIA_DIR} DESTINATION  ".")
			INSTALL(FILES     ${IMGUI_FONTFILES} DESTINATION "media")
		endif ()
	endif()

	# Basic settings check, in case the example is build as stand-alone
	if (ZZZ_EXAMPLE_SINGLE_COMPILE)
	
		# check irrlicht include directory
		if (NOT EXISTS "${IRRIMGUI_INCLUDE_DIR}/")
			message(SEND_ERROR "Irrlicht include path ${IRRIMGUI_INCLUDE_DIR} does not exist. Build example might not be possible...")
		endif ()

		# check if irrlicht library is in place
		if (NOT EXISTS "${IRRIMGUI_LIBRARY}")
			message(SEND_ERROR "Irrlicht library ${IRRIMGUI_LIBRARY} does not exist. Build example might not be possible...")
		endif ()

		# check if shared irrlicht library is in place if needed
		if (NOT IRRIMGUI_STATIC_LIBRARY)
			if(NOT EXISTS "${IRRIMGUI_SHARED_BIN}")
				message(SEND_ERROR "Irrlicht shared library ${IRRIMGUI_SHARED_BIN} does not exist. Build example might not be possible...")
			endif ()
		endif ()

		# check if media files are in place if they should be installed
		if (IRRIMGUI_INSTALL_MEDIA_FILES)
			if (NOT EXISTS "${IRRIMGUI_MEDIA_DIR}/")
				message(WARNING "Irrlicht media path ${IRRIMGUI_MEDIA_DIR} does not exist. Build example will not run without media files...")
			endif ()
		endif ()
				
	endif ()

	if (NOT "${APP_EXTRA_INCLUDES}" STREQUAL "")
		foreach( SINGLEINCLUDEPATH ${APP_EXTRA_INCLUDES} )
			if (NOT EXISTS "${SINGLEINCLUDEPATH}/")
				message(SEND_ERROR "Include path ${SINGLEINCLUDEPATH} does not exist. Build example might not be possible...")
			endif ()
		endforeach()
	endif ()
	
	if (NOT "${APP_EXTRA_LIBS}" STREQUAL "")
		foreach( SINGLELIB ${APP_EXTRA_LIBS} )
			if (NOT EXISTS "${SINGLELIB}")
				message(SEND_ERROR "Library ${SINGLELIB} does not exist. Build example might not be possible...")
			endif ()
		endforeach()	
	endif ()

ENDFUNCTION()

FUNCTION(BUILD_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCE_FILES EXAMPLE_HEADER_FILES EXAMPLE_INSTALL_FILES EXAMPLE_INSTALL_DIRS)
	BUILD_APP_GENERIC("${EXAMPLE_NAME}" "${EXAMPLE_SOURCE_FILES}" "${EXAMPLE_HEADER_FILES}" "${EXAMPLE_INSTALL_FILES}" "${EXAMPLE_INSTALL_DIRS}" FALSE "example/${EXAMPLE_NAME}" "" "" "" IRRIMGUI_INSTALL_EXAMPLE_SOURCE)
ENDFUNCTION()

FUNCTION(BUILD_WIN32_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCE_FILES EXAMPLE_HEADER_FILES EXAMPLE_INSTALL_FILES EXAMPLE_INSTALL_DIRS)
	BUILD_APP_GENERIC("${EXAMPLE_NAME}" "${EXAMPLE_SOURCE_FILES}" "${EXAMPLE_HEADER_FILES}" "${EXAMPLE_INSTALL_FILES}" "${EXAMPLE_INSTALL_DIRS}" TRUE "example/${EXAMPLE_NAME}" "" "" "" IRRIMGUI_INSTALL_EXAMPLE_SOURCE)
ENDFUNCTION()

FUNCTION(BUILD_TOOL TOOL_NAME TOOL_SOURCE_FILES TOOL_HEADER_FILES TOOL_INSTALL_FILES TOOL_INSTALL_DIRS)
	BUILD_APP_GENERIC("${TOOL_NAME}" "${TOOL_SOURCE_FILES}" "${TOOL_HEADER_FILES}" "${TOOL_INSTALL_FILES}" "${TOOL_INSTALL_DIRS}" FALSE "tools/${TOOL_NAME}" "" "" "" IRRIMGUI_INSTALL_EXAMPLE_SOURCE)
ENDFUNCTION()

FUNCTION(BUILD_UTEST TEST_NAME TEST_SOURCE_FILES TEST_HEADER_FILES TEST_INSTALL_FILES TEST_INSTALL_DIRS TEST_INCLUDES TEST_LIBRARIES TEST_INCLUDE_FILES)
	BUILD_APP_GENERIC("${TEST_NAME}" "${TEST_SOURCE_FILES}" "${TEST_HEADER_FILES}" "${TEST_INSTALL_FILES}" "${TEST_INSTALL_DIRS}" FALSE "tests/${TEST_NAME}" "${TEST_INCLUDES}" "${TEST_LIBRARIES}" "${TEST_INCLUDE_FILES}" FALSE)
ENDFUNCTION()
