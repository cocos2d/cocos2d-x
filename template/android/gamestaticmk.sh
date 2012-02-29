#!/bin/bash

FILE=$1
NEED_BOX2D=$2
NEED_CHIPMUNK=$3
NEED_LUA=$4

if [ $NEED_BOX2D = "true" ];then
    BOX2D="Box2D"
fi

if [ $NEED_CHIPMUNK = "true" ]; then
    CHIPMUNK="chipmunk"
fi

if [ $NEED_LUA = "true" ]; then
    LUA="lua/proj.android/jni"
fi

cat > $FILE << EOF
LOCAL_PATH := \$(call my-dir)
include \$(CLEAR_VARS)

subdirs := \$(addprefix \$(LOCAL_PATH)/../../../,\$(addsuffix /Android.mk, \\
           cocos2dx \\
           CocosDenshion/android \\
           $BOX2D $CHIPMUNK $LUA \\
           ))
	
subdirs += \$(LOCAL_PATH)/../../Classes/Android.mk \$(LOCAL_PATH)/helloworld/Android.mk

include \$(subdirs)
EOF
