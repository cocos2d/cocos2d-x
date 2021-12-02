cmake_minimum_required(VERSION 3.6)

# need to whole-archive this lib
set(target_name lua_android_spec)

project(${target_name})

set(${target_name}_src
  ../manual/platform/android/CCLuaJavaBridge.cpp
  ../manual/platform/android/jni/Cocos2dxLuaJavaBridge.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

get_target_property(lua_header ext_luajit INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(tolua_header ext_tolua INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(${target_name}
  PRIVATE ../../..
  PRIVATE ../manual
  PRIVATE ../manual/platform/android
  PRIVATE ${lua_header}
  PRIVATE ${tolua_header}
)

