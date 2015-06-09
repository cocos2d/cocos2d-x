LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := js_tests_shared

LOCAL_MODULE_FILENAME := libjs_tests

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/js_DrawNode3D_bindings.cpp \
                   ../../Classes/js_Effect3D_bindings.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2d_js_static


LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=1

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/js-bindings/proj.android) 
