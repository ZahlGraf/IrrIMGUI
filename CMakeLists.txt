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

cmake_minimum_required(VERSION 2.6)
cmake_policy(VERSION 2.6)
	
PROJECT(IrrIMGUI)

SET(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} 
	${CMAKE_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/Dependencies
	${CMAKE_SOURCE_DIR}/CMake/Options
	${CMAKE_SOURCE_DIR}/CMake/Compiler
	${CMAKE_SOURCE_DIR}/CMake/Packages
	${CMAKE_SOURCE_DIR}/CMake/OperationSystems
)

# Contains a list of source files...
INCLUDE(Version)

# Contains a list of source files...
INCLUDE(SourceFiles)

# Compiler dependent settings
INCLUDE(CompilerMSVCLikeSettings)
INCLUDE(CompilerGccLikeSettings)

# OS dependent settings
INCLUDE(WindowsSettings)
INCLUDE(UnixSettings)

# Option dependent settings
INCLUDE(OptionStaticLib)
INCLUDE(OptionBuildExamples)
INCLUDE(OptionInstallMediaFiles)
INCLUDE(OptionIrrlichtDirectIncludes)
INCLUDE(OptionNativeOpenGL)

# Dependency related settings
INCLUDE(DependencyIMGUI)
INCLUDE(DependencyIrrlicht)
INCLUDE(DependencyOpenGL)
INCLUDE(DependencyDirectX9)
INCLUDE(DependencyDoxygen)

# Print all settings
INCLUDE(PrintSettings)

# Collect all source files
SET(ALL_HEADER_FILES
	${IRRIMGUI_PRIVATE_HEADER_FILES}
	${IRRIMGUI_PUBLIC_HEADER_FILES}
	${IMGUI_PUBLIC_HEADER_FILES}
	${IMGUI_PRIVATE_HEADER_FILES}
)

SET(ALL_SOURCE_FILES
	${IRRIMGUI_SOURCE_FILES}
	${IMGUI_SOURCE_FILES}
)

# Target settings
SET_SOURCE_FILES_PROPERTIES(ALL_HEADER_FILES
                            PROPERTIES HEADER_FILE_ONLY TRUE)
							
LIST(APPEND ALL_SOURCE_FILES ${ALL_HEADER_FILES})

# Cache back the flags (seems to be an error of cmake for msys makefile generator)
if (NOT CFLAG_WRITE_BACK)
	SET(CFLAG_WRITE_BACK TRUE CACHE BOOL "(do not change!)" FORCE)
	mark_as_advanced(FORCE CFLAG_WRITE_BACK)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "compile flags" FORCE)
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "compile flags" FORCE)
endif ()

# Create targets
if (IRRIMGUI_STATIC_LIBRARY)
	ADD_LIBRARY (IrrIMGUI ${ALL_SOURCE_FILES} )
else ()
	ADD_LIBRARY (IrrIMGUI SHARED ${ALL_SOURCE_FILES} )
	SET_TARGET_PROPERTIES(IrrIMGUI PROPERTIES COMPILE_DEFINITIONS "_IRRIMGUI_EXPORTS_;${IMGUI_API_VALUE};IRRLICHT_EXPORTS=1" )	
endif ()
SET_TARGET_PROPERTIES(IrrIMGUI PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${SOVERSION_STRING})

file(WRITE "${CMAKE_BINARY_DIR}/version.txt" "${VERSION_STRING}")

TARGET_LINK_LIBRARIES(IrrIMGUI ${IRRIMGUI_DEPENDENCY_LIBRARIES} ${OS_DEPENDENT_LIBRARIES})

INSTALL(TARGETS IrrIMGUI
	ARCHIVE DESTINATION  "lib" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
	LIBRARY DESTINATION  "lib" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
	RUNTIME DESTINATION  "bin" CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo
)

INSTALL(FILES ${IRRIMGUI_PUBLIC_HEADER_FILES} DESTINATION "includes/IrrIMGUI")
INSTALL(FILES ${IMGUI_PUBLIC_HEADER_FILES} DESTINATION "includes/IMGUI")
INSTALL(FILES ${CMAKE_BINARY_DIR}/version.txt DESTINATION ".")

if (IRRIMGUI_INSTALL_MEDIA_FILES)
	INSTALL(DIRECTORY ${IRRIMGUI_MEDIA_DIR} DESTINATION  ".")
	INSTALL(FILES ${IMGUI_FONTFILES} DESTINATION "media")
endif ()

if (IRRIMGUI_BUILD_EXAMPLES)
	SET(IRRIMGUI_LIB_FILE $<TARGET_LINKER_FILE_NAME:IrrIMGUI>)
	SET(IRRIMGUI_SHARED_FILE $<TARGET_FILE_NAME:IrrIMGUI>)

	SET(ZZZ_EXAMPLE_SINGLE_COMPILE OFF CACHE BOOL "(Do not set!) If this is enabled, cmake assumes that an example should be compiled for itself (This variable is set automatically, so do not set!).")
	mark_as_advanced(FORCE ZZZ_EXAMPLE_SINGLE_COMPILE)
	
	SET(IRRIMGUI_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" CACHE PATH "The include directory for IrrIMGUI headers.")
	mark_as_advanced(FORCE IRRIMGUI_INCLUDE_DIR)
	SET(IRRIMGUI_LIBRARY     "${CMAKE_CURRENT_BINARY_DIR}/${IRRIMGUI_LIB_FILE}" CACHE FILEPATH "The path to the IrrIMGUI library.")
	mark_as_advanced(FORCE IRRIMGUI_LIBRARY)
	if (NOT IRRIMGUI_STATIC_LIBRARY)
		SET(IRRIMGUI_SHARED_BIN  "${CMAKE_CURRENT_BINARY_DIR}/${IRRIMGUI_SHARED_FILE}" CACHE FILEPATH "The path to the IrrIMGUI shared library.")
		mark_as_advanced(FORCE IRRIMGUI_SHARED_BIN)
	endif ()
	
	ADD_SUBDIRECTORY(examples)

	if 	(ZZZ_EXAMPLE_SINGLE_COMPILE)
		message(SEND_ERROR "The variable ZZZ_EXAMPLE_SINGLE_COMPILE must not be set when compiling the IrrIMGUI library!")
	endif ()
endif ()

