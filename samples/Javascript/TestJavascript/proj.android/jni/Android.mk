LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := test_javascript_shared

LOCAL_MODULE_FILENAME := libtestjavascript

LOCAL_SRC_FILES := testjavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_jsb_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/javascript/bindings)
