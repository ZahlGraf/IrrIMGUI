CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

message(STATUS " -> Configure all examples:")

SET(IRRIMGUI_MEDIA_DIR   "${CMAKE_SOURCE_DIR}/../media" CACHE PATH "The directory where the media files are stored in.")

ADD_SUBDIRECTORY(01.HelloWorld)

message(STATUS " ")

