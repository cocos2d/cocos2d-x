LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_gui_static

LOCAL_MODULE_FILENAME := libcocos2dxjsbgui

LOCAL_SRC_FILES := jsb_cocos2dx_gui_manual.cpp \
                   ../../../auto-generated/js-bindings/jsb_cocos2dx_gui_auto.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../../../extensions \
                    $(LOCAL_PATH)/../../../../gui

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                            
LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_gui_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,scripting/javascript/bindings)
$(call import-module,gui)
