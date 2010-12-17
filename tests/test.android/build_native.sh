# set params
ANDROID_NDK_ROOT=/workspace/android-ndk-r5
COCOS2DX_ROOT=/workspace/cocos2d-x
# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $COCOS2DX_ROOT/tests/test.android
popd

