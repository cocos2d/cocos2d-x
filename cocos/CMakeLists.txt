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
    add_definitions(-DUNICODE -D_UNICODE)
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
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CCB_SRC} ${COCOS_CCB_HEADER})
endif(BUILD_EDITOR_COCOSBUILDER)

if(BUILD_EDITOR_COCOSTUDIO)
    include(editor-support/cocostudio/CMakeLists.txt)
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_CS_SRC} ${COCOS_CS_HEADER})
endif(BUILD_EDITOR_COCOSTUDIO)

if(BUILD_EDITOR_SPINE)
    include(editor-support/spine/CMakeLists.txt)
    set(COCOS_EDITOR_SUPPORT_SRC ${COCOS_EDITOR_SUPPORT_SRC} ${COCOS_SPINE_SRC} ${COCOS_SPINE_HEADER})
endif(BUILD_EDITOR_SPINE)

if(BUILD_EXTENSIONS)
    include(../extensions/CMakeLists.txt)
endif(BUILD_EXTENSIONS)

set(COCOS_HEADER cocos2d.h
    ${COCOS_2D_HEADER}
    ${COCOS_3D_HEADER}
    ${COCOS_PLATFORM_HEADER}
    ${COCOS_PHYSICS_HEADER}
    ${COCOS_PHYSICS3D_HEADER}
    ${COCOS_MATH_HEADER}
    ${COCOS_NAVMESH_HEADER}
    ${COCOS_RENDERER_HEADER}
    ${COCOS_VR_HEADER}
    ${COCOS_BASE_HEADER}
    ${COCOS_AUDIO_HEADER}
    ${COCOS_UI_HEADER}
    ${COCOS_DEPRECATED_HEADER}
    ${COCOS_NETWORK_HEADER}
    ${COCOS_EDITOR_SUPPORT_HEADER}
    ${COCOS_EXTENSIONS_HEADER}
    ${COCOS_STORAGE_HEADER}
    )

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

list(APPEND COCOS_SRC ${COCOS_HEADER})

if (OHOS)
    message("real add_compile_options")
    add_compile_options(-DUSE_FILE32API
    -Wno-absolute-value
    -Wno-extra
    -Wno-implicit-int-float-conversion
    -Wno-overloaded-virtual
    -Wno-unused-function
    -Wno-unused-private-field
    -Wno-reorder-ctor
    -Wno-unsequenced
    -Wno-extra
    -Wno-c++11-narrowing
    -DOpenHarmony
    )    
endif()

add_library(cocos2d ${COCOS_SRC})

# use necessary external libs and system libs
if (OHOS)
    find_library( # Sets the name of the path variable.
              Drawing-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              native_drawing )
    find_library( # Sets the name of the path variable.
              libace-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_ndk.z )
    find_library( # Sets the name of the path variable.
              libnapi-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_napi.z )
    find_library( # Sets the name of the path variable.
              GLES-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv3 )
    find_library( # Sets the name of the path variable.
              libuv-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              uv )
    find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )
    find_library( # Sets the name of the path variable.
              EGL-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              EGL )
    
    find_library( # Sets the name of the path variable.
              hilog-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              hilog_ndk.z )
    message("****************  native_drawing:${Drawing-lib}  *************************")
    target_link_libraries(cocos2d ${Drawing-lib} ${libace-lib} ${GLES-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib} ${EGL-lib} ${hilog-lib} libohaudio.so libavplayer.so  libnative_window.so libnative_buffer.so libnative_display_manager.so libohsensor.so
    			  libnative_media_codecbase.so libnative_media_core.so libnative_media_acodec.so libnative_media_avdemuxer.so libnative_media_avsource.so)
endif()

include(CocosUseLibs)
target_use_cocos2d_depend_libs(cocos2d)

if(OHOS)
    # set(BULLET_INCLUDE_DIRS ${COCOS2DX_ROOT_PATH}/external/bullet/include ${COCOS2DX_ROOT_PATH}/external/bullet/src)
    # add_subdirectory(${COCOS2DX_ROOT_PATH}/external/bullet ${ENGINE_BINARY_PATH}/external/bullet)
    # set(BULLET_LIBRARIES bullet)
    # include_directories(${BULLET_INCLUDE_DIRS})
     target_include_directories(cocos2d PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include)
     target_include_directories(cocos2d PUBLIC ${COCOS2DX_ROOT_PATH}/external)
     target_compile_definitions(cocos2d PUBLIC -DOpenHarmony)
 endif()

set_target_properties(cocos2d
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      VERSION "${COCOS2D_X_VERSION}"
                      FOLDER "Internal"
                      )

# set custom target: prebuilt, to copy all libs to prebuilt libs folder
if(GEN_COCOS_PREBUILT)
    add_custom_target(prebuilt ALL)
    add_dependencies(prebuilt cocos2d)
    set_target_properties(prebuilt
                          PROPERTIES
                          FOLDER "Internal"
                          )
    add_custom_command(TARGET "prebuilt"
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_BINARY_DIR}/lib"
                       "${COCOS_PREBUILT_PATH}"
                       COMMENT "copy library directory:${CMAKE_BINARY_DIR}/lib to directory:${COCOS_PREBUILT_PATH}"
                       )
    if(BUILD_LUA_LIBS)
        add_dependencies(prebuilt luacocos2d)
    endif()
    if(BUILD_JS_LIBS)
        add_dependencies(prebuilt jscocos2d)
    endif()
    if(BUILD_SIMU_LIB AND (MACOSX OR WINDOWS))
        add_dependencies(prebuilt simulator)
    endif()
endif()

## Lua bindings lib
if(BUILD_LUA_LIBS)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings ${ENGINE_BINARY_PATH}/cocos/lua-bindings)
endif()
## JS bindings lib
if(BUILD_JS_LIBS)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/scripting/js-bindings ${ENGINE_BINARY_PATH}/cocos/js-bindings)
endif()
# simulator
if(BUILD_SIMU_LIB AND (MACOSX OR WINDOWS))
    add_subdirectory(${COCOS2DX_ROOT_PATH}/tools/simulator/libsimulator ${ENGINE_BINARY_PATH}/cocos/libsimulator)
endif()

if(XCODE OR VS)
    cocos_mark_code_files("cocos2d")
endif()
