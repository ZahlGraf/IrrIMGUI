SET (IRRIMGUI_IRRLICHT_DIRECT_INCLUDES ON CACHE BOOL "Enables this option when Irrlicht headers are NOT in a subdirectory called Irrlicht.")

if (IRRIMGUI_IRRLICHT_DIRECT_INCLUDES)
	message(STATUS "Will use <irrlicht.h> for include irrlicht...")
else ()
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_SUBDIR_IRRLICHT_INCLUDE_
	)	
	message(STATUS "Will use <Irrlicht/irrlicht.h> for include irrlicht...")
endif ()