# architecture
#if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
#set(ARCH_DIR "64-bit")
#else()
#set(ARCH_DIR "32-bit")
#endif()

if(WINDOWS)
  set(AUDIO_SRC
    win32/SimpleAudioEngine.cpp
    win32/MciPlayer.cpp
	  win32/MciPlayer.h
  )

elseif(LINUX)
  set(AUDIO_SRC
    linux/SimpleAudioEngineFMOD.cpp
    linux/FmodAudioPlayer.cpp
	  linux/FmodAudioPlayer.h
	  linux/AudioPlayer.h
  )

  include_directories( ../../external/linux-specific/fmod/include/${ARCH_DIR} )

endif()

add_library(audio STATIC
  ${AUDIO_SRC}
  include/Export.h
  include/SimpleAudioEngine.h
)

if(LINUX)

  if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(FMOD_LIB "fmodex64")
  else()
    set(FMOD_LIB "fmodex")
  endif()

  target_link_libraries(audio ${FMOD_LIB})
elseif(WINDOWS)
  target_link_libraries(audio Winmm)
endif()

set_target_properties(audio
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


