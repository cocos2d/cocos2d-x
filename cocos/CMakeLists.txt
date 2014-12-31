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

# this CMakeLists is to generate libcocos2d.a

cmake_minimum_required(VERSION 2.8)

if(WINDOWS)
  ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
endif()

include(2d/CMakeLists.txt)
include(3d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(math/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(base/CMakeLists.txt)
include(deprecated/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(network/CMakeLists.txt)
include(audio/CMakeLists.txt)
include_directories(audio/include)
include(storage/CMakeLists.txt)

if(BUILD_EDITOR_COCOSBUILDER)
include(editor-support/cocosbuilder/CMakeLists.txt)
set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CCB_SRC})
endif(BUILD_EDITOR_COCOSBUILDER)

if(BUILD_EDITOR_COCOSTUDIO)
include(editor-support/cocostudio/CMakeLists.txt)
set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CS_SRC})
endif(BUILD_EDITOR_COCOSTUDIO)

if(BUILD_EDITOR_SPINE)
include(editor-support/spine/CMakeLists.txt)
set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_SPINE_SRC})
endif(BUILD_EDITOR_SPINE)

include(../extensions/CMakeLists.txt)

set(COCOS_SRC cocos2d.cpp
    ${COCOS_2D_SRC}
    ${COCOS_3D_SRC}
    ${COCOS_PLATFORM_SRC}
    ${COCOS_PHYSICS_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_AUDIO_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_DEPRECATED_SRC}
    ${COCOS_NETWORK_SRC}
    ${COCOS_EDITOR_SUPPORT_SRC}
    ${COCOS_EXTENSIONS_SRC}
    )

  #todo: provide prebuild versions of the xx libs for all platforms
  include_directories(
    ../external/xxhash
    ../external/xxtea)


add_library(cocos2d ${COCOS_SRC})

set(PLATFORM_SPECIFIC_LIBS)
if(WINDOWS)
  foreach(_pkg OPENGL GLEW GLFW3 VORBIS MPG123 OPENAL)
    cocos_use_pkg(cocos2d ${_pkg})
  endforeach()
  list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 winmm)
elseif(LINUX)
  foreach(_pkg OPENGL GLEW GLFW3 FMODEX FONTCONFIG THREADS)
    cocos_use_pkg(cocos2d ${_pkg})
  endforeach()
elseif(MACOSX OR APPLE)
  cocos_use_pkg(cocos2d GLFW3)

 INCLUDE_DIRECTORIES ( /System/Library/Frameworks )

 FIND_LIBRARY(COCOA_LIBRARY Cocoa)
 FIND_LIBRARY(OPENGL_LIBRARY OpenGL )
 FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox)
 FIND_LIBRARY(OPENAL_LIBRARY OpenAL )
 FIND_LIBRARY(QUARTZCORE_LIBRARY QuartzCore )
 FIND_LIBRARY(APPLICATIONSERVICES_LIBRARY ApplicationServices)
 FIND_LIBRARY(IOKIT_LIBRARY IOKit)
 FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)

  set(PLATFORM_SPECIFIC_LIBS
    ${COCOA_LIBRARY}
    ${OPENGL_LIBRARY}
    ${OPENAL_LIBRARY}
    ${AUDIOTOOLBOX_LIBRARY}
    ${QUARTZCORE_LIBRARY}
    ${APPLICATIONSERVICES_LIBRARY}
    ${IOKIT_LIBRARY}
    ${FOUNDATION_LIBRARY}
  )

elseif(ANDROID)
  set(PLATFORM_SPECIFIC_LIBS GLESv2 log android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

foreach(pkg ZLIB MINIZIP JPEG PNG TIFF TinyXML2 FREETYPE WEBSOCKETS CURL FLATBUFFERS)
  cocos_use_pkg(cocos2d ${pkg})
endforeach()

target_link_libraries(cocos2d xxhash ${PLATFORM_SPECIFIC_LIBS})

if(USE_WEBP)
  add_definitions(-DCC_USE_WEBP=1)
  cocos_use_pkg(cocos2d WEBP)
else()
  add_definitions(-DCC_USE_WEBP=0)
endif()

if(USE_CHIPMUNK)
  cocos_use_pkg(cocos2d CHIPMUNK)
endif()

if(USE_BOX2D)
  cocos_use_pkg(cocos2d Box2D)
endif()

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)
