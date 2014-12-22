LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := PluginProtocolStatic
LOCAL_MODULE_FILENAME := libPluginProtocolStatic

LOCAL_SRC_FILES := ./lib/$(TARGET_ARCH_ABI)/libPluginProtocolStatic.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS := -llog
LOCAL_EXPORT_LDLIBS += -lz

include $(PREBUILT_STATIC_LIBRARY)
