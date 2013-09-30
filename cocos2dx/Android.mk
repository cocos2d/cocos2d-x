LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
CCCamera.cpp \
CCConfiguration.cpp \
CCDeprecated.cpp \
CCDirector.cpp \
ccFPSImages.c \
CCScheduler.cpp \
ccTypes.cpp \
cocos2d.cpp \
actions/CCAction.cpp \
actions/CCActionCamera.cpp \
actions/CCActionCatmullRom.cpp \
actions/CCActionEase.cpp \
actions/CCActionGrid.cpp \
actions/CCActionGrid3D.cpp \
actions/CCActionInstant.cpp \
actions/CCActionInterval.cpp \
actions/CCActionManager.cpp \
actions/CCActionPageTurn3D.cpp \
actions/CCActionProgressTimer.cpp \
actions/CCActionTiledGrid.cpp \
actions/CCActionTween.cpp \
base_nodes/CCAtlasNode.cpp \
base_nodes/CCNode.cpp \
cocoa/CCAffineTransform.cpp \
cocoa/CCArray.cpp \
cocoa/CCAutoreleasePool.cpp \
cocoa/CCData.cpp \
cocoa/CCDataVisitor.cpp \
cocoa/CCDictionary.cpp \
cocoa/CCGeometry.cpp \
cocoa/CCNS.cpp \
cocoa/CCObject.cpp \
cocoa/CCSet.cpp \
cocoa/CCString.cpp \
draw_nodes/CCDrawingPrimitives.cpp \
draw_nodes/CCDrawNode.cpp \
effects/CCGrabber.cpp \
effects/CCGrid.cpp \
event_dispatcher/CCEventAcceleration.cpp \
event_dispatcher/CCEventListenerAcceleration.cpp \
event_dispatcher/CCEventCustom.cpp \
event_dispatcher/CCEventListenerCustom.cpp \
event_dispatcher/CCEvent.cpp \
event_dispatcher/CCEventDispatcher.cpp \
event_dispatcher/CCEventListener.cpp \
event_dispatcher/CCEventKeyboard.cpp \
event_dispatcher/CCEventListenerKeyboard.cpp \
event_dispatcher/CCTouch.cpp \
event_dispatcher/CCEventTouch.cpp \
event_dispatcher/CCEventListenerTouch.cpp \
kazmath/src/aabb.c \
kazmath/src/mat3.c \
kazmath/src/mat4.c \
kazmath/src/neon_matrix_impl.c \
kazmath/src/plane.c \
kazmath/src/quaternion.c \
kazmath/src/ray2.c \
kazmath/src/utility.c \
kazmath/src/vec2.c \
kazmath/src/vec3.c \
kazmath/src/vec4.c \
kazmath/src/GL/mat4stack.c \
kazmath/src/GL/matrix.c \
label_nodes/CCFont.cpp \
label_nodes/CCFontAtlas.cpp \
label_nodes/CCFontAtlasCache.cpp \
label_nodes/CCFontAtlasFactory.cpp \
label_nodes/CCFontDefinition.cpp \
label_nodes/CCFontFNT.cpp \
label_nodes/CCFontFreeType.cpp \
label_nodes/CCLabel.cpp \
label_nodes/CCLabelAtlas.cpp \
label_nodes/CCLabelBMFont.cpp \
label_nodes/CCLabelTextFormatter.cpp \
label_nodes/CCLabelTTF.cpp \
label_nodes/CCTextImage.cpp \
layers_scenes_transitions_nodes/CCLayer.cpp \
layers_scenes_transitions_nodes/CCScene.cpp \
layers_scenes_transitions_nodes/CCTransition.cpp \
layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
layers_scenes_transitions_nodes/CCTransitionProgress.cpp \
menu_nodes/CCMenu.cpp \
menu_nodes/CCMenuItem.cpp \
misc_nodes/CCClippingNode.cpp \
misc_nodes/CCMotionStreak.cpp \
misc_nodes/CCProgressTimer.cpp \
misc_nodes/CCRenderTexture.cpp \
particle_nodes/CCParticleBatchNode.cpp \
particle_nodes/CCParticleExamples.cpp \
particle_nodes/CCParticleSystem.cpp \
particle_nodes/CCParticleSystemQuad.cpp \
physics/CCPhysicsBody.cpp \
physics/CCPhysicsContact.cpp \
physics/CCPhysicsJoint.cpp \
physics/CCPhysicsShape.cpp \
physics/CCPhysicsWorld.cpp \
physics/Box2D/CCPhysicsBodyInfo.cpp \
physics/Box2D/CCPhysicsContactInfo.cpp \
physics/Box2D/CCPhysicsJointInfo.cpp \
physics/Box2D/CCPhysicsShapeInfo.cpp \
physics/Box2D/CCPhysicsWorldInfo.cpp \
physics/chipmunk/CCPhysicsBodyInfo.cpp \
physics/chipmunk/CCPhysicsContactInfo.cpp \
physics/chipmunk/CCPhysicsJointInfo.cpp \
physics/chipmunk/CCPhysicsShapeInfo.cpp \
physics/chipmunk/CCPhysicsWorldInfo.cpp \
platform/CCEGLViewProtocol.cpp \
platform/CCFileUtils.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/third_party/common/atitc/atitc.cpp \
platform/third_party/common/etc/etc1.cpp \
platform/third_party/common/s3tc/s3tc.cpp \
script_support/CCScriptSupport.cpp \
shaders/CCGLProgram.cpp \
shaders/ccGLStateCache.cpp \
shaders/CCShaderCache.cpp \
shaders/ccShaders.cpp \
sprite_nodes/CCAnimation.cpp \
sprite_nodes/CCAnimationCache.cpp \
sprite_nodes/CCSprite.cpp \
sprite_nodes/CCSpriteBatchNode.cpp \
sprite_nodes/CCSpriteFrame.cpp \
sprite_nodes/CCSpriteFrameCache.cpp \
support/base64.cpp \
support/CCNotificationCenter.cpp \
support/CCProfiling.cpp \
support/ccUTF8.cpp \
support/ccUtils.cpp \
support/CCVertex.cpp \
support/TransformUtils.cpp \
support/component/CCComponent.cpp \
support/component/CCComponentContainer.cpp \
support/data_support/ccCArray.cpp \
support/image_support/TGAlib.cpp \
support/tinyxml2/tinyxml2.cpp \
support/user_default/CCUserDefaultAndroid.cpp \
support/zip_support/ioapi.cpp \
support/zip_support/unzip.cpp \
support/zip_support/ZipUtils.cpp \
text_input_node/CCIMEDispatcher.cpp \
text_input_node/CCTextFieldTTF.cpp \
textures/CCTexture2D.cpp \
textures/CCTextureAtlas.cpp \
textures/CCTextureCache.cpp \
tilemap_parallax_nodes/CCParallaxNode.cpp \
tilemap_parallax_nodes/CCTileMapAtlas.cpp \
tilemap_parallax_nodes/CCTMXLayer.cpp \
tilemap_parallax_nodes/CCTMXObjectGroup.cpp \
tilemap_parallax_nodes/CCTMXTiledMap.cpp \
tilemap_parallax_nodes/CCTMXXMLParser.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc \
                    $(LOCAL_PATH)/platform/third_party/common/s3tc \
                    $(LOCAL_PATH)/platform/third_party/common/atitc \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/platform/third_party/common/etc \
                    $(LOCAL_PATH)/platform/third_party/common/s3tc \
                    $(LOCAL_PATH)/platform/third_party/common/atitc \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk


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

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   := -Wno-psabi -DUSE_FILE32API
LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API

include $(BUILD_STATIC_LIBRARY)

$(call import-module,libjpeg)
$(call import-module,libpng)
$(call import-module,libtiff)
$(call import-module,libwebp)
$(call import-module,libfreetype2)
$(call import-module,external/chipmunk)
