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
  etc1.cpp
  s3tc.cpp
  atitc.cpp
)

add_library(cocosbase STATIC
  ${COCOS_BASE_SRC}
)
