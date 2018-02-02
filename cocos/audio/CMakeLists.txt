
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

elseif(ANDROID)
    set(COCOS_AUDIO_PLATFORM_SRC
       audio/android/cddSimpleAudioEngine.cpp
       audio/android/ccdandroidUtils.cpp
       audio/android/jni/cddandroidAndroidJavaEngine.cpp
       audio/android/AudioEngine-inl.cpp
       audio/android/CCThreadPool.cpp
       audio/android/AssetFd.cpp
       audio/android/AudioDecoder.cpp
       audio/android/AudioDecoderProvider.cpp
       audio/android/AudioDecoderSLES.cpp
       audio/android/AudioDecoderOgg.cpp
       audio/android/AudioDecoderMp3.cpp
       audio/android/AudioDecoderWav.cpp
       audio/android/AudioPlayerProvider.cpp
       audio/android/AudioResampler.cpp
       audio/android/AudioResamplerCubic.cpp
       audio/android/PcmBufferProvider.cpp
       audio/android/PcmAudioPlayer.cpp
       audio/android/UrlAudioPlayer.cpp
       audio/android/PcmData.cpp
       audio/android/AudioMixerController.cpp
       audio/android/AudioMixer.cpp
       audio/android/PcmAudioService.cpp
       audio/android/Track.cpp
       audio/android/audio_utils/format.c
       audio/android/audio_utils/minifloat.cpp
       audio/android/audio_utils/primitives.c
       audio/android/utils/Utils.cpp
       audio/android/mp3reader.cpp
       audio/android/tinysndfile.cpp
    )

elseif(LINUX)
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/linux/SimpleAudioEngine.cpp
        audio/linux/AudioEngine-linux.h
        audio/linux/AudioEngine-linux.cpp
    )

elseif(APPLE)
    # common
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/apple/AudioCache.mm
        audio/apple/AudioDecoder.mm
        audio/apple/AudioEngine-inl.mm
        audio/apple/AudioPlayer.mm
    )
    # split it in _C and non C
    # because C files needs to be compiled with C compiler and not C++
    # compiler
    if(MACOSX)
        set(COCOS_AUDIO_PLATFORM_SRC_C
            audio/mac/CDAudioManager.m
            audio/mac/CDOpenALSupport.m
            audio/mac/CocosDenshion.m
            audio/mac/SimpleAudioEngine_objc.m
        )
        set(COCOS_AUDIO_PLATFORM_SRC
            ${COCOS_AUDIO_PLATFORM_SRC_C}
            ${COCOS_AUDIO_PLATFORM_SRC}
            audio/mac/SimpleAudioEngine.mm
            audio/mac/CDXMacOSXSupport.mm
        )
    elseif(IOS)
        set(COCOS_AUDIO_PLATFORM_SRC_C
            audio/ios/CDAudioManager.m
            audio/ios/CDOpenALSupport.m
            audio/ios/CocosDenshion.m
            audio/ios/SimpleAudioEngine_objc.m
        )
        set(COCOS_AUDIO_PLATFORM_SRC
            ${COCOS_AUDIO_PLATFORM_SRC_C}
            ${COCOS_AUDIO_PLATFORM_SRC}
            audio/ios/SimpleAudioEngine.mm
        )
    endif()

    set_source_files_properties(
        ${COCOS_AUDIO_PLATFORM_SRC_C}
        PROPERTIES LANGUAGE C
    )
endif()

list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
