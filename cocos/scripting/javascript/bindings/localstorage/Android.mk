LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_localstorage_static

LOCAL_MODULE_FILENAME := libcocos2dxjsblocalstorage

LOCAL_SRC_FILES := js_bindings_system_functions.cpp \
                   js_bindings_system_registration.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../../../extensions

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_localstorage_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,scripting/javascript/bindings)
$(call import-module,storage/local-storage)
