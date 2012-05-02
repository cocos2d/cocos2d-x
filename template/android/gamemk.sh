#!/bin/bash

FILE=$1
NEED_BOX2D=$2
NEED_CHIPMUNK=$3
NEED_LUA=$4

LOCAL_STATIC_LIBRARIES="LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static"
MODULES_TO_CALL="\$(call import-module,CocosDenshion/android) \$(call import-module,cocos2dx)"
LOCAL_SRC_FILES="LOCAL_SRC_FILES := helloworld/main.cpp \\
                   ../../Classes/AppDelegate.cpp \\
                   ../../Classes/HelloWorldScene.cpp"

if [ $NEED_BOX2D = "true" ];then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" box2d_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,Box2D)"
fi

if [ $NEED_CHIPMUNK = "true" ]; then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" chipmunk_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,chipmunk)"
fi

if [ $NEED_LUA = "true" ]; then
    LOCAL_STATIC_LIBRARIES=$LOCAL_STATIC_LIBRARIES" cocos_lua_static"
    MODULES_TO_CALL=$MODULES_TO_CALL" \$(call import-module,lua/proj.android/jni)"
    LOCAL_SRC_FILES=$LOCAL_SRC_FILES" ../../../lua/cocos2dx_support/CCLuaEngine.cpp \\
                                      ../../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \\
                                      ../../../lua/cocos2dx_support/LuaCocos2d.cpp \\
                                      ../../../lua/cocos2dx_support/tolua_fix.c"
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
