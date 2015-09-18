#/****************************************************************************
# Copyright (c) 2014 Chukong Technologies Inc.
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

set(APP_NAME MyGame)
project (${APP_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cmake/Modules/")
include(CocosBuildHelpers)

option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
option(DEBUG_MODE "Debug or release?" ON)
option(BUILD_EXTENSIONS "Build extension library" ON)
option(BUILD_EDITOR_SPINE "Build editor support for spine" ON)
option(BUILD_EDITOR_COCOSTUDIO "Build editor support for cocostudio" ON)
option(BUILD_EDITOR_COCOSBUILDER "Build editor support for cocosbuilder" ON)
option(USE_PREBUILT_LIBS "Use prebuilt libraries in external directory" ON)


if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

set(CMAKE_C_FLAGS_DEBUG "-DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

if(WIN32)
  ADD_DEFINITIONS (-D_USRDLL -DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32)

  if(MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS 
					-D_SCL_SECURE_NO_WARNINGS 
					-wd4251 -wd4244 -wd4334 
					-wd4005 -wd4820 -wd4710
					-wd4514 -wd4056 -wd4996 -wd4099)
  else(MSVC)#MINGW
  
  endif(MSVC)
elseif(APPLE)


else()#Linux
ADD_DEFINITIONS(-DLINUX -DCC_RESOURCE_FOLDER_LINUX="/")
endif()


if(NOT MSVC)# all gcc
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c99")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
endif()

if(MINGW)
  add_definitions(-DGLEW_STATIC)
endif()


if(USE_CHIPMUNK)
  message("Using chipmunk ...")
  add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
elseif(USE_BOX2D)
  message("Using box2d ...")
  add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
else(USE_CHIPMUNK)
  message(FATAL_ERROR "Must choose a physics library.")
endif(USE_CHIPMUNK)

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

if(WIN32) # Win32
  set(PLATFORM_FOLDER win32)
elseif(APPLE)# osx or ios
  set(PLATFORM_FOLDER mac)
else() # Assume Linux
  set(PLATFORM_FOLDER linux)
endif()

set(COCOS_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/base
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/2d
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/ui
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/audio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/storage
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/network
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/editor-support
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/editor-support/spine
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/editor-support/cocosbuilder
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/editor-support/cocostudio
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/deprecated
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/extensions
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external/chipmunk/include/chipmunk
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external/spidermonkey/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/scripting/js-bindings/auto
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/scripting/js-bindings/manual
)

link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external/spidermonkey/prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
)


if(USE_PREBUILT_LIBS)
  include(CocosUsePrebuiltLibs)
endif()

# GLFW3 used on Mac, Windows and Linux desktop platforms
if(LINUX OR MACOSX OR WINDOWS)
  cocos_find_package(OpenGL OPENGL REQUIRED)

  if(LINUX OR WINDOWS)
    cocos_find_package(GLEW GLEW REQUIRED)
  endif()

  cocos_find_package(GLFW3 GLFW3 REQUIRED)
  include_directories(${GLFW3_INCLUDE_DIRS})

  if(LINUX)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_package(Threads REQUIRED)
    set(THREADS_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

    #cocos_find_package(FMODEX FMODEX REQUIRED)
    cocos_find_package(Fontconfig FONTCONFIG REQUIRED)
  endif()

  if(WINDOWS)
    cocos_find_package(Vorbis VORBIS REQUIRED)
    cocos_find_package(MPG123 MPG123 REQUIRED)
    cocos_find_package(OpenAL OPENAL REQUIRED)
    # because FindOpenAL.cmake set include dir for '#include <al.h>' for portability (not for '#include <AL/al.h>'
    set(OPENAL_DEFINITIONS "-DOPENAL_PLAIN_INCLUDES")
  endif()
endif(LINUX OR MACOSX OR WINDOWS)

# Freetype required on all platforms
cocos_find_package(Freetype FREETYPE REQUIRED)

# WebP required if used
if(USE_WEBP)
  cocos_find_package(WebP WEBP REQUIRED)
endif(USE_WEBP)

# Chipmunk
if(USE_CHIPMUNK)
  cocos_find_package(Chipmunk CHIPMUNK REQUIRED)
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
    add_subdirectory(frameworks/cocos2d-x/external/Box2D)
    set(Box2D_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/js-bindings/cocos2d-x/external/box2d/include)
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
  add_subdirectory(frameworks/cocos2d-x/external/tinyxml2)
  set(TinyXML2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external/tinyxml2)
  set(TinyXML2_LIBRARIES tinyxml2)
else()
  cocos_find_package(TinyXML2 TinyXML2 REQUIRED)
endif()
message(STATUS "TinyXML2 include dirs: ${TinyXML2_INCLUDE_DIRS}")

# libjpeg
cocos_find_package(JPEG JPEG REQUIRED)
cocos_find_package(ZLIB ZLIB REQUIRED)

# minizip (we try to migrate to minizip from https://github.com/nmoinvaz/minizip)
# only msys2 currently provides package for this variant, all other
# dists have packages from zlib, thats very old for us.
# moreover our embedded version modified to quick provide
# functionality needed by cocos.
if(USE_PREBUILT_LIBS OR NOT MINGW)
  add_subdirectory(frameworks/cocos2d-x/external/unzip)
  set(MINIZIP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/external/unzip)
  set(MINIZIP_LIBRARIES unzip)
  message(STATUS "MINIZIP include dirs: ${MINIZIP_INCLUDE_DIRS}")
else()
  cocos_find_package(MINIZIP MINIZIP REQUIRED)
  # double check that we have needed functions
  include(CheckLibraryExists)
  check_library_exists(${MINIZIP_LIBRARIES} "unzGoToFirstFile2" "" MINIZIP_HAS_GOTOFIRSTFILE2)
  if(NOT MINIZIP_HAS_GOTOFIRSTFILE2)
    message(FATAL_ERROR "Minizip library on you system very old. Please use recent version from https://github.com/nmoinvaz/minizip or enable USE_PREBUILT_LIBS")
  endif()
  add_definitions(-DMINIZIP_FROM_SYSTEM)
endif()

cocos_find_package(PNG PNG REQUIRED)
cocos_find_package(TIFF TIFF REQUIRED)
cocos_find_package(WEBSOCKETS WEBSOCKETS REQUIRED)
cocos_find_package(CURL CURL REQUIRED)


add_subdirectory(frameworks/cocos2d-x/external/flatbuffers)
set(FLATBUFFERS_INCLUDE_DIRS frameworks/cocos2d-x/external)
message(STATUS "Flatbuffers include dirs: ${FLATBUFFERS_INCLUDE_DIRS}")


# build xxhash
add_subdirectory(frameworks/cocos2d-x/external/xxhash)
include_directories(frameworks/cocos2d-x/external/xxhash)

#buid recast
add_subdirectory(frameworks/cocos2d-x/external/recast)

set(GAME_SRC
  frameworks/runtime-src/proj.linux/main.cpp
  frameworks/runtime-src/Classes/AppDelegate.cpp
)

# cocos2d
add_subdirectory(frameworks/cocos2d-x/cocos)

#jsbindings library
add_subdirectory(frameworks/cocos2d-x/cocos/scripting/js-bindings)


# add the executable
add_executable(${APP_NAME}
  ${GAME_SRC}
)

target_link_libraries(${APP_NAME}
  jscocos2d
  cocos2d
  recast
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/script
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/res
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/src
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}/*.js
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}/*.json
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${APP_BIN_DIR}/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src ${APP_BIN_DIR}/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x/cocos/scripting/js-bindings/script ${APP_BIN_DIR}/script
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/main.js ${APP_BIN_DIR}/main.js
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/project.json ${APP_BIN_DIR}/project.json
)

