LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_freetype2_static
LOCAL_MODULE_FILENAME := freetype2
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/include/freetype2
include $(PREBUILT_STATIC_LIBRARY)
