LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
CCConfiguration.cpp \
CCDrawingPrimitives.cpp \
CCScheduler.cpp \
CCCamera.cpp \
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
cocoa/CCGeometry.cpp \
cocoa/CCAutoreleasePool.cpp \
cocoa/CCDictionary.cpp \
cocoa/CCNS.cpp \
cocoa/CCObject.cpp \
cocoa/CCSet.cpp \
cocoa/CCString.cpp \
cocoa/CCZone.cpp \
cocoa/CCArray.cpp \
cocos2d.cpp \
CCDirector.cpp \
effects/CCGrabber.cpp \
effects/CCGrid.cpp \
extensions/CCNotificationCenter/CCNotificationCenter.cpp \
extensions/CCControlExtension/CCControl.cpp \
extensions/CCControlExtension/CCControlButton.cpp \
extensions/CCControlExtension/CCControlColourPicker.cpp \
extensions/CCControlExtension/CCControlHuePicker.cpp \
extensions/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
extensions/CCControlExtension/CCControlSlider.cpp \
extensions/CCControlExtension/CCControlSwitch.cpp \
extensions/CCControlExtension/CCControlUtils.cpp \
extensions/CCControlExtension/CCInvocation.cpp \
extensions/CCControlExtension/CCMenuPassive.cpp \
extensions/CCControlExtension/CCScale9Sprite.cpp \
extensions/CCControlExtension/CCSpacer.cpp \
extensions/CCListView/CCListView.cpp \
extensions/CCListView/CCListViewCell.cpp \
extensions/CCTextureWatcher/CCTextureWatcher.cpp \
extensions/CCBReader/CCBFileLoader.cpp \
extensions/CCBReader/CCBReader.cpp \
extensions/CCBReader/CCNodeLoaderLibrary.cpp \
extensions/CCBReader/CCNodeLoader.cpp \
extensions/CCBReader/CCControlButtonLoader.cpp \
extensions/CCBReader/CCControlLoader.cpp \
extensions/CCBReader/CCLabelBMFontLoader.cpp \
extensions/CCBReader/CCLabelTTFLoader.cpp \
extensions/CCBReader/CCLayerLoader.cpp \
extensions/CCBReader/CCLayerColorLoader.cpp \
extensions/CCBReader/CCLayerGradientLoader.cpp \
extensions/CCBReader/CCMenuItemLoader.cpp \
extensions/CCBReader/CCMenuItemImageLoader.cpp \
extensions/CCBReader/CCSpriteLoader.cpp \
extensions/CCBReader/CCScale9SpriteLoader.cpp \
extensions/CCBReader/CCScrollViewLoader.cpp \
extensions/CCBReader/CCParticleSystemQuadLoader.cpp \
extensions/CCScrollView/CCScrollView.cpp \
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
keypad_dispatcher/CCKeypadDelegate.cpp \
keypad_dispatcher/CCKeypadDispatcher.cpp \
label_nodes/CCLabelAtlas.cpp \
label_nodes/CCLabelBMFont.cpp \
label_nodes/CCLabelTTF.cpp \
layers_scenes_transitions_nodes/CCLayer.cpp \
layers_scenes_transitions_nodes/CCScene.cpp \
layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
layers_scenes_transitions_nodes/CCTransition.cpp \
layers_scenes_transitions_nodes/CCTransitionProgress.cpp \
menu_nodes/CCMenu.cpp \
menu_nodes/CCMenuItem.cpp \
misc_nodes/CCMotionStreak.cpp \
misc_nodes/CCProgressTimer.cpp \
misc_nodes/CCRenderTexture.cpp \
particle_nodes/CCParticleExamples.cpp \
particle_nodes/CCParticleSystem.cpp \
particle_nodes/CCParticleBatchNode.cpp \
particle_nodes/CCParticleSystemQuad.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/platform.cpp \
platform/CCEGLViewProtocol.cpp \
platform/android/CCEGLView.cpp \
platform/android/CCAccelerometer.cpp \
platform/android/CCApplication.cpp \
platform/android/CCCommon.cpp \
platform/android/CCFileUtils.cpp \
platform/android/CCImage.cpp \
platform/android/jni/JniHelper.cpp \
platform/android/jni/IMEJni.cpp \
platform/android/jni/MessageJni.cpp \
platform/android/jni/SensorJni.cpp \
platform/android/jni/SystemInfoJni.cpp \
platform/android/jni/TouchesJni.cpp \
script_support/CCScriptSupport.cpp \
shaders/ccShaders.cpp \
shaders/CCGLProgram.cpp \
shaders/ccGLStateCache.cpp \
shaders/CCShaderCache.cpp \
sprite_nodes/CCAnimation.cpp \
sprite_nodes/CCAnimationCache.cpp \
sprite_nodes/CCSprite.cpp \
sprite_nodes/CCSpriteBatchNode.cpp \
sprite_nodes/CCSpriteFrame.cpp \
sprite_nodes/CCSpriteFrameCache.cpp \
support/CCProfiling.cpp \
support/CCPointExtension.cpp \
support/TransformUtils.cpp \
support/CCUserDefault.cpp \
support/base64.cpp \
support/ccUtils.cpp \
support/CCVertex.cpp \
support/data_support/ccCArray.cpp \
support/image_support/TGAlib.cpp \
support/zip_support/ZipUtils.cpp \
support/zip_support/ioapi.cpp \
support/zip_support/unzip.cpp \
text_input_node/CCIMEDispatcher.cpp \
text_input_node/CCTextFieldTTF.cpp \
textures/CCTexture2D.cpp \
textures/CCTextureAtlas.cpp \
textures/CCTextureCache.cpp \
textures/CCTexturePVR.cpp \
tileMap_parallax_nodes/CCParallaxNode.cpp \
tileMap_parallax_nodes/CCTMXLayer.cpp \
tileMap_parallax_nodes/CCTMXObjectGroup.cpp \
tileMap_parallax_nodes/CCTMXTiledMap.cpp \
tileMap_parallax_nodes/CCTMXXMLParser.cpp \
tileMap_parallax_nodes/CCTileMapAtlas.cpp \
touch_dispatcher/CCTouchDispatcher.cpp \
touch_dispatcher/CCTouchHandler.cpp 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android


LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv2

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/kazmath/include \
                    $(LOCAL_PATH)/platform/android


LOCAL_LDLIBS := -lGLESv2 \
                -lEGL \
                -llog \
                -lz 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_libpng_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jpeg_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libxml2_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_libtiff_static


# define the macro to compile through support/zip_support/ioapi.c                
LOCAL_CFLAGS := -DUSE_FILE32API

include $(BUILD_STATIC_LIBRARY)

$(call import-module,libjpeg)
$(call import-module,libpng)
$(call import-module,libxml2)
$(call import-module,libtiff)

