LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := quickx_static
LOCAL_MODULE_FILENAME := libquickx
LOCAL_SRC_FILES := ./liblua.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
