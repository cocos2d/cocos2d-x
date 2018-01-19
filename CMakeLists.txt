#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015-2017 Chukong Technologies Inc.
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

# this file only build engine libiary, not pull other project

# The version number
set(COCOS2D_X_VERSION 3.17)

# feature, not finish
if(USE_COCOS_PREBUILT_LIBS)
  # set the staic lib name needed to find
  if(BUILD_CPP_LIBS)
    set(NEED_LIB cocos2d)
  elseif(BUILD_LUA_LIBS)
    set(NEED_LIB luacocos2d)
  elseif(BUILD_JS_LIBS)
    set(NEED_LIB jscocos2d)
  endif()

  # find static libs, for COCOS_PREBUILT_LIBS_PATH
  cocos_find_static_libs(${NEED_LIB})
  if(FIND_COCOS_STATIC_LIBS)
    MESSAGE(STATUS "use cocos prebuilt libs: ${NEED_LIB}")
  else()
    MESSAGE(FATAL_ERROR "[ USE_COCOS_PREBUILT_LIBS=ON ], but can't find cocos prebuilt libs: ${NEED_LIB}")
    return()
  endif(FIND_COCOS_STATIC_LIBS)

else()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cocos ${ENGINE_BINARY_PATH}/cocos2dx/cocos)

  ## Lua lib
  if(BUILD_LUA_LIBS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cocos/scripting/lua-bindings ${ENGINE_BINARY_PATH}/cocos2dx/lua-bindings)
  endif(BUILD_LUA_LIBS)

  ## JS lib
  if(BUILD_JS_LIBS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cocos/scripting/js-bindings ${ENGINE_BINARY_PATH}/cocos2dx/js-bindings)
  endif(BUILD_JS_LIBS)
endif(USE_COCOS_PREBUILT_LIBS)


