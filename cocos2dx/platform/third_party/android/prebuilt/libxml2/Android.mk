LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libxml2_static
LOCAL_MODULE_FILENAME := xml2
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libxml2.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
