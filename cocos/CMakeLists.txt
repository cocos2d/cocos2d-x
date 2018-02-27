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

# this CMakeLists is to generate Cocos2d-x Engine Library
# build libcocos2d
# build luacocos2d if BUILD_LUA_LIBS=ON
# build jscocos2d if BUILD_JS_LIBS=ON

# The version number
set(COCOS2D_X_VERSION 3.17)

set(COCOS_CORE_LIB cocos2d)

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

if(BUILD_EXTENSIONS)
include(../extensions/CMakeLists.txt)
endif(BUILD_EXTENSIONS)

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
    ${COCOS_STORAGE_SRC}
    )

  #todo: provide prebuild versions of the xx libs for all platforms
  include_directories(../external/xxtea)
  include_directories(../external/clipper)

add_library(${COCOS_CORE_LIB} ${COCOS_SRC})

set_target_properties(${COCOS_CORE_LIB}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)

set(PLATFORM_SPECIFIC_LIBS)
if(WINDOWS)
  foreach(_pkg OPENGL GLEW GLFW3 VORBIS MPG123 OPENAL)
    cocos_use_pkg(${COCOS_CORE_LIB} ${_pkg})
  endforeach()
  list(APPEND PLATFORM_SPECIFIC_LIBS ws2_32 winmm Version Iphlpapi)
  if(MINGW)
    list(APPEND PLATFORM_SPECIFIC_LIBS shlwapi version)
  endif()
elseif(LINUX)
  foreach(_pkg OPENGL GLEW GLFW3 FMOD FONTCONFIG THREADS GTK3)
    cocos_use_pkg(${COCOS_CORE_LIB} ${_pkg})
  endforeach()
elseif(APPLE)

  include_directories(/System/Library/Frameworks )
  find_library(ICONV_LIBRARY iconv)
  find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
  find_library(FOUNDATION_LIBRARY Foundation)
  find_library(OPENAL_LIBRARY OpenAL )
  find_library(QUARTZCORE_LIBRARY QuartzCore )
  set(COCOS_APPLE_LIBS
    ${OPENAL_LIBRARY}
    ${AUDIOTOOLBOX_LIBRARY}
    ${QUARTZCORE_LIBRARY}
    ${FOUNDATION_LIBRARY}
    ${ICONV_LIBRARY}
)

  if(MACOSX)
    cocos_use_pkg(${COCOS_CORE_LIB} GLFW3)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL )
    find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices)
    find_library(IOKIT_LIBRARY IOKit)
    

    set(PLATFORM_SPECIFIC_LIBS
      ${COCOA_LIBRARY}
      ${OPENGL_LIBRARY}
      ${APPLICATIONSERVICES_LIBRARY}
      ${IOKIT_LIBRARY}
      ${COCOS_APPLE_LIBS}
    )
  elseif(IOS)
    # Locate system libraries on iOS
    find_library(UIKIT_LIBRARY UIKit)
    find_library(OPENGLES_LIBRARY OpenGLES )
    find_library(CORE_MOTION_LIBRARY CoreMotion)
    find_library(MEDIA_PLAYER_LIBRARY MediaPlayer)
    find_library(CORE_TEXT_LIBRARY CoreText)
    find_library(SECURITY_LIBRARY Security)
    find_library(CORE_GRAPHICS_LIBRARY CoreGraphics)
    find_library(AV_FOUNDATION_LIBRARY AVFoundation)
    find_library(Z_LIBRARY z)
    set(PLATFORM_SPECIFIC_LIBS
      ${UIKIT_LIBRARY}
      ${OPENGLES_LIBRARY}
      ${CORE_MOTION_LIBRARY}
      ${MEDIA_PLAYER_LIBRARY}
      ${CORE_TEXT_LIBRARY}
      ${SECURITY_LIBRARY}
      ${CORE_GRAPHICS_LIBRARY}
      ${AV_FOUNDATION_LIBRARY}
      ${Z_LIBRARY}
      ${COCOS_APPLE_LIBS}
    )
  endif()
  
elseif(ANDROID)
  set(PLATFORM_SPECIFIC_LIBS GLESv2 EGL log android OpenSLES)
  include(../cmake/AndroidNdkModules.cmake)
  android_ndk_import_module_cpufeatures()
  cocos_use_pkg(${COCOS_CORE_LIB} TREMOLO)
  cocos_use_pkg(${COCOS_CORE_LIB} PVMP3DEC)
  include_directories(../external/android-specific/tremolo)
  include_directories(../external/android-specific/pvmp3dec/include)
  include_directories(../external/android-specific/pvmp3dec/src)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

foreach(pkg ZLIB MINIZIP TinyXML2 FREETYPE WEBSOCKETS CURL FLATBUFFERS XXHASH)
  cocos_use_pkg(${COCOS_CORE_LIB} ${pkg})
endforeach()

if(NOT EMSCRIPTEN)
  cocos_use_pkg(${COCOS_CORE_LIB} OPENSSL)
endif()

if(LINUX)
  set(glfw_other_linker_flags X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m)
endif(LINUX)

target_link_libraries(${COCOS_CORE_LIB} ${PLATFORM_SPECIFIC_LIBS} ${glfw_other_linker_flags})

if(USE_JPEG)
  add_definitions(-DCC_USE_JPEG=1)
  cocos_use_pkg(${COCOS_CORE_LIB} JPEG)
else()
  add_definitions(-DCC_USE_JPEG=0)
endif()

if(USE_WEBP)
  add_definitions(-DCC_USE_WEBP=1)
  cocos_use_pkg(${COCOS_CORE_LIB} WEBP)
else()
  add_definitions(-DCC_USE_WEBP=0)
endif()

if(USE_TIFF)
  add_definitions(-DCC_USE_TIFF=1)
  cocos_use_pkg(${COCOS_CORE_LIB} TIFF)
else()
  add_definitions(-DCC_USE_TIFF=0)
endif()

if(USE_PNG)
  add_definitions(-DCC_USE_PNG=1)
  cocos_use_pkg(${COCOS_CORE_LIB} PNG)
else()
  add_definitions(-DCC_USE_PNG=0)
endif()

if(USE_CHIPMUNK)
  cocos_use_pkg(${COCOS_CORE_LIB} CHIPMUNK)
endif()

if(USE_BOX2D)
  cocos_use_pkg(${COCOS_CORE_LIB} Box2D)
endif()

if(USE_BULLET)
  cocos_use_pkg(${COCOS_CORE_LIB} BULLET)
endif()

if(USE_RECAST)
  cocos_use_pkg(${COCOS_CORE_LIB} RECAST)
endif()

if(ANDROID)
  target_link_libraries(${COCOS_CORE_LIB} cpufeatures)
elseif(LINUX)
  target_link_libraries(${COCOS_CORE_LIB} dl)
endif()

set_target_properties(${COCOS_CORE_LIB}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    VERSION "${COCOS2D_X_VERSION}"
)

## Lua bindings lib
if(BUILD_LUA_LIBS OR (CMAKE_PROJECT_NAME STREQUAL Cocos2d-x))
  add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings ${ENGINE_BINARY_PATH}/cocos/lua-bindings)
endif()
## JS bindings lib
if(BUILD_JS_LIBS OR (CMAKE_PROJECT_NAME STREQUAL Cocos2d-x))
  add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings ${ENGINE_BINARY_PATH}/cocos/js-bindings)
endif()

if(XCODE OR VS)
    cocos_mark_code_files("${COCOS_CORE_LIB}")
endif()