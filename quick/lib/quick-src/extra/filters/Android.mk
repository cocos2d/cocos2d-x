
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := extra_filters_static
LOCAL_MODULE_FILENAME := libextrafilters

ifeq ($(CC_USE_EXTRA_FILTERS),1)

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/filters/CCFilter.cpp \
    $(LOCAL_PATH)/filters/CCBlurFilter.cpp \
    $(LOCAL_PATH)/filters/CCBrightnessFilter.cpp \
    $(LOCAL_PATH)/filters/CCContrastFilter.cpp \
    $(LOCAL_PATH)/filters/CCDropShadowFilter.cpp \
    $(LOCAL_PATH)/filters/CCExposureFilter.cpp \
    $(LOCAL_PATH)/filters/CCGammaFilter.cpp \
    $(LOCAL_PATH)/filters/CCGrayFilter.cpp \
    $(LOCAL_PATH)/filters/CCHazeFilter.cpp \
    $(LOCAL_PATH)/filters/CCHueFilter.cpp \
    $(LOCAL_PATH)/filters/CCMaskFilter.cpp \
    $(LOCAL_PATH)/filters/CCRGBFilter.cpp \
    $(LOCAL_PATH)/filters/CCSaturationFilter.cpp \
    $(LOCAL_PATH)/filters/CCSepiaFilter.cpp \
    $(LOCAL_PATH)/filters/CCSharpenFilter.cpp \
    $(LOCAL_PATH)/filters/CCTestFilter.cpp \
    $(LOCAL_PATH)/filters/CCCustomFilter.cpp \
    $(LOCAL_PATH)/nodes/CCFilteredSprite.cpp \
    $(LOCAL_PATH)/shaders/ccFilterShaders.cpp 

else

LOCAL_SRC_FILES += 

endif


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)


LOCAL_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS) -std=c++11
LOCAL_EXPORT_CFLAGS := -Wno-psabi -DUSE_FILE32API -DCC_LUA_ENGINE_ENABLED=1

include $(BUILD_STATIC_LIBRARY)