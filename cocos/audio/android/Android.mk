LOCAL_PATH := $(call my-dir)

#New AudioEngine
include $(CLEAR_VARS)

LOCAL_MODULE := audioengine_static

LOCAL_MODULE_FILENAME := libaudioengine

LOCAL_SRC_FILES := AudioEngine-inl.cpp \
                   ../AudioEngine.cpp \
                   CCThreadPool.cpp \
                   AssetFd.cpp \
                   AudioDecoder.cpp \
<<<<<<< HEAD
=======
                   AudioDecoderProvider.cpp \
                   AudioDecoderSLES.cpp \
                   AudioDecoderOgg.cpp \
                   AudioDecoderMp3.cpp \
                   AudioDecoderWav.cpp \
>>>>>>> cocos2d/v3
                   AudioPlayerProvider.cpp \
                   AudioResampler.cpp \
                   AudioResamplerCubic.cpp \
                   PcmBufferProvider.cpp \
                   PcmAudioPlayer.cpp \
                   UrlAudioPlayer.cpp \
                   PcmData.cpp \
                   AudioMixerController.cpp \
                   AudioMixer.cpp \
                   PcmAudioService.cpp \
                   Track.cpp \
                   audio_utils/format.c \
                   audio_utils/minifloat.cpp \
                   audio_utils/primitives.c \
<<<<<<< HEAD
                   utils/Utils.cpp
=======
                   utils/Utils.cpp \
                   mp3reader.cpp \
                   tinysndfile.cpp
>>>>>>> cocos2d/v3


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_EXPORT_LDLIBS := -lOpenSLES

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android \
<<<<<<< HEAD
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/support \
=======
                    $(LOCAL_PATH)/../../../external/android-specific
>>>>>>> cocos2d/v3

LOCAL_STATIC_LIBRARIES += libvorbisidec libpvmp3dec
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
                    $(LOCAL_PATH)/../../platform/android \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/support \

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android-specific/tremolo)
$(call import-module,android-specific/pvmp3dec)
