cmake_minimum_required(VERSION 2.8)

project (GAFPlayer)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources
  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ShadersPrecompiled
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/math
  ${CMAKE_CURRENT_SOURCE_DIR}/cocos/base
)


file(GLOB_RECURSE gaf_source_files
  "${CMAKE_CURRENT_SOURCE_DIR}/SOURCES/*.cpp")

add_library(gafplayer ${gaf_source_files})

set_target_properties(gafplayer
  PROPERTIES
  ARCHIVER_OUTPUT_DIRECTORY "{CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "{CMAKE_BINARY_DIR}/lib")

install(DIRECTORY Sources/ DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES_MATCHING PATTERN "*.h")


