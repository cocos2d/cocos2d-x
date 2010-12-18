# set params
ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r4-crystax
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x
# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $COCOS2DX_ROOT/HelloWorld/android
popd

