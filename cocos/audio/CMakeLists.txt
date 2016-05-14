
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
endif()

list(APPEND COCOS_AUDIO_SRC ${COCOS_AUDIO_PLATFORM_SRC})
