LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spritebuilder_static

LOCAL_MODULE_FILENAME := libspritebuilder

LOCAL_SRC_FILES := CCBXAnimationManager.cpp \
CCBXButtonLoader.cpp \
CCBXEditBoxLoader.cpp \
CCBXFileLoader.cpp \
CCBXImageViewLoader.cpp \
CCBXKeyframe.cpp \
CCBXLabelTTFLoader.cpp \
CCBXLayoutBoxLoader.cpp \
CCBXLoadingBarLoader.cpp \
CCBXNodeColorLoader.cpp \
CCBXNodeGradientLoader.cpp \
CCBXNodeLoader.cpp \
CCBXNodeLoaderLibrary.cpp \
CCBXNodeLoaderCache.cpp \
CCBXParser.cpp \
CCBXParticleSystemQuadLoader.cpp \
CCBXProgressTimerLoader.cpp \
CCBXReaderParams.cpp \
CCBXScale9SpriteLoader.cpp \
CCBXScissorsNodeLoader.cpp \
CCBXScrollListViewLoader.cpp \
CCBXScrollViewLoader.cpp \
CCBXSequence.cpp \
CCBXSequenceProperty.cpp \
CCBXSliderLoader.cpp \
CCBXSpriteLoader.cpp \
CCBXTextFieldLoader.cpp \
CCBXTextLoader.cpp \
CCBXWidgetLoader.cpp \
CCScrollListView.cpp \
SpriteBuilder.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_CFLAGS += -fexceptions

LOCAL_STATIC_LIBRARIES := cocos_ui_static
LOCAL_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_STATIC_LIBRARY)
