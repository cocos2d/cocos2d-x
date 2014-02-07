#!/bin/bash
# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

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

    # Generate binding glue codes
    echo "Generating bindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh

    cd $COCOS2DX_ROOT

    # Create a directory for temporary objects
    mkdir android_build_objs

    PROJECTS=("test-cpp" "test-javascript" "test-lua")
    for i in ${PROJECTS[*]}; do
        ln -s $COCOS2DX_ROOT/android_build_objs $COCOS2DX_ROOT/tests/$i/proj.android/obj
    done

    # Build all samples
    echo "Building all samples ..."
    cd $COCOS2DX_ROOT/build
    ./android-build.py -n "NDK_BUG=0 -j10" all

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
    cd $COCOS2DX_ROOT/build
    make -j4
elif [ "$PLATFORM"x = "linux"x ]; then
    # Generate binding glue codes
    echo "Generating bindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh

    cd $COCOS2DX_ROOT/build
    mkdir -p linux-build
    cd linux-build
    cmake ../..
    make -j10
    # build template
    echo "Building template projects for linux ..."
    cd $COCOS2DX_ROOT/tools/project-creator
    ./create_project.py -n MyGameCpp -k com.MyCompany.AwesomeGameCpp -l cpp -p $HOME
    ./create_project.py -n MyGameLua -k com.MyCompany.AwesomeGameLua -l lua -p $HOME
    cd $HOME/MyGameCpp
    mkdir build
    cd build
    cmake ..
    make -j10

    cd $HOME/MyGameLua
    mkdir build
    cd build
    cmake ..
    make -j10

elif [ "$PLATFORM"x = "emscripten"x ]; then
    # Generate binding glue codes
    echo "Generating bindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-jsbindings.sh

    cd $COCOS2DX_ROOT/build
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
