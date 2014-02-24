LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_jsb_static

LOCAL_MODULE_FILENAME := libcocos2dxjsb

LOCAL_SRC_FILES := ScriptingCore.cpp \
                   cocos2d_specifics.cpp \
                   js_manual_conversions.cpp \
                   js_bindings_core.cpp \
                   js_bindings_opengl.cpp \
                   jsb_opengl_functions.cpp \
                   jsb_opengl_manual.cpp \
                   jsb_opengl_registration.cpp \
                   ../../auto-generated/js-bindings/jsb_cocos2dx_auto.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../audio/include \
                    $(LOCAL_PATH)/../../../storage \
                    $(LOCAL_PATH)/../../auto-generated/js-bindings \
                    $(LOCAL_PATH)/../../../../extensions \
                    $(LOCAL_PATH)/../../../editor-support/spine \
                    $(LOCAL_PATH)/../../../editor-support


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/../../auto-generated/js-bindings \
                           $(LOCAL_PATH)/../../../audio/include 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,2d)
$(call import-module,audio/android)
