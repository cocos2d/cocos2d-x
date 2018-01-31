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

set(APP_NAME HelloJS)
if(ANDROID)
    set(APP_NAME cocos2djs)
endif(ANDROID)


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
    set(BUILD_JS_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif(NOT DEFINED BUILD_ENGINE_DONE)


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

if(ANDROID)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellojavascript/main.cpp)
elseif(LINUX)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
elseif(MACOSX)
    list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/main.cpp)

    file(GLOB_RECURSE RES_ICON ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac/Icon.icns)
    cocos_mark_resources(FILES ${RES_ICON} BASEDIR ${RUNTIME_SRC_ROOT}/proj.ios_mac/mac)
    # need review
    set(APP_MAIN
        main.js
        project.json
    )
    cocos_mark_resources(FILES ${APP_MAIN} BASEDIR ./ RESOURCEBASE Resources)
  
    file(GLOB_RECURSE APP_RESOURCES res/*)
    cocos_mark_resources(FILES ${APP_RESOURCES} BASEDIR res RESOURCEBASE Resources/res)
    file(GLOB_RECURSE APP_SCRIPTS src/*)
    cocos_mark_resources(FILES ${APP_SCRIPTS} BASEDIR src RESOURCEBASE Resources/src)
    file(GLOB_RECURSE COCOS_SCRIPTS ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script/*)
    cocos_mark_resources(FILES ${COCOS_SCRIPTS} BASEDIR ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script RESOURCEBASE Resources/script)
    
    list(APPEND GAME_SRC ${RES_ICON} ${APP_MAIN} ${APP_RESOURCES} ${APP_SCRIPTS} ${COCOS_SCRIPTS})
endif()

if(ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC})
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
else()
    add_executable(${APP_NAME}
        ${GAME_SRC}
    )
endif(ANDROID)

target_link_libraries(${APP_NAME} jscocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if(LINUX)
    set(RES_PREFIX "/Resources")
else()
    set(RES_PREFIX "")
endif()

if(MACOSX OR APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE 1
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    cocos_pak_macos()
# need cocos_mark_resources, when build on mac, refer to lua project
else(MACOSX OR APPLE)
    pre_build(${APP_NAME}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/script
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.js
        COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.json
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${APP_BIN_DIR}${RES_PREFIX}/res
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src ${APP_BIN_DIR}${RES_PREFIX}/src
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings/script ${APP_BIN_DIR}${RES_PREFIX}/script
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/main.js ${APP_BIN_DIR}${RES_PREFIX}/main.js
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/project.json ${APP_BIN_DIR}${RES_PREFIX}/project.json
        )

endif(MACOSX OR APPLE)
