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

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop
  ${CMAKE_CURRENT_SOURCE_DIR}/audio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/editor-support
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/tinyxml2
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/unzip
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/edtaa3func
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/chipmunk/include/chipmunk
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/jpeg/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/png/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/tiff/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/webp/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw3/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/freetype2/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/websockets/include/${PLATFORM_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/xxhash
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/ConvertUTF
  ${CMAKE_CURRENT_SOURCE_DIR}/../external/linux-specific/fmod/include/${ARCH_DIR}
)


# cocos2d source files and header files
file(GLOB core_source_files 
     "${CMAKE_CURRENT_SOURCE_DIR}/cocos2d.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/base/ccFPSImages.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/2d/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/3d/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/audio/linux/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/base/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/deprecated/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/editor-support/cocosbuilder/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/editor-support/spine/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/math/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/network/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/physics/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/physics/chipmunk/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/platform/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/platform/linux/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/platform/desktop/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/renderer/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/storage/local-storage/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/tinyxml2/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/xxhash/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/unzip/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/chipmunk/src/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/chipmunk/src/constraints/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/edtaa3func/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/ConvertUTF/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../external/ConvertUTF/*.c"
     )
file(GLOB_RECURSE cocostudio_source_files "${CMAKE_CURRENT_SOURCE_DIR}/editor-support/cocostudio/*.cpp")
file(GLOB_RECURSE extensions_source_files "${CMAKE_CURRENT_SOURCE_DIR}/../extensions/*.cpp")
file(GLOB_RECURSE box2d_source_files "${CMAKE_CURRENT_SOURCE_DIR}/../external/Box2D/*.cpp")
set(cocos2d_source_files ${chipmunk_source_files} ${box2d_source_files} ${core_source_files} ${cocostudio_source_files}  ${extensions_source_files})
# exclude files specific for other platforms
list(REMOVE_ITEM cocos2d_source_files 
     "${CMAKE_CURRENT_SOURCE_DIR}/base/CCController-android.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/base/CCUserDefaultAndroid.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/ui/UIVideoPlayerAndroid.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/ui/UIWebView.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/ui/UIWebViewImpl_android.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/storage/local-storage/LocalStorageAndroid.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/base/CCEventController.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/base/CCEventListenerController.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/editor-support/cocostudio/proj.wp8/pch.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/../extensions/proj.wp8/pch.cpp")

add_library(cocos2d STATIC ${cocos2d_source_files})

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(FMOD_LIB "fmodex64")
else()
    set(FMOD_LIB "fmodex")
endif()
target_link_libraries(cocos2d jpeg webp tiff freetype fontconfig png pthread glfw GLEW GL X11 rt z ${FMOD_LIB} curl)

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

