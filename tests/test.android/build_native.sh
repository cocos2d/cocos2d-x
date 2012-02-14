#!/bin/bash
# set params
NDK_ROOT_LOCAL=/cygdrive/e/android/android-ndk-r6b
COCOS2DX_ROOT_LOCAL=/cygdrive/f/Project/dumganhar/cocos2d-x

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

 #build
pushd $NDK_ROOT_LOCAL
./ndk-build -C $TESTS_ROOT $*
popd

