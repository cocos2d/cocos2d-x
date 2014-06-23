#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

BIN="$DIR/proj.mac/bin/__PROJECT_PACKAGE_LAST_NAME_L__.app/Contents/MacOS/__PROJECT_PACKAGE_LAST_NAME_L__"
if [ ! -f $BIN ]; then
    echo "PLEASE BUILD proj.mac/__PROJECT_PACKAGE_LAST_NAME_L__.xcodeproj FIRST"
    exit
fi

echo $QUICK_COCOS2DX_ROOT

ARG="-relaunch-off -quick $QUICK_COCOS2DX_ROOT -workdir $DIR"
SIZE="-__SCREEN_ORIENTATION_L__"
CMD="$BIN $ARG $SIZE"

until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done
