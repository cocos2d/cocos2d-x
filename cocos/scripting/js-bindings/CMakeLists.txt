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

project(JSCOCOS2D)

set(cocos_root ${COCOS2D-X_SOURCE_DIR})

#===============================================================================
# Define library target 'jscocos2d'.
set(JSCOCOS2D_TARGET "jscocos2d" CACHE INTERNAL "")
add_library(${JSCOCOS2D_TARGET} ${CMAKE_CURRENT_LIST_FILE})

#===============================================================================
# Set include directories.
target_include_directories(${JSCOCOS2D_TARGET} PUBLIC
    "auto"
    "manual"
    )
target_include_directories(${JSCOCOS2D_TARGET} PRIVATE
    "${cocos_root}"
    "${cocos_root}/external"
    "${COCOS2D_SOURCE_DIR}/2d"
    # "${COCOS2D_SOURCE_DIR}/3d"
    "${COCOS2D_SOURCE_DIR}/base"
    "${COCOS2D_SOURCE_DIR}/storage"
    "${COCOS2D_SOURCE_DIR}/ui"
    "manual/cocos2d"
    "manual/extension"
    "manual/ui"
    )

#===============================================================================
# Add sources.
cocos_target_sources(${JSCOCOS2D_TARGET} GROUP "manual-binding" FILES
    "manual/ScriptingCore.cpp"
    "manual/cocos2d_specifics.cpp"
    "manual/js_manual_conversions.cpp"
    "manual/js_bindings_core.cpp"
    "manual/js_bindings_opengl.cpp"
    "manual/jsb_opengl_functions.cpp"
    "manual/jsb_opengl_manual.cpp"
    "manual/jsb_opengl_registration.cpp"
    "manual/jsb_event_dispatcher_manual.cpp"
    "manual/chipmunk/js_bindings_chipmunk_manual.cpp"
    "manual/chipmunk/js_bindings_chipmunk_functions.cpp"
    "manual/chipmunk/js_bindings_chipmunk_auto_classes.cpp"
    "manual/chipmunk/js_bindings_chipmunk_registration.cpp"
    "manual/extension/jsb_cocos2dx_extension_manual.cpp"
    "manual/localstorage/js_bindings_system_functions.cpp"
    "manual/localstorage/js_bindings_system_registration.cpp"
    "manual/network/XMLHTTPRequest.cpp"
    "manual/network/jsb_websocket.cpp"
    "manual/network/jsb_socketio.cpp"
    "manual/ui/jsb_cocos2dx_ui_manual.cpp"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    # Why MacOS's source located in ios directory?
    cocos_target_sources(${JSCOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/ios/JavaScriptObjCBridge.h"
        "manual/platform/ios/JavaScriptObjCBridge.mm"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    cocos_target_sources(${JSCOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/ios/JavaScriptObjCBridge.h"
        "manual/platform/ios/JavaScriptObjCBridge.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    cocos_target_sources(${JSCOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/android/CCJavascriptJavaBridge.cpp"
        "manual/platform/android/CCJavascriptJavaBridge.h"
        )
endif()

cocos_target_sources(${JSCOCOS2D_TARGET} GROUP "auto-binding" FILES
    "auto/jsb_cocos2dx_auto.cpp"
    "auto/jsb_cocos2dx_extension_auto.cpp"
    "auto/jsb_cocos2dx_ui_auto.cpp"
    )

#===============================================================================
# Link dependent libraries.

cocos_use_package(${JSCOCOS2D_TARGET} SPIDERMONKEY REQUIRED)

target_link_libraries(${JSCOCOS2D_TARGET}
    ${COCOS2D_TARGET}
    )

#===============================================================================
# Specific settings.

if(COCOS_TARGET_SYSTEM_ANDROID)
    # spidermonkey/js/HashTable.h use limits macros
    target_compile_definitions(${JSCOCOS2D_TARGET} PUBLIC "__STDINT_LIMITS")
endif()
