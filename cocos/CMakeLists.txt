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

project(COCOS2D)

#===============================================================================
#Options for 'cocos2d' library.
if(NOT WINDOWS_PHONE AND NOT WINDOWS_STORE)
    option(BUILD_USE_WEBP "Use WebP codec" "ON")
endif()

#===============================================================================
# Define library target 'cocos2d'.
set(COCOS2D_TARGET cocos2d CACHE INTERNAL "")
add_library(${COCOS2D_TARGET} ${CMAKE_CURRENT_LIST_FILE})
cocos_tweak_target_output_directory(${COCOS2D_TARGET})

#===============================================================================
# Set cocos public include directories.
target_include_directories(${COCOS2D_TARGET} PUBLIC 
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/audio/include"
    "${CMAKE_CURRENT_LIST_DIR}/platform"
    )

# Set cocos private include directories.
target_include_directories(${COCOS2D_TARGET} PRIVATE
    ".."
    "../external"
    )

#===============================================================================
# Include all subdirectories, each subdirectory maybe has headers, sources, 
#   and special definations.
cocos_target_sources(${COCOS2D_TARGET} GROUP "${COCOS2D_TARGET}" FILES
    "cocos2d.h"
    "cocos2d.cpp"
    )

include("platform/CMakeLists.txt")

include("2d/CMakeLists.txt")
include("3d/CMakeLists.txt")
include("audio/CMakeLists.txt")
include("base/CMakeLists.txt")
include("deprecated/CMakeLists.txt")
include("editor-support/CMakeLists.txt")
include("math/CMakeLists.txt")
include("network/CMakeLists.txt")
include("physics/CMakeLists.txt")
include("renderer/CMakeLists.txt")
include("storage/CMakeLists.txt")
include("ui/CMakeLists.txt")

include("../extensions/CMakeLists.txt")

#===============================================================================
# Add dependent libraries.

add_subdirectory("../external/ConvertUTF" "external/ConvertUTF")
add_subdirectory("../external/edtaa3func" "external/edtaa3func")

# Tinyxml2 (not prebuilded, exists as source)
if(BUILD_USE_PREBUILT_LIBS)
    add_subdirectory("../external/tinyxml2" "external/tinyxml2")

    target_link_libraries(${COCOS2D_TARGET} tinyxml2)
else()
    cocos_use_package(${COCOS2D_TARGET} TinyXML2 REQUIRED)
endif()

# minizip(we try to migrate to minizip from https://github.com/nmoinvaz/minizip)
# only msys2 currently provides package for this variant, all other
# dists have packages from zlib, thats very old for us.
# moreover our embedded version modified to quick provide
# functionality needed by cocos.
if(BUILD_USE_PREBUILT_LIBS OR NOT MINGW)
    add_subdirectory("../external/unzip" "external/unzip")

    target_link_libraries(${COCOS2D_TARGET} unzip)
else()
    cocos_find_package(MINIZIP MINIZIP REQUIRED)
    # double check that we have needed functions
    include(CheckLibraryExists)
    check_library_exists(${MINIZIP_LIBRARIES} "unzGoToFirstFile2" "" MINIZIP_HAS_GOTOFIRSTFILE2)
    if(NOT MINIZIP_HAS_GOTOFIRSTFILE2)
        message(FATAL_ERROR "Minizip library on you system very old. Please use recent version from https://github.com/nmoinvaz/minizip or enable BUILD_USE_PREBUILT_LIBS")
    endif()
    add_definitions(-DMINIZIP_FROM_SYSTEM)
    
    cocos_use_package(${COCOS2D_TARGET} MINIZIP REQUIRED)
endif()

add_subdirectory("../external/xxhash" "external/xxhash")

target_link_libraries(${COCOS2D_TARGET}
    ConvertUTF edtaa3func tinyxml2 unzip xxhash
    )

cocos_use_package(${COCOS2D_TARGET} FREETYPE REQUIRED)
cocos_use_package(${COCOS2D_TARGET} JPEG REQUIRED)
cocos_use_package(${COCOS2D_TARGET} PNG REQUIRED)
cocos_use_package(${COCOS2D_TARGET} TIFF REQUIRED)
cocos_use_package(${COCOS2D_TARGET} ZLIB REQUIRED)

