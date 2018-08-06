LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_localstorage_static

LOCAL_MODULE_FILENAME := liblocalstorage

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := LocalStorage.cpp \
LocalStorage-android.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../..

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

include $(BUILD_STATIC_LIBRARY)

$(call import-add-path,$(LOCAL_PATH)/../..)
