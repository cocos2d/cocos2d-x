LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := chipmunk_static

LOCAL_MODULE_FILENAME := libchipmunk

dirs := $(shell find $(LOCAL_PATH) -type d -print)
find_files = $(subst $(LOCAL_PATH)/,,$(wildcard $(dir)/*.c)) 

LOCAL_SRC_FILES := $(foreach dir, $(dirs), $(find_files))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/chipmunk
LOCAL_CFLAGS := -std=c99
                                 
include $(BUILD_STATIC_LIBRARY)
