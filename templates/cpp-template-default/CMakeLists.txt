#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
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

cmake_minimum_required(VERSION 3.1)

set(APP_NAME TemplateCpp)

project (${APP_NAME})

set(common_code_files
    Classes/AppDelegate.cpp
    Classes/HelloWorldScene.cpp
)

set(common_header_files
    Classes/AppDelegate.h
    Classes/HelloWorldScene.h
)

if(NOT DEFINED BUILD_ENGINE_DONE)
    # set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    CocosBuildSet()
    
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
endif(ANDROID)

if(APPLE OR VS)
    set(res_res_folders 
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${res_res_folders})
endif()

if(ANDROID)
    set(platform_specific_src proj.android/app/jni/hellocpp/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(WINDOWS)
    set(windows_src proj.win32/main.cpp)
    set(platform_specific_header
            proj.win32/main.h
            proj.win32/resource.h
            )
    set(platform_specific_src ${cc_common_res} ${windows_src})
elseif(APPLE)
    if(IOS)
        set(ios_code_files
            proj.ios_mac/ios/main.m
            proj.ios_mac/ios/AppController.mm
            proj.ios_mac/ios/RootViewController.mm
        )
        set(ios_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/LaunchScreen.storyboard
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/LaunchScreenBackground.png
        )
        cocos_mark_multi_resources(ios_res_files RES_TO "Resources" FILES ${ios_res_files})
        set(apple_src_files ${ios_code_files} ${ios_res_files})
    elseif(MACOSX)
        set(mac_code_files proj.ios_mac/mac/main.cpp)
        set(mac_res_files
            ${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Icon.icns
        )
        cocos_mark_multi_resources(mac_res_files RES_TO "Resources" FILES ${mac_res_files})
        set(apple_src_files ${mac_res_files} ${mac_code_files})
    endif()
    set(platform_specific_src ${cc_common_res} ${apple_src_files})

elseif(LINUX)
    set(platform_specific_src proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
else()
    message(FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(
	${COCOS2DX_ROOT_PATH}/cocos/audio/include/
	Classes
)

if (WINDOWS)
    include_directories(
        ${COCOS2DX_ROOT_PATH}/external/glfw3/include/${PLATFORM_FOLDER}
        ${COCOS2DX_ROOT_PATH}/external/${PLATFORM_FOLDER}-specific/gles/include/OGLES
    )
elseif (APPLE)
    if (MACOSX)
        include_directories(
            ${COCOS2DX_ROOT_PATH}/external/glfw3/include/mac
        )
    endif()
elseif(LINUX)
    include_directories(
        /usr/local/include/GLFW
        /usr/include/GLFW
    )
endif(WINDOWS)

set(all_code_src
    ${platform_specific_src}
    ${common_code_files}
)

set(all_code_header
    ${platform_specific_header}
    ${common_code_files}
)

# add the executable
if(ANDROID)
    add_library(${APP_NAME} SHARED ${all_code_src} ${all_code_header})
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    endif()
    target_link_libraries(${APP_NAME} -Wl,-whole-archive cocos2d_android -Wl,-no-whole-archive)
    add_dependencies(${APP_NAME} cocos2d_android)
elseif(MSVC)
	add_executable(${APP_NAME} ${all_code_src} ${all_code_header} proj.win32/game.rc)
else()
    add_executable(${APP_NAME} ${all_code_src} ${all_code_header})
endif()

target_link_libraries(${APP_NAME} cocos2d)


if(MSVC)

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/$<CONFIG>")
    #Visual Studio Defaults to wrong type
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS"
                                    RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_BIN_DIR})
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_BIN_DIR} FOLDERS ${CMAKE_CURRENT_SOURCE_DIR}/Resources FILES)

elseif(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
            MACOSX_BUNDLE 1
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    if(MACOSX)
        cocos_pak_xcode(${APP_NAME} BUNDLE_NAME "Cpp Hello Test")
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
    endif()
else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
            )

endif()

if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
endif()
