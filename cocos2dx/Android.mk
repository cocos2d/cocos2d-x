LOCAL_PATH := $(call my-dir)

# compile cocos2d.so
include $(CLEAR_VARS)
LOCAL_MODULE := libcocos2d

LOCAL_SRC_FILES := \
CCConfiguration.cpp \
CCDrawingPrimitives.cpp \
CCScheduler.cpp \
CCCamera.cpp \
actions/CCAction.cpp \
actions/CCActionCamera.cpp \
actions/CCActionEase.cpp \
actions/CCActionGrid.cpp \
actions/CCActionGrid3D.cpp \
actions/CCActionInstant.cpp \
actions/CCActionInterval.cpp \
actions/CCActionManager.cpp \
actions/CCActionPageTurn3D.cpp \
actions/CCActionProgressTimer.cpp \
actions/CCActionTiledGrid.cpp \
base_nodes/CCAtlasNode.cpp \
base_nodes/CCNode.cpp \
cocoa/CCAffineTransform.cpp \
cocoa/CCGeometry.cpp \
cocoa/CCAutoreleasePool.cpp \
cocoa/CCData.cpp \
cocoa/CCNS.cpp \
cocoa/CCObject.cpp \
cocoa/CCSet.cpp \
cocoa/CCZone.cpp \
cocos2d.cpp \
CCDirector.cpp \
effects/CCGrabber.cpp \
effects/CCGrid.cpp \
keypad_dispatcher/CCKeypadDelegate.cpp \
keypad_dispatcher/CCKeypadDispatcher.cpp \
label_nodes/CCLabelAtlas.cpp \
label_nodes/CCLabelBMFont.cpp \
label_nodes/CCLabelTTF.cpp \
layers_scenes_transitions_nodes/CCLayer.cpp \
layers_scenes_transitions_nodes/CCScene.cpp \
layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
layers_scenes_transitions_nodes/CCTransitionRadial.cpp \
layers_scenes_transitions_nodes/CCTransition.cpp \
menu_nodes/CCMenu.cpp \
menu_nodes/CCMenuItem.cpp \
misc_nodes/CCMotionStreak.cpp \
misc_nodes/CCProgressTimer.cpp \
misc_nodes/CCRenderTexture.cpp \
misc_nodes/CCRibbon.cpp \
particle_nodes/CCParticleExamples.cpp \
particle_nodes/CCParticleSystem.cpp \
particle_nodes/CCParticleSystemPoint.cpp \
particle_nodes/CCParticleSystemQuad.cpp \
platform/CCFileUtils.cpp \
platform/CCGL.cpp \
platform/CCImage.cpp \
platform/CCStdC.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/CCCommon.cpp \
platform/platform.cpp \
platform/android/CCEGLView_android.cpp \
platform/android/CCAccelerometer_android.cpp \
platform/android/CCApplication_android.cpp \
platform/android/jni/JniHelper.cpp \
platform/android/jni/IMEJni.cpp \
platform/android/jni/MessageJni.cpp \
platform/android/jni/SensorJni.cpp \
platform/android/jni/SystemInfoJni.cpp \
platform/android/jni/TouchesJni.cpp \
script_support/CCScriptSupport.cpp \
sprite_nodes/CCAnimation.cpp \
sprite_nodes/CCAnimationCache.cpp \
sprite_nodes/CCSprite.cpp \
sprite_nodes/CCSpriteBatchNode.cpp \
sprite_nodes/CCSpriteFrame.cpp \
sprite_nodes/CCSpriteFrameCache.cpp \
support/CCArray.cpp \
support/CCProfiling.cpp \
support/CCPointExtension.cpp \
support/TransformUtils.cpp \
support/CCUserDefault.cpp \
support/base64.cpp \
support/ccUtils.cpp \
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



LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/platform \
                    $(LOCAL_PATH)/platform/third_party/android/iconv \
                    $(LOCAL_PATH)/platform/third_party/android/libpng \
                    $(LOCAL_PATH)/platform/third_party/android/libxml2 \
                    $(LOCAL_PATH)/platform/third_party/android/libjpeg                 

# it is used for ndk-r5  
# if you build with ndk-r4, comment it   
# because the new Windows toolchain doesn't support Cygwin's drive
# mapping (i.e /cygdrive/c/ instead of C:/)  
LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/platform/third_party/android/libraries) \
                 -lGLESv1_CM -llog -lz \
                 -lpng \
                 -lxml2 \
                 -ljpeg

# define the macro to compile through support/zip_support/ioapi.c                
LOCAL_CFLAGS := -DUSE_FILE32API
                                 
include $(BUILD_SHARED_LIBRARY)
