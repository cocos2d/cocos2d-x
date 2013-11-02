set(AUDIO_SRC
  linux/SimpleAudioEngineFMOD.cpp
  linux/FmodAudioPlayer.cpp
)

include_directories(
  third-party/fmod/lib64/api/inc
)

add_library(audio STATIC
  ${AUDIO_SRC}
)

target_link_libraries(audio
  fmodex64
)