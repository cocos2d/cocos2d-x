LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := \
assets-manager/AssetsManager.cpp \
GUI/CCControlExtension/CCControl.cpp \
GUI/CCControlExtension/CCControlButton.cpp \
GUI/CCControlExtension/CCControlColourPicker.cpp \
GUI/CCControlExtension/CCControlHuePicker.cpp \
GUI/CCControlExtension/CCControlPotentiometer.cpp \
GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
GUI/CCControlExtension/CCControlSlider.cpp \
GUI/CCControlExtension/CCControlStepper.cpp \
GUI/CCControlExtension/CCControlSwitch.cpp \
GUI/CCControlExtension/CCControlUtils.cpp \
GUI/CCControlExtension/CCInvocation.cpp \
GUI/CCScrollView/CCScrollView.cpp \
GUI/CCScrollView/CCTableView.cpp \
GUI/CCScrollView/CCTableViewCell.cpp \
physics-nodes/CCPhysicsDebugNode.cpp \
physics-nodes/CCPhysicsSprite.cpp

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_curl_static
LOCAL_STATIC_LIBRARIES += box2d_static

GU/CCEditBox/CCEditBox.cpp \
GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
GUI/CCEditBox/CCEditBoxImplNone.cpp \
GUI/CCEditBox/CCEditBoxImplWin.cpp \
LOCAL_CXXFLAGS += -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../cocos \
                    $(LOCAL_PATH)/../cocos/platform/android \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/curl/include/android \
                    $(LOCAL_PATH)/../external/unzip


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView 
                    
include $(BUILD_STATIC_LIBRARY)
