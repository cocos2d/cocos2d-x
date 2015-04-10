#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
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

# cocos run depends variable 'APP_NAME' for Get target name.
set(APP_NAME HelloJavascript)
set(app_name ${APP_NAME})
project(${app_name} VERSION 1.0.0)

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/frameworks/cocos2d-x)
# Jsbinding depend COCOS2D-X_SOURCE_DIR, it'll be remove soon.
set(COCOS2D-X_SOURCE_DIR ${COCOS2D_ROOT})
include_directories(${COCOS2D_ROOT})

# Specify the project cmake module path and include CocosBuildHelpers.
list(APPEND CMAKE_MODULE_PATH "${COCOS2D_ROOT}/cmake/Modules")
include(CocosBuildHelpers)

#===============================================================================
# CMake settings for entire project.

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# For multi-config IDE(e.g. VS, Xcode), set debug and release as default.
# Takes effect in xcode but not in VS, maybe is a CMake's bug.
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING ""
        FORCE
        )
endif()

if(NOT CMAKE_BUILD_TYPE)
    # For single config generator(e.g. Makefile), set release as default.
    if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
    endif()
endif()

#===============================================================================
# Include library target 'cocos2d'.
add_subdirectory("${COCOS2D_ROOT}/cocos" "cocos")
add_subdirectory("${COCOS2D_ROOT}/cocos/scripting/js-bindings"
    "cocos/scripting/js-bindings"
    )

#===============================================================================
# Define game target.
if(COCOS_TARGET_SYSTEM_ANDROID)
    add_library(${app_name} SHARED ${CMAKE_CURRENT_LIST_FILE})
else()
    add_executable(${app_name} ${CMAKE_CURRENT_LIST_FILE})
endif()

#===============================================================================
# Add include directories.
target_include_directories(${app_name} PRIVATE
    "frameworks/runtime-src/Classes"
    )

#===============================================================================
# Add sources.
cocos_target_sources(${app_name} GROUP "Classes" FILES
    "frameworks/runtime-src/Classes/AppDelegate.cpp"
    "frameworks/runtime-src/Classes/AppDelegate.h"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    set(platform_src
        "frameworks/runtime-src/proj.ios_mac/mac/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(platform_src
        "game.rc"
        "frameworks/runtime-src/proj.win32/main.cpp"
        "frameworks/runtime-src/proj.win32/main.h"
        "frameworks/runtime-src/proj.win32/resource.h"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(platform_src
        "frameworks/runtime-src/proj.linux/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    set(platform_src
        "frameworks/runtime-src/proj.ios_mac/ios/AppController.h"
        "frameworks/runtime-src/proj.ios_mac/ios/AppController.mm"
        "frameworks/runtime-src/proj.ios_mac/ios/main.m"
        "frameworks/runtime-src/proj.ios_mac/ios/RootViewController.h"
        "frameworks/runtime-src/proj.ios_mac/ios/RootViewController.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(platform_src
        "frameworks/runtime-src/proj.android/jni/hellojavascript/main.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build on unsupport system.")
endif()

cocos_target_sources(${app_name} GROUP "proj" FILES ${platform_src})

#===============================================================================
# Project resource files list.
file(GLOB_RECURSE app_resources "res/*")
file(GLOB_RECURSE app_scripts "src/*")

#===============================================================================
# Link dependent libraries.
target_link_libraries(${app_name} ${JSCOCOS2D_TARGET})

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_MACOSX)
    # Add resources to xcodeproj.
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "Resources/res"
        FILES ${app_resources}
        BASEDIR "../res"
        )

    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "Resources/src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.company.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "${CMAKE_CURRENT_LIST_DIR}/frameworks/runtime-src/proj.ios_mac/mac/Icon.icns"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/frameworks/runtime-src/proj.ios_mac/mac/InfoCMake.plist"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set_target_properties(${app_name} PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    #cocos_use_package(${app_name} GLFW3 REQUIRED)
elseif(COCOS_TARGET_SYSTEM_IOS)
    # Add resources to xcodeproj.
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "res"
        FILES ${app_resources}
        BASEDIR "../res"
        )

    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    set(ios_res
        "frameworks/runtime-src/proj.ios_mac/ios/Default-568h@2x.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Default-667h@2x.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Default-736h@3x.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Default.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Default@2x.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-100.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-114.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-120.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-144.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-152.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-29.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-40.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-50.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-57.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-58.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-72.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-76.png"
        "frameworks/runtime-src/proj.ios_mac/ios/Icon-80.png"
        )
    cocos_target_resource(${app_name} GROUP "proj"
        LOCATION "."
        FLAT_TO_LOCATION TRUE
        FILES ${ios_res}
        )

    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.company.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "Icon-57.png"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/frameworks/runtime-src/proj.ios_mac/ios/InfoCMake.plist"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${COCOS2D_X_VERSION}"
        )
endif()

#===============================================================================
# Copy resources.
if(XCODE_VERSION)
    # Nothing to do.
elseif(MSVC_IDE AND COCOS_TARGET_SYSTEM_WINDOWS)
    cocos_add_copy_depends_dll_command(${app_name})

    # Copy resource folders to WorkingDir(is $(ProjectDir) in VS).
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/../res" res_dir)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/../src" src_dir)

    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND xcopy /Y /Q /E
        "\"${res_dir}\""
        "\"$(ProjectDir)res\\\""
        COMMAND xcopy /Y /Q /E
        "\"${src_dir}\""
        "\"$(ProjectDir)src\\\""
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # TODO
else()
    # Copy resource to executable directory.
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/../res"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/res"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/src"
        )
endif()

