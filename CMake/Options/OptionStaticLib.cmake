SET (IRRIMGUI_STATIC_LIBRARY OFF CACHE BOOL "Enabled static lib build (requires also static lib of Irrlicht!).")

if (IRRIMGUI_STATIC_LIBRARY)
	message(STATUS "Build static library...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_STATIC_LIB_
	)		
else ()
	message(STATUS "Build shared library...")
endif ()