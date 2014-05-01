LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
CCAction.cpp \
CCActionCamera.cpp \
CCActionCatmullRom.cpp \
CCActionEase.cpp \
CCActionGrid.cpp \
CCActionGrid3D.cpp \
CCActionInstant.cpp \
CCActionInterval.cpp \
CCActionManager.cpp \
CCActionPageTurn3D.cpp \
CCActionProgressTimer.cpp \
CCActionTiledGrid.cpp \
CCActionTween.cpp \
CCAnimation.cpp \
CCAnimationCache.cpp \
CCAtlasNode.cpp \
CCClippingNode.cpp \
CCComponent.cpp \
CCComponentContainer.cpp \
CCDrawNode.cpp \
CCDrawingPrimitives.cpp \
CCFont.cpp \
CCFontAtlas.cpp \
CCFontAtlasCache.cpp \
CCFontCharMap.cpp \
CCFontFNT.cpp \
CCFontFreeType.cpp \
CCGLBufferedNode.cpp \
CCGLProgram.cpp \
CCGrabber.cpp \
CCGrid.cpp \
CCIMEDispatcher.cpp \
CCLabel.cpp \
CCLabelAtlas.cpp \
CCLabelBMFont.cpp \
CCLabelTTF.cpp \
CCLabelTextFormatter.cpp \
CCLayer.cpp \
CCMenu.cpp \
CCMenuItem.cpp \
CCMotionStreak.cpp \
CCNode.cpp \
CCNodeGrid.cpp \
CCParallaxNode.cpp \
CCParticleBatchNode.cpp \
CCParticleExamples.cpp \
CCParticleSystem.cpp \
CCParticleSystemQuad.cpp \
CCProgressTimer.cpp \
CCRenderTexture.cpp \
CCScene.cpp \
CCScriptSupport.cpp \
CCShaderCache.cpp \
CCSprite.cpp \
CCSpriteBatchNode.cpp \
CCSpriteFrame.cpp \
CCSpriteFrameCache.cpp \
CCTMXLayer.cpp \
CCTMXObjectGroup.cpp \
CCTMXTiledMap.cpp \
CCTMXXMLParser.cpp \
CCTextFieldTTF.cpp \
CCTexture2D.cpp \
CCTextureAtlas.cpp \
CCTextureCache.cpp \
CCTileMapAtlas.cpp \
CCTransition.cpp \
CCTransitionPageTurn.cpp \
CCTransitionProgress.cpp \
CCTweenFunction.cpp \
CCUserDefault.cpp \
CCUserDefaultAndroid.cpp \
CCVertex.cpp \
TGAlib.cpp \
ccCArray.cpp \
ccGLStateCache.cpp \
ccShaders.cpp \
ccUTF8.cpp \
ccUtils.cpp \
ccFPSImages.c \
../cocos2d.cpp \
platform/CCGLViewProtocol.cpp \
platform/CCFileUtils.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/CCImage.cpp \
../math/CCAffineTransform.cpp \
../math/CCGeometry.cpp \
../math/MathUtil.cpp \
../math/Matrix.cpp \
../math/Quaternion.cpp \
../math/TransformUtils.cpp \
../math/Vector2.cpp \
../math/Vector3.cpp \
../math/Vector4.cpp \
../base/CCAutoreleasePool.cpp \
../base/CCConfiguration.cpp \
../base/CCConsole.cpp \
../base/CCData.cpp \
../base/CCDataVisitor.cpp \
../base/CCDirector.cpp \
../base/CCEvent.cpp \
../base/CCEventAcceleration.cpp \
../base/CCEventCustom.cpp \
../base/CCEventDispatcher.cpp \
../base/CCEventKeyboard.cpp \
../base/CCEventListener.cpp \
../base/CCEventListenerAcceleration.cpp \
../base/CCEventListenerCustom.cpp \
../base/CCEventListenerKeyboard.cpp \
../base/CCEventListenerMouse.cpp \
../base/CCEventListenerTouch.cpp \
../base/CCEventMouse.cpp \
../base/CCEventTouch.cpp \
../base/CCNS.cpp \
../base/CCProfiling.cpp \
../base/CCRef.cpp \
../base/CCScheduler.cpp \
../base/CCTouch.cpp \
../base/CCValue.cpp \
../base/ZipUtils.cpp \
../base/atitc.cpp \
../base/base64.cpp \
../base/ccTypes.cpp \
../base/etc1.cpp \
../base/s3tc.cpp \
../renderer/CCCustomCommand.cpp \
../renderer/CCGroupCommand.cpp \
../renderer/CCQuadCommand.cpp \
../renderer/CCBatchCommand.cpp \
../renderer/CCRenderCommand.cpp \
../renderer/CCRenderer.cpp \
../deprecated/CCArray.cpp \
../deprecated/CCSet.cpp \
../deprecated/CCString.cpp \
../deprecated/CCDictionary.cpp \
../deprecated/CCDeprecated.cpp \
../deprecated/CCNotificationCenter.cpp \
../physics/CCPhysicsBody.cpp \
../physics/CCPhysicsContact.cpp \
../physics/CCPhysicsJoint.cpp \
../physics/CCPhysicsShape.cpp \
../physics/CCPhysicsWorld.cpp \
../physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
../physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
../../external/tinyxml2/tinyxml2.cpp \
../../external/unzip/ioapi.cpp \
../../external/unzip/unzip.cpp \
../../external/edtaa3func/edtaa3func.cpp \
../../external/xxhash/xxhash.c


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/renderer \
                    $(LOCAL_PATH)/../math \
                    platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../deprecated \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../../external/xxhash

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/renderer \
                    $(LOCAL_PATH)/../math \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../deprecated \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../../external/edtaa3func \
                    $(LOCAL_PATH)/../../external/xxhash


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
