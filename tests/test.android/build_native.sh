#!/bin/bash
# set params
NDK_ROOT_LOCAL=/cygdrive/d/programe/android/ndk/android-ndk-r7b
COCOS2DX_ROOT_LOCAL=/cygdrive/e/cocos2d-x

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -s	Build externals from source
   -h	this help
EOF
}

while getopts "s" OPTION; do
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

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
    NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $COCOS2DX_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of COCOS2DX_ROOT: $COCOS2DX_ROOT"
    COCOS2DX_ROOT_LOCAL=$COCOS2DX_ROOT
fi

TESTS_ROOT=$COCOS2DX_ROOT_LOCAL/tests/test.android

# make sure assets is exist
if [ -d $TESTS_ROOT/assets ]; then
    rm -rf $TESTS_ROOT/assets
fi

mkdir $TESTS_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT_LOCAL/tests/Resources/*
do
    if [ -d $file ]; then
        cp -rf $file $TESTS_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $TESTS_ROOT/assets
    fi
done

# remove test_image_rgba4444.pvr.gz
rm -f $TESTS_ROOT/assets/Images/test_image_rgba4444.pvr.gz

# build
if [[ $buildexternalsfromsource ]]; then
    echo "Building external dependencies from source"
    $NDK_ROOT_LOCAL/ndk-build -C $TESTS_ROOT $* \
        NDK_MODULE_PATH=${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/source
else
    echo "Using prebuilt externals"
    $NDK_ROOT_LOCAL/ndk-build -C $TESTS_ROOT $* \
        NDK_MODULE_PATH=${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/prebuilt
fi
