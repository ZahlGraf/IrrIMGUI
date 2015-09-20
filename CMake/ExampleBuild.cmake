SET(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} 
	${CMAKE_CURRENT_LIST_DIR}/Dependencies
	${CMAKE_CURRENT_LIST_DIR}/Options
)

FUNCTION(BUILD_APP_GENERIC APP_NAME APP_SOURCE_FILES APP_HEADER_FILES APP_INSTALL_FILES, APP_INSTALL_DIRS APP_IS_WIN32 APP_INSTALL_PATH)
	
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

	if (IRRIMGUI_INSTALL_EXAMPLE_SOURCE)
		SET(APP_INSTALL_FILES
			${APP_INSTALL_FILES}
			${ALL_APP_SOURCE_FILES}
		)
	endif ()
	
	# When the examples are build without irrlicht library, we need to apply the same settings like for irrlicht
	if (ZZZ_EXAMPLE_SINGLE_COMPILE)
		# Option dependent settings
		INCLUDE(OptionStaticLib)
		INCLUDE(OptionBuildExamples)
		INCLUDE(OptionInstallMediaFiles)
		INCLUDE(OptionIrrlichtDirectIncludes)
		INCLUDE(OptionNativeOpenGL)

		# Dependency related settings
		INCLUDE(DependencyIMGUI)
		INCLUDE(DependencyIrrlicht)

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
	TARGET_LINK_LIBRARIES(${APP_NAME} ${IRRIMGUI_LIBRARY} ${IRRIMGUI_DEPENDENCY_LIBRARIES})

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
		if (IRRLICHT_INSTALL_MEDIA_FILES)
			if (NOT EXISTS "${IRRIMGUI_MEDIA_DIR}/")
				message(WARNING "Irrlicht media path ${IRRIMGUI_MEDIA_DIR} does not exist. Build example will not run without media files...")
			endif ()
		endif ()
		
	endif ()

ENDFUNCTION()

FUNCTION(BUILD_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCE_FILES EXAMPLE_HEADER_FILES EXAMPLE_INSTALL_FILES, EXAMPLE_INSTALL_DIRS)
	BUILD_APP_GENERIC("${EXAMPLE_NAME}" "${EXAMPLE_SOURCE_FILES}" "${EXAMPLE_HEADER_FILES}" "${EXAMPLE_INSTALL_FILES}" "${EXAMPLE_INSTALL_DIRS}" FALSE "example/${EXAMPLE_NAME}")
ENDFUNCTION()

FUNCTION(BUILD_WIN32_EXAMPLE EXAMPLE_NAME EXAMPLE_SOURCE_FILES EXAMPLE_HEADER_FILES EXAMPLE_INSTALL_FILES, EXAMPLE_INSTALL_DIRS)
	BUILD_APP_GENERIC("${EXAMPLE_NAME}" "${EXAMPLE_SOURCE_FILES}" "${EXAMPLE_HEADER_FILES}" "${EXAMPLE_INSTALL_FILES}" "${EXAMPLE_INSTALL_DIRS}" TRUE "example/${EXAMPLE_NAME}")
ENDFUNCTION()

FUNCTION(BUILD_TOOL TOOL_NAME TOOL_SOURCE_FILES TOOL_HEADER_FILES TOOL_INSTALL_FILES, TOOL_INSTALL_DIRS)
	BUILD_APP_GENERIC("${TOOL_NAME}" "${TOOL_SOURCE_FILES}" "${TOOL_HEADER_FILES}" "${TOOL_INSTALL_FILES}" "${TOOL_INSTALL_DIRS}" FALSE "tools/${TOOL_NAME}")
ENDFUNCTION()
