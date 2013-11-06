cmake_minimum_required(VERSION 2.6)
project (Cocos2dx)

# The version number
set(Cocos2dxSamples_VERSION_MAJOR 3)
set(Cocos2dxSamples_VERSION_MINOR 0)

include(build/BuildHelpers.CMakeLists.txt)

option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
option(USE_BOX2D "Use box2d for physics library" OFF)
option(DEBUG_MODE "Debug or release?" ON)
option(BUILD_LIBS_LUA "Build lua libraries" ON)
option(BUILD_GUI "Build GUI library" ON)
option(BUILD_NETWORK "Build network library" ON)
option(BUILD_EXTENSIONS "Build extension library" ON)
option(BUILD_EDITOR_SPINE "Build editor support for spine" ON)
option(BUILD_EDITOR_COCOSTUDIO "Build editor support for cocostudio" ON)
option(BUILD_EDITOR_COCOSBUILDER "Build editor support for cocosbuilder" ON)


option(BUILD_HelloCpp "Only build HelloCpp sample" ON)
option(BUILD_TestCpp "Only build TestCpp sample" ON)
option(BUILD_HelloLua "Only build HelloLua sample" ON)
option(BUILD_TestLua "Only build TestLua sample" ON)


if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c99")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

if(USE_CHIPMUNK)
  message("Using chipmunk ...")
  add_definitions(-DLINUX -DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
elseif(USE_BOX2D)
  message("Using box2d ...")
  add_definitions(-DLINUX -DCC_ENABLE_BOX2D_INTEGRATION=1)
else(USE_CHIPMUNK)
  message(FATAL_ERROR "Must choose a physics library.")
endif(USE_CHIPMUNK)

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
  external/linux-specific/fmod/include/${ARCH_DIR}
)

link_directories(
  /usr/local/lib
  ${CMAKE_SOURCE_DIR}/external/jpeg/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/tiff/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/webp/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/freetype2/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/curl/prebuilt/linux/${ARCH_DIR}
  ${CMAKE_SOURCE_DIR}/external/linux-specific/fmod/prebuilt/${ARCH_DIR}
)


# kazmath
add_subdirectory(cocos/math/kazmath)

# chipmunk library
add_subdirectory(external/chipmunk/src)

# box2d library
add_subdirectory(external/Box2D)

# unzip library
add_subdirectory(external/unzip)

# tinyxml2 library
add_subdirectory(external/tinyxml2)

# audio
add_subdirectory(cocos/audio)

# cocos base library
add_subdirectory(cocos/base)

# cocos 2d library
add_subdirectory(cocos/2d)

if(BUILD_GUI)
# gui
add_subdirectory(cocos/gui)
endif(BUILD_GUI)

if(BUILD_NETWORK)
# network
add_subdirectory(cocos/network)
endif(BUILD_NETWORK)

if(BUILD_EXTENSIONS)
# extensions
add_subdirectory(extensions)
endif(BUILD_EXTENSIONS)

## Editor Support

if(BUILD_EDITOR_SPINE)
# spine
add_subdirectory(cocos/editor-support/spine)
endif(BUILD_EDITOR_SPINE)

if(BUILD_EDITOR_COCOSBUILDER)
# cocosbuilder
add_subdirectory(cocos/editor-support/cocosbuilder)
endif(BUILD_EDITOR_COCOSBUILDER)

if(BUILD_EDITOR_COCOSTUDIO)
# cocostudio
add_subdirectory(cocos/editor-support/cocostudio)
# jsoncpp library, cocostuido depends on jsoncpp
add_subdirectory(external/json)
endif(BUILD_EDITOR_COCOSTUDIO)

if(BUILD_LIBS_LUA)
## Scripting
# lua
add_subdirectory(external/lua/lua)

# tolua
add_subdirectory(external/lua/tolua)

# luabinding
add_subdirectory(cocos/scripting)
endif(BUILD_LIBS_LUA)

# build samples
add_subdirectory(samples)
