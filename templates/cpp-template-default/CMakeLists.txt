#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME MyGame)
project (${APP_NAME})

# define some variables
# set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
# engine path changed, after cocos new
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})

# works before libcocos2d
include(CocosBuildSet)
CocosBuildSet()

# add engine directory, get cocos libiary
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua libiary")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js libiary")
add_subdirectory(${COCOS2DX_ROOT_PATH} ${ENGINE_BINARY_PATH}/cocos2dx)

if(ANDROID)
    set(PLATFORM_SPECIFIC_SRC proj.android/app/jni/hellocpp/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    set(PLATFORM_SPECIFIC_SRC proj.win32/main.cpp)
    set(PLATFORM_SPECIFIC_HEADERS
            proj.win32/main.h
            proj.win32/resource.h
            )
    set(RES_PREFIX "")
elseif(IOS)
    set(PLATFORM_SPECIFIC_SRC
            proj.ios_mac/ios/main.m
            proj.ios_mac/ios/AppController.mm
            proj.ios_mac/ios/RootViewController.mm
            )

elseif(MACOSX OR APPLE)
    set(PLATFORM_SPECIFIC_SRC proj.ios_mac/mac/main.cpp)
    
    set(MACOSX_BUNDLE_BUNDLE_NAME "\${PRODUCT_NAME}")
    set(MACOSX_BUNDLE_INFO_PLIST proj.ios_mac/mac/Info.plist)
    set(MACOSX_BUNDLE_ICON_FILE Icon)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER org.cocos2dx.hellocpp)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0)
    set(MACOSX_BUNDLE_BUNDLE_VERSION 1)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright © 2017. All rights reserved.")

    file(GLOB_RECURSE RES_FILES Resources/*)
    cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
    file(GLOB_RECURSE RES_ICON proj.ios_mac/mac/Icon.icns)
    cocos_mark_resources(FILES ${RES_ICON} BASEDIR proj.ios_mac/mac)

    list(APPEND PLATFORM_SPECIFIC_SRC ${RES_FILES} ${RES_ICON})

elseif(LINUX)
    set(PLATFORM_SPECIFIC_SRC proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(
	${COCOS2DX_ROOT_PATH}/cocos/audio/include/
	Classes
)

if (WINDOWS)
    include_directories(
        ${COCOS2DX_ROOT_PATH}/external/glfw3/include/${PLATFORM_FOLDER}
        ${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/gles/include/OGLES
    )
elseif (MACOSX OR APPLE)
    include_directories(
        ${COCOS2DX_ROOT_PATH}/external/glfw3/include/mac
    )
elseif(LINUX)
    include_directories(
        /usr/local/include/GLFW
        /usr/include/GLFW
    )
endif(WINDOWS)

set(GAME_SRC
    ${PLATFORM_SPECIFIC_SRC}
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
)

set(GAME_HEADERS
    ${PLATFORM_SPECIFIC_HEADERS}
    Classes/AppDelegate.h
    Classes/HelloWorldScene.h
)

# add the executable
if(ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC} ${GAME_HEADERS})
    IF(CMAKE_BUILD_TYPE STREQUAL "Release")
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
elseif(MSVC)
	add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS} proj.win32/game.rc)
else()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
endif()

target_link_libraries(${APP_NAME} cocos2d)


if(MSVC)

	set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${PLATFORM_FOLDER}/$<CONFIG>")

    #get our resources
    add_custom_command(TARGET ${APP_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR})
	    
    # create a list of dlls to copy
	file(GLOB THIRD_PARTY_DLLS
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/gles/prebuilt/glew32.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/zlib/prebuilt/zlib1.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/OggDecoder/prebuilt/libogg.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/OggDecoder/prebuilt/libvorbis.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/OggDecoder/prebuilt/libvorbisfile.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/MP3Decoder/prebuilt/libmpg123.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/OpenalSoft/prebuilt/OpenAL32.dll"
		"${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/icon/prebuilt/iconv.dll"
		"${COCOS2DX_ROOT_PATH}/external/tiff/prebuilt/${PLATFORM_FOLDER}/libtiff.dll"
	)
	
	list(SORT THIRD_PARTY_DLLS)

	# do the copying
	foreach( file_i ${THIRD_PARTY_DLLS})
		add_custom_command(TARGET ${APP_NAME} PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			${file_i} 
			${APP_BIN_DIR}
		)
	endforeach( file_i )

    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS"
									RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

elseif(MACOSX OR APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
            MACOSX_BUNDLE 1
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
            )

else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

    set_target_properties(${APP_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
            )

endif()
