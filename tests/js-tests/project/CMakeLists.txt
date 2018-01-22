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
    set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

    message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
    message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
    # works before libcocos2d
    include(CocosBuildSet)
    CocosBuildSet()

    # add engine directory, get cocos library
    set(BUILD_JS_LIBS ON)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH})
    
endif(NOT DEFINED BUILD_ENGINE_DONE)

if(WIN32)

elseif(ANDROID)
  set(PLATFORM_SRC
    proj.android/app/jni/main.cpp
  )
else()
  set(PLATFORM_SRC
    proj.linux/main.cpp
  )
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
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
  # add the executable
  add_executable(${APP_NAME}
    ${SAMPLE_SRC}
  )
endif(ANDROID)

target_link_libraries(${APP_NAME} jscocos2d)

if(LINUX)
  set(RES_PREFIX "/Resources")

else()
  set(RES_PREFIX "")
  set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

  set_target_properties(${APP_NAME} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

endif()

# need cocos_mark_resources, when build on mac, refer to lua project
if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

else(MACOSX OR APPLE)
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
endif(MACOSX OR APPLE)