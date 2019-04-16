# print cmake debug info
set(CMAKE_DEBUG_TARGET_PROPERTIES
    # INCLUDE_DIRECTORIES
    # COMPILE_DEFINITIONS
    # COMPILE_OPTIONS
    # AUTOUIC_OPTIONS
    # POSITION_INDEPENDENT_CODE
)

# some useful variables for every one cocos project
set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "using toolchain file:" ${CMAKE_TOOLCHAIN_FILE})
endif()

message(STATUS "PROJECT_NAME:" ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
# delete binary dir if you hope a full clean re-build
message(STATUS "PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})
message(STATUS "ENGINE_BINARY_PATH:" ${ENGINE_BINARY_PATH})

# the default behavior of build module
option(DEBUG_MODE "Debug or Release?" ON)
option(BUILD_LUA_LIBS "Build lua libraries" OFF)
option(BUILD_JS_LIBS "Build js libraries" OFF)

# include helper functions
include(CocosBuildHelpers)

# set common compiler options
# add target compile define function
# add target compile options function
include(CocosConfigDefine)

# config libraries dependence
include(CocosConfigDepend)
