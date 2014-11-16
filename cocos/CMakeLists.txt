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

if(WINDOWS AND NOT BUILD_STATIC)
  ADD_DEFINITIONS (-D_USRDLL)
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

if(MINGW)
  find_package(Protobuf REQUIRED)
  #find_package(MiniZip REQUIRED)
  #${MINIZIP_INCLUDE_DIR}

  find_package(ZLIB REQUIRED)

  message( STATUS "ZLIB dirs: ${ZLIB_INCLUDE_DIRS}")
  message( STATUS "Protobuf dirs: ${PROTOBUF_INCLUDE_DIRS}")

  include_directories(${ZLIB_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})

else()

  #todo: provide prebuild versions of minizip for android ios mac and msvc
  #done: prebuilt version for mingw-w64 (linux distros should have them also)
  # check for opensuse the buildbot system arch and ubuntu

  include_directories(
    ../external/unzip)

endif()

  #todo: provide prebuild versions of the xx libs for all platforms
  include_directories(
    ../external/xxhash
    ../external/xxtea)


add_library(cocos2d ${BUILD_TYPE} ${COCOS_SRC})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(FMOD_LIB "fmodex64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(FMOD_LIB "fmodex")
endif()

if(MINGW)
  set(PLATFORM_SPECIFIC_LIBS curl glew32 opengl32 iconv bz2)
elseif(WINDOWS)
  set(PLATFORM_SPECIFIC_LIBS libcurl_imp glew32 opengl32 libiconv)
elseif(LINUX)
  set(PLATFORM_SPECIFIC_LIBS curl ssl crypto fontconfig pthread GLEW GL X11 rt ${FMOD_LIB})
elseif(MACOSX OR APPLE)
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
    curl
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

# Add GLFW3 for desktop platforms
if(LINUX OR MACOSX OR WINDOWS)
  list(APPEND PLATFORM_SPECIFIC_LIBS ${GLFW3_LIBRARIES})
endif()

add_definitions(${PNG_DEFINITIONS})

include_directories(
  ${ZLIB_INCLUDE_DIRS}
  ${JPEG_INCLUDE_DIRS}
  ${PNG_INCLUDE_DIRS}
  ${TIFF_INCLUDE_DIRS}
  ${TinyXML2_INCLUDE_DIRS}
  ${WEBSOCKETS_INCLUDE_DIRS}
  )
target_link_libraries(cocos2d
  protobuf unzip xxhash
  ${ZLIB_LIBRARIES}
  ${JPEG_LIBRARIES}
  ${PNG_LIBRARIES}
  ${TIFF_LIBRARIES}
  ${TinyXML2_LIBRARIES}
  ${WEBSOCKETS_LIBRARIES}
  ${FREETYPE_LIBRARIES}
  ${PLATFORM_SPECIFIC_LIBS}
  )

if(USE_WEBP)
  add_definitions(-DCC_USE_WEBP=1)
  include_directories(${WEBP_INCLUDE_DIRS})
  target_link_libraries(cocos2d ${WEBP_LIBRARIES})
else()
  add_definitions(-DCC_USE_WEBP=0)
endif()

if(USE_CHIPMUNK)
  include_directories(${CHIPMUNK_INCLUDE_DIRS})
  target_link_libraries(cocos2d ${CHIPMUNK_LIBRARIES})
endif()

if(USE_BOX2D)
  include_directories(${Box2D_INCLUDE_DIRS})
  target_link_libraries(cocos2d ${Box2D_LIBRARIES})
endif()

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)
