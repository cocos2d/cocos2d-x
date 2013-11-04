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

set_target_properties(audio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

