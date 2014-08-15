LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_ui_static

LOCAL_MODULE_FILENAME := libui

LOCAL_SRC_FILES := \
UIWidget.cpp \
UILayout.cpp \
UILayoutParameter.cpp \
UILayoutManager.cpp \
CocosGUI.cpp \
UIHelper.cpp \
UIListView.cpp \
UIPageView.cpp \
UIScrollView.cpp \
UIButton.cpp \
UICheckBox.cpp \
UIImageView.cpp \
UIText.cpp \
UITextAtlas.cpp \
UITextBMFont.cpp \
UILoadingBar.cpp \
UISlider.cpp \
UITextField.cpp \
UIRichText.cpp \
UIHBox.cpp \
UIVBox.cpp \
UIRelativeBox.cpp \
UIVideoPlayerAndroid.cpp \
UIDeprecated.cpp \
UIScale9Sprite.cpp \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../editor-support

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../../external \
$(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../.. \
$(LOCAL_PATH)/../editor-support


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,extensions)
$(call import-module,.)
