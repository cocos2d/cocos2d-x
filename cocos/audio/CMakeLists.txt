
set(COCOS_AUDIO_SRC
    audio/AudioEngine.cpp
    )

if(WINDOWS OR LINUX)

    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/desktop/AudioDecoderManager.h
        audio/desktop/AudioDecoder.h
        audio/desktop/AudioPlayer.h
        audio/desktop/AudioDecoderOgg.h
        audio/desktop/AudioMacros.h
        audio/desktop/AudioEngine-desktop.h
        audio/desktop/AudioDecoderMp3.h
        audio/desktop/AudioCache.h
        )

    set(COCOS_AUDIO_PLATFORM_SRC
        audio/desktop/AudioEngine-desktop.cpp
        audio/desktop/AudioCache.cpp
        audio/desktop/AudioPlayer.cpp
        audio/desktop/AudioDecoder.cpp
        audio/desktop/AudioDecoderManager.cpp
        audio/desktop/AudioDecoderMp3.cpp
        audio/desktop/AudioDecoderOgg.cpp
        )

endif()

if(WINDOWS)

    set(COCOS_AUDIO_PLATFORM_HEADER
        ${COCOS_AUDIO_PLATFORM_HEADER}
        audio/win32/MciPlayer.h
        )

    set(COCOS_AUDIO_PLATFORM_SRC
        ${COCOS_AUDIO_PLATFORM_SRC}
        audio/win32/MciPlayer.cpp
        )

elseif(ANDROID)

    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/android/PcmAudioService.h
        audio/android/AudioBufferProvider.h
        audio/android/IAudioPlayer.h
        audio/android/AudioResampler.h
        audio/android/AudioDecoder.h
        audio/android/AudioResamplerPublic.h
        audio/android/AudioMixer.h
        audio/android/tinysndfile.h
        audio/android/mp3reader.h
        audio/android/AudioMixerOps.h
        audio/android/cutils/bitops.h
        audio/android/cutils/log.h
        audio/android/audio.h
        audio/android/AudioPlayerProvider.h
        audio/android/utils/Utils.h
        audio/android/utils/Errors.h
        audio/android/utils/Compat.h
        audio/android/ccdandroidUtils.h
        audio/android/AudioDecoderOgg.h
        audio/android/Track.h
        audio/android/OpenSLHelper.h
        audio/android/PcmAudioPlayer.h
        audio/android/AssetFd.h
        audio/android/PcmBufferProvider.h
        audio/android/CCThreadPool.h
        audio/android/audio_utils/include/audio_utils/minifloat.h
        audio/android/audio_utils/include/audio_utils/primitives.h
        audio/android/audio_utils/include/audio_utils/format.h
        audio/android/audio_utils/private/private.h
        audio/android/ICallerThreadUtils.h
        audio/android/AudioDecoderWav.h
        audio/android/AudioDecoderProvider.h
        audio/android/UrlAudioPlayer.h
        audio/android/AudioDecoderSLES.h
        audio/android/AudioDecoderMp3.h
        audio/android/PcmData.h
        audio/android/AudioMixerController.h
        audio/android/AudioResamplerCubic.h
        audio/android/AudioEngine-inl.h
        audio/android/IVolumeProvider.h

        )

    set(COCOS_AUDIO_PLATFORM_SRC
        audio/android/ccdandroidUtils.cpp
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

elseif(APPLE)
    # common
    set(COCOS_AUDIO_PLATFORM_HEADER
        audio/apple/AudioDecoder.h
        audio/apple/AudioPlayer.h
        audio/apple/AudioMacros.h
        audio/apple/AudioCache.h
        audio/apple/AudioEngine-inl.h
        )
    set(COCOS_AUDIO_PLATFORM_SRC
        audio/apple/AudioCache.mm
        audio/apple/AudioDecoder.mm
        audio/apple/AudioEngine-inl.mm
        audio/apple/AudioPlayer.mm
        )
endif()

set(COCOS_AUDIO_HEADER
    audio/include/AudioEngine.h
    audio/include/Export.h
    ${COCOS_AUDIO_PLATFORM_HEADER}
    )
list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
