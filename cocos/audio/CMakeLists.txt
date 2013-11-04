set(AUDIO_SRC
  linux/SimpleAudioEngineFMOD.cpp
  linux/FmodAudioPlayer.cpp
)

add_library(audio STATIC
  ${AUDIO_SRC}
)

target_link_libraries(audio
  fmodex64
)