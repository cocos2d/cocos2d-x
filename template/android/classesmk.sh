#!/bin/bash

FILE=$1
NEED_BOX2D=$2
NEED_CHIPMUNK=$3
NEED_LUA=$4

LOCAL_SHARED_LIBRARIES="LOCAL_SHARED_LIBRARIES := cocosdenshion_shared"

if [ $NEED_BOX2D = "true" ];then
    LOCAL_SHARED_LIBRARIES=$LOCAL_SHARED_LIBRARIES" box2d_shared"
fi

if [ $NEED_CHIPMUNK = "true" ]; then
    LOCAL_SHARED_LIBRARIES=$LOCAL_SHARED_LIBRARIES" chipmunk_shared"
fi

if [ $NEED_LUA = "true" ]; then
    LOCAL_SHARED_LIBRARIES=$LOCAL_SHARED_LIBRARIES" lua_shared"
fi

cat > $FILE << EOF
LOCAL_PATH := \$(call my-dir)

include \$(CLEAR_VARS)

LOCAL_MODULE := game_logic_static

LOCAL_MODULE_FILENAME := libgame_logic

LOCAL_SRC_FILES := AppDelegate.cpp \\
                   HelloWorldScene.cpp
                   
LOCAL_EXPORT_C_INCLUDES := \$(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
                
$LOCAL_SHARED_LIBRARIES
            
include \$(BUILD_STATIC_LIBRARY)

\$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
\$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
\$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)
EOF
