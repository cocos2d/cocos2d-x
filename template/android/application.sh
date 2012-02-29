#!/bin/bash

FILE=$1
NEED_BOX2D=$2
NEED_CHIPMUNK=$3
NEED_LUA=$4

APP_MODULES="APP_MODULES := cocos2dx_static cocosdenshion_shared"
if [ $NEED_BOX2D = "true" ];then
    APP_MODULES=$APP_MODULES" box2d_shared"
fi

if [ $NEED_CHIPMUNK = "true" ]; then
    APP_MODULES=$APP_MODULES" chipmunk_shared"
fi

if [ $NEED_LUA = "true" ]; then
    APP_MODULES=$APP_MODULES" lua_shared"
fi

APP_MODULES=$APP_MODULES" game_shared"

cat > $FILE << EOF
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti
$APP_MODULES
EOF
