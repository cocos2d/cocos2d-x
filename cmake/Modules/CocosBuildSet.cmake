# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
        FATAL: In-source builds are not allowed.
            You should create a separate directory for build files.
        ")
endif()

# print cmake debug info
set(CMAKE_DEBUG_TARGET_PROPERTIES
    # INCLUDE_DIRECTORIES
    # COMPILE_DEFINITIONS
    # COMPILE_OPTIONS
    # AUTOUIC_OPTIONS
    # POSITION_INDEPENDENT_CODE
)
# It ensures that when Find*.cmake files included from cmake's Modules dir
# include another *.cmake file with relative path, that file will be included
# also from cmake's Modules dir, to not clash with per-project files.
cmake_policy(SET CMP0017 NEW)

# Use new behaviour with cmake >= 3.1:
# Only interpret if() arguments as variables or keywords when unquoted.
cmake_policy(SET CMP0054 NEW)

# print the info of CMAKE_TOOLCHAIN_FILE, if defined it
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# some useful variables for every one cocos project
set(COCOS_EXTERNAL_DIR ${COCOS2DX_ROOT_PATH}/external)
set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

message(STATUS "PROJECT_NAME:" ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
message(STATUS "COCOS_EXTERNAL_DIR:" ${COCOS_EXTERNAL_DIR})
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
