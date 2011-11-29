#!/bin/bash
# set params
ANDROID_NDK_ROOT=/cygdrive/d/programe/android/ndk/android-ndk-r6b
COCOS2DX_ROOT=/cygdrive/e/cocos2d-x
TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

# make sure assets is exist
if [ -d $TESTS_ROOT/assets ]; then
    rm -rf $TESTS_ROOT/assets
fi

mkdir $TESTS_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT/tests/Res/*
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
pushd $ANDROID_NDK_ROOT
./ndk-build -C $TESTS_ROOT $*
popd

