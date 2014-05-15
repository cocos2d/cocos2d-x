LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
cocos2d.cpp \
2d/CCAction.cpp \
2d/CCActionCamera.cpp \
2d/CCActionCatmullRom.cpp \
2d/CCActionEase.cpp \
2d/CCActionGrid3D.cpp \
2d/CCActionGrid.cpp \
2d/CCActionInstant.cpp \
2d/CCActionInterval.cpp \
2d/CCActionManager.cpp \
2d/CCActionPageTurn3D.cpp \
2d/CCActionProgressTimer.cpp \
2d/CCActionTiledGrid.cpp \
2d/CCActionTween.cpp \
2d/CCAnimationCache.cpp \
2d/CCAnimation.cpp \
2d/CCAtlasNode.cpp \
2d/ccCArray.cpp \
2d/CCClippingNode.cpp \
2d/CCComponentContainer.cpp \
2d/CCComponent.cpp \
2d/CCDrawingPrimitives.cpp \
2d/CCDrawNode.cpp \
2d/CCFontAtlasCache.cpp \
2d/CCFontAtlas.cpp \
2d/CCFontCharMap.cpp \
2d/CCFont.cpp \
2d/CCFontFNT.cpp \
2d/CCFontFreeType.cpp \
2d/CCGLBufferedNode.cpp \
2d/CCGrabber.cpp \
2d/CCGrid.cpp \
2d/CCIMEDispatcher.cpp \
2d/CCLabelAtlas.cpp \
2d/CCLabelBMFont.cpp \
2d/CCLabel.cpp \
2d/CCLabelTextFormatter.cpp \
2d/CCLabelTTF.cpp \
2d/CCLayer.cpp \
2d/CCMenu.cpp \
2d/CCMenuItem.cpp \
2d/CCMotionStreak.cpp \
2d/CCNode.cpp \
2d/CCNodeGrid.cpp \
2d/CCParallaxNode.cpp \
2d/CCParticleBatchNode.cpp \
2d/CCParticleExamples.cpp \
2d/CCParticleSystem.cpp \
2d/CCParticleSystemQuad.cpp \
2d/CCProgressTimer.cpp \
2d/CCRenderTexture.cpp \
2d/CCScene.cpp \
2d/CCScriptSupport.cpp \
2d/CCSpriteBatchNode.cpp \
2d/CCSprite.cpp \
2d/CCSpriteFrameCache.cpp \
2d/CCSpriteFrame.cpp \
2d/CCTextFieldTTF.cpp \
2d/CCTexture2D.cpp \
2d/CCTextureAtlas.cpp \
2d/CCTextureCache.cpp \
2d/CCTileMapAtlas.cpp \
2d/CCTMXLayer.cpp \
2d/CCTMXObjectGroup.cpp \
2d/CCTMXTiledMap.cpp \
2d/CCTMXXMLParser.cpp \
2d/CCTransition.cpp \
2d/CCTransitionPageTurn.cpp \
2d/CCTransitionProgress.cpp \
2d/CCTweenFunction.cpp \
2d/CCUserDefaultAndroid.cpp \
2d/CCUserDefault.cpp \
2d/ccUTF8.cpp \
2d/ccUtils.cpp \
2d/CCVertex.cpp \
2d/TGAlib.cpp \
2d/ccFPSImages.c \
2d/platform/CCGLViewProtocol.cpp \
2d/platform/CCFileUtils.cpp \
2d/platform/CCSAXParser.cpp \
2d/platform/CCThread.cpp \
2d/platform/CCImage.cpp \
3d/CCMesh.cpp \
3d/CCSprite3DDataCache.cpp \
3d/CCObjLoader.cpp \
3d/CCSprite3D.cpp \
3d/CCSprite3DEffect.cpp \
math/CCAffineTransform.cpp \
math/CCGeometry.cpp \
math/MathUtil.cpp \
math/Matrix.cpp \
math/Quaternion.cpp \
math/TransformUtils.cpp \
math/Vector2.cpp \
math/Vector3.cpp \
math/Vector4.cpp \
base/CCAutoreleasePool.cpp \
base/CCConfiguration.cpp \
base/CCConsole.cpp \
base/CCData.cpp \
base/CCDataVisitor.cpp \
base/CCDirector.cpp \
base/CCEvent.cpp \
base/CCEventAcceleration.cpp \
base/CCEventCustom.cpp \
base/CCEventDispatcher.cpp \
base/CCEventKeyboard.cpp \
base/CCEventListener.cpp \
base/CCEventListenerAcceleration.cpp \
base/CCEventListenerCustom.cpp \
base/CCEventListenerKeyboard.cpp \
base/CCEventListenerMouse.cpp \
base/CCEventListenerTouch.cpp \
base/CCEventMouse.cpp \
base/CCEventTouch.cpp \
base/CCEventFocus.cpp \
base/CCEventListenerFocus.cpp \
base/CCNS.cpp \
base/CCProfiling.cpp \
base/CCRef.cpp \
base/CCScheduler.cpp \
base/CCTouch.cpp \
base/CCValue.cpp \
base/ZipUtils.cpp \
base/atitc.cpp \
base/base64.cpp \
base/ccTypes.cpp \
base/etc1.cpp \
base/s3tc.cpp \
renderer/CCBatchCommand.cpp \
renderer/CCCustomCommand.cpp \
renderer/CCGLProgram.cpp \
renderer/CCGLProgramState.cpp \
renderer/CCGLProgramStateCache.cpp \
renderer/ccGLStateCache.cpp \
renderer/CCGroupCommand.cpp \
renderer/CCQuadCommand.cpp \
renderer/CCRenderCommand.cpp \
renderer/CCRenderer.cpp \
renderer/CCGLProgramCache.cpp \
renderer/ccShaders.cpp \
deprecated/CCArray.cpp \
deprecated/CCSet.cpp \
deprecated/CCString.cpp \
deprecated/CCDictionary.cpp \
deprecated/CCDeprecated.cpp \
deprecated/CCNotificationCenter.cpp \
physics/CCPhysicsBody.cpp \
physics/CCPhysicsContact.cpp \
physics/CCPhysicsJoint.cpp \
physics/CCPhysicsShape.cpp \
physics/CCPhysicsWorld.cpp \
physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
../external/ConvertUTF/ConvertUTFWrapper.cpp \
../external/ConvertUTF/ConvertUTF.c \
../external/tinyxml2/tinyxml2.cpp \
../external/unzip/ioapi.cpp \
../external/unzip/unzip.cpp \
../external/edtaa3func/edtaa3func.cpp \
../external/xxhash/xxhash.c


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \
                    $(LOCAL_PATH)/2d \
                    $(LOCAL_PATH)/2d/platform/android \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/xxhash

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \
                    $(LOCAL_PATH)/2d/platform/android \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/edtaa3func \
                    $(LOCAL_PATH)/../external/xxhash \
                    $(LOCAL_PATH)/../external/ConvertUTF


LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_freetype2_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   := -Wno-psabi  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-literal-suffix -Wno-deprecated-declarations
LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-literal-suffix -Wno-deprecated-declarations

include $(BUILD_STATIC_LIBRARY)

$(call import-module,freetype2/prebuilt/android)
$(call import-module,chipmunk)
$(call import-module,2d/platform/android)
