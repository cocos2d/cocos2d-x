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

build_android()
{
    cd $COCOS2DX_ROOT/samples/$1/$2/proj.android
    ./build_native.sh
}

if [ "$PLATFORM"x = "android"x ]; then 
    build_android Cpp HelloCpp
    build_android Javascript TestJavascript
    build_android Lua TestLua
fi

if [ "$PLATFORM"x = "nacl"x ]; then
    cd $COCOS2DX_ROOT
    make -j4
fi

if [ "$PLATFORM"x = "linux"x ]; then
    cd $COCOS2DX_ROOT
    make -j4
fi

