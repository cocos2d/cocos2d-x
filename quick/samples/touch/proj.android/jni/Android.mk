LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
    ../../sources/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../sources

LOCAL_CFLAGS += -D__GXX_EXPERIMENTAL_CXX0X__ -std=gnu++11 -Wno-psabi -DCC_LUA_ENGINE_ENABLED=1 $(ANDROID_COCOS2D_BUILD_FLAGS)

LOCAL_WHOLE_STATIC_LIBRARIES := quickcocos2dx

include $(BUILD_SHARED_LIBRARY)

$(call import-module,lib/proj.android)
