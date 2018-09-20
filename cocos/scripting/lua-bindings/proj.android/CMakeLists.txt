cmake_minimum_required(VERSION 3.6)

set(target_name lua_android_spec)

project(${target_name})

set(${target_name}_src
  ../manual/platform/android/CCLuaJavaBridge.cpp
  ../manual/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(
  PRIVATE ../../..
)
# whole-archive JNI relatived codes
set_property(TARGET ${target_name} PROPERTY INTERFACE_LINK_LIBRARIES
  -Wl,--whole-archive,$<TARGET_FILE:${target_name}>,--no-whole-archive)     


target_include_directories()
