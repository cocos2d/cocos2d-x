#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
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

cmake_minimum_required(VERSION 3.1)

set(APP_NAME TemplateJS)

project(${APP_NAME})

set(RUNTIME_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/runtime-src)

if(NOT DEFINED BUILD_ENGINE_DONE)
    # set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    CocosBuildSet()
    
    if(NOT USE_COCOS_PREBUILT_LIBS)
        set(USE_JSCOCOS2D ON)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif(NOT USE_COCOS_PREBUILT_LIBS)
endif()

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME cocos2djs)
endif(ANDROID)

include_directories(
    ${COCOS2DX_ROOT_PATH}
    ${COCOS2DX_ROOT_PATH}/cocos
    ${COCOS2DX_ROOT_PATH}/deprecated
    ${COCOS2DX_ROOT_PATH}/cocos/platform
    ${COCOS2DX_ROOT_PATH}/extensions
    ${COCOS2DX_ROOT_PATH}/external
    ${COCOS2DX_ROOT_PATH}/external/spidermonkey/include/${PLATFORM_FOLDER}
    ${COCOS2DX_ROOT_PATH}/cocos/editor-support
)

include_directories(${RUNTIME_SRC_ROOT}/Classes)

set(GAME_SRC ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp
)
if(APPLE OR VS)
    set(res_main_files
        "${CMAKE_CURRENT_SOURCE_DIR}/main.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/project.json" 
    )
    set(res_res_folders 
        "${CMAKE_CURRENT_SOURCE_DIR}/res" 
    )
    set(res_src_folders
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
    set(res_script_folders
        "${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script"
    )
    cocos_mark_multi_resources(res_main RES_TO "Resources" FILES ${res_main_files})
    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
    cocos_mark_multi_resources(res_script RES_TO "Resources/script" FOLDERS ${res_script_folders})
    set(cc_common_res ${res_main} ${res_res} ${res_src} ${res_script})
endif()

if(WINDOWS)
    set(WINDOWS_SRC ${RUNTIME_SRC_ROOT}/proj.win32/main.cpp)
    set(PLATFORM_SPECIFIC_HEADERS
        ${RUNTIME_SRC_ROOT}/proj.win32/main.h
        ${RUNTIME_SRC_ROOT}/proj.win32/resource.h
    )
    list(APPEND GAME_SRC ${WINDOWS_SRC} ${PLATFORM_SPECIFIC_HEADERS} ${cc_common_res})
elseif(ANDROID)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellojavascript/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
elseif(APPLE)
    if(IOS)
        set(ios_code_files
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/main.m
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/AppController.mm
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/RootViewController.mm
        )
        set(ios_res_files
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreen.storyboard
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/main.cpp)
        set(mac_res_files
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()
    
    list(APPEND GAME_SRC ${apple_src_files} ${cc_common_res})
endif()

# mark app complie info and libs info
cocos_mark_app(${APP_NAME} 
    APP_SRC "${GAME_SRC}"
    DEPEND_COMMON_LIBS "jscocos2d" "cocos2d"
    DEPEND_ANDROID_LIBS "cocos2d_android"
)

if(GEN_COCOS_PREBUILT_LIBS)
    add_dependencies(${APP_NAME} prebuilt_libs)
endif()

if(USE_COCOS_PREBUILT_LIBS)
    target_use_jscocos2d_depend_libs(${APP_NAME})
endif()

# mark app resources
if(APPLE)
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "LuaTestsApp")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(MSVC)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif()

if(LINUX OR MSVC)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR} FILES ${res_main_files})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/script FOLDERS ${res_script_folders})
endif()

