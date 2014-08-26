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

cmake_minimum_required(VERSION 2.8)
project (Cocos2dx)

# The version number
set(Cocos2dxSamples_VERSION_MAJOR 3)
set(Cocos2dxSamples_VERSION_MINOR 1)

include(build/BuildHelpers.CMakeLists.txt)

message(${BUILDING_STRING})

if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

set(CMAKE_C_FLAGS_DEBUG "-DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

if(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
endif(MSVC)

if(WINDOWS)
  ADD_DEFINITIONS (-D_USRDLL -DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX)
  set(PLATFORM_FOLDER mac)
else(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
endif()

if(MINGW)
  add_definitions(-DGLEW_STATIC)
  add_definitions(-D__SSIZE_T)
  set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lws2_32")
  set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lws2_32")

  if(CLANG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions ")
  endif()
endif()

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

include_directories(
  /usr/include
  /usr/include/GLFW
  /usr/local/include/GLFW
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/platform/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/extensions
  ${CMAKE_CURRENT_SOURCE_DIR}/external
)

link_directories(
  /usr/local/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/external/jpeg/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/tiff/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/webp/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/png/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/websockets/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/external/${PLATFORM_FOLDER}-specific/fmod/prebuilt/${ARCH_DIR}
)

# libcocos2d.a
add_subdirectory(cocos)

## Scripting
add_subdirectory(cocos/scripting/lua-bindings)

# build tests
add_subdirectory(tests/cpp-empty-test)
add_subdirectory(tests/cpp-tests)

add_subdirectory(tests/lua-tests/project)
add_subdirectory(tests/lua-empty-test/project)
