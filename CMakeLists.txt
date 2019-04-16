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

# build engine library and all tests

cmake_minimum_required(VERSION 3.6)

project(Cocos2d-x)

# cocos2dx root path
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

# prevent in-source-build
include(PreventInSourceBuilds)
AssureOutOfSourceBuilds()

# works before build libcocos2d
include(CocosBuildSet)

# build options
option(BUILD_TESTS "Build tests" ON)

# default tests include lua, js test project, so we set those option on to build libs
set(BUILD_LUA_LIBS ON)
set(BUILD_JS_LIBS ON)

add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# prevent tests project to build "cocos2d-x/cocos" again
set(BUILD_ENGINE_DONE ON)
# add engine all tests project
if (BUILD_TESTS)
  add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-empty-test ${ENGINE_BINARY_PATH}/tests/cpp-empty-test)
  add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-tests ${ENGINE_BINARY_PATH}/tests/cpp-tests)
  add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/js-tests/project ${ENGINE_BINARY_PATH}/tests/js-tests)
  add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-empty-test/project ${ENGINE_BINARY_PATH}/tests/lua-empty-test)
  add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-tests/project ${ENGINE_BINARY_PATH}/tests/lua-test)
endif()
