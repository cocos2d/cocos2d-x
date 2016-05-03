LOCAL_PATH := $(call my-dir)

#New AudioEngine
include $(CLEAR_VARS)

LOCAL_MODULE := audioengine_static

LOCAL_MODULE_FILENAME := libaudioengine

LOCAL_SRC_FILES := AudioEngine-inl.cpp \
                   ../AudioEngine.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_EXPORT_LDLIBS := -lOpenSLES

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android

include $(BUILD_STATIC_LIBRARY)

#SimpleAudioEngine
include $(CLEAR_VARS)

LOCAL_MODULE := cocosdenshion_static

LOCAL_MODULE_FILENAME := libcocosdenshion

LOCAL_SRC_FILES := cddSimpleAudioEngine.cpp \
                   ccdandroidUtils.cpp \
                   jni/cddandroidAndroidJavaEngine.cpp

LOCAL_STATIC_LIBRARIES := audioengine_static
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android

include $(BUILD_STATIC_LIBRARY)
