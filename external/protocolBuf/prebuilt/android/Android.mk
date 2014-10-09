LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := protocolBuffer_static
LOCAL_MODULE_FILENAME := libprotobuf
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libprotobuf.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)
