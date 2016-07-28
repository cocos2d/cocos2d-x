LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libpng_static
LOCAL_MODULE_FILENAME := png
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libpng.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
