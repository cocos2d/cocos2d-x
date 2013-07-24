#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
HOST_NAME=""
LLVM_VERSION=""
LLVM_PACKAGE=""
LLVM_PACKAGE_SUFFIX=""

mkdir -p $HOME/bin
cd $HOME/bin

install_android_ndk()
{
    # Download android ndk
    if [ "$PLATFORM"x = "ios"x ]; then
        HOST_NAME="darwin"
    else
        HOST_NAME="linux"
    fi
    echo "Download android-ndk-r8e-${HOST_NAME}-x86_64.tar.bz2 ..."
    curl -O http://dl.google.com/android/ndk/android-ndk-r8e-${HOST_NAME}-x86_64.tar.bz2
    echo "Decompress android-ndk-r8e-${HOST_NAME}-x86_64.tar.bz2 ..."
    tar xjf android-ndk-r8e-${HOST_NAME}-x86_64.tar.bz2
    # Rename ndk
    mv android-ndk-r8e android-ndk
}

install_llvm()
{
    LLVM_VERSION="3.3"
    if [ "$PLATFORM"x = "ios"x ]; then
        LLVM_PACKAGE="clang+llvm-3.3-x86_64-apple-darwin12"
        LLVM_PACKAGE_SUFFIX=".tar.gz"
    else
        LLVM_PACKAGE="clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu"
        LLVM_PACKAGE_SUFFIX=".tar.bz2"
    fi

    # Download llvm
    echo "Download ${LLVM_PACKAGE} ..."
    curl -O http://llvm.org/releases/${LLVM_VERSION}/${LLVM_PACKAGE}${LLVM_PACKAGE_SUFFIX}
    echo "Decompress ${LLVM_PACKAGE} ..."
    if [ "$PLATFORM"x = "ios"x ]; then
        tar xzf ${LLVM_PACKAGE}${LLVM_PACKAGE_SUFFIX}
    else
        tar xjf ${LLVM_PACKAGE}${LLVM_PACKAGE_SUFFIX}
    fi

    # Rename llvm
    mv ${LLVM_PACKAGE} clang+llvm-${LLVM_VERSION}
}

install_llvm_3_2()
{
    if [ "$PLATFORM"x = "ios"x ]; then
        HOST_NAME="apple-darwin11"
    else
        HOST_NAME="linux-ubuntu-12.04"
    fi
    # Download llvm3.2
    echo "Download clang+llvm-3.2-x86_64-${HOST_NAME}.tar.gz"
    curl -O http://llvm.org/releases/3.2/clang+llvm-3.2-x86_64-${HOST_NAME}.tar.gz
    echo "Decompress clang+llvm-3.2-x86_64-${HOST_NAME}.tar.gz ..."
    tar xzf clang+llvm-3.2-x86_64-${HOST_NAME}.tar.gz
    # Rename llvm
    mv clang+llvm-3.2-x86_64-${HOST_NAME} clang+llvm-3.2
}

install_nacl_sdk()
{
    # NaCl compilers are built for 32-bit linux so we need to install
    # the runtime support for this.
    if [ ! -e "/lib/ld-linux.so.2" ]; then
        sudo apt-get update
        sudo apt-get install libc6:i386 libstdc++6:i386
    fi
    if [ ! -d nacl_sdl ]; then
        echo "Download nacl_sdk ..."
        wget http://storage.googleapis.com/nativeclient-mirror/nacl/nacl_sdk/nacl_sdk.zip
        echo "Decompress nacl_sdk.zip"
        unzip nacl_sdk.zip
    fi
    nacl_sdk/naclsdk update --force pepper_canary
}

if [ "$GEN_JSB"x = "YES"x ]; then
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
        exit 0
    fi
    install_android_ndk
    install_llvm
elif [ "$PLATFORM"x = "linux"x ]; then
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-4.7 g++-4.7
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.6
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 90 --slave /usr/bin/g++ g++ /usr/bin/g++-4.7
    g++ --version
    bash $COCOS2DX_ROOT/install-deps-linux.sh
elif [ "$PLATFORM"x = "nacl"x ]; then
    install_nacl_sdk
elif [ "$PLATFORM"x = "android"x ]; then
    install_android_ndk
    install_llvm
elif [ "$PLATFORM"x = "emscripten"x ]; then
    sudo rm -rf /dev/shm && sudo ln -s /run/shm /dev/shm
    install_llvm_3_2
elif [ "$PLATFORM"x = "ios"x ]; then
    install_android_ndk
    install_llvm

    pushd $COCOS2DX_ROOT
    git submodule add https://github.com/facebook/xctool.git ./xctool
    git submodule init
    git submodule update
    popd
else
    echo "Unknown \$PLATFORM: '$PLATFORM'"
    exit 1
fi
