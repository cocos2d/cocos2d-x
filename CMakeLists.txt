cmake_minimum_required(VERSION 2.6)
project (Cocos2dxSamples)

# The version number
set(Cocos2dxSamples_VERSION_MAJOR 3)
set(Cocos2dxSamples_VERSION_MINOR 0)

add_definitions(-DLINUX)

# debug
message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG" )
    add_definitions(-D_DEBUG)
endif()

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c99")

include_directories(
  cocos/2d
  cocos/2d/platform
  cocos/2d/platform/linux
  cocos/base
  cocos/physics
  cocos/math/kazmath/include
  external/jpeg/include/linux
  external/tiff/include/linux
  external/webp/include/linux
  external/glfw3/include/linux
  external/tinyxml2
  external/unzip
  external/chipmunk/include/chipmunk
  external/freetype2/include/linux
)

link_directories(
  /usr/local/lib
  ${CMAKE_SOURCE_DIR}/external/jpeg/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/tiff/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/webp/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/freetype2/prebuilt/linux/${ARCH_DIR}
)

set(COCOS_LIBRARIES
  cocos2d
  cocosbase
  chipmunk_static
  tinyxml2
  kazmath
  unzip
  jpeg
  webp
  tiff
  freetype
  fontconfig
  png
  glfw
  GLEW
  GL
  rt
  z
)

# kazmath
add_subdirectory(cocos/math/kazmath)

# chipmunk library
set(BUILD_STATIC 1)

# chipmunk library
add_subdirectory(external/chipmunk/src)

# unzip library
add_subdirectory(external/unzip)

# tinyxml2 library
add_subdirectory(external/tinyxml2)

# cocos base library
add_subdirectory(cocos/base)

# cocos physics sources
#add_subdirectory(cocos/physics)

# cocos 2d library
add_subdirectory(cocos/2d)

# sample HelloCpp
add_subdirectory(samples/Cpp/HelloCpp)

