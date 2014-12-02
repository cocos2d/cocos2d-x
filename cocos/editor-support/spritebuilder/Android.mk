LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spritebuilder_static

LOCAL_MODULE_FILENAME := libspritebuilder

LOCAL_SRC_FILES := CCBAnimationManager.cpp \
CCBFileLoader.cpp \
CCBKeyframe.cpp \
CCBLocalizationManager.cpp \
CCBReader.cpp \
CCBSequence.cpp \
CCBSequenceProperty.cpp \
CCControlButtonLoader.cpp \
CCControlLoader.cpp \
CCLabelBMFontLoader.cpp \
CCLabelTTFLoader.cpp \
CCLayerColorLoader.cpp \
CCLayerGradientLoader.cpp \
CCLayerLoader.cpp \
CCLayout.cpp \
CCLayoutBox.cpp \
CCLayoutBoxLoader.cpp \
CCMenuItemImageLoader.cpp \
CCMenuItemLoader.cpp \
CCNode+CCBRelativePositioning.cpp \
CCNodeLoader.cpp \
CCNodeLoaderLibrary.cpp \
CCParticleSystemQuadLoader.cpp \
CCPhysicsNode.cpp \
CCPhysicsNodeLoader.cpp \
CCScale9SpriteLoader.cpp \
CCScrollViewLoader.cpp \
CCSliderLoader.cpp \
CCSpriteLoader.cpp \
CCTextFieldLoader.cpp \
CCBPhysicsBody.cpp \
CCBPhysicsWorld.cpp \
CCExtTextField.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH)/../../physics/chipmunk \
$(LOCAL_PATH) \
$(LOCAL_PATH)/../../.. \
$(LOCAL_PATH)/../../renderer \
$(LOCAL_PATH)/../../audio/include

#LOCAL_CFLAGS += -Wno-psabi
#LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_STATIC_LIBRARIES := cocos_extension_static


include $(BUILD_STATIC_LIBRARY)

