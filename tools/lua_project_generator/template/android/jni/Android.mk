LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(addprefix $(LOCAL_PATH)/../../../,$(addsuffix /Android.mk, \
           cocos2dx \
           CocosDenshion/android \
           lua/proj.android/jni \
    ))
subdirs += $(LOCAL_PATH)/LuaProjectTemplate/Android.mk

include $(subdirs)
