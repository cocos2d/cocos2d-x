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
CCTweenFunction.cpp \
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
platform/CCImage.cpp \
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
../base/CCAutoreleasePool.cpp \
../base/CCConsole.cpp \
../base/CCData.cpp \
../base/CCDataVisitor.cpp \
../base/CCGeometry.cpp \
../base/CCNS.cpp \
../base/CCRef.cpp \
../base/CCValue.cpp \
../base/etc1.cpp \
../base/s3tc.cpp \
../deprecated/CCArray.cpp \
../deprecated/CCSet.cpp \
../deprecated/CCString.cpp \
../deprecated/CCDictionary.cpp \
../deprecated/CCDeprecated.cpp \
../deprecated/CCNotificationCenter.cpp \
../math/kazmath/kazmath/aabb.c \
../math/kazmath/kazmath/mat3.c \
../math/kazmath/kazmath/mat4.c \
../math/kazmath/kazmath/neon_matrix_impl.c \
../math/kazmath/kazmath/plane.c \
../math/kazmath/kazmath/quaternion.c \
../math/kazmath/kazmath/ray2.c \
../math/kazmath/kazmath/ray3.c \
../math/kazmath/kazmath/utility.c \
../math/kazmath/kazmath/vec2.c \
../math/kazmath/kazmath/vec3.c \
../math/kazmath/kazmath/vec4.c \
../math/kazmath/kazmath/GL/mat4stack.c \
../math/kazmath/kazmath/GL/matrix.c \
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
                    $(LOCAL_PATH)/../math/kazmath \
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
                    $(LOCAL_PATH)/../math/kazmath \
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
