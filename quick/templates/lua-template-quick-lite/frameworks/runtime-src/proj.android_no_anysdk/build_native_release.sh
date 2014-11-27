#!/usr/bin/env bash

# set .bash_profile or .profile
if [ -f ~/.bash_profile ]; then
PROFILE_NAME=~/.bash_profile
else
PROFILE_NAME=~/.profile
fi
source $PROFILE_NAME

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$DIR/../../.."
APP_ANDROID_ROOT="$DIR"
export COCOS2DX_ROOT=`cat ~/.QUICK_V3_ROOT`

echo "- config:"
echo "  ANDROID_NDK_ROOT    = $ANDROID_NDK_ROOT"
echo "  COCOS2DX_ROOT       = $COCOS2DX_ROOT"
echo "  APP_ROOT            = $APP_ROOT"
echo "  APP_ANDROID_ROOT    = $APP_ANDROID_ROOT"

echo "- cleanup"
find "$APP_ANDROID_ROOT" -type d | xargs chmod 755 $1
if [ -d "$APP_ANDROID_ROOT"/bin ]; then
    rm -rf "$APP_ANDROID_ROOT"/bin/*.apk
fi
mkdir -p "$APP_ANDROID_ROOT"/bin
chmod 755 "$APP_ANDROID_ROOT"/bin

if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets/*
fi
mkdir -p "$APP_ANDROID_ROOT"/assets
chmod 755 "$APP_ANDROID_ROOT"/assets

echo "- copy scripts"
cp -rf "$APP_ROOT"/src "$APP_ANDROID_ROOT"/assets/
echo "- copy resources"
cp -rf "$APP_ROOT"/res "$APP_ANDROID_ROOT"/assets/
echo "- copy config"
cp -rf "$APP_ROOT"/config.json "$APP_ANDROID_ROOT"/assets/

# echo COPY framework_precompiled.zip
# echo FROM: $QUICK_V3_ROOT/quick/lib/framework_precompiled
# echo TO: "$APP_ANDROID_ROOT"/assets/res/
# cp $QUICK_V3_ROOT/quick/lib/framework_precompiled/framework_precompiled.zip "$APP_ANDROID_ROOT"/assets/res/
echo ""

# build
echo "Using prebuilt externals"
"$ANDROID_NDK_ROOT"/ndk-build $ANDROID_NDK_BUILD_FLAGS NDK_DEBUG=$NDK_DEBUG $NDK_BUILD_FLAGS -C "$APP_ANDROID_ROOT" $* \
"NDK_MODULE_PATH=${APP_ANDROID_ROOT}:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos:${COCOS2DX_ROOT}/quick/lib:${COCOS2DX_ROOT}/external:${COCOS2DX_ROOT}/cocos/scripting:${APP_ANDROID_ROOT}/../Classes"
