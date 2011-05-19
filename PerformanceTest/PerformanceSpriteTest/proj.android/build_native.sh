# set params
ANDROID_NDK_ROOT=/cygdrive/e/android/android-ndk-r5b
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x
GAME_ROOT=$COCOS2DX_ROOT/PerformanceTest/PerformanceSpriteTest
GAME_ANDROID_ROOT=$GAME_ROOT/proj.android
RESOURCE_ROOT=$GAME_ROOT/Resource

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $GAME_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $GAME_ANDROID_ROOT/assets
    fi
done

# build
$ANDROID_NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT $*

