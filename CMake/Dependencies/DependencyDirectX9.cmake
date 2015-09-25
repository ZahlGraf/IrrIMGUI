cmake_policy(SET CMP0007 NEW)
if(IRRIMGUI_LINK_TO_DIRECTX)
	if(WIN32)
		message(STATUS "Looking for DirectX9 header and library...")
		
		find_package(DirectX)
		
		if (DirectX9_FOUND)
			MESSAGE(STATUS "DirectX Correctly Found: ")
			MESSAGE(STATUS " * Include-Dir: ${DirectX9_INCLUDE_DIR}")
			MESSAGE(STATUS " * Libraries: ${DirectX9_LIBRARIES}")
			INCLUDE_DIRECTORIES("${DirectX9_INCLUDE_DIR}")
			SET(IRRIMGUI_DEPENDENCY_LIBRARIES
				${IRRIMGUI_DEPENDENCY_LIBRARIES}
				${DirectX9_LIBRARIES}
			)			
			
		else ()
			MESSAGE(SEND_ERROR "DirectX environment missing")
			
		endif ()
	
	else ()
		message(SEND_ERROR "Operating system does not support DirectX.")
		
	endif ()
endif ()

