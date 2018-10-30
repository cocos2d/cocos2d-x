LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ccstorage

LOCAL_MODULE_FILENAME := libstorage

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := LocalStorage.cpp \
LocalStorage-android.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../..

LOCAL_STATIC_LIBRARIES := cc_core

include $(BUILD_STATIC_LIBRARY)
