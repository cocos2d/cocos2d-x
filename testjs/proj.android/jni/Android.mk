LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := test_js_shared

LOCAL_MODULE_FILENAME := libtestjs

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/simple_class.cpp \
                   ../../Classes/simple_native_generated.cpp \
                   ../../../js/JSBindings/cocos_denshion_generated.cpp \
                   ../../../js/JSBindings/cocos2d_generated.cpp \
                   ../../../js/JSBindings/cocos2d_manual_bindings.cpp \
                   ../../../js/JSBindings/ScriptingCore.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,spidermonkey-android)

