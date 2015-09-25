SET (IRRIMGUI_NATIVE_OPENGL OFF CACHE BOOL "Enables the native OpenGL Driver for IMGUI (ATTENTION: This is just a fallback solution!).")

if (IRRIMGUI_NATIVE_OPENGL)
	message(STATUS "Use native OpenGL render driver (Fallback solution, do not use it for productive work!)...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_NATIVE_OPENGL_
	)
	SET (IRRIMGUI_FAST_OPENGL_TEXTURE_CREATION ON CACHE BOOL "Enables the fast OpenGL texture creation to translate a ITexture object to an OpenGL handle instead of creating a copy. This is a very instable hack. Disable this, when the example 7 (RenderWindow) fails.")	
else ()
	message(STATUS "Use Irrlicht based render driver...")
endif ()

if (IRRIMGUI_FAST_OPENGL_TEXTURE_CREATION)
	message(STATUS "Use fast OpenGL texture ID creation (fast but risky!)...")
	ADD_DEFINITIONS(	
	-D_IRRIMGUI_FAST_OPENGL_TEXTURE_HANDLE_
	)
else ()
	message(STATUS "Creaty texture copy for generating OpenGL texture IDs...")
endif ()

