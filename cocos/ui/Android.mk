LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_ui_static

LOCAL_MODULE_FILENAME := libui

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

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
UIScrollViewBar.cpp \
UIButton.cpp \
UIAbstractCheckButton.cpp \
UICheckBox.cpp \
UIRadioButton.cpp \
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
UIVideoPlayer-android.cpp \
UIDeprecated.cpp \
UIScale9Sprite.cpp \
UIWebView.cpp \
UIWebViewImpl-android.cpp \
UIEditBox/UIEditBox.cpp \
UIEditBox/UIEditBoxImpl-android.cpp \
UILayoutComponent.cpp \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../editor-support

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../editor-support

LOCAL_STATIC_LIBRARIES := cocos_extension_static

include $(BUILD_STATIC_LIBRARY)
