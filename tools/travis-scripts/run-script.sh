#!/bin/bash
# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

if [ -z "$NDK_ROOT" ]; then
    export NDK_ROOT=$HOME/bin/android-ndk
fi

if [ -z "$PYTHON_BIN" ]; then
    export PYTHON_BIN=/usr/bin/python
fi

if [ "$GEN_BINDING"x = "YES"x ]; then
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
        exit 1
    fi
    if [ -z "${GH_USER}" ]; then
        echo "GH_USER not set"
        exit 1
    fi
    if [ -z "${GH_PASSWORD}" ]; then
        echo "GH_USER not set"
        exit 1
    fi

    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-bindings.sh
elif [ "$GEN_COCOS_FILES"x = "YES"x ]; then
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
        exit 0
    fi
    if [ -z "${GH_EMAIL}" ]; then
        echo "GH_EMAIL not set"
        exit 1
    fi
    if [ -z "${GH_USER}" ]; then
        echo "GH_USER not set"
        exit 1
    fi
    if [ -z "${GH_PASSWORD}" ]; then
        echo "GH_USER not set"
        exit 1
    fi

    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-cocosfiles.sh
elif [ "$PLATFORM"x = "android"x ]; then
    export NDK_ROOT=$HOME/bin/android-ndk

    # Generate binding glue codes
    echo "Generating bindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-bindings.sh
    ./generate-cocosfiles.sh

    cd $COCOS2DX_ROOT

    # Create a directory for temporary objects
    mkdir android_build_objs

    PROJECTS=("cpp-empty-test" "cpp-tests" "lua-empty-test/project" "lua-tests/project")
    for i in ${PROJECTS[*]}; do
        ln -s $COCOS2DX_ROOT/android_build_objs $COCOS2DX_ROOT/tests/$i/proj.android/obj
    done

    # Build all samples
    echo "Building all samples ..."
    cd $COCOS2DX_ROOT/build
    ./android-build.py -n "NDK_BUG=0 -j10" all

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
    ./generate-bindings.sh
    ./generate-cocosfiles.sh

    echo "Building cocos2d-x"
    cd $COCOS2DX_ROOT/build
    mkdir -p linux-build
    cd linux-build
    cmake ../..
    make -j10

elif [ "$PLATFORM"x = "emscripten"x ]; then
    # Generate binding glue codes
    echo "Generating bindings glue codes ..."
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-bindings.sh
    ./generate-cocosfiles.sh

    cd $COCOS2DX_ROOT/build
    export PYTHON=/usr/bin/python
    export LLVM=$HOME/bin/clang+llvm-3.2/bin
    export LLVM_ROOT=$LLVM
    EMCC_DEBUG=1 make PLATFORM=emscripten -j 8
elif [ "$PLATFORM"x = "ios"x ]; then
    cd $COCOS2DX_ROOT/tools/travis-scripts
    ./generate-bindings.sh
    ./generate-cocosfiles.sh

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
