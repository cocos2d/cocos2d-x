LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_network_static

LOCAL_MODULE_FILENAME := libnetwork

LOCAL_SRC_FILES := HttpClient.cpp \
SocketIO.cpp \
WebSocket.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../.. \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../platform/android \
$(LOCAL_PATH)/../../external/curl/include/android \
$(LOCAL_PATH)/../../external/websockets/include/android

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static
LOCAL_STATIC_LIBRARIES += libwebsockets_static

include $(BUILD_STATIC_LIBRARY)
