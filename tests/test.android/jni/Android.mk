LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(addprefix $(LOCAL_PATH)/../../../,$(addsuffix /Android.mk, \
        Box2D \
        chipmunk \
	      cocos2dx \
	      CocosDenshion/android \
	      ))
	
subdirs += $(LOCAL_PATH)/../../Android.mk $(LOCAL_PATH)/tests/Android.mk

include $(subdirs)
