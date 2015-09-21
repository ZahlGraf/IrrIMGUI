message(STATUS "Looking for Doxygen...")

find_package(Doxygen)

if (DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen Correctly Found:")
	
	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
	ADD_CUSTOM_TARGET(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
	
	INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/Doxygen DESTINATION  "." COMPONENT doc OPTIONAL)
	INSTALL(FILES ${CMAKE_SOURCE_DIR}/Doxygen/index.html DESTINATION "Doxygen" COMPONENT doc OPTIONAL)
	
else ()
    MESSAGE(STATUS "Doxygen missing: Cannot create documentation.")
	
endif ()