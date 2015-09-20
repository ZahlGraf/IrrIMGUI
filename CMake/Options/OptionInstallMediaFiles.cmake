SET (IRRIMGUI_INSTALL_MEDIA_FILES ON CACHE BOOL "Installs the media files.")
SET(IRRIMGUI_MEDIA_DIR "${CMAKE_SOURCE_DIR}/media" CACHE PATH "The directory where the media files are stored in.")

if (IRRIMGUI_INSTALL_MEDIA_FILES)
	message(STATUS "Install media files...")
else ()
	message(STATUS "Do not install media files...")
endif ()