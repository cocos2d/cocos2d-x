set(AUDIO_SRC
  linux/SimpleAudioEngineFMOD.cpp
  linux/FmodAudioPlayer.cpp
)

add_library(audio STATIC
  ${AUDIO_SRC}
)

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
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

