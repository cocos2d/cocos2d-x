set(CCB_SRC
  CCBFileLoader.cpp
  CCMenuItemImageLoader.cpp
  CCBReader.cpp
  CCMenuItemLoader.cpp
  CCControlButtonLoader.cpp
  CCNodeLoader.cpp
  CCControlLoader.cpp
  CCNodeLoaderLibrary.cpp
  CCLabelBMFontLoader.cpp
  CCParticleSystemQuadLoader.cpp
  CCLabelTTFLoader.cpp
  CCScale9SpriteLoader.cpp
  CCLayerColorLoader.cpp
  CCScrollViewLoader.cpp
  CCLayerGradientLoader.cpp
  CCSpriteLoader.cpp
  CCLayerLoader.cpp
  CCBAnimationManager.cpp
  CCBKeyframe.cpp
  CCBSequence.cpp
  CCBSequenceProperty.cpp
  CCBValue.cpp
  CCNode+CCBRelativePositioning.cpp
)

include_directories(
  ..
)

add_library(cocosbuilder STATIC
  ${CCB_SRC}
)
