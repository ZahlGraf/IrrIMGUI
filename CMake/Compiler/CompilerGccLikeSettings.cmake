SET(GCC_LIKE_COMPILER OFF)
SET(IRRIMGUI_LINK_TO_DIRECTX OFF)
#cmake_policy(SET CMP0054 NEW)

if ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xClang")
	message(STATUS "Detect CLANG compiler and handle it like GCC...")
	SET(GCC_LIKE_COMPILER ON)
elseif ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xGNU")
	message(STATUS "Detect GCC compiler...")
	SET(GCC_LIKE_COMPILER ON)
elseif ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xIntel")
	if(UNIX)
		message(STATUS "Detect Intel compiler and handle it like GCC...")
		SET(GCC_LIKE_COMPILER ON)
	endif ()
endif ()

if (GCC_LIKE_COMPILER)
	SET (CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} -std=c++11"
	)
	
	INCLUDE(CheckCSourceCompiles)
	CHECK_C_SOURCE_COMPILES("
		#ifndef __x86_64__
		#error
		#endif
		
		int main(void) { return 0; }
		" 
		WITH_64BIT
		)

	if(WITH_64BIT)
		message(STATUS "Detect 64bit GCC like compiler...")
		SET(CMAKE_CL_64 TRUE CACHE BOOL "" FORCE)
		mark_as_advanced(CMAKE_CL_64)
	else()
		message(STATUS "Detect 32bit GCC like compiler...")
		SET(CMAKE_CL_64 FALSE CACHE BOOL "" FORCE)
		mark_as_advanced(CMAKE_CL_64)
	endif()
				
endif ()

