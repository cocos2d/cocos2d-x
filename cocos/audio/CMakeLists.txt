
set(audio_src

    ${CMAKE_CURRENT_LIST_FILE}
    "audio/AudioEngine.cpp"
    )

if(COCOS_TARGET_SYSTEM_WINDOWS)
    list(APPEND audio_src
        "audio/win32/SimpleAudioEngine.cpp"
        "audio/win32/MciPlayer.cpp"
        "audio/win32/MciPlayer.h"
        "audio/win32/AudioEngine-win32.cpp"
        "audio/win32/AudioCache.cpp"
        "audio/win32/AudioPlayer.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    list(APPEND audio_src
        "audio/linux/SimpleAudioEngineFMOD.cpp"
        "audio/linux/FmodAudioPlayer.cpp"
        "audio/linux/FmodAudioPlayer.h"
        "audio/linux/AudioPlayer.h"
        )
elseif(COCOS_TARGET_SYSTEM_MACOSX)
    # split it in _C and non C
    # because C files needs to be compiled with C compiler and not C++
    # compiler
    set(platform_specific_c
        "audio/mac/CDAudioManager.m"
        "audio/mac/CDOpenALSupport.m"
        "audio/mac/CocosDenshion.m"
        "audio/mac/SimpleAudioEngine_objc.m"
        )
    set_source_files_properties(${platform_specific_c} PROPERTIES LANGUAGE C)

    list(APPEND audio_src
        ${platform_specific_c}
        "audio/apple/AudioCache.mm"
        "audio/apple/AudioEngine-inl.mm"
        "audio/apple/AudioPlayer.mm"
        "audio/mac/SimpleAudioEngine.mm"
        "audio/mac/CDXMacOSXSupport.mm"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    set(platform_specific_c
        "audio/ios/CDAudioManager.m"
        "audio/ios/CDOpenALSupport.m"
        "audio/ios/CocosDenshion.m"
        "audio/ios/SimpleAudioEngine_objc.m"
        )
    set_source_files_properties(${platform_specific_c} PROPERTIES LANGUAGE C)

    list(APPEND audio_src
        ${platform_specific_c}
        "audio/apple/AudioCache.mm"
        "audio/apple/AudioEngine-inl.mm"
        "audio/apple/AudioPlayer.mm"
        "audio/ios/SimpleAudioEngine.mm"
        )
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    list(APPEND audio_src
        "audio/android/AudioEngine-inl.cpp"
        "audio/android/AudioEngine-inl.h"
        "audio/android/ccdandroidUtils.cpp"
        "audio/android/ccdandroidUtils.h"
        "audio/android/cddSimpleAudioEngine.cpp"
        "audio/android/jni/cddandroidAndroidJavaEngine.cpp"
        "audio/android/jni/cddandroidAndroidJavaEngine.h"
        )
endif()

cocos_target_sources(${COCOS2D_TARGET} GROUP "audio" FILES ${audio_src})

if(COCOS_TARGET_SYSTEM_MACOSX OR COCOS_TARGET_SYSTEM_IOS)
    find_library(OPENAL_FRAMEWORK "OpenAL" CMAKE_FIND_FRAMEWORK ONLY)
    find_library(AUDIOTOOLBOX_FRAMEWORK "AudioToolbox" CMAKE_FIND_FRAMEWORK ONLY)
    mark_as_advanced(
        OPENAL_FRAMEWORK
        AUDIOTOOLBOX_FRAMEWORK
        )
    target_link_libraries(${COCOS2D_TARGET}
        ${OPENAL_FRAMEWORK}
        ${AUDIOTOOLBOX_FRAMEWORK}
        )

elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    target_compile_definitions(${COCOS2D_TARGET} PRIVATE "-D_EXPORT_DLL_")

    cocos_use_package(${COCOS2D_TARGET} MPG123 REQUIRED)
    cocos_use_package(${COCOS2D_TARGET} OPENAL REQUIRED)
    cocos_use_package(${COCOS2D_TARGET} OGG REQUIRED)
    cocos_use_package(${COCOS2D_TARGET} VORBIS REQUIRED)
    cocos_use_package(${COCOS2D_TARGET} VORBISFILE REQUIRED)
    target_link_libraries(${COCOS2D_TARGET} winmm.lib)

elseif(COCOS_TARGET_SYSTEM_LINUX)
    cocos_use_package(${COCOS2D_TARGET} FMODEX REQUIRED)

elseif(COCOS_TARGET_SYSTEM_ANDROID)
    target_link_libraries(${COCOS2D_TARGET} "OpenSLES")

    # cddandroidAndroidJavaEngine.cpp include "ccdandroidUtils.h" yet,
    #   need change path sometime.
    target_include_directories(${COCOS2D_TARGET} PRIVATE
        "audio/android"
        )

else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build unsupported system.")
endif()

