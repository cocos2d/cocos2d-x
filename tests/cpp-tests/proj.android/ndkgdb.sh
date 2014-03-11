APPNAME="CppTests"
APP_ANDROID_NAME="org.cocos2dx.cpp_tests"

# read local.properties

_LOCALPROPERTIES_FILE=$(dirname "$0")"/local.properties"
if [ -f "$_LOCALPROPERTIES_FILE" ]
then
    [ -r "$_LOCALPROPERTIES_FILE" ] || die "Fatal Error: $_LOCALPROPERTIES_FILE exists but is unreadable"

    # strip out entries with a "." because Bash cannot process variables with a "."
    _PROPERTIES=$(sed '/\./d' "$_LOCALPROPERTIES_FILE")
    for line in $_PROPERTIES
    do
        declare "$line"
    done
fi

if [ -z "${SDK_ROOT+aaa}" ]; then
echo "SDK_ROOT not defined. Please define SDK_ROOT in your environment or in local.properties"
exit 1
fi

if [ -z "${NDK_ROOT+aaa}" ]; then
echo "NDK_ROOT not defined. Please define NDK_ROOT in your environment or in local.properties"
exit 1
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
    APP_ROOT="$COCOS2DX_ROOT/samples/$APPNAME"
    APP_ANDROID_ROOT="$COCOS2DX_ROOT/samples/$APPNAME/proj.android"
fi

echo "NDK_ROOT = $NDK_ROOT"
echo "SDK_ROOT = $SDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

set -x

"${SDK_ROOT}"/platform-tools/adb shell am force-stop "${APP_ANDROID_NAME}"

NDK_MODULE_PATH="${COCOS2DX_ROOT}":"${COCOS2DX_ROOT}"/cocos2dx/platform/third_party/android/prebuilt \
    "${NDK_ROOT}"/ndk-gdb-py \
    --adb="${SDK_ROOT}"/platform-tools/adb \
    --tui \
    --verbose \
    --launch=android.app.NativeActivity \
    --force \
    --nowait
