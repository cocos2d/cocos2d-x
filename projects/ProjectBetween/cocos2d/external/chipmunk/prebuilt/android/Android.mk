LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_chipmunk_static
LOCAL_MODULE_FILENAME := chipmunk
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libchipmunk.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
