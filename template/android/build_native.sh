#!/bin/sh
PROJECT_PATH=${PWD}
APPNAME="__projectname__"
COCOS2DX_ROOT="__cocos2dxroot__"
NDK_ROOT="__ndkroot__"
DIR=$(cd `dirname $0`;pwd)
APP_ROOT=$(cd $DIR/..;pwd)

# options

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}

while getopts "sh" OPTION ; do
    case "$OPTION" in
        s)
            buildexternalsfromsource=1
            ;;
        h)
            usage
            exit 0
            ;;
    esac
done

# paths

# ... use paths relative to current directory
APP_ANDROID_ROOT="$DIR"

#echo "NDK_ROOT = $NDK_ROOT"
#echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
#echo "APP_ROOT = $APP_ROOT"
#echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

# copy resources
cp -rf "$APP_ROOT"/Resources/* "$APP_ANDROID_ROOT"/assets

# copy icons (if they exist)
file="$APP_ANDROID_ROOT"/assets/Icon-72.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-hdpi/icon.png
fi
file="$APP_ANDROID_ROOT"/assets/Icon-48.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-mdpi/icon.png
fi
file="$APP_ANDROID_ROOT"/assets/Icon-32.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-ldpi/icon.png
fi


if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
