set(cocos_root ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include_directories(
  ${cocos_root}/external/lua/tolua/
  ${cocos_root}/external/lua/lua
  ${cocos_root}/external/xxtea
  ${cocos_root}/external 
  ${cocos_root}/cocos 
  ${cocos_root}/cocos/base
  ${cocos_root}/cocos/physics
  ${cocos_root}/cocos/audio/include
  ${cocos_root}/cocos/2d
  ${cocos_root}/cocos/3d
  ${cocos_root}/cocos/editor-support/spine 
  ${cocos_root}/cocos/editor-support/cocostudio 
  ${cocos_root}/cocos/editor-support/cocosbuilder
  ${cocos_root}/cocos/ui
  ${cocos_root}/cocos/network
  ${cocos_root}/cocos/storage
  ${cocos_root}/cocos/editor-support 
  ${cocos_root}/cocos/platform   
  ${CMAKE_CURRENT_SOURCE_DIR}/manual
  ${CMAKE_CURRENT_SOURCE_DIR}/manual/extension
  ${CMAKE_CURRENT_SOURCE_DIR}/manual/cocostudio
  ${CMAKE_CURRENT_SOURCE_DIR}/manual/ui
  ${CMAKE_CURRENT_SOURCE_DIR}/ui
  ${CMAKE_CURRENT_SOURCE_DIR}/manual/cocos2d 
  ${CMAKE_CURRENT_SOURCE_DIR}/auto          
)

file(GLOB lua_cocos2d_source_files 
    "${cocos_root}/external/lua/lua/*.c"
    "${cocos_root}/external/lua/tolua/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/auto/*.cpp"
    "${cocos_root}/external/xxtea/xxtea.cpp"
    )
file(GLOB_RECURSE lua_binding_manual_files "${CMAKE_CURRENT_SOURCE_DIR}/manual/*.cpp")
set(lua_cocos2d_source_files ${lua_cocos2d_source_files} ${lua_binding_manual_files})
# exclude files for other platforms
list(REMOVE_ITEM lua_cocos2d_source_files
     "${CMAKE_CURRENT_SOURCE_DIR}/manual/platform/android/CCLuaJavaBridge.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp"
)

add_library(luacocos2d STATIC ${lua_cocos2d_source_files})
target_link_libraries(luacocos2d cocos2d)
set_target_properties(luacocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
