# set params
ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r4-crystax
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x

# copy resources

TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

if [ -d $TESTS_ROOT/assets/animations ]; then
    echo "resources already exist"
else
    cp -R $COCOS2DX_ROOT/tests/Res/animations $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/fonts $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/Images $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/TileMaps $TESTS_ROOT/assets
fi


# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $TESTS_ROOT
popd

