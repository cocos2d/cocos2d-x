cmake_minimum_required(VERSION 3.6)

# need to whole-archive this lib
set(target_name js_android_spec)

project(${target_name})

set(${target_name}_src
  ../manual/platform/android/CCJavascriptJavaBridge.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(${target_name}
  PRIVATE ../../..
)

