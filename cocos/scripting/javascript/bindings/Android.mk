LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_jsb_static

LOCAL_MODULE_FILENAME := libcocos2dxjsb

LOCAL_SRC_FILES := ScriptingCore.cpp \
                   cocos2d_specifics.cpp \
                   jsb_cocos2dx_extension_manual.cpp \
                   js_manual_conversions.cpp \
                   cocosjs_manual_conversions.cpp \
                   js_bindings_chipmunk_manual.cpp \
                   js_bindings_chipmunk_functions.cpp \
                   js_bindings_chipmunk_auto_classes.cpp \
                   js_bindings_chipmunk_registration.cpp \
                   js_bindings_system_functions.cpp \
                   js_bindings_system_registration.cpp \
                   js_bindings_ccbreader.cpp \
                   js_bindings_core.cpp \
                   js_bindings_opengl.cpp \
                   jsb_opengl_functions.cpp \
                   jsb_opengl_manual.cpp \
                   jsb_opengl_registration.cpp \
                   ../../auto-generated/js-bindings/jsb_cocos2dx_auto.cpp \
                   ../../auto-generated/js-bindings/jsb_cocos2dx_extension_auto.cpp \
                   XMLHTTPRequest.cpp \
                   jsb_websocket.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../auto-generated/js-bindings \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../editor-support/cocostudio

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/../../auto-generated/js-bindings 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_localstorage_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += websockets_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_gui_static

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,extensions)
$(call import-module,2d)
$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,network)
$(call import-module,chipmunk)
$(call import-module,storage/local-storage)
$(call import-module,editor-support/cocostudio)
$(call import-module,websockets/prebuilt/android)
$(call import-module,gui)
