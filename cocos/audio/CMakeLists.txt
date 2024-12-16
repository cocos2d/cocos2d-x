
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
    )

elseif(LINUX)
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/linux/SimpleAudioEngineFMOD.cpp
        audio/linux/FmodAudioPlayer.cpp
        audio/linux/FmodAudioPlayer.h
        audio/linux/AudioPlayer.h
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
        audio/apple/AudioEngine-inl.mm
        audio/apple/AudioPlayer.mm
        audio/mac/SimpleAudioEngine.mm
        audio/mac/CDXMacOSXSupport.mm
    )
    set_source_files_properties(
        ${COCOS_AUDIO_PLATFORM_SRC_C}
        PROPERTIES LANGUAGE C
    )
elseif(OHOS)
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
endif()

list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
