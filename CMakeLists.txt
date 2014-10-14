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
project (Cocos2d-X)

# The version number
set(COCOS2D_X_VERSION 3.3.0-beta0)

include(cmake/BuildHelpers.CMakeLists.txt)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

message(${BUILDING_STRING})

option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
option(USE_BOX2D "Use box2d for physics library" OFF)
option(BUILD_STATIC "Build static libraries" ON)
option(DEBUG_MODE "Debug or release?" ON)
option(BUILD_EXTENSIONS "Build extension library" ON)
option(BUILD_EDITOR_SPINE "Build editor support for spine" ON)
option(BUILD_EDITOR_COCOSTUDIO "Build editor support for cocostudio" ON)
option(BUILD_EDITOR_COCOSBUILDER "Build editor support for cocosbuilder" ON)
option(BUILD_CPP_TESTS "Build TestCpp samples" ON)
option(BUILD_LUA_LIBS "Build lua libraries" ON)
option(BUILD_LUA_TESTS "Build TestLua samples" ON)

if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

set(CMAKE_C_FLAGS_DEBUG "-DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

# Compiler options
if(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
                  -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
                  -wd4514 -wd4056 -wd4996 -wd4099)
else()
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -std=c99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
  if(CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif(MSVC)

if(BUILD_STATIC)
 set (BUILD_TYPE STATIC)
else()
 set (BUILD_TYPE SHARED)
endif()

# Some macro definitions
if(WINDOWS)

  if(BUILD_STATIC)
    ADD_DEFINITIONS (-DCC_STATIC)
  else()
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
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
elseif ( CMAKE_SIZEOF_VOID_P EQUAL 4 )
  set(ARCH_DIR "32-bit")
else()
  message( FATAL_ERROR "Unsupported architecture, CMake will exit" )
endif()

include_directories(
  ${PLATFORM_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/deprecated
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/extensions
  ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# Specific Link Directories
if(LINUX)
  set(PLATFORM_LINK_DIR
    /usr/local/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/${PLATFORM_FOLDER}-specific/fmod/prebuilt/${ARCH_DIR}
  )
  set(PLATFORM_FOLDER_ARCH
      ${PLATFORM_FOLDER}/${ARCH_DIR}
  )
elseif(NOT MINGW)
  set(PLATFORM_FOLDER_ARCH
    ${PLATFORM_FOLDER}
  )
  set(PLATFORM_LINK_DIR
   ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw3/prebuilt/${PLATFORM_FOLDER_ARCH}
  )
endif()


# NB
# we need to return these to libraries to their official state rather than 
# having our custom cocos2d namespace so that we may use system versions if 
# the platform provides them. It is very important that this
# is done before we make prebuilt versions of these two libs

include_directories(

  ${CMAKE_CURRENT_SOURCE_DIR}/../external/unzip
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/xxhash

)

if(LINUX)

  find_package(GLFW3 REQUIRED)
  message( STATUS "GLFW3 dirs: ${GLFW3_INCLUDE_DIRS}")
  include_directories(${GLFW3_INCLUDE_DIRS})

endif(LINUX)


if(NOT MINGW)

  include_directories(

    ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2
    ${CMAKE_CURRENT_SOURCE_DIR}/external/chipmunk/include/chipmunk
    ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/jpeg/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/png/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/tiff/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/webp/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw3/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/websockets/include/${PLATFORM_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/curl/include/${PLATFORM_FOLDER}


    ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/include/${PLATFORM_FOLDER}/freetype2
  )

#todo: fix location of freetype includes for linux android on cocos prebuilt repo
#i.e we should not need to include an extra dir of /freetype2

  link_directories(
    ${PLATFORM_LINK_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/jpeg/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/tiff/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/webp/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/png/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/websockets/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/chipmunk/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/prebuilt/${PLATFORM_FOLDER_ARCH}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/curl/prebuilt/${PLATFORM_FOLDER_ARCH}

  )


endif()

# build for 3rd party libraries
if(LINUX)
add_subdirectory(external/Box2D)
add_subdirectory(external/unzip)
add_subdirectory(external/xxhash)
add_subdirectory(external/tinyxml2)
add_subdirectory(external/protobuf-lite)
endif()

# libcocos2d.a
add_subdirectory(cocos)

# build cpp tests
if(BUILD_CPP_TESTS)
  add_subdirectory(tests/cpp-empty-test)
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
