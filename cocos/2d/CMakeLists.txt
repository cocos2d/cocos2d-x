if(WIN32)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

set(PLATFORM_SRC
  platform/win32/CCStdC.cpp
  platform/win32/CCFileUtilsWin32.cpp
  platform/win32/CCCommon.cpp
  platform/win32/CCApplication.cpp
  platform/win32/CCEGLView.cpp
  platform/win32/CCImage.cpp
  platform/win32/CCDevice.cpp
)

elseif(APPLE)

else()

set(PLATFORM_SRC
  platform/linux/CCStdC.cpp
  platform/linux/CCFileUtilsLinux.cpp
  platform/linux/CCCommon.cpp
  platform/linux/CCApplication.cpp
  platform/desktop/CCEGLView.cpp
  platform/linux/CCImage.cpp
  platform/linux/CCDevice.cpp
)

endif()


set(COCOS2D_SRC
  CCAction.cpp
  CCActionCamera.cpp
  CCActionEase.cpp
  CCActionGrid.cpp
  CCActionGrid3D.cpp
  CCActionInstant.cpp
  CCActionInterval.cpp
  CCActionManager.cpp
  CCActionPageTurn3D.cpp
  CCActionProgressTimer.cpp
  CCActionTiledGrid.cpp
  CCActionCatmullRom.cpp
  CCActionTween.cpp
  CCAtlasNode.cpp
  CCNode.cpp
  CCEventAcceleration.cpp
  CCEventListenerAcceleration.cpp
  CCEvent.cpp
  CCEventDispatcher.cpp
  CCEventListener.cpp
  CCEventKeyboard.cpp
  CCEventListenerKeyboard.cpp
  CCEventMouse.cpp
  CCEventListenerMouse.cpp
  CCTouch.cpp
  CCEventTouch.cpp
  CCEventListenerTouch.cpp
  CCEventCustom.cpp
  CCEventListenerCustom.cpp
  CCDrawingPrimitives.cpp
  CCDrawNode.cpp
  CCGrabber.cpp
  CCGrid.cpp
  CCNodeGrid.cpp
  CCFont.cpp
  CCFontAtlas.cpp
  CCFontAtlasCache.cpp
  CCFontFNT.cpp
  CCFontFreeType.cpp
  CCFontCharMap.cpp
  CCLabel.cpp
  CCLabelAtlas.cpp
  CCLabelBMFont.cpp
  CCLabelTTF.cpp
  CCLabelTextFormatter.cpp
  CCLayer.cpp
  CCScene.cpp
  CCTransition.cpp
  CCTransitionPageTurn.cpp
  CCTransitionProgress.cpp
  CCMenu.cpp
  CCMenuItem.cpp
  CCMotionStreak.cpp
  CCProgressTimer.cpp
  CCClippingNode.cpp
  CCRenderTexture.cpp
  CCParticleExamples.cpp
  CCParticleSystem.cpp
  CCParticleSystemQuad.cpp
  CCParticleBatchNode.cpp
  CCScriptSupport.cpp
  CCAnimation.cpp
  CCAnimationCache.cpp
  CCSprite.cpp
  CCSpriteBatchNode.cpp
  CCSpriteFrame.cpp
  CCSpriteFrameCache.cpp
  ccUTF8.cpp
  CCProfiling.cpp
  CCUserDefault.cpp
  TransformUtils.cpp
  base64.cpp
  ccUtils.cpp
  CCVertex.cpp
  CCNotificationCenter.cpp
  TGAlib.cpp
  ZipUtils.cpp
  ccCArray.cpp
  CCComponent.cpp
  CCComponentContainer.cpp
  CCIMEDispatcher.cpp
  CCTextFieldTTF.cpp
  CCTexture2D.cpp
  CCTextureAtlas.cpp
  CCTextureCache.cpp
  CCParallaxNode.cpp
  CCTMXLayer.cpp
  CCTMXObjectGroup.cpp
  CCTMXTiledMap.cpp
  CCTMXXMLParser.cpp
  CCTileMapAtlas.cpp
  CCGLProgram.cpp
  ccGLStateCache.cpp
  CCShaderCache.cpp
  ccShaders.cpp
  CCConfiguration.cpp
  CCDirector.cpp
  CCScheduler.cpp
  ccFPSImages.c
  ccTypes.cpp
  cocos2d.cpp
  CCDeprecated.cpp
  platform/CCSAXParser.cpp
  platform/CCThread.cpp
  platform/CCEGLViewProtocol.cpp
  platform/CCFileUtils.cpp
  ../../external/edtaa3func/edtaa3func.cpp
  renderer/CCCustomCommand.cpp
  renderer/CCFrustum.cpp
  renderer/CCGroupCommand.cpp
  renderer/CCMaterialManager.cpp
  renderer/CCQuadCommand.cpp
  renderer/CCBatchCommand.cpp
  renderer/CCRenderCommand.cpp
  renderer/CCRenderer.cpp
  renderer/CCRenderMaterial.cpp
)

include(../physics/CMakeLists.txt)

add_library(cocos2d STATIC
  ${COCOS2D_SRC}
  ${PLATFORM_SRC}
  ${COCOS_PHYSICS_SRC}
)

if(WIN32)

if(MINGW)

set(COCOS_LINK
  z
  jpeg
  png
  webp
  tiff
  glfw3
  glew32
  opengl32
  iconv
  freetype
  bz2
  )

else()


set(COCOS_LINK
  libjpeg
  libpng
  libwebp
  libtiff
  freetype250
  glfw3
  glew32
  opengl32
  libiconv
  libzlib
  )

endif()

elseif(APPLE)

else()
set(COCOS_LINK
  jpeg
  webp
  tiff
  freetype
  fontconfig
  png
  pthread
  glfw
  GLEW
  GL
  X11
  rt
  z
)
endif()

target_link_libraries(cocos2d
  cocosbase
  chipmunk_static
  tinyxml2
  kazmath
  unzip
  ${COCOS_LINK}
)

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

