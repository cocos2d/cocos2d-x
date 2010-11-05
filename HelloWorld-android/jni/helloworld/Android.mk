LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := helloworld

LOCAL_SRC_FILES := HelloWorld.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../cocos2dx \
                   $(LOCAL_PATH)/../cocos2dx/include 
                   
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../../libs/armeabi -lcocos2d -llog

LOCAL_CPPFLAGS := -D_ANDROID              
include $(BUILD_SHARED_LIBRARY)
                   