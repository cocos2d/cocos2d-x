APPNAME="HelloAnalytics-JS"

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
PLUGIN_ROOT="$DIR/../../.."
COCOS2DX_ROOT="$DIR/../../../.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"
BINDINGS_JS_ROOT="$COCOS2DX_ROOT/scripting/javascript/bindings/js"

echo "PLUGIN_ROOT = $PLUGIN_ROOT"
echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "---------------------------------------------------------"

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

# copy bindings/*.js into assets' root
cp -f "$BINDINGS_JS_ROOT"/* "$APP_ANDROID_ROOT"/assets
# copy plugin js into assets' path
cp -f "$PLUGIN_ROOT/jsbindings/js"/* "$APP_ANDROID_ROOT"/assets

if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    set -x
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${PLUGIN_ROOT}/publish:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    set -x
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${PLUGIN_ROOT}/publish:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
