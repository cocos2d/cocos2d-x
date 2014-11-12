
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := extra_static
LOCAL_MODULE_FILENAME := libextra

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/luabinding/cocos2dx_extra_luabinding.cpp \
    $(LOCAL_PATH)/luabinding/HelperFunc_luabinding.cpp \
    $(LOCAL_PATH)/apptools/HelperFunc.cpp \
    $(LOCAL_PATH)/crypto/CCCrypto.cpp \
    $(LOCAL_PATH)/crypto/base64/libbase64.c \
    $(LOCAL_PATH)/network/CCNetwork.cpp \
    $(LOCAL_PATH)/platform/android/CCHTTPRequestAndroid.cpp \
    $(LOCAL_PATH)/platform/android/CCCryptoAndroid.cpp \
    $(LOCAL_PATH)/platform/android/CCNativeAndroid.cpp \
    $(LOCAL_PATH)/platform/android/CCNetworkAndroid.cpp


#filters
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/luabinding/lua_cocos2dx_extension_filter_auto.cpp \
    $(LOCAL_PATH)/filters/filters/CCFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCBlurFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCBrightnessFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCContrastFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCDropShadowFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCExposureFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCGammaFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCGrayFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCHazeFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCHueFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCMaskFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCRGBFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCSaturationFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCSepiaFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCSharpenFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCTestFilter.cpp \
    $(LOCAL_PATH)/filters/filters/CCCustomFilter.cpp \
    $(LOCAL_PATH)/filters/nodes/CCFilteredSprite.cpp \
    $(LOCAL_PATH)/filters/shaders/ccFilterShaders.cpp 


ifeq ($(ANYSDK_DEFINE),1)
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/anysdk/src/AnySDKListener.cpp \
    $(LOCAL_PATH)/anysdk/src/lua_anysdk_auto.cpp \
    $(LOCAL_PATH)/anysdk/src/lua_anysdk_manual.cpp
endif


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/luabinding

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES) \
                    $(LOCAL_PATH)/../../../../cocos2d-x/cocos \
                    $(LOCAL_PATH)/../../../../cocos2d-x/external/lua/luajit/include \
                    $(LOCAL_PATH)/../../../../cocos2d-x/external/lua/tolua \
                    $(LOCAL_PATH)/../../../../cocos2d-x/external \
                    $(LOCAL_PATH)/../../../../cocos2d-x/cocos/scripting/lua-bindings/manual

#filters
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../cocos2d-x/extensions





include $(BUILD_STATIC_LIBRARY)

