set(JSBINDING_SRC
  ../auto-generated/js-bindings/jsb_cocos2dx_auto.cpp            
  ../auto-generated/js-bindings/jsb_cocos2dx_gui_auto.cpp
  ../auto-generated/js-bindings/jsb_cocos2dx_builder_auto.cpp    
  ../auto-generated/js-bindings/jsb_cocos2dx_spine_auto.cpp
  ../auto-generated/js-bindings/jsb_cocos2dx_extension_auto.cpp  
  ../auto-generated/js-bindings/jsb_cocos2dx_studio_auto.cpp
  bindings/cocos2d_specifics.cpp
  bindings/jsb_opengl_functions.cpp
  bindings/js_manual_conversions.cpp
  bindings/js_bindings_core.cpp
  bindings/jsb_opengl_manual.cpp
  bindings/ScriptingCore.cpp
  bindings/js_bindings_opengl.cpp
  bindings/jsb_opengl_registration.cpp
  bindings/chipmunk/js_bindings_chipmunk_auto_classes.cpp
  bindings/extension/jsb_cocos2dx_extension_manual.cpp
  bindings/chipmunk/js_bindings_chipmunk_functions.cpp
  bindings/gui/jsb_cocos2dx_gui_manual.cpp
  bindings/chipmunk/js_bindings_chipmunk_manual.cpp
  bindings/localstorage/js_bindings_system_functions.cpp
  bindings/chipmunk/js_bindings_chipmunk_registration.cpp
  bindings/localstorage/js_bindings_system_registration.cpp
  bindings/cocosbuilder/js_bindings_ccbreader.cpp
  bindings/network/jsb_websocket.cpp
  bindings/cocostudio/jsb_cocos2dx_studio_manual.cpp
  bindings/network/XMLHTTPRequest.cpp
)

include_directories(
  ../auto-generated/js-bindings
  bindings
  ../../../cocos/
  ../../../cocos/storage
  ../../../cocos/editor-support/cocosbuilder
  ../../../cocos/editor-support/cocostudio
  ../../../cocos/editor-support/spine
  ../../../cocos/gui
  ../../../external/spidermonkey/include/linux/${ARCH_DIR}
)


add_library(jsbinding STATIC
  ${JSBINDING_SRC}
)

target_link_libraries(jsbinding
  js_static
  spine
)

set_target_properties(jsbinding
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

