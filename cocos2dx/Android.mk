LOCAL_PATH := $(call my-dir)

# compile cocos2d.so
include $(CLEAR_VARS)
LOCAL_MODULE := libcocos2d

LOCAL_SRC_FILES := \
CCConfiguration.cpp \
CCDirector.cpp \
CCDrawingPrimitives.cpp \
CCScheduler.cpp \
CCamera.cpp \
actions/CCAction.cpp \
actions/CCActionManager.cpp \
actions/CCCameraAction.cpp \
actions/CCEaseAction.cpp \
actions/CCGrid3DAction.cpp \
actions/CCGridAction.cpp \
actions/CCInstantAction.cpp \
actions/CCIntervalAction.cpp \
actions/CCPageTurn3DAction.cpp \
actions/CCProgressTimerActions.cpp \
actions/CCTiledGridAction.cpp \
base_nodes/CCAtlasNode.cpp \
base_nodes/CCNode.cpp \
cocoa/CGAffineTransform.cpp \
cocoa/CGGeometry.cpp \
cocoa/NSAutoreleasePool.cpp \
cocoa/NSData.cpp \
cocoa/NSObject.cpp \
cocoa/NSSet.cpp \
cocoa/NSZone.cpp \
cocos2d.cpp \
effects/CCGrabber.cpp \
effects/CCGrid.cpp \
label_nodes/CCBitmapFontAtlas.cpp \
label_nodes/CCLabel.cpp \
label_nodes/CCLabelAtlas.cpp \
layers_scenes_transitions_nodes/CCLayer.cpp \
layers_scenes_transitions_nodes/CCPageTurnTransition.cpp \
layers_scenes_transitions_nodes/CCRadialTransition.cpp \
layers_scenes_transitions_nodes/CCScene.cpp \
layers_scenes_transitions_nodes/CCTransition.cpp \
menu_nodes/CCMenu.cpp \
menu_nodes/CCMenuItem.cpp \
misc_nodes/CCMotionStreak.cpp \
misc_nodes/CCProgressTimer.cpp \
misc_nodes/CCRenderTexture.cpp \
misc_nodes/CCRibbon.cpp \
particle_nodes/CCParticleExamples.cpp \
particle_nodes/CCParticleSystem.cpp \
particle_nodes/CCPointParticleSystem.cpp \
particle_nodes/CCQuadParticleSystem.cpp \
platform/android/CCTime.cpp \
platform/android/CCXApplication_android.cpp \
platform/android/CCXBitmapDC.cpp \
platform/android/CCXEGLView_android.cpp \
platform/android/CCXFileUtils_android.cpp \
platform/android/CCXUIImage_android.cpp \
platform/android/NSLock.cpp \
platform/android/UncompressFile.cpp \
platform/android/ZipUtils.cpp \
sprite_nodes/CCSprite.cpp \
sprite_nodes/CCSpriteFrame.cpp \
sprite_nodes/CCSpriteFrameCache.cpp \
sprite_nodes/CCSpriteSheet.cpp \
support/CCProfiling.cpp \
support/CGPointExtension.cpp \
support/TransformUtils.cpp \
support/base64.cpp \
support/image_support/TGAlib.cpp \
support/opengl_support/glu.cpp \
textures/CCTexture2D.cpp \
textures/CCTextureAtlas.cpp \
textures/CCTextureCache.cpp \
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
                    $(LOCAL_PATH)/platform/android/third_party/iconv \
                    $(LOCAL_PATH)/platform/android/third_party/libpng \
                    $(LOCAL_PATH)/platform/android/third_party/libxml2 \
                    $(LOCAL_PATH)/platform/android/third_party/libjpeg 

LOCAL_LDLIBS := -lGLESv1_CM -llog -lz -ljnigraphics\
                -L$(LOCAL_PATH)/platform/android/third_party/libs -lpng \
                -L$(LOCAL_PATH)/platform/android/third_party/libs -lxml2 \
                -L$(LOCAL_PATH)/platform/android/third_party/libs -ljpeg 
                                 
include $(BUILD_SHARED_LIBRARY)