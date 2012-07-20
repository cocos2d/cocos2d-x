LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := test_javascript_shared

LOCAL_MODULE_FILENAME := libtestjavascript

LOCAL_SRC_FILES := testjavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../../../scripting/javascript/bindings/cocos_denshion_generated.cpp \
                   ../../../../scripting/javascript/bindings/cocos2d_generated.cpp \
                   ../../../../scripting/javascript/bindings/cocos2d_manual_bindings.cpp \
                   ../../../../scripting/javascript/bindings/ScriptingCore.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/javascript/spidermonkey-android)
$(call import-module,cocos2dx)
$(call import-module,cocosdenshion/android)


