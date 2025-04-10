if(WIN32)
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

set(PLATFORM_SRC
  platform/win32/CCStdC.cpp
  platform/win32/CCFileUtilsWin32.cpp
  platform/win32/CCCommon.cpp
  platform/win32/CCApplication.cpp
  platform/desktop/CCGLView.cpp
  platform/win32/CCDevice.cpp
)

elseif(APPLE)

elseif(OHOS)
    include_directories(
          ../../cocos/2d
          ../../cocos/base
          platform/ohos
          platform/ohos/napi
          platform/ohos/napi/modules
          platform/ohos/napi/common
          platform/ohos/napi/render
          platform/ohos/napi/plugin_manager.h
          platform/ohos/napi/helper/NapiValueConverter.h
          platform/ohos/napi/helper/Js_Cocos2dxHelper.h
          platform/ohos/napi/helper/NapiHelper.h
          ../../external/freetype2/include/ohos/
          ../../external/freetype2/include/ohos/freetype 
    )
    set(PLATFORM_SRC
          platform/ohos/CCApplication.cpp
          platform/ohos/CCCommon.cpp
          platform/ohos/CCDevice.cpp
          platform/ohos/CCGLView.cpp
          platform/ohos/CCFileUtils-ohos.cpp
          platform/ohos/CCTextBitmap.cpp
          platform/ohos/napi/modules/MouseNapi.cpp
          platform/ohos/napi/modules/RawFileUtils.cpp
          platform/ohos/napi/modules/TouchesNapi.cpp
          platform/ohos/napi/modules/InputNapi.cpp
          platform/ohos/napi/modules/WebViewNapi.cpp
          platform/ohos/napi/modules/VideoPlayerNapi.cpp
          platform/ohos/napi/helper/NapiValueConverter.cpp
          platform/ohos/napi/helper/Js_Cocos2dxHelper.cpp
          platform/ohos/napi/helper/NapiHelper.cpp
          platform/ohos/napi/render/egl_core.cpp
          platform/ohos/napi/render/plugin_render.cpp
          platform/ohos/napi/plugin_manager.cpp
          platform/ohos/napi/WorkerMessageQueue.cpp
    )
else()
set(PLATFORM_SRC
  platform/linux/CCStdC.cpp
  platform/linux/CCFileUtilsLinux.cpp
  platform/linux/CCCommon.cpp
  platform/linux/CCApplication.cpp
  platform/desktop/CCGLView.cpp
  platform/linux/CCDevice.cpp
)

endif()

if(OHOS)
set(COCOS2D_SRC
  CCUserDefault-ohos.cpp
)
else()
set(COCOS2D_SRC
  CCUserDefault.cpp
)
endif()
set(COCOS2D_SRC
  ${COCOS2D_SRC}
  CCAction.cpp
  CCActionCamera.cpp
  CCTweenFunction.cpp
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
  TransformUtils.cpp
  base64.cpp
  ccUtils.cpp
  CCVertex.cpp
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
  platform/CCSAXParser.cpp
  platform/CCThread.cpp
  platform/CCGLViewProtocol.cpp
  platform/CCFileUtils.cpp
  platform/CCImage.cpp
  renderer/CCCustomCommand.cpp
  renderer/CCFrustum.cpp
  renderer/CCGroupCommand.cpp
  renderer/CCMaterialManager.cpp
  renderer/CCQuadCommand.cpp
  renderer/CCBatchCommand.cpp
  renderer/CCRenderCommand.cpp
  renderer/CCRenderer.cpp
  renderer/CCRenderMaterial.cpp
  ../deprecated/CCDeprecated.cpp
  ../deprecated/CCNotificationCenter.cpp
  ../../external/edtaa3func/edtaa3func.cpp
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

elseif(OHOS)
  find_library( # Sets the name of the path variable.
                rawfile-lib
                # Specifies the name of the NDK library that
                # you want CMake to locate.
                rawfile.z )
  find_library( # Sets the name of the path variable.
                libnapi-lib
                # Specifies the name of the NDK library that
                # you want CMake to locate.
                ace_napi.z )
  find_library( # Sets the name of the path variable.
                Drawing-lib
                # Specifies the name of the NDK library that
                # you want CMake to locate.
                native_drawing )
  set(COCOS_LINK ext_freetype ext_png ext_jpeg ext_tiff ext_webp ext_zlib ${rawfile-lib} ${libnapi-lib} ${Drawing-lib} OpenSLES libnative_window.so libnative_buffer.so libnative_display_manager.so libohsensor.so)
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
  xxhash
  ${COCOS_LINK}
)

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

