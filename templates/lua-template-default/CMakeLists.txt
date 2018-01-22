#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_minimum_required(VERSION 3.1)

set(APP_NAME cocos2dlua)
project(${APP_NAME})

# define some variables
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../..)
# engine path changed, after cocos new
# set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)
set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)
set(RUNTIME_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/runtime-src)


message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})

# works before libcocos2d
include(CocosBuildSet)
CocosBuildSet()

# add engine directory, get cocos library
set(BUILD_LUA_LIBS ON)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH})

set(GAME_SRC ${RUNTIME_SRC_ROOT}/Classes/AppDelegate.cpp
)

if(ANDROID)
  list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.android/app/jni/hellolua/main.cpp)
elseif(LINUX)
  list(APPEND GAME_SRC ${RUNTIME_SRC_ROOT}/proj.linux/main.cpp)
endif()

if(LINUX)
  include_directories(
    /usr/include
    /usr/include/GLFW
    /usr/local/include/GLFW
  )
endif(LINUX)

# Todo solve bug, libGLESv1: STS_GLApi : DTS is not allowed for Package : org.cocos2dx.hellolua
include_directories(
  ${RUNTIME_SRC_ROOT}/Classes
  ${COCOS2DX_ROOT_PATH}/
  ${COCOS2DX_ROOT_PATH}/cocos
  ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/auto
  ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/manual
  ${COCOS2DX_ROOT_PATH}/external/lua/luajit/include
  ${COCOS2DX_ROOT_PATH}/external/
  ${COCOS2DX_ROOT_PATH}/external/lua/tolua
  ${COCOS2DX_ROOT_PATH}/cocos/audio/include
)

if(ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC})
    IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
  # add the executable
  add_executable(${APP_NAME} ${GAME_SRC})
endif(ANDROID)

target_link_libraries(${APP_NAME} luacocos2d)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

# need cocos_mark_resources, when build on mac, refer to lua project
else(MACOSX OR APPLE)
  pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}/Resources/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}/Resources/src
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/cocos2d ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/cocosdenshion ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/cocosbuilder ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/cocostudio ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/extension ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/network ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/ui ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/3d ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/physics3d ${APP_BIN_DIR}/Resources
    )

endif(MACOSX OR APPLE)
