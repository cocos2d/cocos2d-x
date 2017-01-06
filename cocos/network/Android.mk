LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_network_static

LOCAL_MODULE_FILENAME := libnetwork

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := HttpClient-android.cpp \
SocketIO.cpp \
WebSocket.cpp \
CCDownloader.cpp \
CCDownloader-android.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += libwebsockets_static

include $(BUILD_STATIC_LIBRARY)
