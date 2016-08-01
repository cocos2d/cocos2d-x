#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015 Chukong Technologies Inc.
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

project (Cocos2d-X)

# The version number
set(COCOS2D_X_VERSION 3.13)

# define some variables

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")
set(COCOS_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}/deprecated
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/extensions
  ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(USE_PREBUILT_LIBS)
  include(CocosUsePrebuiltLibs)
endif()

include(BuildModules)
BuildModules()

# build cpp-empty-test
if(BUILD_CPP_EMPTY_TEST)
  add_subdirectory(tests/cpp-empty-test)
endif(BUILD_CPP_EMPTY_TEST)

# build cpp-tests
if(BUILD_CPP_TESTS)
  add_subdirectory(tests/cpp-tests)
endif(BUILD_CPP_TESTS)

## Scripting
if(BUILD_LUA_LIBS)
    add_subdirectory(cocos/scripting/lua-bindings)

  # build lua tests
  if(BUILD_LUA_TESTS)
    add_subdirectory(tests/lua-tests/project)
    add_subdirectory(tests/lua-empty-test/project)
  endif(BUILD_LUA_TESTS)

endif(BUILD_LUA_LIBS)

## JS
if(BUILD_JS_LIBS)
  add_subdirectory(cocos/scripting/js-bindings)

  # build js tests
  if(BUILD_JS_TESTS)
    add_subdirectory(tests/js-tests/project)
  endif(BUILD_JS_TESTS)

endif(BUILD_JS_LIBS)
