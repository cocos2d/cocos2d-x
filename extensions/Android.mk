LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := CCBReader/CCBFileLoader.cpp \
CCBReader/CCBReader.cpp \
CCBReader/CCControlButtonLoader.cpp \
CCBReader/CCControlLoader.cpp \
CCBReader/CCLabelBMFontLoader.cpp \
CCBReader/CCLabelTTFLoader.cpp \
CCBReader/CCLayerColorLoader.cpp \
CCBReader/CCLayerGradientLoader.cpp \
CCBReader/CCLayerLoader.cpp \
CCBReader/CCMenuItemImageLoader.cpp \
CCBReader/CCMenuItemLoader.cpp \
CCBReader/CCNodeLoader.cpp \
CCBReader/CCNodeLoaderLibrary.cpp \
CCBReader/CCParticleSystemQuadLoader.cpp \
CCBReader/CCScale9SpriteLoader.cpp \
CCBReader/CCScrollViewLoader.cpp \
CCBReader/CCSpriteLoader.cpp \
UI/CCControlExtension/CCControl.cpp \
UI/CCControlExtension/CCControlButton.cpp \
UI/CCControlExtension/CCControlColourPicker.cpp \
UI/CCControlExtension/CCControlHuePicker.cpp \
UI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
UI/CCControlExtension/CCControlSlider.cpp \
UI/CCControlExtension/CCControlSwitch.cpp \
UI/CCControlExtension/CCControlUtils.cpp \
UI/CCControlExtension/CCInvocation.cpp \
UI/CCControlExtension/CCMenuPassive.cpp \
UI/CCControlExtension/CCScale9Sprite.cpp \
UI/CCControlExtension/CCSpacer.cpp \
UI/CCScrollView/CCScrollView.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/CCBReader \
                           $(LOCAL_PATH)/UI/CCControlExtension \
                           $(LOCAL_PATH)/UI/CCScrollView
                    

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
