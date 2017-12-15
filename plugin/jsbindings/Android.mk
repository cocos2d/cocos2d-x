LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_pluginx_static

LOCAL_MODULE_FILENAME := libcocos2dxjsbpluginx

LOCAL_SRC_FILES := auto/jsb_cocos2dx_pluginx_auto.cpp \
                   manual/jsb_pluginx_basic_conversions.cpp \
                   manual/jsb_pluginx_extension_registration.cpp \
                   manual/jsb_pluginx_manual_callback.cpp \
                   manual/jsb_pluginx_manual_protocols.cpp \
                   manual/jsb_pluginx_spidermonkey_specifics.cpp \
                   manual/pluginxUTF8.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT -std=c++11

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH)/manual \
                    $(LOCAL_PATH)/auto \
                    $(LOCAL_PATH)/../../cocos \
                    $(LOCAL_PATH)/../protocols/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/manual \
                           $(LOCAL_PATH)/auto

LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,.)
$(call import-module,plugin/protocols/proj.android/jni)
