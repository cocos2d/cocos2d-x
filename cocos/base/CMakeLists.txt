set(COCOS_BASE_SRC
  CCAffineTransform.cpp
  CCAutoreleasePool.cpp
  CCGeometry.cpp
  CCNS.cpp
  CCObject.cpp
  CCSet.cpp
  CCArray.cpp
  CCDictionary.cpp
  CCString.cpp
  CCDataVisitor.cpp
  CCData.cpp
  CCValue.cpp
  etc1.cpp
  s3tc.cpp
  atitc.cpp
  CCConsole.cpp
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

