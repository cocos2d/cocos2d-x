LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_network_static

LOCAL_MODULE_FILENAME := libcocos2dxjsbnetwork

LOCAL_SRC_FILES := XMLHTTPRequest.cpp \
                   jsb_websocket.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += websockets_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,spidermonkey/prebuilt/android)
$(call import-module,scripting/javascript/bindings)
$(call import-module,network)
$(call import-module,websockets/prebuilt/android)
