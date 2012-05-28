# include libandprof.a in the build
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_spidermonkey_static
LOCAL_MODULE_FILENAME := spidermonkey
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libjs_static.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include \
                           $(LOCAL_PATH)/../JSBindings
include $(PREBUILT_STATIC_LIBRARY)
