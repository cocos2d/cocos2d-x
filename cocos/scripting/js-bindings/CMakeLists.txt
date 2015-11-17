#/****************************************************************************
# Copyright (c) 2014 Chukong Technologies Inc.
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

set(cocos_root ../../..)

#platform
if(WIN32) # Win32
  set(PLATFORM_FOLDER win32)
elseif(APPLE)# osx or ios
  set(PLATFORM_FOLDER mac)
else() # Assume Linux
  set(PLATFORM_FOLDER linux)
endif()

set(JSBINDING_SRC
  auto/jsb_cocos2dx_auto.cpp
  auto/jsb_cocos2dx_audioengine_auto.cpp
  auto/jsb_cocos2dx_builder_auto.cpp
  auto/jsb_cocos2dx_extension_auto.cpp
  auto/jsb_cocos2dx_spine_auto.cpp
  auto/jsb_cocos2dx_studio_auto.cpp
  auto/jsb_cocos2dx_ui_auto.cpp
  auto/jsb_cocos2dx_3d_auto.cpp
  auto/jsb_cocos2dx_3d_extension_auto.cpp
  auto/jsb_cocos2dx_physics3d_auto.cpp
  auto/jsb_cocos2dx_navmesh_auto.cpp
  manual/ScriptingCore.cpp
  manual/cocos2d_specifics.cpp
  manual/js_manual_conversions.cpp
  manual/js_bindings_core.cpp
  manual/js_bindings_opengl.cpp
  manual/jsb_opengl_functions.cpp
  manual/jsb_opengl_manual.cpp
  manual/jsb_opengl_registration.cpp
  manual/jsb_event_dispatcher_manual.cpp
  manual/component/CCComponentJS.cpp
  manual/chipmunk/js_bindings_chipmunk_manual.cpp
  manual/chipmunk/js_bindings_chipmunk_functions.cpp
  manual/chipmunk/js_bindings_chipmunk_auto_classes.cpp
  manual/chipmunk/js_bindings_chipmunk_registration.cpp
  manual/cocosbuilder/js_bindings_ccbreader.cpp
  manual/cocostudio/jsb_cocos2dx_studio_manual.cpp
  manual/cocostudio/jsb_cocos2dx_studio_conversions.cpp
  manual/extension/jsb_cocos2dx_extension_manual.cpp
  manual/localstorage/js_bindings_system_functions.cpp
  manual/localstorage/js_bindings_system_registration.cpp
  manual/network/XMLHTTPRequest.cpp
  manual/network/jsb_websocket.cpp
  manual/network/jsb_socketio.cpp
  manual/spine/jsb_cocos2dx_spine_manual.cpp
  manual/ui/jsb_cocos2dx_ui_manual.cpp
  manual/3d/jsb_cocos2dx_3d_manual.cpp
  manual/physics3d/jsb_cocos2dx_physics3d_manual.cpp
  manual/navmesh/jsb_cocos2dx_navmesh_conversions.cpp
  manual/navmesh/jsb_cocos2dx_navmesh_manual.cpp
  ${cocos_root}/cocos/storage/local-storage/LocalStorage.cpp
)

include_directories(
  auto
  manual
  manual/cocostudio
  manual/spine
  manual/navmesh
  ${cocos_root}/external/spidermonkey/include/${PLATFORM_FOLDER}
  ${cocos_root}/cocos
  ${cocos_root}/cocos/base
  ${cocos_root}/cocos/2d
  ${cocos_root}/cocos/3d
  ${cocos_root}/cocos/ui 
  ${cocos_root}/cocos/audio/include
  ${cocos_root}/cocos/storage
  ${cocos_root}/cocos/network
  ${cocos_root}/cocos/platform
  ${cocos_root}/cocos/physics3d
  ${cocos_root}/cocos/navmesh
  ${cocos_root}/extensions
  ${cocos_root}/external
  ${cocos_root}/cocos/editor-support
  ${cocos_root}/cocos/editor-support/spine
  ${cocos_root}/cocos/editor-support/cocosbuilder
  ${cocos_root}/cocos/editor-support/cocostudio
  ${cocos_root}/external/chipmunk/include/chipmunk
)

add_library(jscocos2d STATIC
  ${JSBINDING_SRC}
)

target_link_libraries(jscocos2d
  sqlite3
  js_static
  xxhash
)

set_target_properties(jscocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

