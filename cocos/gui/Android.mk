LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_gui_static

LOCAL_MODULE_FILENAME := libgui

LOCAL_SRC_FILES := UIRootWidget.cpp \
UIWidget.cpp \
Layout.cpp \
LayoutParameter.cpp \
UILayoutDefine.cpp \
CocosGUI.cpp \
UIHelper.cpp \
UIInputManager.cpp \
UILayer.cpp \
UIDragPanel.cpp \
UIListView.cpp \
UIPageView.cpp \
UIScrollView.cpp \
UIButton.cpp \
UICheckBox.cpp \
UIImageView.cpp \
UILabel.cpp \
UILabelAtlas.cpp \
UILabelBMFont.cpp \
UILoadingBar.cpp \
UISlider.cpp \
UITextField.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH)/..

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

include $(BUILD_STATIC_LIBRARY)


$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)
$(call import-module,2d)
