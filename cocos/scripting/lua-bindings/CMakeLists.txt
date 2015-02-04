project(LUACOCOS2D)

set(cocos_root ${COCOS2D-X_SOURCE_DIR})

#===============================================================================
# Define library target 'luacocos2d'.
set(LUACOCOS2D_TARGET "luacocos2d" CACHE INTERNAL "")
add_library(${LUACOCOS2D_TARGET} ${CMAKE_CURRENT_LIST_FILE})
cocos_tweak_target_output_directory(${LUACOCOS2D_TARGET})

#===============================================================================
# Set include directories.
target_include_directories(${LUACOCOS2D_TARGET} PUBLIC
    "manual"
    )
target_include_directories(${LUACOCOS2D_TARGET} PRIVATE
    "${cocos_root}/external/lua"
    "${cocos_root}"
    "${cocos_root}/external"
    "${COCOS2D_SOURCE_DIR}/2d"
    "${COCOS2D_SOURCE_DIR}/3d"
    "${COCOS2D_SOURCE_DIR}/base"
    "${COCOS2D_SOURCE_DIR}/editor-support/spine"
    "${COCOS2D_SOURCE_DIR}/editor-support/cocostudio"
    "${COCOS2D_SOURCE_DIR}/editor-support/cocostudio/ActionTimeline"
    "${COCOS2D_SOURCE_DIR}/editor-support/cocosbuilder"
    "${COCOS2D_SOURCE_DIR}/ui"
    "manual/extension"
    "manual/cocostudio"
    "manual/ui"
    "manual/cocos2d"
    "auto"
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
    "manual/tolua_fix.cpp"
    "manual/cocos2d/LuaOpengl.cpp"
    "manual/cocos2d/LuaScriptHandlerMgr.cpp"
    "manual/cocos2d/lua_cocos2dx_deprecated.cpp"
    "manual/cocos2d/lua_cocos2dx_experimental_manual.cpp"
    "manual/cocos2d/lua_cocos2dx_manual.cpp"
    "manual/cocos2d/lua_cocos2dx_physics_manual.cpp"
    "manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp"
    "manual/3d/lua_cocos2dx_3d_manual.cpp"
    "manual/cocosbuilder/CCBProxy.cpp"
    "manual/cocosbuilder/lua_cocos2dx_cocosbuilder_manual.cpp"
    "manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp"
    "manual/cocostudio/CustomGUIReader.cpp"
    "manual/cocostudio/lua_cocos2dx_coco_studio_manual.cpp"
    "manual/cocostudio/lua-cocos-studio-conversions.cpp"
    "manual/cocostudio/lua_cocos2dx_csloader_manual.cpp"
    "manual/controller/lua_cocos2dx_controller_manual.cpp"
    "manual/extension/lua_cocos2dx_extension_manual.cpp"
    "manual/network/lua_extensions.c"
    "manual/network/lua_cocos2dx_network_manual.cpp"
    "manual/network/Lua_web_socket.cpp"
    "manual/network/lua_xml_http_request.cpp"
    "manual/spine/lua_cocos2dx_spine_manual.cpp"
    "manual/spine/LuaSkeletonAnimation.cpp"
    "manual/ui/lua_cocos2dx_experimental_video_manual.cpp"
    "manual/ui/lua_cocos2dx_ui_manual.cpp"
    "manual/video/lua_cocos2dx_experimental_video_manual.cpp"
    "manual/audioengine/lua_cocos2dx_audioengine_manual.cpp"
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
    "auto/lua_cocos2dx_cocosbuilder_auto.cpp"
    "auto/lua_cocos2dx_cocosdenshion_auto.cpp"
    "auto/lua_cocos2dx_controller_auto.cpp"
    "auto/lua_cocos2dx_experimental_auto.cpp"
    "auto/lua_cocos2dx_experimental_video_auto.cpp"
    "auto/lua_cocos2dx_extension_auto.cpp"
    "auto/lua_cocos2dx_physics_auto.cpp"
    "auto/lua_cocos2dx_spine_auto.cpp"
    "auto/lua_cocos2dx_studio_auto.cpp"
    "auto/lua_cocos2dx_csloader_auto.cpp"
    "auto/lua_cocos2dx_ui_auto.cpp"
    "auto/lua_cocos2dx_audioengine_auto.cpp"
    )

#===============================================================================
# Link dependent libraries.
if(COCOS_TARGET_SYSTEM_ANDROID OR
        COCOS_TARGET_SYSTEM_WINDOWS OR
        COCOS_TARGET_SYSTEM_MACOSX)
    cocos_use_package(${LUACOCOS2D_TARGET} LUAJIT REQUIRED)
elseif(COCOS_TARGET_SYSTEM_IOS)
    # luajit for arch: i386, x86_64, arm7, arm7s
    cocos_use_package(${LUACOCOS2D_TARGET} LUAJIT REQUIRED)
    # lua for arch: arm64
    add_subdirectory("../../../external/lua/lua"    "external/lua")
    target_link_libraries(${LUACOCOS2D_TARGET} lua)
elseif(COCOS_TARGET_SYSTEM_LINUX)
    add_subdirectory("../../../external/lua/lua"    "external/lua")
    target_link_libraries(${LUACOCOS2D_TARGET} lua)
else()
endif()
add_subdirectory("../../../external/xxtea"          "external/xxtea")
add_subdirectory("../../../external/lua/luasocket"  "external/luasocket")
add_subdirectory("../../../external/lua/tolua"      "external/tolua")

target_link_libraries(${LUACOCOS2D_TARGET}
    ${COCOS2D_TARGET} xxtea luasocket tolua
    )

# Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp include CCLuaJavaBridge.h,
#    need modify sometime.
if(COCOS_TARGET_SYSTEM_ANDROID)
    target_include_directories(${LUACOCOS2D_TARGET} PRIVATE
        "manual/platform/android"
        )
endif()

