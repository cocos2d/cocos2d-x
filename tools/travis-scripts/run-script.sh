#!/bin/bash
# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

if [ "$GEN_JSB"x = "YES"x ]; then
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
        exit 0
    fi
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh
fi

if [ "$PLATFORM"x = "android"x ]; then 
    cd $COCOS2DX_ROOT/samples/$SAMPLE_LANG/$APPNAME/proj.android
    ./build_native.sh
fi

if [ "$PLATFORM"x = "nacl"x ]; then
    cd $COCOS2DX_ROOT
    make -j4
fi

if [ "$PLATFORM"x = "linux"x ]; then
    cd $COCOS2DX_ROOT
    make -j4
fi

