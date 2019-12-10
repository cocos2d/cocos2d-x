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

find_program(PYTHON_COMMAND NAMES python2 python)
find_program(COCOS_COMMAND NAME cocos
    PATHS ${COCOS2DX_ROOT_PATH}/tools/cocos2d-console/bin $ENV{COCOS_CONSOLE_ROOT})

message(STATUS "PROJECT_NAME:" ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
# delete binary dir if you hope a full clean re-build
message(STATUS "PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})
message(STATUS "ENGINE_BINARY_PATH:" ${ENGINE_BINARY_PATH})
message(STATUS "PYTHON_PATH:"  ${PYTHON_COMMAND})
message(STATUS "COCOS_COMMAND_PATH:"  ${COCOS_COMMAND})
message(STATUS "HOST_SYSTEM:" ${CMAKE_HOST_SYSTEM_NAME})
# the default behavior of build module
option(BUILD_LUA_LIBS "Build lua libraries" OFF)

# include helper functions
include(CocosBuildHelpers)

# set common compiler options
# add target compile define function
# add target compile options function
include(CocosConfigDefine)

# config libraries dependence
include(CocosConfigDepend)

if(COCOS_COMMAND)
    get_filename_component(cocos2dx_console_dir ${COCOS_COMMAND} DIRECTORY)
    set(COCOS2DX_LUAJIT_ROOT ${cocos2dx_console_dir}/../plugins/plugin_luacompile/bin)
    message(STATUS "COCOS2DX_LUAJIT_ROOT:" ${COCOS2DX_LUAJIT_ROOT})
    if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
        find_program(LUAJIT32_COMMAND NAMES luajit-win32 PATHS ${COCOS2DX_LUAJIT_ROOT}/32bit NO_SYSTEM_ENVIRONMENT_PATH)
        find_program(LUAJIT64_COMMAND NAMES luajit-win32 PATHS ${COCOS2DX_LUAJIT_ROOT}/64bit NO_SYSTEM_ENVIRONMENT_PATH)
    elseif("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux")
        find_program(LUAJIT32_COMMAND NAMES luajit-linux PATHS ${COCOS2DX_LUAJIT_ROOT}/32bit NO_SYSTEM_ENVIRONMENT_PATH)
        find_program(LUAJIT64_COMMAND NAMES luajit-linux PATHS ${COCOS2DX_LUAJIT_ROOT}/64bit NO_SYSTEM_ENVIRONMENT_PATH)
    endif()
endif()


if(WINDOWS OR LINUX)
    message(STATUS "LUAJIT32_COMMAND:" ${LUAJIT32_COMMAND})
    message(STATUS "LUAJIT64_COMMAND:" ${LUAJIT64_COMMAND})
endif()
