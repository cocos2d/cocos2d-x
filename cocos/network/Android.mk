LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_network_static

LOCAL_MODULE_FILENAME := libnetwork

LOCAL_SRC_FILES := \
SocketIO.cpp \
WebSocket.cpp

ifeq ($(CC_USE_CURL),1)
LOCAL_SRC_FILES += HttpClient.cpp
endif


LOCAL_EXPORT_C_INCLUDES :=

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../external/curl/include/android \
                    $(LOCAL_PATH)/../../external/websockets/include/android

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

ifeq ($(CC_USE_CURL),1)
LOCAL_STATIC_LIBRARIES += cocos_curl_static
endif

LOCAL_STATIC_LIBRARIES += libwebsockets_static

include $(BUILD_STATIC_LIBRARY)
