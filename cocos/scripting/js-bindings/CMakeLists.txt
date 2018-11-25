#/****************************************************************************
# Copyright (c) 2014-2017 Chukong Technologies Inc.
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

set(cocos_root ${COCOS2DX_ROOT_PATH})

#platform
if(APPLE)# osx or ios
    set(PLATFORM_HEADER manual/platform/ios/JavaScriptObjCBridge.h)
    set(PLATFORM_SRC manual/platform/ios/JavaScriptObjCBridge.mm)
elseif(ANDROID)
    # refer to: cocos/scripting/js-bindings/proj.android
endif()

if(ANDROID OR IOS)
    set(PLATFORM_HEADER
        ${PLATFORM_HEADER}
        auto/jsb_cocos2dx_experimental_webView_auto.hpp
        manual/experimental/jsb_cocos2dx_experimental_webView_manual.h
        auto/jsb_cocos2dx_experimental_video_auto.hpp
        manual/experimental/jsb_cocos2dx_experimental_video_manual.h
        )
    set(PLATFORM_SRC
        ${PLATFORM_SRC}
        auto/jsb_cocos2dx_experimental_webView_auto.cpp
        manual/experimental/jsb_cocos2dx_experimental_webView_manual.cpp
        auto/jsb_cocos2dx_experimental_video_auto.cpp
        manual/experimental/jsb_cocos2dx_experimental_video_manual.cpp
        )
endif()

set(JSBINDING_HEADER
    ${PLATFORM_HEADER}
    auto/jsb_cocos2dx_extension_auto.hpp
    auto/jsb_cocos2dx_builder_auto.hpp
    auto/jsb_cocos2dx_physics3d_auto.hpp
    auto/jsb_cocos2dx_ui_auto.hpp
    auto/jsb_cocos2dx_spine_auto.hpp
    auto/jsb_cocos2dx_auto.hpp
    auto/jsb_cocos2dx_studio_auto.hpp
    auto/jsb_cocos2dx_navmesh_auto.hpp
    auto/jsb_cocos2dx_audioengine_auto.hpp
    auto/js_bindings_chipmunk_functions_registration.h
    auto/js_bindings_chipmunk_auto_classes.h
    auto/js_bindings_chipmunk_auto_classes_registration.h
    auto/jsb_cocos2dx_network_auto.hpp
    auto/jsb_cocos2dx_3d_auto.hpp
    auto/jsb_cocos2dx_3d_extension_auto.hpp
    auto/js_bindings_chipmunk_functions.h
    manual/js_bindings_core.h
    manual/js_module_register.h
    manual/ui/jsb_cocos2dx_ui_manual.h
    manual/3d/jsb_cocos2dx_3d_manual.h
    manual/cocosbuilder/js_bindings_ccbreader.h
    manual/js_manual_conversions.h
    manual/extension/jsb_cocos2dx_extension_manual.h
    manual/spine/jsb_cocos2dx_spine_manual.h
    manual/jsb_opengl_registration.h
    manual/jsb_opengl_manual.h
    manual/network/jsb_websocket.h
    manual/network/js_network_manual.h
    manual/network/XMLHTTPRequest.h
    manual/network/jsb_socketio.h
    manual/component/CCComponentJS.h
    manual/navmesh/jsb_cocos2dx_navmesh_conversions.h
    manual/navmesh/jsb_cocos2dx_navmesh_manual.h
    manual/jsb_helper.h
    manual/js_bindings_opengl.h
    manual/chipmunk/js_bindings_chipmunk_manual.h
    manual/chipmunk/js_bindings_chipmunk_registration.h
    manual/js_bindings_config.h
    manual/ScriptingCore.h
    manual/localstorage/js_bindings_system_functions.h
    manual/localstorage/js_bindings_system_functions_registration.h
    manual/localstorage/js_bindings_system_registration.h
    manual/js-BindingsExport.h
    manual/physics3d/jsb_cocos2dx_physics3d_manual.h
    manual/jsb_opengl_functions.h
    manual/cocostudio/jsb_cocos2dx_studio_conversions.h
    manual/cocostudio/jsb_cocos2dx_studio_manual.h
    manual/jsb_event_dispatcher_manual.h
    manual/spidermonkey_specifics.h
    )

set(JSBINDING_SRC
    ${PLATFORM_SRC}
    auto/jsb_cocos2dx_auto.cpp
    auto/jsb_cocos2dx_audioengine_auto.cpp
    auto/jsb_cocos2dx_builder_auto.cpp
    auto/jsb_cocos2dx_extension_auto.cpp
    auto/jsb_cocos2dx_network_auto.cpp
    auto/jsb_cocos2dx_spine_auto.cpp
    auto/jsb_cocos2dx_studio_auto.cpp
    auto/jsb_cocos2dx_ui_auto.cpp
    auto/jsb_cocos2dx_3d_auto.cpp
    auto/jsb_cocos2dx_3d_extension_auto.cpp
    auto/jsb_cocos2dx_physics3d_auto.cpp
    auto/jsb_cocos2dx_navmesh_auto.cpp
    auto/js_bindings_chipmunk_functions.cpp
    auto/js_bindings_chipmunk_auto_classes.cpp
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
    manual/network/js_network_manual.cpp
    manual/spine/jsb_cocos2dx_spine_manual.cpp
    manual/ui/jsb_cocos2dx_ui_manual.cpp
    manual/3d/jsb_cocos2dx_3d_manual.cpp
    manual/physics3d/jsb_cocos2dx_physics3d_manual.cpp
    manual/navmesh/jsb_cocos2dx_navmesh_conversions.cpp
    manual/navmesh/jsb_cocos2dx_navmesh_manual.cpp
    )

list(APPEND JSBINDING_SRC ${JSBINDING_HEADER} ${PLATFORM_HEADER})

add_library(jscocos2d STATIC
            ${JSBINDING_SRC}
            )

target_link_libraries(jscocos2d cocos2d)
add_dependencies(jscocos2d cocos2d)

get_target_property(js_ext_depend external CC_JS_DEPEND)
target_link_libraries(jscocos2d ${js_ext_depend})

target_include_directories(jscocos2d
        INTERFACE ${cocos_root}/cocos/scripting/js-bindings/auto
        INTERFACE ${cocos_root}/cocos/scripting/js-bindings/manual
)

if(WINDOWS)
    target_compile_definitions(jscocos2d PRIVATE _USRJSSTATIC)
endif()

set_target_properties(jscocos2d
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      FOLDER "Internal"
                      )

if(XCODE OR VS)
    cocos_mark_code_files("jscocos2d")
endif()