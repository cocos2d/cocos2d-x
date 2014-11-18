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
set(COCOS2D_X_VERSION 3.3.0-rc1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(CocosBuildHelpers)

message(${BUILDING_STRING})

set(USE_WEBP_DEFAULT ON)
if(WINRT OR WP8)
    set(USE_WEBP_DEFAULT OFF)
endif()

option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
option(USE_BOX2D "Use box2d for physics library" OFF)
option(USE_WEBP "Use WebP codec" ${USE_WEBP_DEFAULT})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(DEBUG_MODE "Debug or release?" ON)
option(BUILD_EXTENSIONS "Build extension library" ON)
option(BUILD_EDITOR_SPINE "Build editor support for spine" ON)
option(BUILD_EDITOR_COCOSTUDIO "Build editor support for cocostudio" ON)
option(BUILD_EDITOR_COCOSBUILDER "Build editor support for cocosbuilder" ON)
option(BUILD_CPP_TESTS "Build TestCpp samples" ON)
option(BUILD_LUA_LIBS "Build lua libraries" ON)
option(BUILD_LUA_TESTS "Build TestLua samples" ON)

option(USE_PREBUILT_LIBS "Use prebuilt libraries in external directory" ON)

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

set(COCOS_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Some macro definitions
if(WINDOWS)

  if(BUILD_SHARED_LIBS)
    ADD_DEFINITIONS (-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
  else()
    ADD_DEFINITIONS (-DCC_STATIC)
  endif()

  ADD_DEFINITIONS (-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32)
  set(PLATFORM_FOLDER win32)
elseif(MACOSX OR APPLE)
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
  #add_definitions(-DGLEW_STATIC)
  add_definitions(-D__SSIZE_T)

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
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/deprecated
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/extensions
  ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(LINUX)
  find_package(FMODEX REQUIRED)
  message(STATUS "FMOD Ex include dirs: ${FMODEX_INCLUDE_DIRS}")
endif()

# GLFW3 used on Mac, Windows and Linux desktop platforms
if(LINUX OR MACOSX OR WINDOWS)
  find_package(OpenGL REQUIRED)
  set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR}) # fix inconsistency
  message(STATUS "OpenGL include dirs: ${OPENGL_INCLUDE_DIRS}")

  if(LINUX OR WINDOWS)
    find_package(GLEW REQUIRED)
    message(STATUS "GLEW libs: ${GLEW_LIBRARIES}")
  endif()

  find_package(GLFW3 REQUIRED)
  message(STATUS "GLFW3 include dirs: ${GLFW3_INCLUDE_DIRS}")
  include_directories(${GLFW3_INCLUDE_DIRS})

  if(WINDOWS)
    if(USE_PREBUILT_LIBS)
        set(VORBIS_PREBUILT_ROOT ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/OggDecoder)
        list(APPEND CMAKE_INCLUDE_PATH ${VORBIS_PREBUILT_ROOT}/include)
        list(APPEND CMAKE_LIBRARY_PATH ${VORBIS_PREBUILT_ROOT}/prebuilt)
    endif()
    find_package(Vorbis REQUIRED)
    message(STATUS "Vorbis include dirs: ${VORBIS_INCLUDE_DIRS}")

    if(USE_PREBUILT_LIBS)
        list(APPEND CMAKE_INCLUDE_PATH ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/MP3Decoder/include)
        list(APPEND CMAKE_LIBRARY_PATH ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/MP3Decoder/prebuilt)
    endif()
    find_package(MPG123 REQUIRED)
    message(STATUS "MPG123 include dirs: ${MPG123_INCLUDE_DIRS}")

    if(USE_PREBUILT_LIBS)
        set(OPENAL_PREBUILT_ROOT ${COCOS_EXTERNAL_DIR}/${PLATFORM_FOLDER}-specific/OpenalSoft)
        list(APPEND CMAKE_INCLUDE_PATH ${OPENAL_PREBUILT_ROOT})
        list(APPEND CMAKE_LIBRARY_PATH ${OPENAL_PREBUILT_ROOT}/prebuilt)
    endif()
    find_package(OpenAL REQUIRED)
    set(OPENAL_INCLUDE_DIRS ${OPENAL_INCLUDE_DIR})
    set(OPENAL_LIBRARIES ${OPENAL_LIBRARY})
    # because FindOpenAL.cmake set include dir for '#include <al.h>' for portability (not for '#include <AL/al.h>'
    set(OPENAL_DEFINITIONS "-DOPENAL_PLAIN_INCLUDES")
    message(STATUS "OpenAL include dirs: ${OPENAL_INCLUDE_DIRS}")
  endif()
endif(LINUX OR MACOSX OR WINDOWS)

# Freetype required on all platforms
find_package(Freetype REQUIRED)
message(STATUS "FreeType include dirs: ${FREETYPE_INCLUDE_DIRS}")
include_directories(${FREETYPE_INCLUDE_DIRS})

# WebP required if used
if(USE_WEBP)
  find_package(WebP REQUIRED)
  message(STATUS "WebP include dirs: ${WEBP_INCLUDE_DIRS}")
endif(USE_WEBP)

# Chipmunk
if(USE_CHIPMUNK)
  find_package(Chipmunk REQUIRED)
  message(STATUS "Chipmunk include dirs: ${CHIPMUNK_INCLUDE_DIRS}")
  add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
  if(IOS OR MACOSX)
    # without this chipmunk will try to use apple defined geometry types, that conflicts with cocos
    add_definitions(-DCP_USE_CGPOINTS=0)
  endif()
else(USE_CHIPMUNK)
  add_definitions(-DCC_USE_PHYSICS=0)
endif(USE_CHIPMUNK)

# Box2d (not prebuilded, exists as source)
if(USE_BOX2D)
  if(USE_PREBUILT_LIBS)
    add_subdirectory(external/Box2D)
    set(Box2D_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include)
    set(Box2D_LIBRARIES box2d)
  else()
    find_package(Box2D REQUIRED CONFIG)
    # actually Box2D in next line is not a library, it is target exported from Box2DConfig.cmake
    set(Box2D_LIBRARIES Box2D)
  endif()
  message(STATUS "Box2D include dirs: ${Box2D_INCLUDE_DIRS}")
  add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
else()
  add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=0)
