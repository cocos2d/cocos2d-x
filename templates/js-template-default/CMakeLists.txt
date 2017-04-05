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
# It ensures that when Find*.cmake files included from cmake's Modules dir
# include another *.cmake file with relative path, that file will be included
# also from cmake's Modules dir, to not clash with per-project files.
cmake_policy(SET CMP0017 NEW)

# Use new behaviour with cmake >= 3.1:
# Only interpret if() arguments as variables or keywords when unquoted.
if(CMAKE_VERSION VERSION_GREATER 3.1)
    cmake_policy(SET CMP0054 NEW)
endif()

set(APP_NAME MyGame)
project (${APP_NAME})

# define some variables
set(COCOS2D_X_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
set(RUNTIME_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/runtime-src)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_X_ROOT}/cmake/Modules/")
set(COCOS_EXTERNAL_DIR ${COCOS2D_X_ROOT}/external)
# architecture
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH_DIR "64-bit")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(ARCH_DIR "32-bit")
else()
  message(FATAL_ERROR "Unsupported architecture, CMake will exit")
  return()
endif()
# CMAKE_BUILD_TYPE has precedence over DEBUG_MODE
# Still supporting DEBUG_MODE for backwards compatibility
if (NOT CMAKE_BUILD_TYPE)
  if(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE DEBUG)
  else(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE RELEASE)
  endif(DEBUG_MODE)
endif(NOT CMAKE_BUILD_TYPE)

include(CocosBuildHelpers)

message(${BUILDING_STRING})

# SelectModule() is a macro to select building modules
include(SelectModule)
SelectModule()

# set compiler options
include(SetCompilerOptions)
SetCompilerOptions()

if (CMAKE_FIND_ROOT_PATH AND USE_PREBUILT_LIBS)
  # Adds cocos2d-x external folder to the list of valid include/library paths when cross-compiling and using prebuilds
  set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} ${COCOS_EXTERNAL_DIR})
endif ()

include_directories(
  ${COCOS2D_X_ROOT}
  ${COCOS2D_X_ROOT}/cocos
  ${COCOS2D_X_ROOT}/deprecated
  ${COCOS2D_X_ROOT}/cocos/platform
  ${COCOS2D_X_ROOT}/extensions
  ${COCOS2D_X_ROOT}/external
  ${COCOS2D_X_ROOT}/external/spidermonkey/include/${PLATFORM_FOLDER}
  ${COCOS2D_X_ROOT}/cocos/editor-support
)

if(USE_PREBUILT_LIBS)
  include(CocosUsePrebuiltLibs)
endif()

set(PREV_CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CURRENT_SOURCE_DIR ${COCOS2D_X_ROOT})
include(BuildModules)
BuildModules()
set(CMAKE_CURRENT_SOURCE_DIR ${PREV_CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
else()
  set(GAME_SRC
    ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp
    ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp
  )
endif()


# jsbinding library
add_subdirectory(${COCOS2D_X_ROOT}/cocos/scripting/js-bindings)

add_executable(${APP_NAME}
  ${GAME_SRC}
)

target_link_libraries(${APP_NAME}
  jscocos2d
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if(LINUX)
  set(RES_PREFIX "/Resources")
else()
  set(RES_PREFIX "")
endif()

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/script
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/src
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.js
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.json
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src ${APP_BIN_DIR}${RES_PREFIX}/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2D_X_ROOT}/cocos/scripting/js-bindings/script ${APP_BIN_DIR}${RES_PREFIX}/script
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/main.js ${APP_BIN_DIR}${RES_PREFIX}/main.js
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/project.json ${APP_BIN_DIR}${RES_PREFIX}/project.json
  )

