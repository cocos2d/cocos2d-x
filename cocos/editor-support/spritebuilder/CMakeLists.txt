
if(WINDOWS AND NOT BUILD_STATIC)
  ADD_DEFINITIONS (-D_USRSTUDIODLL)
endif()

set(COCOS_SB_SRC
  editor-support/spritebuilder/CCBXAnimationManager.cpp
  editor-support/spritebuilder/CCBXButtonLoader.cpp
  editor-support/spritebuilder/CCBXEditBoxLoader.cpp 
  editor-support/spritebuilder/CCBXFileLoader.cpp
  editor-support/spritebuilder/CCBXImageViewLoader.cpp
  editor-support/spritebuilder/CCBXKeyframe.cpp
  editor-support/spritebuilder/CCBXLabelTTFLoader.cpp
  editor-support/spritebuilder/CCBXLayoutBoxLoader.cpp
  editor-support/spritebuilder/CCBXLoadingBarLoader.cpp
  editor-support/spritebuilder/CCBXNodeColorLoader.cpp
  editor-support/spritebuilder/CCBXNodeGradientLoader.cpp
  editor-support/spritebuilder/CCBXNodeLoader.cpp
  editor-support/spritebuilder/CCBXNodeLoaderLibrary.cpp
  editor-support/spritebuilder/CCBXParser.cpp
  editor-support/spritebuilder/CCBXParticleSystemQuadLoader.cpp
  editor-support/spritebuilder/CCBXProgressTimerLoader.cpp
  editor-support/spritebuilder/CCBXReaderParams.cpp
  editor-support/spritebuilder/CCBXScale9SpriteLoader.cpp
  editor-support/spritebuilder/CCBXScissorsNodeLoader.cpp
  editor-support/spritebuilder/CCBXScrollListViewLoader.cpp
  editor-support/spritebuilder/CCBXScrollViewLoader.cpp
  editor-support/spritebuilder/CCBXSequence.cpp
  editor-support/spritebuilder/CCBXSequenceProperty.cpp
  editor-support/spritebuilder/CCBXSliderLoader.cpp
  editor-support/spritebuilder/CCBXSpriteLoader.cpp
  editor-support/spritebuilder/CCBXTextFieldLoader.cpp
  editor-support/spritebuilder/CCBXTextLoader.cpp
  editor-support/spritebuilder/CCBXWidgetLoader.cpp
  editor-support/spritebuilder/CCScrollListView.cpp
  editor-support/spritebuilder/SpriteBuilder.cpp
)

include_directories( editor-support )
