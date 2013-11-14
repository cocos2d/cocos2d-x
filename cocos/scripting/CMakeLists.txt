set(LUABINDING_SRC
  auto-generated/lua-bindings/lua_cocos2dx_auto.cpp
  auto-generated/lua-bindings/lua_cocos2dx_extension_auto.cpp
  auto-generated/lua-bindings/lua_cocos2dx_studio_auto.cpp
  lua/bindings/tolua_fix.c
  lua/bindings/CCLuaBridge.cpp
  lua/bindings/CCLuaEngine.cpp
  lua/bindings/CCLuaStack.cpp
  lua/bindings/CCLuaValue.cpp
  lua/bindings/Cocos2dxLuaLoader.cpp
  lua/bindings/CCBProxy.cpp
  lua/bindings/LuaOpengl.cpp
  lua/bindings/LuaScriptHandlerMgr.cpp
  lua/bindings/LuaBasicConversions.cpp
  lua/bindings/lua_cocos2dx_manual.cpp
  lua/bindings/lua_cocos2dx_extension_manual.cpp
  lua/bindings/lua_cocos2dx_coco_studio_manual.cpp
  lua/bindings/lua_cocos2dx_deprecated.cpp
  lua/bindings/lua_xml_http_request.cpp
)

include_directories(
  auto-generated/lua-bindings
  lua/bindings
  ../../cocos/editor-support/cocosbuilder
  ../../cocos/editor-support/cocostudio
  ../../cocos/gui
  ../../external/lua/lua
  ../../external/lua/tolua
)


add_library(luabinding STATIC
  ${LUABINDING_SRC}
)

target_link_libraries(luabinding
  tolua
  lua
)

set_target_properties(luabinding
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)
