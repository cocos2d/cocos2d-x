LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PluginFlurryStatic

LOCAL_MODULE_FILENAME := libPluginFlurryStatic

LOCAL_SRC_FILES := \
$(addprefix ../../platform/android/, \
    AnalyticsFlurry.cpp \
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
