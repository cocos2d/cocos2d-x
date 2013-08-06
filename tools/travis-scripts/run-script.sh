#!/bin/bash
# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

build_android()
{
    echo "Current dir: `pwd`"
    pushd $1/proj.android
    ln -s $COCOS2DX_ROOT/android_build_objs obj
    ./build_native.sh
    popd
}

if [ "$GEN_JSB"x = "YES"x ]; then
    # Re-generation of the javascript bindings can perform push of the new
    # version back to github.  We don't do this for pull requests, or if
    # GH_USER/GH_EMAIL/GH_PASSWORD environment variables are not set correctly
    # by the encoded variables in the .travis.yml file.  (e.g. if cloned repo's
    # want to use travis).
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
        exit 0
    fi
    if [ -z "${GH_EMAIL}" ]; then
        echo "GH_EMAIL not set"
        exit 0
    fi
    if [ -z "${GH_USER}" ]; then
        echo "GH_USER not set"
        exit 0
    fi
    if [ -z "${GH_PASSWORD}" ]; then
        echo "GH_USER not set"
        exit 0
    fi
    export NDK_ROOT=$HOME/bin/android-ndk
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh
elif [ "$PLATFORM"x = "android"x ]; then
    export NDK_ROOT=$HOME/bin/android-ndk

    # Generate jsbinding glue codes
    echo "Generating jsbindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh

    cd $COCOS2DX_ROOT

    # Create a directory for temporary objects
    mkdir android_build_objs

    # Build samples
    echo "Building samples ..."
    cd $COCOS2DX_ROOT/samples/Cpp
    build_android HelloCpp
    build_android TestCpp
    build_android AssetsManagerTest

    cd $COCOS2DX_ROOT/samples/Javascript
    build_android TestJavascript
    build_android CocosDragonJS
    build_android CrystalCraze
    build_android MoonWarriors
    build_android WatermelonWithMe

    cd $COCOS2DX_ROOT/samples/Lua
    build_android HelloLua
    build_android TestLua

    # Build template
    # echo "Building template ..."
    # cd $COCOS2DX_ROOT/template
    # build_android multi-platform-cpp
    # build_android multi-platform-js
    # build_android multi-platform-lua

elif [ "$PLATFORM"x = "nacl"x ]; then
    export NACL_SDK_ROOT=$HOME/bin/nacl_sdk/pepper_canary
    export PATH=$PATH:$NACL_SDK_ROOT/toolchain/linux_x86_newlib/bin
    export PATH=$PATH:$NACL_SDK_ROOT/toolchain/linux_arm_newlib/bin
    cd $COCOS2DX_ROOT
    make -j4
elif [ "$PLATFORM"x = "linux"x ]; then
    cd $COCOS2DX_ROOT
    make -j4
elif [ "$PLATFORM"x = "emscripten"x ]; then
    cd $COCOS2DX_ROOT
    export PYTHON=/usr/bin/python
    export LLVM=$HOME/bin/clang+llvm-3.2/bin
    export LLVM_ROOT=$LLVM
    EMCC_DEBUG=1 make PLATFORM=emscripten -j 8
elif [ "$PLATFORM"x = "ios"x ]; then
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
else
    echo "Unknown \$PLATFORM: '$PLATFORM'"
    exit 1
fi
