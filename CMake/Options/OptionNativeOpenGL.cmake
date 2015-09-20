SET (IRRIMGUI_NATIVE_OPENGL OFF CACHE BOOL "Enables the native OpenGL Driver for IMGUI (ATTENTION: This is just a fallback solution!).")

if (IRRIMGUI_STATIC_LIBRARY)
	message(STATUS "Use native OpenGL render driver (Fallback solution, do not use it for productive work!)...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_NATIVE_OPENGL_
	)
else ()
	message(STATUS "Use Irrlicht based render driver...")
	INCLUDE(DependencyOpenGL)	
endif ()