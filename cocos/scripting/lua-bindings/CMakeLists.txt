set(cocos_root ${Cocos2d-X_SOURCE_DIR})

if(WINDOWS)
  add_definitions(-DLUASOCKET_INET_ATON -DLUASOCKET_INET_PTON)
endif()

include_directories(
  ${cocos_root}/external/lua/tolua
  ${cocos_root}/external/lua/lua
  ${cocos_root}/external/lua
  ${cocos_root}/external/xxtea
  ${cocos_root}/external
  ${cocos_root}/cocos
  ${cocos_root}/cocos/ui
  ${cocos_root}/cocos/2d
  ${cocos_root}/cocos/3d
  ${cocos_root}/cocos/base
  ${cocos_root}/cocos/editor-support/spine
  ${cocos_root}/cocos/editor-support/cocostudio
  ${cocos_root}/cocos/editor-support/cocostudio/ActionTimeline
  ${cocos_root}/cocos/editor-support/cocosbuilder
  ${cocos_root}/cocos/editor-support
  ${cocos_root}/cocos/platform
  ${cocos_root}/cocos/audio/include
  manual
  manual/extension
  manual/cocostudio
  manual/ui
  manual/cocos2d
  auto
)

file(GLOB lua_cocos2d_source_files
    "${cocos_root}/external/lua/lua/*.c"
    "${cocos_root}/external/lua/tolua/*.c"
    "${cocos_root}/external/xxtea/xxtea.cpp"
    )

list(APPEND lua_cocos2d_source_files
        ${cocos_root}/external/lua/luasocket/luasocket.c
        ${cocos_root}/external/lua/luasocket/timeout.c
        ${cocos_root}/external/lua/luasocket/buffer.c
        ${cocos_root}/external/lua/luasocket/io.c
        ${cocos_root}/external/lua/luasocket/auxiliar.c
        ${cocos_root}/external/lua/luasocket/options.c
        ${cocos_root}/external/lua/luasocket/inet.c
        ${cocos_root}/external/lua/luasocket/except.c
        ${cocos_root}/external/lua/luasocket/select.c
        ${cocos_root}/external/lua/luasocket/tcp.c
        ${cocos_root}/external/lua/luasocket/udp.c
        ${cocos_root}/external/lua/luasocket/mime.c
        ${cocos_root}/external/lua/luasocket/luasocket_scripts.c
	)

if(WINDOWS)
    list(APPEND lua_cocos2d_source_files
        ${cocos_root}/external/lua/luasocket/wsocket.c
        )
elseif(UNIX)
    # because we have -std=c99
    add_definitions(-D_POSIX_C_SOURCE=200809L)
    if(LINUX)
        add_definitions(-D_BSD_SOURCE)
    endif()
    if(APPLE)
        add_definitions(-D_DARWIN_C_SOURCE)
    endif()

    list(APPEND lua_cocos2d_source_files
        ${cocos_root}/external/lua/luasocket/serial.c
        ${cocos_root}/external/lua/luasocket/unix.c
        ${cocos_root}/external/lua/luasocket/usocket.c
        )
endif()

set(lua_bindings_manual_files
    manual/CCLuaBridge.cpp
    manual/CCLuaEngine.cpp
    manual/CCLuaStack.cpp
    manual/CCLuaValue.cpp
    manual/Cocos2dxLuaLoader.cpp
    manual/LuaBasicConversions.cpp
    manual/tolua_fix.cpp
    manual/cocos2d/LuaOpengl.cpp
    manual/cocos2d/LuaScriptHandlerMgr.cpp
    manual/cocos2d/lua_cocos2dx_deprecated.cpp
    manual/cocos2d/lua_cocos2dx_experimental_manual.cpp
    manual/cocos2d/lua_cocos2dx_manual.cpp
    manual/cocos2d/lua_cocos2dx_physics_manual.cpp
    manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp
    manual/3d/lua_cocos2dx_3d_manual.cpp
    manual/cocosbuilder/CCBProxy.cpp
    manual/cocosbuilder/lua_cocos2dx_cocosbuilder_manual.cpp
    manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp
    manual/cocostudio/CustomGUIReader.cpp
    manual/cocostudio/lua_cocos2dx_coco_studio_manual.cpp
    manual/cocostudio/lua-cocos-studio-conversions.cpp
    manual/cocostudio/lua_cocos2dx_csloader_manual.cpp
    manual/controller/lua_cocos2dx_controller_manual.cpp
    manual/extension/lua_cocos2dx_extension_manual.cpp
    manual/network/lua_extensions.c
    manual/network/lua_cocos2dx_network_manual.cpp
    manual/network/Lua_web_socket.cpp
    manual/network/lua_xml_http_request.cpp
    manual/spine/lua_cocos2dx_spine_manual.cpp
    manual/spine/LuaSkeletonAnimation.cpp
    manual/ui/lua_cocos2dx_experimental_video_manual.cpp
    manual/ui/lua_cocos2dx_ui_manual.cpp
    manual/video/lua_cocos2dx_experimental_video_manual.cpp
    manual/audioengine/lua_cocos2dx_audioengine_manual.cpp
    )

set(lua_bindings_auto_files
    auto/lua_cocos2dx_3d_auto.cpp
    auto/lua_cocos2dx_auto.cpp
    auto/lua_cocos2dx_cocosbuilder_auto.cpp
    auto/lua_cocos2dx_cocosdenshion_auto.cpp
    auto/lua_cocos2dx_controller_auto.cpp
    auto/lua_cocos2dx_experimental_auto.cpp
    auto/lua_cocos2dx_experimental_video_auto.cpp
    auto/lua_cocos2dx_extension_auto.cpp
    auto/lua_cocos2dx_physics_auto.cpp
    auto/lua_cocos2dx_spine_auto.cpp
    auto/lua_cocos2dx_studio_auto.cpp
    auto/lua_cocos2dx_csloader_auto.cpp
    auto/lua_cocos2dx_ui_auto.cpp
    auto/lua_cocos2dx_audioengine_auto.cpp
    )

if(MACOSX)
    set(lua_bindings_manual_files 
        ${lua_bindings_manual_files}
        manual/platform/ios/CCLuaObjcBridge.mm
        )
endif()

set(lua_bindings_files ${lua_cocos2d_source_files} ${lua_bindings_manual_files} ${lua_bindings_auto_files})

add_library(luacocos2d ${lua_bindings_files})
target_link_libraries(luacocos2d cocos2d)
set_target_properties(luacocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
