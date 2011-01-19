# set params
ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r4-crystax
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x
TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

# make sure assets is exist
if [ ! -d $TESTS_ROOT/assets ]; then
    mkdir $TESTS_ROOT/assets
fi

# copy resources
if [ -d $TESTS_ROOT/assets/animations ]; then
    echo "resources already exist"
else
    cp -R $COCOS2DX_ROOT/tests/Res/animations $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/fonts $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/Images $TESTS_ROOT/assets
    cp -R $COCOS2DX_ROOT/tests/Res/TileMaps $TESTS_ROOT/assets
    cp $COCOS2DX_ROOT/tests/Res/effect1.wav $TESTS_ROOT/assets
    cp $COCOS2DX_ROOT/tests/Res/effect2.wav $TESTS_ROOT/assets
    cp $COCOS2DX_ROOT/tests/Res/music.mid $TESTS_ROOT/assets
fi


# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $TESTS_ROOT
popd

