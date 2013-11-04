cmake_minimum_required(VERSION 2.6)
project (Cocos2dxSamples)

# The version number
set(Cocos2dxSamples_VERSION_MAJOR 3)
set(Cocos2dxSamples_VERSION_MINOR 0)

include(build/BuildHelpers.CMakeLists.txt)

set(CMAKE_BUILE_TYPE DEBUG)
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c99")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_definitions(-DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1)

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

include_directories(
  .
  cocos
  cocos/audio/include
  cocos/2d
  cocos/2d/platform
  cocos/2d/platform/linux
  cocos/base
  cocos/physics
  cocos/editor-support
  cocos/math/kazmath/include
  extensions
  external
  external/jpeg/include/linux
  external/tiff/include/linux
  external/webp/include/linux
  external/glfw3/include/linux
  external/curl/include/linux/${ARCH_DIR}
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
  ${CMAKE_SOURCE_DIR}/external/curl/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/cocos/audio/third-party/fmod/lib64/api/lib
)

# kazmath
add_subdirectory(cocos/math/kazmath)

# chipmunk library
set(BUILD_STATIC 1)
add_subdirectory(external/chipmunk/src)

# box2d library
add_subdirectory(external/Box2D)

# unzip library
add_subdirectory(external/unzip)

# tinyxml2 library
add_subdirectory(external/tinyxml2)

add_subdirectory(external/json)

# audio
add_subdirectory(cocos/audio)

# cocos base library
add_subdirectory(cocos/base)

# cocos 2d library
add_subdirectory(cocos/2d)

add_subdirectory(cocos/gui)

add_subdirectory(cocos/network)

add_subdirectory(extensions)

add_subdirectory(cocos/editor-support/spine)
add_subdirectory(cocos/editor-support/cocosbuilder)
add_subdirectory(cocos/editor-support/cocostudio)


add_subdirectory(external/lua/lua)
add_subdirectory(external/lua/tolua)

add_subdirectory(cocos/scripting)

# build samples
add_subdirectory(samples)

