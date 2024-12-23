
set(COCOS_AUDIO_SRC
    audio/AudioEngine.cpp
    )

if(WINDOWS)
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/win32/SimpleAudioEngine.cpp
        audio/win32/MciPlayer.cpp
        audio/win32/MciPlayer.h
        audio/win32/AudioEngine-win32.cpp
        audio/win32/AudioCache.cpp
        audio/win32/AudioPlayer.cpp
        audio/win32/AudioDecoder.cpp
        audio/win32/AudioDecoderManager.cpp
        audio/win32/AudioDecoderMp3.cpp
        audio/win32/AudioDecoderOgg.cpp
    )

ELSEIF(ANDROID)
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/android/AudioEngine-inl.cpp
        audio/android/ccdandroidUtils.cpp
        audio/android/cddSimpleAudioEngine.cpp
        audio/android/jni/cddandroidAndroidJavaEngine.cpp
    )

elseif(LINUX)
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/linux/SimpleAudioEngine.cpp
        audio/linux/AudioEngine-linux.h
        audio/linux/AudioEngine-linux.cpp
    )

elseif(OHOS)
    message("************      audio cmakelists ohos        ***********")
    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/ohos/PcmAudioService.h
        audio/ohos/AudioBufferProvider.h
        audio/ohos/IAudioPlayer.h
        audio/ohos/AudioResampler.h
        audio/ohos/AudioDecoder.h
        audio/ohos/AudioResamplerPublic.h
        audio/ohos/AudioMixer.h
        audio/ohos/tinysndfile.h
        audio/ohos/mp3reader.h
        audio/ohos/AudioMixerOps.h
        audio/ohos/cutils/bitops.h
        audio/ohos/cutils/log.h
        audio/ohos/audio.h
        audio/ohos/AudioPlayerProvider.h
        audio/ohos/utils/Utils.h
        audio/ohos/utils/Errors.h
        audio/ohos/utils/Compat.h
        audio/ohos/AudioDecoderOgg.h
        audio/ohos/Track.h
        audio/ohos/OpenSLHelper.h
        audio/ohos/PcmAudioPlayer.h
        audio/ohos/AssetFd.h
        audio/ohos/PcmBufferProvider.h
        audio/ohos/CCThreadPool.h
        audio/ohos/audio_utils/include/audio_utils/minifloat.h
        audio/ohos/audio_utils/include/audio_utils/primitives.h
        audio/ohos/audio_utils/AudioDef.h
        audio/ohos/audio_utils/RefCounted.h
        audio/ohos/ICallerThreadUtils.h
        audio/ohos/AudioDecoderWav.h
        audio/ohos/AudioDecoderProvider.h
        audio/ohos/UrlAudioPlayer.h
        audio/ohos/AudioDecoderSLES.h
        audio/ohos/AudioDecoderMp3.h
        audio/ohos/PcmData.h
        audio/ohos/AudioMixerController.h
        audio/ohos/AudioResamplerCubic.h
        audio/ohos/AudioEngine-inl.h
        audio/ohos/IVolumeProvider.h
        audio/ohos/Macros.h
        audio/ohos/Value.h
        )

    set(COCOS_AUDIO_PLATFORM_SRC
            audio/ohos/SimpleAudioEngine.cpp
            audio/ohos/AudioEngine-inl.cpp
            audio/ohos/CCThreadPool.cpp
            audio/ohos/AssetFd.cpp
            audio/ohos/AudioDecoder.cpp
            audio/ohos/AudioDecoderProvider.cpp
            audio/ohos/AudioDecoderSLES.cpp
            audio/ohos/AudioDecoderOgg.cpp
            audio/ohos/AudioDecoderMp3.cpp
            audio/ohos/AudioDecoderWav.cpp
            audio/ohos/AudioPlayerProvider.cpp
            audio/ohos/AudioResampler.cpp
            audio/ohos/AudioResamplerCubic.cpp
            audio/ohos/PcmBufferProvider.cpp
            audio/ohos/PcmAudioPlayer.cpp
            audio/ohos/PcmData.cpp
            audio/ohos/PcmAudioService.cpp
            audio/ohos/UrlAudioPlayer.cpp
            audio/ohos/AudioMixerController.cpp
            audio/ohos/AudioMixer.cpp
            audio/ohos/mp3reader.cpp
            audio/ohos/tinysndfile.cpp
            audio/ohos/Track.cpp
            audio/ohos/audio_utils/RefCounted.cpp
            audio/ohos/audio_utils/Value.cpp
            audio/ohos/audio_utils/minifloat.cpp
            audio/ohos/audio_utils/primitives.cpp
            audio/ohos/utils/Utils.cpp
            )


elseif(MACOSX)
    # split it in _C and non C
    # because C files needs to be compiled with C compiler and not C++
    # compiler
    set(COCOS_AUDIO_PLATFORM_SRC_C
        audio/mac/CDAudioManager.m
        audio/mac/CDOpenALSupport.m
        audio/mac/CocosDenshion.m
        audio/mac/SimpleAudioEngine_objc.m
    )
    set(COCOS_AUDIO_PLATFORM_SRC
        ${COCOS_AUDIO_PLATFORM_SRC_C}
        audio/apple/AudioCache.mm
        audio/apple/AudioDecoder.mm
        audio/apple/AudioEngine-inl.mm
        audio/apple/AudioPlayer.mm
        audio/mac/SimpleAudioEngine.mm
        audio/mac/CDXMacOSXSupport.mm
    )
    set_source_files_properties(
        ${COCOS_AUDIO_PLATFORM_SRC_C}
        PROPERTIES LANGUAGE C
    )
endif()
if(OHOS)
    set(COCOS_AUDIO_HEADER
      audio/include/AudioEngine.h
      audio/include/Export.h
      audio/include/SimpleAudioEngine.h
      ${COCOS_AUDIO_PLATFORM_HEADER}
    )
endif()
list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
