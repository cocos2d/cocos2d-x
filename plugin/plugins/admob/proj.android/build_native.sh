# set params
PLUGIN_ANDROID_ROOT=$(cd "$(dirname "$0")"; pwd)

if [ ! "${PLUGIN_ROOT}" ]; then
    PLUGIN_ROOT="$PLUGIN_ANDROID_ROOT"/../..
fi

# build
"$ANDROID_NDK_ROOT"/ndk-build -C "$PLUGIN_ANDROID_ROOT" \
NDK_MODULE_PATH="$PLUGIN_ROOT"

echo
if [ "0" != "$?" ]; then
    echo "Build error occoured!!!"
    exit 1
fi

echo
echo "Native build action success."
exit 0