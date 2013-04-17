#!/bin/bash

FILE=$1
NEED_BOX2D=$2
NEED_CHIPMUNK=$3
NEED_LUA=$4

LOCAL_STATIC_LIBRARIES="LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static"
MODULES_TO_CALL="\$(call import-module,CocosDenshion/android) \\
\$(call import-module,cocos2dx) \\
\$(call import-module,extensions)"

LOCAL_SRC_FILES="LOCAL_SRC_FILES := hellocpp/main.cpp \\
                   ../../Classes/AppDelegate.cpp \\
                   ../../Classes/HelloWorldScene.cpp"

if [ $NEED_BOX2D = "true" ];then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" box2d_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,external/Box2D)"
fi

if [ $NEED_CHIPMUNK = "true" ]; then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" chipmunk_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,external/chipmunk)"
fi

if [ $NEED_LUA = "true" ]; then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" cocos_lua_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,scripting/lua/proj.android)"
fi

cat > $FILE << EOF
LOCAL_PATH := \$(call my-dir)

include \$(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

$LOCAL_SRC_FILES
                   
LOCAL_C_INCLUDES := \$(LOCAL_PATH)/../../Classes                   

$LOCAL_STATIC_LIBRARIES
            
include \$(BUILD_SHARED_LIBRARY)

$MODULES_TO_CALL
EOF
