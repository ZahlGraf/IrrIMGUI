CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

message(STATUS " -> Configure all examples:")

SET(IRRIMGUI_MEDIA_DIR   "${CMAKE_SOURCE_DIR}/../media" CACHE PATH "The directory where the media files are stored in.")

ADD_SUBDIRECTORY(01.HelloWorld)
ADD_SUBDIRECTORY(02.AnotherWindow)
ADD_SUBDIRECTORY(03.DifferentFonts)
ADD_SUBDIRECTORY(04.Images)
ADD_SUBDIRECTORY(05.DragNDrop)
ADD_SUBDIRECTORY(06.RenderWindow)
ADD_SUBDIRECTORY(Demo)

message(STATUS " ")

