LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocosdenshion

LOCAL_SRC_FILES := SimpleAudioEngine.cpp \
jni/SimpleAudioEngineJni.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../../cocos2dx                   
            
include $(BUILD_STATIC_LIBRARY)