if(BUILD_USE_WEBP)
    # target_compile_definitions(-DCC_USE_WEBP=1)
    cocos_use_package(${COCOS2D_TARGET} WEBP REQUIRED)
    # target_compile_definitions "HAVE_NEON=1")
endif()
#target_compile_definitions(-DCC_USE_WEBP=0)

if(COCOS_TARGET_SYSTEM_WINDOWS OR COCOS_TARGET_SYSTEM_LINUX)
    cocos_use_package(${COCOS2D_TARGET} GLEW REQUIRED)
endif()

if(COCOS_TARGET_SYSTEM_MACOSX OR
        COCOS_TARGET_SYSTEM_WINDOWS OR
        COCOS_TARGET_SYSTEM_LINUX)
    cocos_use_package(${COCOS2D_TARGET} GLFW3 REQUIRED)
endif()

if(COCOS_TARGET_SYSTEM_MACOSX)
    # There is no specific libs for MacOSX.
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    # Cocos::Console depend ws2_32.lib on windows.
    target_link_libraries(${COCOS2D_TARGET} "ws2_32.lib")

elseif(COCOS_TARGET_SYSTEM_LINUX)
    # OpenGL libs have GLU GL SM ICE X11 Xext, we just need GL and X11.
    cocos_find_package(OpenGL OPENGL REQUIRED)
    #cocos_use_package(${COCOS2D_TARGET} OpenGL REQUIRED)
    # Fontconfig libs have fontconfig and freetype, we just need fontconfig.
    cocos_find_package(Fontconfig FONTCONFIG REQUIRED)
    target_link_libraries(${COCOS2D_TARGET} "${OPENGL_gl_LIBRARY}" fontconfig)
    # cocos_use_package don't satisfy the Threads library, use find_package
    #   instead.
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    cocos_use_package(${COCOS2D_TARGET} Threads REQUIRED)
    # find_package(Threads REQUIRED)
    # target_link_libraries(${COCOS2D_TARGET} Threads::Threads)
    #GLFW3 dependent libs
    target_link_libraries(${COCOS2D_TARGET}
        rt m Xxf86vm X11 Xrandr Xi Xinerama Xcursor
        )

elseif(COCOS_TARGET_SYSTEM_IOS)
    target_link_libraries(${COCOS2D_TARGET}
        "-framework AVFoundation"
        "-framework CoreGraphics"
        "-framework CoreMotion"
        "-framework Foundation"
        "-framework MediaPlayer"
        "-framework OpenGLES"
        "-framework QuartzCore"
        "-framework UIKit"
        )

elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # math and webp depends cpufeatures
    target_link_libraries(${COCOS2D_TARGET}
        "GLESv1_CM"
        "GLESv2"
        "EGL"
        "log"
        "android"
        "cpufeatures"
        )

else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build for unsupported os.")
endif()

#===============================================================================
#  Specific settings.
if(COCOS_TARGET_SYSTEM_WINDOWS)
    target_compile_definitions(${COCOS2D_TARGET} PUBLIC UNICODE _UNICODE)
    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${COCOS2D_TARGET} PRIVATE _USRDLL _USE3DDLL)
    else()
        target_compile_definitions(${COCOS2D_TARGET} PUBLIC CC_STATIC)
    endif()

endif()

# Show cocos2d includes and libraries information.
get_target_property(COCOS_INTERFACE_INCLUDES ${COCOS2D_TARGET}
    INTERFACE_INCLUDE_DIRECTORIES
    )
message(STATUS
    "Target '${COCOS2D_TARGET}' public header dir: ${COCOS_INTERFACE_INCLUDES}"
    )
get_target_property(COCOS_INCLUDES ${COCOS2D_TARGET} INCLUDE_DIRECTORIES)
message(STATUS "Target '${COCOS2D_TARGET}' include dirs: ${COCOS_INCLUDES}")
get_target_property(_INTERFACE_LINK_LIBRARIES ${COCOS2D_TARGET}
    INTERFACE_LINK_LIBRARIES
    )
message(STATUS
    "Target '${COCOS2D_TARGET}' dependent libs: ${_INTERFACE_LINK_LIBRARIES}"
    )
return()

#==============================================================================

if(USE_CHIPMUNK)
  cocos_use_pkg(cocos2d CHIPMUNK)
endif()

if(USE_BOX2D)
  cocos_use_pkg(cocos2d Box2D)
endif()

