#/****************************************************************************
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

set(APP_NAME js_tests)

project(${APP_NAME})

# default build, not build when build engine and all tests
if(NOT DEFINED BUILD_ENGINE_DONE)
    # define some variables
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()
    # add engine directory, get cocos library
    set(BUILD_JS_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
    
endif(NOT DEFINED BUILD_ENGINE_DONE)

if(APPLE OR VS)
    set(res_main_files
        "${CMAKE_CURRENT_SOURCE_DIR}/../main.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/../project.json" 
    )
    set(res_res_folders 
        "${CMAKE_CURRENT_SOURCE_DIR}/../resjs" 
        "${CMAKE_CURRENT_SOURCE_DIR}/../res" 
        "${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources"
    )
    set(res_src_folders
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
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

if(WIN32)
    set(WINDOWS_SRC proj.win32/main.cpp)
    set(RES_PREFIX "")
    set(PLATFORM_SRC ${cc_common_res} ${WINDOWS_SRC})
elseif(ANDROID)
    set(PLATFORM_SRC
        proj.android/app/jni/main.cpp
        )
elseif(LINUX)
    set(PLATFORM_SRC
        proj.linux/main.cpp
        )
elseif(APPLE)

    if(IOS)
        set(ios_code_files
            proj.ios/main.m
            proj.ios/NativeOcClass.m
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

    set(PLATFORM_SRC ${cc_common_res} ${apple_src_files})
endif()

set(SAMPLE_SRC
    Classes/AppDelegate.cpp
    Classes/js_DrawNode3D_bindings.cpp
    Classes/js_Effect3D_bindings.cpp
    ${PLATFORM_SRC}
    )

include_directories(
    Classes
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/auto
    ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/manual
    ${COCOS2DX_ROOT_PATH}/cocos/base
    ${COCOS2DX_ROOT_PATH}/cocos/editor-support
    ${COCOS2DX_ROOT_PATH}/cocos/audio/include
    ${COCOS2DX_ROOT_PATH}/external/spidermonkey/include/${PLATFORM_FOLDER}
    ${COCOS2DX_ROOT_PATH}/external/chipmunk/include/chipmunk
    )

if(ANDROID)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})
    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
else()
    # add the executable
    add_executable(${APP_NAME}
        ${SAMPLE_SRC}
    )
endif()

target_link_libraries(${APP_NAME} jscocos2d)
add_dependencies(${APP_NAME} jscocos2d)

if(LINUX)
    set(RES_PREFIX "/Resources")

else()
    set(RES_PREFIX "")
endif()

if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE 1
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "JS Tests")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
elseif(MSVC)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/$<CONFIG>")
    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR} FILES ${res_main_files})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/res FOLDERS ${res_res_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/src FOLDERS ${res_src_folders})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR}/script FOLDERS ${res_script_folders})
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")
    set_target_properties(${APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/script
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.js
        COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.json
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../resjs ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../../cocos/scripting/js-bindings/script ${APP_BIN_DIR}${RES_PREFIX}/script
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../main.js ${APP_BIN_DIR}${RES_PREFIX}/main.js
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../project.json ${APP_BIN_DIR}${RES_PREFIX}/project.json
        )
endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
endif()