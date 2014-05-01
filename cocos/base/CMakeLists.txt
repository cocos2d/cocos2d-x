set(COCOS_BASE_SRC
  ../deprecated/CCSet.cpp
  ../deprecated/CCArray.cpp
  ../deprecated/CCDictionary.cpp
  ../deprecated/CCString.cpp
  CCAutoreleasePool.cpp
  CCAutoreleasePool.h
  CCConfiguration.cpp
  CCConfiguration.h
  CCConsole.cpp
  CCConsole.h
  CCData.cpp
  CCData.h
  CCDataVisitor.cpp
  CCDataVisitor.h
  CCDirector.cpp
  CCDirector.h
  CCEvent.cpp
  CCEvent.h
  CCEventAcceleration.cpp
  CCEventAcceleration.h
  CCEventCustom.cpp
  CCEventDispatcher.cpp
  CCEventKeyboard.cpp
  CCEventListener.cpp
  CCEventListenerAcceleration.cpp
  CCEventListenerCustom.cpp
  CCEventListenerKeyboard.cpp
  CCEventListenerMouse.cpp
  CCEventListenerTouch.cpp
  CCEventMouse.cpp
  CCEventTouch.cpp
  CCNS.cpp
  CCProfiling.cpp
  CCRef.cpp
  CCScheduler.cpp
  CCTouch.cpp
  CCValue.cpp
  ZipUtils.cpp
  atitc.cpp
  base64.cpp
  ccTypes.cpp
  etc1.cpp
  s3tc.cpp
)

add_library(cocosbase STATIC
  ${COCOS_BASE_SRC}
)

if(WIN32)
target_link_libraries(cocosbase
  Ws2_32
)
endif()

set_target_properties(cocosbase
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

