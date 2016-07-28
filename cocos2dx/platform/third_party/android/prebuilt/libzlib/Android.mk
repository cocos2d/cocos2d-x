LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libzlib_static
LOCAL_MODULE_FILENAME := zlib

LOCAL_SRC_FILES  := libs/$(TARGET_ARCH_ABI)/libz.a

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
