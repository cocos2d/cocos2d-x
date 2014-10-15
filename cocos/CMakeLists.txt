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

include(editor-support/cocosbuilder/CMakeLists.txt)
include(editor-support/cocostudio/CMakeLists.txt)
include(editor-support/spine/CMakeLists.txt)

include(../extensions/CMakeLists.txt)

set(COCOS_EDITOR_SUPPORT_SRC
  ${COCOS_CCB_SRC}
  ${COCOS_CS_SRC}
  ${COCOS_SPINE_SRC}
)

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
  find_package(Freetype REQUIRED)
  find_package(WebP REQUIRED)
  #find_package(MiniZip REQUIRED)
  #${MINIZIP_INCLUDE_DIR}

  #find_package(GLFW REQUIRED)
  #${GLFW_INCLUDE_DIRS}

  find_package(ZLIB REQUIRED)

  find_package(Chipmunk REQUIRED)

  message( STATUS "ZLIB dirs: ${ZLIB_INCLUDE_DIRS}")
  message( STATUS "WEBP dirs: ${WEBP_INCLUDE_DIRS}")
  message( STATUS "FREETYPE dirs: ${FREETYPE_INCLUDE_DIRS}")
  message( STATUS "Chipmunk dirs: ${CHIPMUNK_INCLUDE_DIRS}")

  include_directories(${FREETYPE_INCLUDE_DIRS} ${WEBP_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${CHIPMUNK_INCLUDE_DIRS})

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
  set(PLATFORM_SPECIFIC_LIBS z jpeg png webp tiff curl websockets glfw3 glew32 opengl32 iconv freetype bz2)
elseif(WINDOWS)
  set(PLATFORM_SPECIFIC_LIBS libjpeg libpng libwebp libtiff libcurl_imp libwebsockets freetype250 glfw3 glew32 opengl32 libiconv libzlib)
elseif(LINUX)
  set(PLATFORM_SPECIFIC_LIBS jpeg webp tiff freetype curl websockets
  fontconfig png pthread glfw GLEW GL X11 rt z protobuf ${FMOD_LIB})
elseif(MACOSX)

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
    z jpeg png webp tiff curl glfw3
    websockets
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
  set(PLATFORM_SPECIFIC_LIBS GLESv2 log z android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

target_link_libraries(cocos2d chipmunk box2d tinyxml2 unzip xxhash ${PLATFORM_SPECIFIC_LIBS})

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)
