LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_localstorage_static

LOCAL_MODULE_FILENAME := liblocalstorage

LOCAL_SRC_FILES := LocalStorage.cpp \
LocalStorageAndroid.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../..

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
