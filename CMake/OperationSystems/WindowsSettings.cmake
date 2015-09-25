
if (WIN32)						

	if (GCC_LIKE_COMPILER)
		SET (OS_DEPENDENT_LIBRARIES
			${OS_DEPENDENT_LIBRARIES}
			imm32.lib
		)	
		
		# The MingW compiler needs directx libraries if Irrlicht has DirectX support enabled
		SET(IRRIMGUI_LINK_TO_DIRECTX ON)
		
		if (IRRIMGUI_STATIC_LIBRARY)
			SET(CMAKE_CXX_FLAGS
				"${CMAKE_CXX_FLAGS} -static -lpthread -static-libgcc -static-libstdc++ "
			)
		endif ()
		
	endif ()
		
	SET (IMGUI_API_VALUE
		"IMGUI_API=__declspec(dllexport)"
	)
		
endif ()