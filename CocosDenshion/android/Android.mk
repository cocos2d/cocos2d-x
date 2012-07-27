LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocosdenshion_static

LOCAL_MODULE_FILENAME := libcocosdenshion

LOCAL_SRC_FILES := SimpleAudioEngine.cpp \
		   jni/SimpleAudioEngineJni.cpp 

# for OpenSLES
ifeq ($(APP_PLATFORM), android-9)

# define # define the macro to compile through CocosDenshion/android/SimpleAudioEngine.cpp
# LOCAL_CFLAGS := -DENABLE_OPENSL

LOCAL_SRC_FILES += opensl/OpenSLEngine.cpp \
		   opensl/SimpleAudioEngineOpenSL.cpp

LOCAL_EXPORT_LDLIBS := -lOpenSLES\
                       -landroid 

LOCAL_LDLIBS    := -lOpenSLES
LOCAL_LDLIBS    += -llog
LOCAL_LDLIBS    += -landroid

endif


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../cocos2dx/platform/android
            
include $(BUILD_STATIC_LIBRARY)
