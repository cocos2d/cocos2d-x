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

# default build, not build when build engine and all tests
if(NOT DEFINED BUILD_ENGINE_DONE)
    # define some variables
    # set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    # engine path changed, after cocos new
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()

    # add engine directory, get cocos library
    set(BUILD_LUA_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

endif(NOT DEFINED BUILD_ENGINE_DONE)

if(ANDROID)
  # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
  set(APP_NAME cocos2dlua)
endif(ANDROID)

set(GAME_SRC ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp
)

if(ANDROID)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellolua/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
elseif(APPLE)

    if(IOS)
        set(IOS_SRC
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/main.m
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/AppController.mm
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/RootViewController.mm
            )
        file(GLOB_RECURSE RES_LS ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreen.storyboard)
        cocos_mark_resources(FILES ${RES_LS} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios)
        file(GLOB_RECURSE RES_LSBG ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios/LaunchScreenBackground.png)
        cocos_mark_resources(FILES ${RES_LSBG} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/ios)
        set(APPLE_SRC ${IOS_SRC} ${RES_LS} ${RES_LSBG})
    elseif(MACOSX)
        set(MAC_SRC 
            ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/main.m
            # it needed tools/simulator, but not existed cmake files
            # ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/SimulatorApp.mm
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

    file(GLOB_RECURSE APP_RESOURCES res/*)
    cocos_mark_resources(FILES ${APP_RESOURCES} BASEDIR res RESOURCEBASE Resources/res)
    file(GLOB_RECURSE APP_SCRIPTS src/*)
    cocos_mark_resources(FILES ${APP_SCRIPTS} BASEDIR src RESOURCEBASE Resources/src)
    file(GLOB_RECURSE COCOS_SCRIPTS ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/*)
    cocos_mark_resources(FILES ${COCOS_SCRIPTS} BASEDIR ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script RESOURCEBASE Resources/src/cocos)
    
    list(APPEND GAME_SRC ${APPLE_SRC} ${APP_RESOURCES} ${APP_SCRIPTS} ${COCOS_SCRIPTS})
endif()

include_directories(
    ${RUNTIME_SRC_ROOT}/Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
    ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include
    ${COCOS2DX_ROOT_PATH}/external/lua/tolua
)

if(ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC})
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
else()
    # add the executable
    add_executable(${APP_NAME} ${GAME_SRC})
endif(ANDROID)

target_link_libraries(${APP_NAME} luacocos2d)

if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE 1
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
        RESOURCE "${APPLE_RES_UI}"
        )
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "MacOSXBundleInfo.LuaTemplate.plist.in" BUNDLE_NAME "LuaTestsApp")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
    
    pre_build(${APP_NAME}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${APP_BIN_DIR}/Resources/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src ${APP_BIN_DIR}/Resources/src
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/ ${APP_BIN_DIR}/Resources/src/cocos
        )

endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME} GROUPBASE ${RUNTIME_SRC_ROOT})
endif()
