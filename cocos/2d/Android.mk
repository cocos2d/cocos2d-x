LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/base64.cpp \
$(LOCAL_PATH)/CCAction.cpp \
$(LOCAL_PATH)/CCActionCamera.cpp \
$(LOCAL_PATH)/CCActionCatmullRom.cpp \
$(LOCAL_PATH)/CCActionEase.cpp \
$(LOCAL_PATH)/CCActionGrid.cpp \
$(LOCAL_PATH)/CCActionGrid3D.cpp \
$(LOCAL_PATH)/CCActionInstant.cpp \
$(LOCAL_PATH)/CCActionInterval.cpp \
$(LOCAL_PATH)/CCActionManager.cpp \
$(LOCAL_PATH)/CCActionPageTurn3D.cpp \
$(LOCAL_PATH)/CCActionProgressTimer.cpp \
$(LOCAL_PATH)/CCActionTiledGrid.cpp \
$(LOCAL_PATH)/CCActionTween.cpp \
$(LOCAL_PATH)/CCAnimation.cpp \
$(LOCAL_PATH)/CCAnimationCache.cpp \
$(LOCAL_PATH)/CCAtlasNode.cpp \
$(LOCAL_PATH)/CCCamera.cpp \
$(LOCAL_PATH)/ccCArray.cpp \
$(LOCAL_PATH)/CCClippingNode.cpp \
$(LOCAL_PATH)/CCComponent.cpp \
$(LOCAL_PATH)/CCComponentContainer.cpp \
$(LOCAL_PATH)/CCConfiguration.cpp \
$(LOCAL_PATH)/CCDeprecated.cpp \
$(LOCAL_PATH)/CCDirector.cpp \
$(LOCAL_PATH)/CCDrawingPrimitives.cpp \
$(LOCAL_PATH)/CCDrawNode.cpp \
$(LOCAL_PATH)/CCEvent.cpp \
$(LOCAL_PATH)/CCEventAcceleration.cpp \
$(LOCAL_PATH)/CCEventCustom.cpp \
$(LOCAL_PATH)/CCEventDispatcher.cpp \
$(LOCAL_PATH)/CCEventKeyboard.cpp \
$(LOCAL_PATH)/CCEventListener.cpp \
$(LOCAL_PATH)/CCEventListenerAcceleration.cpp \
$(LOCAL_PATH)/CCEventListenerCustom.cpp \
$(LOCAL_PATH)/CCEventListenerKeyboard.cpp \
$(LOCAL_PATH)/CCEventListenerTouch.cpp \
$(LOCAL_PATH)/CCEventTouch.cpp \
$(LOCAL_PATH)/CCFont.cpp \
$(LOCAL_PATH)/CCFontAtlas.cpp \
$(LOCAL_PATH)/CCFontAtlasCache.cpp \
$(LOCAL_PATH)/CCFontAtlasFactory.cpp \
$(LOCAL_PATH)/CCFontDefinition.cpp \
$(LOCAL_PATH)/CCFontFNT.cpp \
$(LOCAL_PATH)/CCFontFreeType.cpp \
$(LOCAL_PATH)/ccFPSImages.c \
$(LOCAL_PATH)/CCGLBufferedNode.cpp \
$(LOCAL_PATH)/CCGLProgram.cpp \
$(LOCAL_PATH)/ccGLStateCache.cpp \
$(LOCAL_PATH)/CCGrabber.cpp \
$(LOCAL_PATH)/CCGrid.cpp \
$(LOCAL_PATH)/CCIMEDispatcher.cpp \
$(LOCAL_PATH)/CCLabel.cpp \
$(LOCAL_PATH)/CCLabelAtlas.cpp \
$(LOCAL_PATH)/CCLabelBMFont.cpp \
$(LOCAL_PATH)/CCLabelTextFormatter.cpp \
$(LOCAL_PATH)/CCLabelTTF.cpp \
$(LOCAL_PATH)/CCLayer.cpp \
$(LOCAL_PATH)/CCMenu.cpp \
$(LOCAL_PATH)/CCMenuItem.cpp \
$(LOCAL_PATH)/CCMotionStreak.cpp \
$(LOCAL_PATH)/CCNode.cpp \
$(LOCAL_PATH)/CCNotificationCenter.cpp \
$(LOCAL_PATH)/CCParallaxNode.cpp \
$(LOCAL_PATH)/CCParticleBatchNode.cpp \
$(LOCAL_PATH)/CCParticleExamples.cpp \
$(LOCAL_PATH)/CCParticleSystem.cpp \
$(LOCAL_PATH)/CCParticleSystemQuad.cpp \
$(LOCAL_PATH)/CCProfiling.cpp \
$(LOCAL_PATH)/CCProgressTimer.cpp \
$(LOCAL_PATH)/CCRenderTexture.cpp \
$(LOCAL_PATH)/CCScene.cpp \
$(LOCAL_PATH)/CCScheduler.cpp \
$(LOCAL_PATH)/CCScriptSupport.cpp \
$(LOCAL_PATH)/CCShaderCache.cpp \
$(LOCAL_PATH)/ccShaders.cpp \
$(LOCAL_PATH)/CCSprite.cpp \
$(LOCAL_PATH)/CCSpriteBatchNode.cpp \
$(LOCAL_PATH)/CCSpriteFrame.cpp \
$(LOCAL_PATH)/CCSpriteFrameCache.cpp \
$(LOCAL_PATH)/CCTextFieldTTF.cpp \
$(LOCAL_PATH)/CCTextImage.cpp \
$(LOCAL_PATH)/CCTexture2D.cpp \
$(LOCAL_PATH)/CCTextureAtlas.cpp \
$(LOCAL_PATH)/CCTextureCache.cpp \
$(LOCAL_PATH)/CCTileMapAtlas.cpp \
$(LOCAL_PATH)/CCTMXLayer.cpp \
$(LOCAL_PATH)/CCTMXObjectGroup.cpp \
$(LOCAL_PATH)/CCTMXTiledMap.cpp \
$(LOCAL_PATH)/CCTMXXMLParser.cpp \
$(LOCAL_PATH)/CCTouch.cpp \
$(LOCAL_PATH)/CCTransition.cpp \
$(LOCAL_PATH)/CCTransitionPageTurn.cpp \
$(LOCAL_PATH)/CCTransitionProgress.cpp \
$(LOCAL_PATH)/ccTypes.cpp \
$(LOCAL_PATH)/CCUserDefault.cpp \
$(LOCAL_PATH)/CCUserDefaultAndroid.cpp \
$(LOCAL_PATH)/ccUTF8.cpp \
$(LOCAL_PATH)/ccUtils.cpp \
$(LOCAL_PATH)/CCVertex.cpp \
$(LOCAL_PATH)/cocos2d.cpp \
$(LOCAL_PATH)/TGAlib.cpp \
$(LOCAL_PATH)/TransformUtils.cpp \
$(LOCAL_PATH)/ZipUtils.cpp \
$(LOCAL_PATH)/platform/CCEGLViewProtocol.cpp \
$(LOCAL_PATH)/platform/CCFileUtils.cpp \
$(LOCAL_PATH)/platform/CCSAXParser.cpp \
$(LOCAL_PATH)/platform/CCThread.cpp \
$(LOCAL_PATH)/../base/atitc.cpp \
$(LOCAL_PATH)/../base/CCAffineTransform.cpp \
$(LOCAL_PATH)/../base/CCArray.cpp \
$(LOCAL_PATH)/../base/CCAutoreleasePool.cpp \
$(LOCAL_PATH)/../base/CCData.cpp \
$(LOCAL_PATH)/../base/CCDataVisitor.cpp \
$(LOCAL_PATH)/../base/CCDictionary.cpp \
$(LOCAL_PATH)/../base/CCGeometry.cpp \
$(LOCAL_PATH)/../base/CCNS.cpp \
$(LOCAL_PATH)/../base/CCObject.cpp \
$(LOCAL_PATH)/../base/CCSet.cpp \
$(LOCAL_PATH)/../base/CCString.cpp \
$(LOCAL_PATH)/../base/etc1.cpp \
$(LOCAL_PATH)/../base/s3tc.cpp \
$(LOCAL_PATH)/../math/kazmath/src/aabb.c \
$(LOCAL_PATH)/../math/kazmath/src/mat3.c \
$(LOCAL_PATH)/../math/kazmath/src/mat4.c \
$(LOCAL_PATH)/../math/kazmath/src/neon_matrix_impl.c \
$(LOCAL_PATH)/../math/kazmath/src/plane.c \
$(LOCAL_PATH)/../math/kazmath/src/quaternion.c \
$(LOCAL_PATH)/../math/kazmath/src/ray2.c \
$(LOCAL_PATH)/../math/kazmath/src/utility.c \
$(LOCAL_PATH)/../math/kazmath/src/vec2.c \
$(LOCAL_PATH)/../math/kazmath/src/vec3.c \
$(LOCAL_PATH)/../math/kazmath/src/vec4.c \
$(LOCAL_PATH)/../math/kazmath/src/GL/mat4stack.c \
$(LOCAL_PATH)/../math/kazmath/src/GL/matrix.c \
$(LOCAL_PATH)/../physics/CCPhysicsBody.cpp \
$(LOCAL_PATH)/../physics/CCPhysicsContact.cpp \
$(LOCAL_PATH)/../physics/CCPhysicsJoint.cpp \
$(LOCAL_PATH)/../physics/CCPhysicsShape.cpp \
$(LOCAL_PATH)/../physics/CCPhysicsWorld.cpp \
$(LOCAL_PATH)/../physics/box2d/CCPhysicsBodyInfo.cpp \
$(LOCAL_PATH)/../physics/box2d/CCPhysicsContactInfo.cpp \
$(LOCAL_PATH)/../physics/box2d/CCPhysicsJointInfo.cpp \
$(LOCAL_PATH)/../physics/box2d/CCPhysicsShapeInfo.cpp \
$(LOCAL_PATH)/../physics/box2d/CCPhysicsWorldInfo.cpp \
$(LOCAL_PATH)/../physics/chipmunk/CCPhysicsBodyInfo.cpp \
$(LOCAL_PATH)/../physics/chipmunk/CCPhysicsContactInfo.cpp \
$(LOCAL_PATH)/../physics/chipmunk/CCPhysicsJointInfo.cpp \
$(LOCAL_PATH)/../physics/chipmunk/CCPhysicsShapeInfo.cpp \
$(LOCAL_PATH)/../physics/chipmunk/CCPhysicsWorldInfo.cpp \
$(LOCAL_PATH)/../../external/tinyxml2/tinyxml2.cpp \
$(LOCAL_PATH)/../../external/unzip/ioapi.cpp \
$(LOCAL_PATH)/../../external/unzip/unzip.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/../math/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/../math/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../physics \
                    $(LOCAL_PATH)/../base \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk


LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_libpng_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jpeg_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libxml2_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libtiff_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libwebp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_freetype2_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   := -Wno-psabi -DUSE_FILE32API
LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API

include $(BUILD_STATIC_LIBRARY)

$(call import-module,jpeg/prebuilt/android)
$(call import-module,png/prebuilt/android)
$(call import-module,tiff/prebuilt/android)
$(call import-module,webp/prebuilt/android)
$(call import-module,freetype2/prebuilt/android)
$(call import-module,chipmunk)
$(call import-module,2d/platform/android)
