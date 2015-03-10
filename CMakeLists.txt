#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
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

project(COCOS2D-X)

# The version number
set(COCOS2D_X_VERSION 4.0alpha1)

# Specify the project cmake module path and include CocosBuildHelpers.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")
include(CocosBuildHelpers)

#===============================================================================
# CMake settings for entire project.

#set(CMAKE_USE_RELATIVE_PATHS TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# For multi-config IDE(e.g. VS, Xcode), set debug and release as default.
# Takes effect in xcode but not in VS, maybe is a CMake's bug.
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING ""
        FORCE
        )
endif()

if(NOT CMAKE_BUILD_TYPE)
    # For single config generator(e.g. Makefile), set release as default.
    if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
    endif()
endif()

#===============================================================================
# Include library target 'cocos2d'.
add_subdirectory("cocos")

# Include cpp tests.
option(BUILD_TESTS_CPP "Build Cocos2D cpp tests." ON)
if(BUILD_TESTS_CPP)
    add_subdirectory("tests/cpp-empty-test")
    add_subdirectory("tests/cpp-tests")
    if(COCOS_TARGET_SYSTEM_IOS)
        add_subdirectory("tests/game-controller-test")
    endif()
endif()

#===============================================================================
# Include library target 'luacocos2d'.
option(BUILD_LUA_COCOS2D "Build Cocos2D LUA binding libraries." ON)
if(BUILD_LUA_COCOS2D)
    add_subdirectory("cocos/scripting/lua-bindings")
endif()
# Include lua tests.
include(CMakeDependentOption)
CMAKE_DEPENDENT_OPTION(BUILD_TESTS_LUA
    "Build Cocos2D LUA binging tests, depends BUILD_TESTS_CPP."
    ON "BUILD_LUA_COCOS2D AND BUILD_TESTS_CPP"
    OFF
    )
if(BUILD_TESTS_LUA)
    add_subdirectory("tests/lua-empty-test/project")
    add_subdirectory("tests/lua-tests/project")
    if(COCOS_TARGET_SYSTEM_IOS)
        add_subdirectory("tests/lua-game-controller-test/project")
    endif()
endif()

#===============================================================================
# Include library target 'jscocos2d'.
option(BUILD_JS_COCOS2D "Build Cocos2D JavaScript binding libraries." ON)
if(BUILD_JS_COCOS2D)
    add_subdirectory("cocos/scripting/js-bindings")
endif()
CMAKE_DEPENDENT_OPTION(BUILD_TESTS_JS
    "Build Cocos2D JavaScript binging tests."
    ON "BUILD_JS_COCOS2D"
    OFF
    )
if(BUILD_TESTS_JS)
    add_subdirectory("tests/js-tests/project")
endif()

