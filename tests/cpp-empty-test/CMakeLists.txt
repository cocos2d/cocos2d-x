#/****************************************************************************
# Copyright (c) 2015-2017 Chukong Technologies Inc.

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
cmake_minimum_required(VERSION 3.1)

set(APP_NAME cpp_empty_test)

project(${APP_NAME})

# default build, not build when build engine and all tests
if(NOT DEFINED BUILD_ENGINE_DONE)
    # define some variables
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()
    # add engine directory, get cocos library
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

endif(NOT DEFINED BUILD_ENGINE_DONE)

if(ANDROID)
    set(PLATFORM_SRC proj.android/app/jni/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    set(PLATFORM_SRC proj.win32/main.cpp)
    set(RES_PREFIX "")
elseif(APPLE)
    file(GLOB_RECURSE RES_FILES Resources/*)
    cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
    if(IOS)
        set(IOS_SRC
            proj.ios/main.m
            proj.ios/AppController.mm
            proj.ios/RootViewController.mm
        )
        file(GLOB_RECURSE RES_LS proj.ios/LaunchScreen.storyboard)
        cocos_mark_resources(FILES ${RES_LS} BASEDIR proj.ios)
        file(GLOB_RECURSE RES_LSBG proj.ios/LaunchScreenBackground.png)
        cocos_mark_resources(FILES ${RES_LSBG} BASEDIR proj.ios)
        set(APPLE_SRC ${IOS_SRC} ${RES_LS} ${RES_LSBG})
    elseif(MACOSX)
        set(MAC_SRC proj.mac/main.cpp)

        file(GLOB_RECURSE RES_ICON proj.mac/Icon.icns)
        cocos_mark_resources(FILES ${RES_ICON} BASEDIR proj.mac)
        set(APPLE_SRC ${MAC_SRC} ${RES_ICON})
    endif()
    set(PLATFORM_SRC ${RES_FILES} ${APPLE_SRC})

elseif(LINUX)
    set(PLATFORM_SRC proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(Classes)

set(SAMPLE_SRC
    ${PLATFORM_SRC}
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
)

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} cocos2d)
add_dependencies(${APP_NAME} cocos2d)

if(MSVC)

    #get our resources
    add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR})
    #get our dlls
    add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy
                      ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/gles/prebuilt/glew32.dll 
                      ${CMAKE_CURRENT_BINARY_DIR})

    add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy
                      ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/zlib/prebuilt/zlib1.dll 
                      ${CMAKE_CURRENT_BINARY_DIR}/Debug)

    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

elseif(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE 1
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "Cpp Empty Test")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
    
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
        )

endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
endif()