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
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh
    
    build_android Cpp HelloCpp
    build_android Cpp TestCpp
    build_android Cpp AssetsManagerTest
    build_android Javascript TestJavascript
    build_android Lua HelloLua
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

if [ "$PLATFORM"x = "ios"x ]; then
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh

    cd $COCOS2DX_ROOT
    xctool/xctool.sh -project samples/Cpp/HelloCpp/proj.ios/HelloCpp.xcodeproj -scheme HelloCpp test
    xctool/xctool.sh -project samples/Cpp/SimpleGame/proj.ios/SimpleGame.xcodeproj -scheme SimpleGame test
    xctool/xctool.sh -project samples/Cpp/TestCpp/proj.ios/TestCpp.xcodeproj -scheme TestCpp test
    #xctool/xctool.sh -project samples/Cpp/AssetsManagerTest/proj.ios/AssetsManagerTest.xcodeproj -scheme AssetsManagerTest test
    #xctool/xctool.sh -project samples/Javascript/CocosDragonJS/proj.ios/CocosDragonJS.xcodeproj -scheme CocosDragonJS test
    #xctool/xctool.sh -project samples/Javascript/CrystalCraze/proj.ios/CrystalCraze.xcodeproj -scheme CrystalCraze test
    xctool/xctool.sh -project samples/Javascript/MoonWarriors/proj.ios/MoonWarriors.xcodeproj -scheme MoonWarriors test
    xctool/xctool.sh -project samples/Javascript/TestJavascript/proj.ios/TestJavascript.xcodeproj -scheme TestJavascript test
    #xctool/xctool.sh -project samples/Javascript/WatermelonWithMe/proj.ios/WatermelonWithMe.xcodeproj -scheme WatermelonWithMe test
    xctool/xctool.sh -project samples/Lua/HelloLua/proj.ios/HelloLua.xcodeproj -scheme HelloLua test
    xctool/xctool.sh -project samples/Lua/TestLua/proj.ios/TestLua.xcodeproj -scheme TestLua test
fi
