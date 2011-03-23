# set params
ANDROID_NDK_ROOT=__ndkroot__
COCOS2DX_ROOT=__cocos2dxroot__
HELLOWORLD_ROOT=$COCOS2DX_ROOT/__projectname__
HELLOWORLD_ANDROID_ROOT=$HELLOWORLD_ROOT/android
RESOURCE_ROOT=$HELLOWORLD_ROOT/Resource

# make sure assets is exist
if [ -d $HELLOWORLD_ANDROID_ROOT/assets ]; then
    rm -rf $HELLOWORLD_ANDROID_ROOT/assets
fi

mkdir $HELLOWORLD_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $HELLOWORLD_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $HELLOWORLD_ANDROID_ROOT/assets
    fi
done

# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $HELLOWORLD_ANDROID_ROOT $*
popd

