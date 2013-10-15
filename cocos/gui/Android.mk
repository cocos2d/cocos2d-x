LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := gui_static

LOCAL_MODULE_FILENAME := libgui

LOCAL_SRC_FILES := base-classes/UIRootWidget.cpp \
base-classes/UIWidget.cpp \
layouts/Layout.cpp \
layouts/LayoutParameter.cpp \
layouts/UILayoutDefine.cpp \
system/CocosGUI.cpp \
system/UIHelper.cpp \
system/UIInputManager.cpp \
system/UILayer.cpp \
widgets/scroll-widget/UIDragPanel.cpp \
widgets/scroll-widget/UIListView.cpp \
widgets/scroll-widget/UIPageView.cpp \
widgets/scroll-widget/UIScrollView.cpp \
widgets/UIButton.cpp \
widgets/UICheckBox.cpp \
widgets/UIImageView.cpp \
widgets/UILabel.cpp \
widgets/UILabelAtlas.cpp \
widgets/UILabelBMFont.cpp \
widgets/UILoadingBar.cpp \
widgets/UISlider.cpp \
widgets/UITextField.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../2d \
$(LOCAL_PATH) \
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