endif(USE_BOX2D)

# Tinyxml2 (not prebuilded, exists as source)
if(USE_PREBUILT_LIBS)
  add_subdirectory(external/tinyxml2)
  set(TinyXML2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2)
  set(TinyXML2_LIBRARIES tinyxml2)
else()
  find_package(TinyXML2)
endif()
message(STATUS "TinyXML2 include dirs: ${TinyXML2_INCLUDE_DIRS}")

# libjpeg
find_package(JPEG REQUIRED)
message(STATUS "JPEG include dirs: ${JPEG_INCLUDE_DIRS}")

find_package(ZLIB REQUIRED)
message(STATUS "ZLIB include dirs: ${ZLIB_INCLUDE_DIRS}")

# minizip (we try to migrate to minizip from https://github.com/nmoinvaz/minizip)
# only msys2 currently provides package for this variant, all other
# dists have packages from zlib, thats very old for us.
# moreover our embedded version modified to quick provide
# functionality needed by cocos.
if(USE_PREBUILT_LIBS OR NOT MINGW)
  add_subdirectory(external/unzip)
  set(MINIZIP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/unzip)
  set(MINIZIP_LIBRARIES unzip)
else()
  find_package(MINIZIP REQUIRED)
  # double check that we have needed functions
  include(CheckLibraryExists)
  check_library_exists(${MINIZIP_LIBRARIES} "unzGoToFirstFile2" "" MINIZIP_HAS_GOTOFIRSTFILE2)
  if(NOT MINIZIP_HAS_GOTOFIRSTFILE2)
    message(FATAL_ERROR "Minizip library on you system very old. Please use recent version from https://github.com/nmoinvaz/minizip or enable USE_PREBUILT_LIBS")
  endif()
  add_definitions(-DMINIZIP_FROM_SYSTEM)
endif()
message(STATUS "MINIZIP include dirs: ${MINIZIP_INCLUDE_DIRS}")

find_package(PNG REQUIRED)
message(STATUS "PNG include dirs: ${PNG_INCLUDE_DIRS}")

find_package(TIFF REQUIRED)
message(STATUS "TIFF include dirs: ${TIFF_INCLUDE_DIRS}")

find_package(WEBSOCKETS REQUIRED)
message(STATUS "WEBSOCKETS include dirs: ${WEBSOCKETS_INCLUDE_DIRS}")

find_package(CURL REQUIRED)
message(STATUS "CURL include dirs: ${CURL_INCLUDE_DIRS}")

# protobuf-lite (not prebuilded, exists as source)
# TODO: for now we can't use upstream protobuf because these files:
#  cocos/editor-support/cocostudio/CSParseBinary.pb.h
#  cocos/editor-support/cocostudio/CSParseBinary.pb.cc
# was generated by concrete version of protobuf compiler
# and source file not provided. So these files can be
# compiled only with our in-source version of protobuf-lite
## if(USE_PREBUILT_LIBS)
  add_subdirectory(external/protobuf-lite)
  set(PROTOBUF_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/protobuf-lite/src)
  set(PROTOBUF_LITE_LIBRARIES protobuf)
## else()
##  find_package(Protobuf REQUIRED PROTOBUF_LITE_LIBRARIES)
## endif()
message(STATUS "Protobuf lite libs: ${PROTOBUF_LITE_LIBRARIES}")
message(STATUS "Protobuf include dirs: ${PROTOBUF_INCLUDE_DIRS}")


# build for 3rd party libraries
if(LINUX OR APPLE)
add_subdirectory(external/xxhash)
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
