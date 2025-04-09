cmake_minimum_required(VERSION 3.6)
set(target_name lua_ohos_spec)

project(${target_name})

set(${target_name}_src
  ../manual/CCLuaBridge.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

get_target_property(lua_header ext_luajit INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(tolua_header ext_tolua INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(${target_name}
  PRIVATE ../../..
  PRIVATE ../manual
  PRIVATE ../manual/platform
  PRIVATE ${lua_header}
  PRIVATE ${tolua_header}
)