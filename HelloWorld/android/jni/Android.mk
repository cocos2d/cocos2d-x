LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(addprefix $(LOCAL_PATH)/../../../,$(addsuffix /Android.mk, \
           cocos2dx \
           CocosDenshion/android \
	))
subdirs += $(LOCAL_PATH)/helloworld/Android.mk

include $(subdirs)
