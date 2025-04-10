# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

if(WIN32)
  set(AUDIO_SRC
    win32/SimpleAudioEngine.cpp
    win32/MciPlayer.cpp
  )
elseif(APPLE)

elseif(OHOS)
    set(AUDIO_SRC
            ohos/AudioEngine.cpp
            ohos/SimpleAudioEngine.cpp
            ohos/AudioEngine-inl.cpp
            ohos/CCThreadPool.cpp
            ohos/AssetFd.cpp
            ohos/AudioDecoder.cpp
            ohos/AudioDecoderProvider.cpp
            ohos/AudioDecoderWav.cpp
            ohos/AudioDecoderOH.cpp
            ohos/AudioPlayerProvider.cpp
            ohos/AudioResampler.cpp
            ohos/AudioResamplerCubic.cpp
            ohos/PcmBufferProvider.cpp
            ohos/PcmAudioPlayer.cpp
            ohos/PcmData.cpp
            ohos/PcmAudioService.cpp
            ohos/BigAudioPlayer.cpp
            ohos/BigAudioService.cpp
            ohos/AudioMixerController.cpp
            ohos/AudioMixer.cpp
            ohos/tinysndfile.cpp
            ohos/Track.cpp
            ohos/audio_utils/RefCounted.cpp
            ohos/audio_utils/Value.cpp
            ohos/audio_utils/minifloat.cpp
            ohos/audio_utils/primitives.cpp
            ohos/utils/Utils.cpp
    )
else()
  set(AUDIO_SRC
    linux/SimpleAudioEngineFMOD.cpp
    linux/FmodAudioPlayer.cpp
  )

  include_directories(
    ../../external/linux-specific/fmod/include/${ARCH_DIR}
  )

endif()

add_library(audio STATIC
  ${AUDIO_SRC}
)

if(OHOS)
  include_directories(
    ../../cocos/2d
  )
  target_link_libraries(audio 
      # ext_cpufeatures  TBD need fixed?
      libohaudio.so
      libnative_media_codecbase.so 
      libnative_media_core.so
      libnative_media_acodec.so 
      libnative_media_avdemuxer.so 
      libnative_media_avsource.so
  )
endif()




if((NOT APPLE) AND (NOT WIN32) AND (NOT OHOS) )

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(FMOD_LIB "fmodex64")
else()
set(FMOD_LIB "fmodex")
endif()

target_link_libraries(audio
  ${FMOD_LIB}
)

set_target_properties(audio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

elseif(WIN32)

target_link_libraries(audio
  Winmm
)

endif()
