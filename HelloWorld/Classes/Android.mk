LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game_logic

LOCAL_SRC_FILES := AppDelegate.cpp \
                   HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../cocos2dx/lua_support 

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../android/libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -lcocosdenshion \
                -L$(call host-path, $(LOCAL_PATH)/../../cocos2dx/platform/third_party/android/libraries/$(TARGET_ARCH_ABI)) -lcurl
            
include $(BUILD_SHARED_LIBRARY)