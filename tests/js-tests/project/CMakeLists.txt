#/****************************************************************************
# Copyright (c) 2014 Chukong Technologies Inc.
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

project(JS_TESTS)

#===============================================================================
# Define executable target 'js-empty-test'.
set(app_name js-tests)

if(COCOS_TARGET_SYSTEM_ANDROID)
    add_library(${app_name} SHARED ${CMAKE_CURRENT_LIST_FILE})
else()
    add_executable(${app_name} ${CMAKE_CURRENT_LIST_FILE})
endif()
set_target_properties(${app_name} PROPERTIES
    FOLDER "tests"
    )

#===============================================================================
# Set include directories.
target_include_directories(${app_name} PRIVATE
    "${COCOS2D_SOURCE_DIR}/base"
    "Classes"
    "${COCOS2D-X_SOURCE_DIR}"
    )

#===============================================================================
# Add sources.
cocos_target_sources(${app_name} GROUP "Classes" FILES
    "Classes/AppDelegate.cpp"
    "Classes/AppDelegate.h"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    set(app_src
        "proj.mac/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set(app_src
        "proj.win32/main.cpp"
        "proj.win32/js-tests.rc"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    set(app_src
        "proj.linux/main.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    set(app_src
        "proj.ios/AppController.h"
        "proj.ios/AppController.mm"
        "proj.ios/main.m"
        "proj.ios/NativeOcClass.h"
        "proj.ios/NativeOcClass.m"
        "proj.ios/RootViewController.h"
        "proj.ios/RootViewController.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(app_src
        "proj.android/jni/main.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build on unsupport system.")
endif()
cocos_target_sources(${app_name} GROUP "proj" FILES ${app_src})

#===============================================================================
# Add resources.
set(app_resources
    "../main.js"
    "../project.json"
    )

# Get cpp-tests resources list.
file(GLOB_RECURSE cpp_res "${CPP_TESTS_SOURCE_DIR}/Resources/*")

#===============================================================================
# Link dependent libraries.
target_link_libraries(${app_name} ${JSCOCOS2D_TARGET})

if(COCOS_TARGET_SYSTEM_IOS)
    set(facebook_sdk_dir "plugin/plugins/facebook/proj.ios/sdk")
    target_include_directories(${app_name} PRIVATE
        "${COCOS2D-X_SOURCE_DIR}/plugin/jsbindings/auto"
        "${COCOS2D-X_SOURCE_DIR}/plugin/jsbindings/manual"
        "${COCOS2D-X_SOURCE_DIR}/${facebook_sdk_dir}/FacebookSDK.framework"
        )
    target_link_libraries(${app_name}
        "-F ${COCOS2D-X_SOURCE_DIR}/${facebook_sdk_dir}"
        "-framework FacebookSDK"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(plugin_protocols_dir "plugin/protocols")
    target_include_directories(${app_name} PRIVATE
        "${COCOS2D-X_SOURCE_DIR}/plugin/jsbindings/auto"
        "${COCOS2D-X_SOURCE_DIR}/plugin/jsbindings/manual"
        "${COCOS2D-X_SOURCE_DIR}/plugin/protocols/platform"
        )
endif()

#===============================================================================
# Specific settings.
if(COCOS_TARGET_SYSTEM_MACOSX)
    # Add resources to xcodeproj.
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "Resources"
        FILES ${app_resources}
        BASEDIR "../"
        )

    file(GLOB_RECURSE app_scripts "../src/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "Resources/src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    file(GLOB_RECURSE cocos_scripts "${CMAKE_SOURCE_DIR}/cocos/scripting/js-bindings/script/*")
    cocos_target_resource(${app_name} GROUP "Resources\\script"
        LOCATION "Resources/script"
        FILES ${cocos_scripts}
        BASEDIR "${COCOS2D_SOURCE_DIR}/scripting/js-bindings/script"
        )
    # Add cpp-tests resources.
    cocos_target_resource(${app_name} GROUP "Resources\\res" LOCATION "Resources/res"
        FILES ${cpp_res}
        BASEDIR "${CPP_TESTS_SOURCE_DIR}/Resources"
        )
    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "${CMAKE_CURRENT_LIST_DIR}/proj.mac/Icon.icns"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    set_target_properties(${app_name} PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    # Nothing to do.
elseif(COCOS_TARGET_SYSTEM_IOS)
    # Add resources to xcodeproj.
    cocos_target_resource(${app_name} GROUP "Resources"
        LOCATION "."
        FILES ${app_resources}
        BASEDIR "../"
        )

    file(GLOB_RECURSE app_scripts "../src/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src"
        LOCATION "src"
        FILES ${app_scripts}
        BASEDIR "../src"
        )

    file(GLOB_RECURSE cocos_scripts "${CMAKE_SOURCE_DIR}/cocos/scripting/js-bindings/script/*")
    cocos_target_resource(${app_name} GROUP "Resources\\src\\cocos"
        LOCATION "script"
        FILES ${cocos_scripts}
        BASEDIR "${COCOS2D_SOURCE_DIR}/scripting/js-bindings/script"
        )
    # Add cpp-tests resources.
    cocos_target_resource(${app_name} GROUP "Resources\\res"
        LOCATION "res"
        FILES ${cpp_res}
        BASEDIR "${CPP_TESTS_SOURCE_DIR}/Resources"
        )
    set(ios_res
        "proj.ios/Default-568h@2x.png"
        "proj.ios/Default.png"
        "proj.ios/Default@2x.png"
        "proj.ios/Icon-114.png"
        "proj.ios/Icon-120.png"
        "proj.ios/Icon-144.png"
        "proj.ios/Icon-152.png"
        "proj.ios/Icon-57.png"
        "proj.ios/Icon-72.png"
        "proj.ios/Icon-76.png"
        )
    cocos_target_resource(${app_name} GROUP "proj"
        LOCATION "."
        FLAT_TO_LOCATION TRUE
        FILES ${ios_res}
        )

    set_target_properties(${app_name} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "${app_name}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${COCOS2D_X_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.$(PRODUCT_NAME)"
        MACOSX_BUNDLE_ICON_FILE "Icon-57.png"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/proj.ios/InfoCMake.plist"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${COCOS2D_X_VERSION}"
        )
endif()

#===============================================================================
# Copy resources.
if(XCODE_VERSION)
    # Nothing to do.
elseif(MSVC_IDE)
    cocos_add_copy_depends_dll_command(${app_name})

    # Copy app resources.
    foreach(res ${app_resources})
        file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/${res}" res_path)
        get_filename_component(res_name ${res} NAME)
        add_custom_command(TARGET ${app_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${res_path}"
            "\"$(ProjectDir)${res_name}\""
            )
    endforeach()

    # Copy resource folders to WorkingDir(is $(ProjectDir) in VS).
    file(TO_NATIVE_PATH "${CPP_TESTS_SOURCE_DIR}/Resources" cpp_res)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_LIST_DIR}/../src" src_dir)
    file(TO_NATIVE_PATH
        "${CMAKE_SOURCE_DIR}/cocos/scripting/js-bindings/script" 
        cocos_src_dir
        )

    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND xcopy /Y /Q /E
        "\"${cpp_res}\""
        "\"$(ProjectDir)res\\\""
        COMMAND xcopy /Y /Q /E
        "\"${src_dir}\""
        "\"$(ProjectDir)src\\\""
        COMMAND xcopy /Y /Q /E
        "\"${cocos_src_dir}\""
        "\"$(ProjectDir)script\\\""
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # TODO
else()
    # Copy resource to executable directory.

    # Copy app resources.
    foreach(res ${app_resources})
        get_filename_component(res_name ${res} NAME)
        add_custom_command(TARGET ${app_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_LIST_DIR}/${res}"
            "$<TARGET_FILE_DIR:${app_name}>/Resources/${res_name}"
            )
    endforeach()
    # Copy cpp resources, scripts, src directory to executable directory.
    add_custom_command(TARGET ${app_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CPP_TESTS_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/res"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/src"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_SOURCE_DIR}/cocos/scripting/js-bindings/script"
        "$<TARGET_FILE_DIR:${app_name}>/Resources/script"
        )
endif()

