LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocosdenshion

LOCAL_SRC_FILES := SimpleAudioEngine.cpp \
jni/SimpleAudioEngineJni.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include
                   
LOCAL_LDLIBS := -llog

            
include $(BUILD_SHARED_LIBRARY)