set(LUABINDING_SRC
  ../auto-generated/lua-bindings/lua_cocos2dx_auto.cpp
  ../auto-generated/lua-bindings/lua_cocos2dx_extension_auto.cpp
  ../auto-generated/lua-bindings/lua_cocos2dx_studio_auto.cpp
  ../auto-generated/lua-bindings/lua_cocos2dx_gui_auto.cpp
  ../auto-generated/lua-bindings/lua_cocos2dx_spine_auto.cpp
  ../auto-generated/lua-bindings/lua_cocos2dx_physics_auto.cpp
  bindings/tolua_fix.cpp
  bindings/CCLuaBridge.cpp
  bindings/CCLuaEngine.cpp
  bindings/CCLuaStack.cpp
  bindings/CCLuaValue.cpp
  bindings/Cocos2dxLuaLoader.cpp
  bindings/CCBProxy.cpp
  bindings/LuaOpengl.cpp
  bindings/LuaScriptHandlerMgr.cpp
  bindings/LuaBasicConversions.cpp
  bindings/lua_cocos2dx_manual.cpp
  bindings/lua_cocos2dx_extension_manual.cpp
  bindings/lua_cocos2dx_coco_studio_manual.cpp
  bindings/lua_cocos2dx_gui_manual.cpp
  bindings/lua_cocos2dx_spine_manual.cpp
  bindings/lua_cocos2dx_physics_manual.cpp
  bindings/lua_cocos2dx_deprecated.cpp
  bindings/lua_xml_http_request.cpp
  bindings/LuaSkeletonAnimation.cpp
)

include_directories(
  ../auto-generated/lua-bindings
  bindings
  ../../../cocos/editor-support/cocosbuilder
  ../../../cocos/editor-support/cocostudio
  ../../../cocos/editor-support/spine
  ../../../cocos/gui
  ../../../external/lua/lua
  ../../../external/lua/tolua
)


add_library(luabinding STATIC
  ${LUABINDING_SRC}
)

target_link_libraries(luabinding
  tolua
  lua
  spine
)

set_target_properties(luabinding
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

