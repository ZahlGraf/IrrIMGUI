INCLUDE_DIRECTORIES(
  includes
  )

SET (IRRIMGUI_PUBLIC_HEADER_FILES
	includes/IrrIMGUI/CCharFifo.h
	includes/IrrIMGUI/CIMGUIEventReceiver.h
	includes/IrrIMGUI/CIMGUIEventStorage.h
	includes/IrrIMGUI/CIMGUIHandle.h
	includes/IrrIMGUI/IrrIMGUI.h
	includes/IrrIMGUI/IrrIMGUIDebug.h
	includes/IrrIMGUI/SIMGUISettings.h
	includes/IrrIMGUI/IncludeIrrlicht.h
	includes/IrrIMGUI/IncludeIMGUI.h
	includes/IrrIMGUI/IrrIMGUIConfig.h
)

SET (IRRIMGUI_PRIVATE_HEADER_FILES
	source/COpenGLIMGUIDriver.h
	source/IIMGUIDriver.h
	source/IrrIMGUIDebug_priv.h
)

SET (IRRIMGUI_SOURCE_FILES
	source/CChannelBuffer.cpp
	source/CCharFifo.cpp
	source/CIMGUIEventReceiver.cpp
	source/CIMGUIHandle.cpp
	source/COpenGLIMGUIDriver.cpp
	source/IIMGUIDriver.cpp
)
