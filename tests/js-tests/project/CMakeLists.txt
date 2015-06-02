#/****************************************************************************
# Copyright (c) 2015 Chukong Technologies Inc.
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

set(APP_NAME js-tests)

if(WIN32)

else()
  set(PLATFORM_SRC
    proj.linux/main.cpp
  )
endif()

set(SAMPLE_SRC
  Classes/AppDelegate.cpp
  Classes/js_DrawNode3D_bindings.cpp
  Classes/js_Effect3D_bindings.cpp
  ${PLATFORM_SRC}
)

include_directories(
  Classes
  ../../../cocos/scripting/js-bindings/auto
  ../../../cocos/scripting/js-bindings/manual
  ../../../cocos/base
  ../../../cocos/editor-support
  ../../../cocos/audio/include
  ../../../external/spidermonkey/include/${PLATFORM_FOLDER}
  ../../../external/chipmunk/include/chipmunk
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME}
  jscocos2d
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")


if(LINUX)
    set(RES_PREFIX "/Resources")
else()
    set(RES_PREFIX "")
endif()

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/script
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}${RES_PREFIX}/src
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.js
  COMMAND ${CMAKE_COMMAND} -E remove ${APP_BIN_DIR}${RES_PREFIX}/*.json
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../../cocos/scripting/js-bindings/script ${APP_BIN_DIR}${RES_PREFIX}/script
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../main.js ${APP_BIN_DIR}${RES_PREFIX}/main.js
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../project.json ${APP_BIN_DIR}${RES_PREFIX}/project.json
  )
