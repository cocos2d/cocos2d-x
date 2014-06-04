set(LUABINDING_SRC
  auto/lua_cocos2dx_auto.cpp
  auto/lua_cocos2dx_extension_auto.cpp
  auto/lua_cocos2dx_studio_auto.cpp
  auto/lua_cocos2dx_ui_auto.cpp
  auto/lua_cocos2dx_spine_auto.cpp
  auto/lua_cocos2dx_physics_auto.cpp
  manual/tolua_fix.cpp
  manual/CCLuaBridge.cpp
  manual/CCLuaEngine.cpp
  manual/CCLuaStack.cpp
  manual/CCLuaValue.cpp
  manual/Cocos2dxLuaLoader.cpp
  manual/CCBProxy.cpp
  manual/LuaOpengl.cpp
  manual/LuaScriptHandlerMgr.cpp
  manual/LuaBasicConversions.cpp
  manual/lua_cocos2dx_manual.cpp
  manual/lua_cocos2dx_extension_manual.cpp
  manual/lua_cocos2dx_coco_studio_manual.cpp
  manual/lua_cocos2dx_ui_manual.cpp
  manual/lua_cocos2dx_spine_manual.cpp
  manual/lua_cocos2dx_physics_manual.cpp
  manual/lua_cocos2dx_deprecated.cpp
  manual/lua_xml_http_request.cpp
  manual/LuaSkeletonAnimation.cpp
)

include_directories(
  auto
  manual
  ../../editor-support/cocosbuilder
  ../../editor-support/cocostudio
  ../../editor-support/spine
  ../../ui
  ../../../external/lua/lua
  ../../../external/lua/tolua
  ../../../external/xxtea
)


add_library(luabinding STATIC
  ${LUABINDING_SRC}
)

target_link_libraries(luabinding
  tolua
  lua
  spine
  xxtea
)

set_target_properties(luabinding
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

