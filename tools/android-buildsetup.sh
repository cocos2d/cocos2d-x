#!/bin/bash

# Set up this cocos2d-x directory to build the Android port
#
# 1. Generate local.properties where necessary
# The END

# exit this script if any commmand fails
set -e

# read user.cfg if it exists and is readable

_CFG_FILE=$(dirname "$0")"/user.cfg"
if [ -f "$_CFG_FILE" ]
then
    [ -r "$_CFG_FILE" ] || die "Fatal Error: $_CFG_FILE exists but is unreadable"
    . "$_CFG_FILE"
fi

# paths

if [ -z "${ANDROID_SDK_ROOT+aaa}" ]; then
# ... if ANDROID_SDK_ROOT is not set, use "$HOME/bin/android-sdk"
    ANDROID_SDK_ROOT="$HOME/bin/android-sdk"
fi

if [ -z "${ANDROID_NDK_ROOT+aaa}" ]; then
# ... if ANDROID_NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    ANDROID_NDK_ROOT="$HOME/bin/android-ndk"
fi

# find current dir
SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# find working dir
WORKINGDIR="$(pwd)"

# paths with defaults hardcoded to relative paths

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
    COCOS2DX_ROOT="$WORKINGDIR"
fi

if [ ! -f "$COCOS2DX_ROOT/tools/android-buildsetup.sh" ]
then
    echo "Run..."
    echo "> ./tools/android-buildsetup.sh"
    echo "... from the top level of the cocos2d-x source tree"
    echo "OR"
    echo "Run..."
    echo "> COCOS2DX_ROOT=<path/to/cocos2d-x> <path/to/cocos2d-x>/build/setupandroid.sh"
    exit -1
fi

echo "Paths :"
echo "    ANDROID_SDK_ROOT: $ANDROID_SDK_ROOT"
echo "    ANDROID_NDK_ROOT: $ANDROID_NDK_ROOT"
echo "    COCOS2DX_ROOT   : $COCOS2DX_ROOT"
echo "    WORKINGDIR      : $WORKINGDIR"
echo "    SCRIPTDIR       : $SCRIPTDIR"

_CONTENTS=""
_CONTENTS+="sdk.dir=$ANDROID_SDK_ROOT"'\n'
_CONTENTS+="NDK_ROOT=$ANDROID_NDK_ROOT"'\n'
echo 
echo "--- local.properties"
echo "---"
echo -e "$_CONTENTS"
echo "---"

_ANDROIDMANIFESTS=(`find "$COCOS2DX_ROOT/cocos2dx" -type f -name "AndroidManifest.xml"`)
_ANDROIDMANIFESTS+=(`find "$COCOS2DX_ROOT/samples" -type f -name "AndroidManifest.xml"`)

for a in "${_ANDROIDMANIFESTS[@]}"; do
    _LOCAL_PROPERTIES_FILE=${a/AndroidManifest\.xml/local\.properties}

# write local.properties if it doesn't already exist
    if [ -f "$_LOCAL_PROPERTIES_FILE" ]
    then
        echo "$_LOCAL_PROPERTIES_FILE exists. skipping overwrite"
    else
        echo "writing $_LOCAL_PROPERTIES_FILE"
        echo -e "$_CONTENTS" > "$_LOCAL_PROPERTIES_FILE"
    fi
done
