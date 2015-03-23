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

project(LUACOCOS2D)

set(cocos_root ${COCOS2D-X_SOURCE_DIR})

#===============================================================================
# Define library target 'luacocos2d'.
set(LUACOCOS2D_TARGET "luacocos2d" CACHE INTERNAL "")
add_library(${LUACOCOS2D_TARGET} ${CMAKE_CURRENT_LIST_FILE})

#===============================================================================
# Set include directories.
target_include_directories(${LUACOCOS2D_TARGET} PUBLIC
    "manual"
    "manual/tolua"
    )
target_include_directories(${LUACOCOS2D_TARGET} PRIVATE
    "${cocos_root}"
    "${cocos_root}/external"
    "${cocos_root}/external/lua"
    "${COCOS2D_SOURCE_DIR}/2d"
    "${COCOS2D_SOURCE_DIR}/3d"
    "${COCOS2D_SOURCE_DIR}/base"
    "${COCOS2D_SOURCE_DIR}/ui"
    "auto"
    "manual/cocos2d"
    "manual/extension"
    "manual/ui"
    )

#===============================================================================
# Add sources.
cocos_target_sources(${LUACOCOS2D_TARGET} GROUP "manual-binding" FILES
    "manual/CCLuaBridge.cpp"
    "manual/CCLuaEngine.cpp"
    "manual/CCLuaStack.cpp"
    "manual/CCLuaValue.cpp"
    "manual/Cocos2dxLuaLoader.cpp"
    "manual/LuaBasicConversions.cpp"
    "manual/cocos2d/LuaOpengl.cpp"
    "manual/cocos2d/LuaScriptHandlerMgr.cpp"
    "manual/cocos2d/lua_cocos2dx_deprecated.cpp"
    "manual/cocos2d/lua_cocos2dx_experimental_manual.cpp"
    "manual/cocos2d/lua_cocos2dx_manual.cpp"
    "manual/cocos2d/lua_cocos2dx_physics_manual.cpp"
    "manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp"
    "manual/3d/lua_cocos2dx_3d_manual.cpp"
    "manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp"
    "manual/controller/lua_cocos2dx_controller_manual.cpp"
    "manual/extension/lua_cocos2dx_extension_manual.cpp"
    "manual/network/lua_extensions.c"
    "manual/network/lua_cocos2dx_network_manual.cpp"
    "manual/network/Lua_web_socket.cpp"
    "manual/network/lua_xml_http_request.cpp"
    "manual/ui/lua_cocos2dx_experimental_video_manual.cpp"
    "manual/ui/lua_cocos2dx_ui_manual.cpp"
    "manual/video/lua_cocos2dx_experimental_video_manual.cpp"
    "manual/audioengine/lua_cocos2dx_audioengine_manual.cpp"
    "manual/tolua/tolua_event.c"
    "manual/tolua/tolua_is.c"
    "manual/tolua/tolua_map.c"
    "manual/tolua/tolua_push.c"
    "manual/tolua/tolua_to.c"
    "manual/tolua/tolua_fix.cpp"
    )

if(COCOS_TARGET_SYSTEM_MACOSX)
    # Why MacOS's source located in ios directory?
    cocos_target_sources(${LUACOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/ios/CCLuaObjcBridge.h"
        "manual/platform/ios/CCLuaObjcBridge.mm"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    cocos_target_sources(${LUACOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/ios/CCLuaObjcBridge.h"
        "manual/platform/ios/CCLuaObjcBridge.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    cocos_target_sources(${LUACOCOS2D_TARGET} GROUP "platform-binding" FILES
        "manual/platform/android/CCLuaJavaBridge.cpp"
        "manual/platform/android/CCLuaJavaBridge.h"
        "manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp"
        "manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.h"
        )
endif()

cocos_target_sources(${LUACOCOS2D_TARGET} GROUP "auto-binding" FILES
    "auto/lua_cocos2dx_3d_auto.cpp"
    "auto/lua_cocos2dx_auto.cpp"
    "auto/lua_cocos2dx_cocosdenshion_auto.cpp"
    "auto/lua_cocos2dx_controller_auto.cpp"
    "auto/lua_cocos2dx_experimental_auto.cpp"
    "auto/lua_cocos2dx_experimental_video_auto.cpp"
    "auto/lua_cocos2dx_extension_auto.cpp"
    "auto/lua_cocos2dx_physics_auto.cpp"
    "auto/lua_cocos2dx_ui_auto.cpp"
    "auto/lua_cocos2dx_audioengine_auto.cpp"
    )

#===============================================================================
# Link dependent libraries.
cocos_use_package(${LUACOCOS2D_TARGET} LUAJIT REQUIRED)
if(COCOS_TARGET_SYSTEM_IOS)
    # lua for arch: arm64
    cocos_use_package(${LUACOCOS2D_TARGET} LUA REQUIRED)
endif()

cocos_use_package(${LUACOCOS2D_TARGET} XXTEA REQUIRED)
cocos_use_package(${LUACOCOS2D_TARGET} LUASOCKET REQUIRED)

target_link_libraries(${LUACOCOS2D_TARGET} ${COCOS2D_TARGET})

# Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp include CCLuaJavaBridge.h,
#    need modify sometime.
if(COCOS_TARGET_SYSTEM_ANDROID)
    target_include_directories(${LUACOCOS2D_TARGET} PRIVATE
        "manual/platform/android"
        )
endif()

