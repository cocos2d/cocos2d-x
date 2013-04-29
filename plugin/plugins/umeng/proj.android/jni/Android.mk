LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PluginUmengStatic

LOCAL_MODULE_FILENAME := libPluginUmengStatic

LOCAL_SRC_FILES := \
$(addprefix ../../platform/android/, \
    AnalyticsUmeng.cpp \
) \

LOCAL_CFLAGS := 

LOCAL_EXPORT_CFLAGS := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include 

LOCAL_WHOLE_STATIC_LIBRARIES := PluginProtocolStatic

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)

$(call import-module, protocols/proj.android/jni)

