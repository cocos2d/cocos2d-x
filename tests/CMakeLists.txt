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

# build all test projects, it need the engine library

# library have been build, on ../CMakeLists.txt, uesed to prevent tests project build engine lib again
set(BUILD_ENGINE_DONE ON)

# add engine all tests project
add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-empty-test ${ENGINE_BINARY_PATH}/tests/cpp-empty-test)

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-tests ${ENGINE_BINARY_PATH}/tests/cpp-tests)

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/js-tests/project ${ENGINE_BINARY_PATH}/tests/js-tests)

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-empty-test/project ${ENGINE_BINARY_PATH}/tests/lua-empty-test)

# run on xcode failed, reason might be get GLView failed, but on mac command line, it's success
add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/lua-tests/project ${ENGINE_BINARY_PATH}/tests/lua-test)

# temp feature: add engine all template project, as the test project, it make template project test easier
add_subdirectory(${COCOS2DX_ROOT_PATH}/templates/cpp-template-default ${ENGINE_BINARY_PATH}/template/cpp-template-default)

add_subdirectory(${COCOS2DX_ROOT_PATH}/templates/js-template-default ${ENGINE_BINARY_PATH}/template/js-template-default)

# TODO run on mac/win didn't perfect, need to check later
add_subdirectory(${COCOS2DX_ROOT_PATH}/templates/lua-template-default ${ENGINE_BINARY_PATH}/template/lua-template-default)


