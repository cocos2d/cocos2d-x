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

set(common_code_files
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
)

if(APPLE OR VS)
    set(res_res_folders 
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${res_res_folders})
endif()

if(ANDROID)
    set(platform_code_files proj.android/app/jni/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    set(WINDOWS_SRC proj.win32/main.cpp)
    set(platform_code_files ${cc_common_res} ${WINDOWS_SRC})
elseif(APPLE)
    if(IOS)
        set(ios_code_files
            proj.ios/main.m
            proj.ios/AppController.mm
            proj.ios/RootViewController.mm
        )
        set(ios_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreen.storyboard
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files proj.mac/main.cpp)
        set(mac_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()
        set(platform_code_files ${cc_common_res} ${apple_src_files})

elseif(LINUX)
    set(platform_code_files proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(Classes)

set(all_code_files
    ${platform_code_files}
    ${common_code_files}
)

if(ANDROID)
    add_library(${APP_NAME} SHARED ${all_code_files})
    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
else()
    # add the executable
    add_executable(${APP_NAME} ${all_code_files})
endif()

target_link_libraries(${APP_NAME} cocos2d)
add_dependencies(${APP_NAME} cocos2d)

if(MSVC)

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/$<CONFIG>")
    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR} FOLDERS ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

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