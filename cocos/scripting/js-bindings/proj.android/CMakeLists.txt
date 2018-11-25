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

# WARN, CCJavascriptJavaBridge.h:51 char TypeInvalid = -1 [-Wc++11-narrowing]
target_compile_options(${target_name} PUBLIC -Wno-c++11-narrowing)

get_target_property(spiderm_header ext_spidermonkey INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(${target_name}
  PRIVATE ../../..
  PRIVATE ../manual
  PRIVATE ../manual/platform/android
  PRIVATE ${spiderm_header}
)

