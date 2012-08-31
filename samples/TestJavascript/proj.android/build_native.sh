APPNAME="TestJavascript"

# options

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}

while getopts "sh" OPTION; do
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

echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

copy_resources_into_assets(){
for file in $1/*; do
if [ -d "$file" ]; then
copy_resources_into_assets "$file"
else
cp -f "$file" "$APP_ANDROID_ROOT"/assets
fi
done
}

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

for file in "$APP_ANDROID_ROOT"/assets/Images/*; do
if [ -d "$file" ];then
copy_resources_into_assets "$file"
else 
cp -f "$file" "$APP_ANDROID_ROOT"/assets
fi

done
rm -rf "$APP_ANDROID_ROOT"/assets/Images

for file in "$APP_ANDROID_ROOT"/assets/Fonts/*; do
if [ -d "$file" ];then
copy_resources_into_assets "$file"
else 
cp -f "$file" "$APP_ANDROID_ROOT"/assets
fi

done
rm -rf "$APP_ANDROID_ROOT"/assets/Fonts

rm -f "$APP_ANDROID_ROOT"/assets/landscape-1024x1024-rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_1021x1024_a8.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_1021x1024_rgb888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_1021x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_1021x1024_rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/texture1024x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/PlanetCute-1024x1024-rgba4444.pvr.gz


# copy js
if [ -d "$APP_ROOT/js" ]; then
    cp -rf "$APP_ROOT/js" "$APP_ANDROID_ROOT"/assets
fi

if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
