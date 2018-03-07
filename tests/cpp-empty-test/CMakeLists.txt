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

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    CocosBuildSet()
    if(NOT USE_COCOS_PREBUILT)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif()
endif()

set(common_code_files
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
)

set(res_res_folders 
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
)
if(APPLE OR VS)
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${res_res_folders})
endif()

if(ANDROID)
    set(platform_specific_src proj.android/app/jni/main.cpp)
elseif(LINUX)
    set(platform_specific_src proj.linux/main.cpp)
elseif(WINDOWS)
    set(windows_src proj.win32/main.cpp)
    set(platform_specific_src ${cc_common_res} ${windows_src})
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
        set(platform_specific_src ${cc_common_res} ${apple_src_files})
else()
    message(FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

include_directories(Classes)

set(all_code_files
    ${platform_specific_src}
    ${common_code_files}
)

# mark app complie info and libs info
cocos_build_app(${APP_NAME} 
    APP_SRC "${all_code_files}"
    DEPEND_COMMON_LIBS "cocos2d"
    DEPEND_ANDROID_LIBS "cocos2d_android"
)

# mark app resources
if(APPLE)
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "Cpp Empty Test")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif()

if(LINUX OR WINDOWS)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${res_res_folders})
endif()
