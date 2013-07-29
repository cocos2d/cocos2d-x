APPNAME="TestLua"

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

# read local.properties

_LOCALPROPERTIES_FILE=$(dirname "$0")"/local.properties"
if [ -f "$_LOCALPROPERTIES_FILE" ]
then
    [ -r "$_LOCALPROPERTIES_FILE" ] || die "Fatal Error: $_LOCALPROPERTIES_FILE exists but is unreadable"

    # strip out entries with a "." because Bash cannot process variables with a "."
    _PROPERTIES=`sed '/\./d' "$_LOCALPROPERTIES_FILE"`
    for line in "$_PROPERTIES"; do
        declare "$line";
    done
fi

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "NDK_ROOT not defined. Please define NDK_ROOT in your environment or in local.properties"
exit 1
fi

# For compatibility of android-ndk-r9, 4.7 was removed from r9
if [ -d "${NDK_ROOT}/toolchains/arm-linux-androideabi-4.7" ]; then
    export NDK_TOOLCHAIN_VERSION=4.7
    echo "The Selected NDK toolchain version was 4.7 !"
else
    if [ -d "${NDK_ROOT}/toolchains/arm-linux-androideabi-4.8" ]; then
        export NDK_TOOLCHAIN_VERSION=4.8
        echo "The Selected NDK toolchain version was 4.8 !"
    else
        echo "Couldn't find the gcc toolchain."
        exit 1
    fi
fi


if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
# ... if COCOS2DX_ROOT is not set
# ... find current working directory
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
    COCOS2DX_ROOT="$DIR/../../../.."
    APP_ROOT="$DIR/.."
    APP_ANDROID_ROOT="$DIR"
else
    APP_ROOT="$COCOS2DX_ROOT"/samples/Lua/"$APPNAME"
    APP_ANDROID_ROOT="$COCOS2DX_ROOT"/samples/Lua/"$APPNAME"/proj.android
fi

echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

# copy resources
for file in "$APP_ROOT"/../../Cpp/TestCpp/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

# copy luaScript
for file in "$APP_ROOT"/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

# copy common luaScript
for file in "$APP_ROOT"/../../../scripting/lua/script/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

# remove test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgb888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_a8.pvr.gz

if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
