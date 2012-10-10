APPNAME="MoonWarriors"

# options

buildexternalsfromsource=
PARALLEL_BUILD_FLAG=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-p  Run make with -j8 option to take advantage of multiple processors
-h	this help
EOF
}

while getopts "sph" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
p)
PARALLEL_BUILD_FLAG=\-j8
;;
h)
usage
exit 0
;;
esac
done

# exit this script if any commmand fails
set -e

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "please define NDK_ROOT"
exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
COCOS2DX_ROOT="$DIR/../../.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"

echo
echo "Paths"
echo "    NDK_ROOT = $NDK_ROOT"
echo "    COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "    APP_ROOT = $APP_ROOT"
echo "    APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets


# copy resources
for file in "$APP_ROOT"/Resources/*
do
if [ -d "$file" ]; then
	cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi


if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done


rm -f "$APP_ANDROID_ROOT"/assets/Images/landscape-1024x1024-rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_a8.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgb888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/texture1024x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/PlanetCute-1024x1024-rgba4444.pvr.gz


echo "Using prebuilt externals"
echo

set -x

"$NDK_ROOT"/ndk-build $PARALLEL_BUILD_FLAG -C "$APP_ANDROID_ROOT" $* \
    "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt" \
    NDK_LOG=1 V=1
