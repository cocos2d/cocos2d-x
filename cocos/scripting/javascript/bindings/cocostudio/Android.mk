LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_studio_static

LOCAL_MODULE_FILENAME := libcocos2dxjsbstudio

LOCAL_SRC_FILES := jsb_cocos2dx_studio_manual.cpp \
                   ../../../auto-generated/js-bindings/jsb_cocos2dx_studio_auto.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../../../extensions \
                    $(LOCAL_PATH)/../../../../editor-support/cocostudio

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                            
LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,scripting/javascript/bindings)
$(call import-module,editor-support/cocostudio)
