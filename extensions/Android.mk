LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/assets-manager/AssetsManager.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControl.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlButton.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlColourPicker.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlHuePicker.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlPotentiometer.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlSlider.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlStepper.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlSwitch.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCControlUtils.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCInvocation.cpp \
$(LOCAL_PATH)/GUI/CCControlExtension/CCScale9Sprite.cpp \
$(LOCAL_PATH)/GUI/CCEditBox/CCEditBox.cpp \
$(LOCAL_PATH)/GUI/CCEditBox/CCEditBoxImplAndroid.cpp \
$(LOCAL_PATH)/GUI/CCEditBox/CCEditBoxImplNone.cpp \
$(LOCAL_PATH)/GUI/CCEditBox/CCEditBoxImplTizen.cpp \
$(LOCAL_PATH)/GUI/CCEditBox/CCEditBoxImplWin.cpp \
$(LOCAL_PATH)/GUI/CCScrollView/CCScrollView.cpp \
$(LOCAL_PATH)/GUI/CCScrollView/CCSorting.cpp \
$(LOCAL_PATH)/GUI/CCScrollView/CCTableView.cpp \
$(LOCAL_PATH)/GUI/CCScrollView/CCTableViewCell.cpp \
$(LOCAL_PATH)/physics-nodes/CCPhysicsDebugNode.cpp \
$(LOCAL_PATH)/physics-nodes/CCPhysicsSprite.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static

LOCAL_CXXFLAGS += -fexceptions

LOCAL_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1
LOCAL_EXPORT_CFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCScrollView 
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,chipmunk)
$(call import-module,websockets/prebuilt/android)
