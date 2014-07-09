#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

BIN="$DIR/proj.mac/bin/anysdk.app/Contents/MacOS/anysdk"
if [ ! -f $BIN ]; then
    echo "PLEASE BUILD proj.mac/anysdk.xcodeproj FIRST"
    exit
fi

echo $QUICK_V3_ROOT

ARG="-relaunch-off -quick $QUICK_V3_ROOT/quick -workdir $DIR"
SIZE="-portrait"
CMD="$BIN $ARG $SIZE"

until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done
