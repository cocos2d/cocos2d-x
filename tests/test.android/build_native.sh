#!/bin/sh

ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r4-crystax
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x

# define some variables
BOX2D_ROOT=$COCOS2DX_ROOT/Box2D
CHIPMUNK_ROOT=$COCOS2DX_ROOT/chipmunk
COCOS2D_ROOT=$COCOS2DX_ROOT/cocos2dx
TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

# create symbol link to other source code
ln -s $BOX2D_ROOT $TESTS_ROOT/jni
ln -s $CHIPMUNK_ROOT $TESTS_ROOT/jni
ln -s $COCOS2D_ROOT $TESTS_ROOT/jni

# build 
pushd $ANDROID_NDK_ROOT
./ndk-build -C $TESTS_ROOT
popd
