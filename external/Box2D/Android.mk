LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := box2d_static

LOCAL_MODULE_FILENAME := libbox2d

dirs := $(shell find $(LOCAL_PATH) -type d -print)
find_files = $(subst $(LOCAL_PATH)/,,$(wildcard $(dir)/*.cpp)) 

LOCAL_SRC_FILES := $(foreach dir, $(dirs), $(find_files))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
                                 
include $(BUILD_STATIC_LIBRARY)
