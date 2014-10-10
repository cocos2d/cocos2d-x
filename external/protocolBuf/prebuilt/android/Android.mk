LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_protocolBuffer_static
LOCAL_MODULE_FILENAME := protocolbuffer
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/protocolbuffer.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
