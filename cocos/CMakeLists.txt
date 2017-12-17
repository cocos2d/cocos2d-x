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

# this CMakeLists is to generate libcocos2d.a

cmake_minimum_required(VERSION 3.1)

if(WINDOWS)
  ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
endif()

include(2d/CMakeLists.txt)
include(3d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(physics3d/CMakeLists.txt)
include(math/CMakeLists.txt)
include(navmesh/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(vr/CMakeLists.txt)
include(base/CMakeLists.txt)
include(deprecated/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(network/CMakeLists.txt)
include(audio/CMakeLists.txt)
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
    ${COCOS_PHYSICS3D_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_NAVMESH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_VR_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_AUDIO_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_DEPRECATED_SRC}
    ${COCOS_NETWORK_SRC}
    ${COCOS_EDITOR_SUPPORT_SRC}
    ${COCOS_EXTENSIONS_SRC}
    )

  #todo: provide prebuild versions of the xx libs for all platforms
  include_directories(../external/xxtea)
  include_directories(../external/clipper)

add_library(cocos2dInternal ${COCOS_SRC})

set_target_properties(cocos2dInternal
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)

set(PLATFORM_SPECIFIC_LIBS)
if(WINDOWS)
  foreach(_pkg OPENGL GLEW GLFW3 VORBIS MPG123 OPENAL)
    cocos_use_pkg(cocos2dInternal ${_pkg})
  endforeach()
  list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 winmm version)
  if(MINGW)
    list(APPEND PLATFORM_SPECIFIC_LIBS shlwapi version)
  endif()
elseif(LINUX)
  foreach(_pkg OPENGL GLEW GLFW3 FMOD FONTCONFIG THREADS GTK3)
    cocos_use_pkg(cocos2dInternal ${_pkg})
  endforeach()
elseif(MACOSX OR APPLE)
  cocos_use_pkg(cocos2dInternal GLFW3)

 INCLUDE_DIRECTORIES ( /System/Library/Frameworks )

 FIND_LIBRARY(COCOA_LIBRARY Cocoa)
 FIND_LIBRARY(OPENGL_LIBRARY OpenGL )
 FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox)
 FIND_LIBRARY(OPENAL_LIBRARY OpenAL )
 FIND_LIBRARY(QUARTZCORE_LIBRARY QuartzCore )
 FIND_LIBRARY(APPLICATIONSERVICES_LIBRARY ApplicationServices)
 FIND_LIBRARY(IOKIT_LIBRARY IOKit)
 FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)
 FIND_LIBRARY(ICONV_LIBRARY iconv)

  set(PLATFORM_SPECIFIC_LIBS
    ${COCOA_LIBRARY}
    ${OPENGL_LIBRARY}
    ${OPENAL_LIBRARY}
    ${AUDIOTOOLBOX_LIBRARY}
    ${QUARTZCORE_LIBRARY}
    ${APPLICATIONSERVICES_LIBRARY}
    ${IOKIT_LIBRARY}
    ${FOUNDATION_LIBRARY}
    ${ICONV_LIBRARY}
  )

elseif(ANDROID)
  set(PLATFORM_SPECIFIC_LIBS GLESv1_CM GLESv2 EGL log android OpenSLES)
  get_filename_component(__module_path "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
  include(${__module_path}/AndroidNdkModules.cmake)
  android_ndk_import_module_cpufeatures()
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

foreach(pkg ZLIB MINIZIP JPEG PNG TIFF TinyXML2 FREETYPE WEBSOCKETS CURL OPENSSL FLATBUFFERS XXHASH)
  cocos_use_pkg(cocos2dInternal ${pkg})
endforeach()

if(LINUX)
  set(glfw_other_linker_flags X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m)
endif(LINUX)

target_link_libraries(cocos2dInternal ${PLATFORM_SPECIFIC_LIBS} ${glfw_other_linker_flags})

if(USE_WEBP)
  add_definitions(-DCC_USE_WEBP=1)
  cocos_use_pkg(cocos2dInternal WEBP)
else()
  add_definitions(-DCC_USE_WEBP=0)
endif()

if(USE_CHIPMUNK)
  cocos_use_pkg(cocos2dInternal CHIPMUNK)
endif()

if(USE_BOX2D)
  cocos_use_pkg(cocos2dInternal Box2D)
endif()

if(USE_BULLET)
  cocos_use_pkg(cocos2dInternal BULLET)
endif()

if(USE_RECAST)
  cocos_use_pkg(cocos2dInternal RECAST)
endif()

ADD_LIBRARY(cocos2d cc_dummy.c)

if(ANDROID)
  target_link_libraries(cocos2d -Wl,-whole-archive cocos2dxandroid_static -Wl,-no-whole-archive)
  target_link_libraries(cocos2d cocos2dInternal cpufeatures)
elseif(LINUX)
  target_link_libraries(cocos2d cocos2dInternal dl)
else()
  target_link_libraries(cocos2d cocos2dInternal)
endif()

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)
