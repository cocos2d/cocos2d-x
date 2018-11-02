LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ccnet

LOCAL_MODULE_FILENAME := libnet

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := HttpClient-android.cpp \
SocketIO.cpp \
WebSocket.cpp \
CCDownloader.cpp \
CCDownloader-android.cpp \
Uri.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES := cc_core
LOCAL_STATIC_LIBRARIES += ext_websockets

include $(BUILD_STATIC_LIBRARY)
