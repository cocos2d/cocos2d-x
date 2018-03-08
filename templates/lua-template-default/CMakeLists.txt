#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
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

set(APP_NAME TemplateLua)

project(${APP_NAME})

set(RUNTIME_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/runtime-src)

if(NOT DEFINED BUILD_ENGINE_DONE)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    CocosBuildSet()
    if(NOT USE_COCOS_PREBUILT)
        set(BUILD_LUA_LIBS ON)
        set(USE_SIMULATOR ON)
        add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    endif()
endif()

# script and source files info, not need to compile
set(res_res_folders 
    "${CMAKE_CURRENT_SOURCE_DIR}/res" 
)
set(res_src_folders
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
set(res_script_folders
    "${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script"
)
if(APPLE OR VS)
    cocos_mark_multi_resources(res_res RES_TO "Resources/res" FOLDERS ${res_res_folders})
    cocos_mark_multi_resources(res_src RES_TO "Resources/src" FOLDERS ${res_src_folders})
    cocos_mark_multi_resources(res_script RES_TO "Resources/src/cocos" FOLDERS ${res_script_folders})
    set(cc_common_res ${res_res} ${res_src} ${res_script})
endif()

# sources need to compile info, include dirs and source files
include_directories(
    ${RUNTIME_SRC_ROOT}/Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
    ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include
    ${COCOS2DX_ROOT_PATH}/external/lua/tolua
    ${COCOS2DX_ROOT_PATH}/tools/simulator/libsimulator/lib
)
set(GAME_SRC ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp)
if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME cocos2dlua)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellolua/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
elseif(WINDOWS)
    add_definitions(-D_USRLUASTATIC -D_USRLIBSIMSTATIC)
    list(APPEND GAME_SRC
        ${RUNTIME_SRC_ROOT}/proj.win32/game.rc
        ${RUNTIME_SRC_ROOT}/proj.win32/stdafx.cpp
        ${RUNTIME_SRC_ROOT}/proj.win32/main.cpp
        ${RUNTIME_SRC_ROOT}/proj.win32/SimulatorWin.cpp
        ${cc_common_res}
    )
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
        set(APPLE_RES_UI ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(MAC_SRC
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/main.m
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/SimulatorApp.mm
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/ConsoleWindowController.m
        )
        file(GLOB_RECURSE RES_ICON ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Icon.icns)
        cocos_mark_resources(FILES ${RES_ICON} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
        # special for lua-template
        file(GLOB_RECURSE RES_MAIN_BASE ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Base.lproj/MainMenu.xib)
        cocos_mark_resources(FILES ${RES_MAIN_BASE} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
        file(GLOB_RECURSE RES_MAIN_EN ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/en.lproj/MainMenu.xib)
        cocos_mark_resources(FILES ${RES_MAIN_EN} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
        file(GLOB_RECURSE RES_MAIN_ZH ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/zh-Hans.lproj/MainMenu.xib)
        cocos_mark_resources(FILES ${RES_MAIN_ZH} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
        file(GLOB_RECURSE RES_CONSOLE ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/ConsoleWindow.xib)
        cocos_mark_resources(FILES ${RES_CONSOLE} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
        set(APPLE_SRC ${MAC_SRC} ${RES_ICON} ${RES_MAIN_BASE} ${RES_MAIN_EN} ${RES_MAIN_ZH} ${RES_CONSOLE})
        # xib -> nib, need mark resources
        set(APPLE_RES_UI ${RES_MAIN_BASE} ${RES_MAIN_EN} ${RES_MAIN_ZH} ${RES_CONSOLE})
    endif()
    list(APPEND GAME_SRC ${APPLE_SRC} ${cc_common_res})
else()
    message(FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

# mark app complie info and libs info
cocos_build_app(${APP_NAME} 
    APP_SRC "${GAME_SRC}"
    DEPEND_COMMON_LIBS "luacocos2d" "cocos2d"
    DEPEND_ANDROID_LIBS "cocos2d_android"
    DEPEND_MACOSX_LIBS "simulator"
    DEPEND_WINDOWS_LIBS "simulator"
)

# mark app resources
if(APPLE)
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
            RESOURCE "${APPLE_RES_UI}"
        )
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "MacOSXBundleInfo.LuaTemplate.plist.in" BUNDLE_NAME "LuaTestsApp")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
endif()
# copy resource on linux or WINDOWS
if(LINUX OR WINDOWS)
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR}/src/cocos FOLDERS ${res_script_folders})
endif()
