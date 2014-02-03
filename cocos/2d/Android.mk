LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
base64.cpp \
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
ccCArray.cpp \
CCClippingNode.cpp \
CCComponent.cpp \
CCComponentContainer.cpp \
CCConfiguration.cpp \
CCDeprecated.cpp \
CCDirector.cpp \
CCDrawingPrimitives.cpp \
CCDrawNode.cpp \
CCEvent.cpp \
CCEventAcceleration.cpp \
CCEventCustom.cpp \
CCEventDispatcher.cpp \
CCEventKeyboard.cpp \
CCEventListener.cpp \
CCEventListenerAcceleration.cpp \
CCEventListenerCustom.cpp \
CCEventListenerKeyboard.cpp \
CCEventListenerMouse.cpp \
CCEventListenerTouch.cpp \
CCEventMouse.cpp \
CCEventTouch.cpp \
CCFont.cpp \
CCFontCharMap.cpp \
CCFontAtlas.cpp \
CCFontAtlasCache.cpp \
CCFontFNT.cpp \
CCFontFreeType.cpp \
ccFPSImages.c \
CCGLBufferedNode.cpp \
CCGLProgram.cpp \
ccGLStateCache.cpp \
CCGrabber.cpp \
CCGrid.cpp \
CCNodeGrid.cpp \
CCIMEDispatcher.cpp \
CCLabel.cpp \
CCLabelAtlas.cpp \
CCLabelBMFont.cpp \
CCLabelTextFormatter.cpp \
CCLabelTTF.cpp \
CCLayer.cpp \
CCMenu.cpp \
CCMenuItem.cpp \
CCMotionStreak.cpp \
CCNode.cpp \
CCNotificationCenter.cpp \
CCParallaxNode.cpp \
CCParticleBatchNode.cpp \
CCParticleExamples.cpp \
CCParticleSystem.cpp \
CCParticleSystemQuad.cpp \
CCProfiling.cpp \
CCProgressTimer.cpp \
CCRenderTexture.cpp \
CCScene.cpp \
CCScheduler.cpp \
CCScriptSupport.cpp \
CCShaderCache.cpp \
ccShaders.cpp \
CCSprite.cpp \
CCSpriteBatchNode.cpp \
CCSpriteFrame.cpp \
CCSpriteFrameCache.cpp \
CCTextFieldTTF.cpp \
CCTexture2D.cpp \
CCTextureAtlas.cpp \
CCTextureCache.cpp \
CCTileMapAtlas.cpp \
CCTMXLayer.cpp \
CCTMXObjectGroup.cpp \
CCTMXTiledMap.cpp \
CCTMXXMLParser.cpp \
CCTouch.cpp \
CCTransition.cpp \
CCTransitionPageTurn.cpp \
CCTransitionProgress.cpp \
ccTypes.cpp \
CCUserDefault.cpp \
CCUserDefaultAndroid.cpp \
ccUTF8.cpp \
ccUtils.cpp \
CCVertex.cpp \
cocos2d.cpp \
TGAlib.cpp \
TransformUtils.cpp \
ZipUtils.cpp \
platform/CCGLViewProtocol.cpp \
platform/CCFileUtils.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
renderer/CCCustomCommand.cpp \
renderer/CCFrustum.cpp \
renderer/CCGroupCommand.cpp \
renderer/CCMaterialManager.cpp \
renderer/CCQuadCommand.cpp \
renderer/CCBatchCommand.cpp \
renderer/CCRenderCommand.cpp \
renderer/CCRenderer.cpp \
renderer/CCRenderMaterial.cpp \
../base/atitc.cpp \
../base/CCAffineTransform.cpp \
../base/CCArray.cpp \
../base/CCAutoreleasePool.cpp \
../base/CCConsole.cpp \
../base/CCData.cpp \
../base/CCDataVisitor.cpp \
../base/CCDictionary.cpp \
../base/CCGeometry.cpp \
../base/CCNS.cpp \
../base/CCObject.cpp \
../base/CCSet.cpp \
../base/CCString.cpp \
../base/CCValue.cpp \
../base/etc1.cpp \
../base/s3tc.cpp \
../math/kazmath/src/aabb.c \
../math/kazmath/src/mat3.c \
../math/kazmath/src/mat4.c \
../math/kazmath/src/neon_matrix_impl.c \
../math/kazmath/src/plane.c \
../math/kazmath/src/quaternion.c \
../math/kazmath/src/ray2.c \
../math/kazmath/src/utility.c \
../math/kazmath/src/vec2.c \
../math/kazmath/src/vec3.c \
../math/kazmath/src/vec4.c \
../math/kazmath/src/GL/mat4stack.c \
../math/kazmath/src/GL/matrix.c \
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
../../external/edtaa3func/edtaa3func.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/renderer \
                    $(LOCAL_PATH)/../math/kazmath/include \
                    platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/renderer \
                    $(LOCAL_PATH)/../math/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../../external/edtaa3func


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
