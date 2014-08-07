#luacocos2d
set(LIBLUACOCOS2D_SRC
  auto/lua_cocos2dx_auto.cpp
  auto/lua_cocos2dx_physics_auto.cpp
  auto/lua_cocos2dx_experimental_auto.cpp
  manual/tolua_fix.cpp
  manual/CCLuaBridge.cpp
  manual/CCLuaEngine.cpp
  manual/CCLuaStack.cpp
  manual/CCLuaValue.cpp
  manual/Cocos2dxLuaLoader.cpp
  manual/LuaBasicConversions.cpp
  manual/cocos2d/lua_cocos2dx_deprecated.cpp
  manual/cocos2d/lua_cocos2dx_experimental_manual.cpp
  manual/cocos2d/lua_cocos2dx_manual.cpp
  manual/cocos2d/lua_cocos2dx_physics_manual.cpp
  manual/cocos2d/LuaOpengl.cpp
  manual/cocos2d/LuaScriptHandlerMgr.cpp
)

include_directories(
  auto
  manual
  manual/cocos2d
  manual/extension 
  manual/cocostudio
  manual/ui
  ../../2d
  ../../3d
  ../../../extensions
  ../../../external/lua/lua
  ../../../external/lua/tolua
  ../../../external/xxtea
)


add_library(luacocos2d STATIC
  ${LIBLUACOCOS2D_SRC}
)

target_link_libraries(luacocos2d
  tolua
  lua
  xxtea
)

set_target_properties(luacocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


#luacocosdenshion
set(LIBLUACOCOSDENSHION_SRC
  auto/lua_cocos2dx_cocosdenshion_auto.cpp
  manual/cocosdenshion/lua_cocos2dx_cocosdenshion_manual.cpp
)

include_directories(
  auto
  manual/cocosdenshion
  ../../audio/include
)

add_library(luacocosdenshion STATIC
  ${LIBLUACOCOSDENSHION_SRC}
)

set_target_properties(luacocosdenshion
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luanetwork
set(LIBLUANETWORK_SRC
  manual/network/lua_cocos2dx_network_manual.cpp
  manual/network/lua_xml_http_request.cpp
)

include_directories(
  manual/network
  ../../network
)

add_library(luanetwork STATIC
  ${LIBLUANETWORK_SRC}
)

set_target_properties(luanetwork
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luacocosbuilder
set(LIBLUACOCOSBUILDER_SRC
  auto/lua_cocos2dx_cocosbuilder_auto.cpp
  manual/cocosbuilder/lua_cocos2dx_cocosbuilder_manual.cpp
  manual/cocosbuilder/CCBProxy.cpp
)

include_directories(
  auto
  manual/cocosbuilder
  ../../editor-support/cocosbuilder
)

add_library(luacocosbuilder STATIC
  ${LIBLUACOCOSBUILDER_SRC}
)

set_target_properties(luacocosbuilder
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luacocostudio
set(LIBLUACOCOSTUDIO_SRC
  auto/lua_cocos2dx_studio_auto.cpp
  manual/cocostudio/lua_cocos2dx_coco_studio_manual.cpp
)

include_directories(
  auto
  manual/cocostudio
  ../../editor-support/cocostudio
)

add_library(luacocostudio STATIC
  ${LIBLUACOCOSTUDIO_SRC}
)

set_target_properties(luacocostudio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luaspine
set(LIBLUASPINE_SRC
  auto/lua_cocos2dx_spine_auto.cpp
  manual/spine/LuaSkeletonAnimation.cpp
  manual/spine/lua_cocos2dx_spine_manual.cpp
)

include_directories(
  auto
  manual/spine
  ../../editor-support/spine
)

add_library(luaspine STATIC
  ${LIBLUASPINE_SRC}
)

set_target_properties(luaspine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luaextension
set(LIBLUAEXTENSION_SRC
  auto/lua_cocos2dx_extension_auto.cpp
  manual/extension/lua_cocos2dx_extension_manual.cpp
)

include_directories(
  auto
  manual/extension
  ../../../extensions
)

add_library(luaextension STATIC
  ${LIBLUAEXTENSION_SRC}
)

set_target_properties(luaextension
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#luaui
set(LIBLUAUI_SRC
  auto/lua_cocos2dx_ui_auto.cpp
  manual/ui/lua_cocos2dx_ui_manual.cpp
)

include_directories(
  auto
  manual/ui
  ../../ui
)

add_library(luaui STATIC
  ${LIBLUAUI_SRC}
)

set_target_properties(luaui
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
