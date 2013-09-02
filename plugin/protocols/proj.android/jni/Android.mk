LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PluginProtocolStatic

LOCAL_MODULE_FILENAME := libPluginProtocolStatic

LOCAL_SRC_FILES :=\
$(addprefix ../../platform/android/, \
	PluginFactory.cpp \
    PluginJniHelper.cpp \
    PluginUtils.cpp \
    PluginProtocol.cpp \
    ProtocolAnalytics.cpp \
    ProtocolIAP.cpp \
    ProtocolAds.cpp \
    ProtocolShare.cpp \
    ProtocolUser.cpp \
    ProtocolSocial.cpp \
) \
../../PluginManager.cpp \
../../PluginParam.cpp

LOCAL_CFLAGS := -Wno-psabi
LOCAL_EXPORT_CFLAGS := -Wno-psabi

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include $(LOCAL_PATH)/../../platform/android
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include $(LOCAL_PATH)/../../platform/android

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
