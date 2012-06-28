# set params
NDK_ROOT_LOCAL=/cygdrive/e/android/android-ndk-r8
COCOS2DX_ROOT_LOCAL=/cygdrive/f/Project/dumganhar/cocos2d-x

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}

while getopts "s" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
h)
usage
exit 0
;;
esac
done

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
echo "use global definition of NDK_ROOT: $NDK_ROOT"
NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $COCOS2DX_ROOT"aaa" != "aaa" ]; then
echo "use global definition of COCOS2DX_ROOT: $COCOS2DX_ROOT"
COCOS2DX_ROOT_LOCAL=$COCOS2DX_ROOT
fi

TEST_JS_ROOT=$COCOS2DX_ROOT_LOCAL/testjs/proj.android

# make sure assets is exist
if [ -d $TEST_JS_ROOT/assets ]; then
rm -rf $TEST_JS_ROOT/assets
fi

mkdir $TEST_JS_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT_LOCAL/testjs/Resources/*
do
if [ -d "$file" ]; then
cp -rf "$file" $TEST_JS_ROOT/assets
fi

if [ -f "$file" ]; then
cp "$file" $TEST_JS_ROOT/assets
fi
done


if [[ $buildexternalsfromsource ]]; then
echo "Building external dependencies from source"
$NDK_ROOT_LOCAL/ndk-build -C $TEST_JS_ROOT $* \
NDK_MODULE_PATH=${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/prebuilt:${COCOS2DX_ROOT_LOCAL}/js
else
echo "Using prebuilt externals"
$NDK_ROOT_LOCAL/ndk-build -C $TEST_JS_ROOT $* \
NDK_MODULE_PATH=${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/prebuilt:${COCOS2DX_ROOT_LOCAL}/js
fi
