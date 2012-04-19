# set params
NDK_ROOT_LOCAL=/cygdrive/d/programe/android/ndk/android-ndk-r6b
COCOS2DX_ROOT_LOCAL=/cygdrive/e/cocos2d-x

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
    NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $COCOS2DX_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of COCOS2DX_ROOT: $COCOS2DX_ROOT"
    COCOS2DX_ROOT_LOCAL=$COCOS2DX_ROOT
fi

GAME_ROOT=$COCOS2DX_ROOT_LOCAL/HelloLua
GAME_ANDROID_ROOT=$GAME_ROOT/android
GAME_RESOURCE_ROOT=$GAME_ROOT/Resources

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $GAME_RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $GAME_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $GAME_ANDROID_ROOT/assets
    fi
done

# build
pushd $NDK_ROOT_LOCAL
./ndk-build -C $GAME_ANDROID_ROOT $*
popd

