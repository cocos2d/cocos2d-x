
if(WINDOWS AND NOT BUILD_STATIC)
  ADD_DEFINITIONS (-D_EXPORT_DLL_)
endif()

if(WINDOWS)
  set(COCOS_AUDIO_SRC
    audio/win32/SimpleAudioEngine.cpp
    audio/win32/MciPlayer.cpp
	  audio/win32/MciPlayer.h
  )

elseif(LINUX)
  set(COCOS_AUDIO_SRC
    audio/linux/SimpleAudioEngineFMOD.cpp
    audio/linux/FmodAudioPlayer.cpp
	  audio/linux/FmodAudioPlayer.h
	  audio/linux/AudioPlayer.h
  )

  include_directories( ../external/linux-specific/fmod/include/${ARCH_DIR} )

elseif(MACOSX)
    # split it in _C and non C
    # because C files needs to be compiled with C compiler and not C++
    # compiler
    set(COCOS_AUDIO_SRC_C
        audio/mac/CDAudioManager.m
        audio/mac/CDOpenALSupport.m
        audio/mac/CocosDenshion.m
        audio/mac/SimpleAudioEngine_objc.m
       )
    set(COCOS_AUDIO_SRC
        ${COCOS_AUDIO_SRC_C}
        audio/mac/SimpleAudioEngine.mm
        audio/mac/CDXMacOSXSupport.mm
       )
    SET_SOURCE_FILES_PROPERTIES(
        ${COCOS_AUDIO_SRC_C}
        PROPERTIES LANGUAGE C
    )
endif()

if(LINUX)
  if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(FMOD_LIB "fmodex64")
  else()
    set(FMOD_LIB "fmodex")
  endif()
  set(AUDIO_LIB ${FMOD_LIB})
elseif(WINDOWS)
  set(AUDIO_LIB Winmm)
endif()

include_directories( audio/include )
