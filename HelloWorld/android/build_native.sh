# set params
ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r5
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x
HELLOWORLD_ROOT=$COCOS2DX_ROOT/HelloWorld/android

# make sure assets is exist
if [ -d $HELLOWORLD_ROOT/assets ]; then
    rm -rf $HELLOWORLD_ROOT/assets
fi

mkdir $HELLOWORLD_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT/HelloWorld/Resource/*
do
    if [ -d $file ]; then
        cp -rf $file $HELLOWORLD_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $HELLOWORLD_ROOT/assets
    fi
done

# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $HELLOWORLD_ROOT $*
popd

