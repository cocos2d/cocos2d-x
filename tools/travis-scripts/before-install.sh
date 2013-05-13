#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

mkdir -p $HOME/bin
pushd $HOME/bin


install_android_ndk()
{
    # Download android ndk
    echo "Download android ndk ..."
    curl -O http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2
    echo "Decompress android-ndk-r8e-linux-x86_64.tar.bz2 ..."
    tar xjf android-ndk-r8e-linux-x86_64.tar.bz2
    # Rename ndk
    mv android-ndk-r8e android-ndk
}

if [ "$GEN_JSB"x = "YES"x ]; then
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
        exit 0
    fi
    install_android_ndk
    # Download llvm3.1
    echo "Download llvm3.1 ..."
    curl -O http://llvm.org/releases/3.1/clang+llvm-3.1-x86_64-linux-ubuntu_12.04.tar.gz
    echo "Decompress android-ndk-r8e-linux-x86_64.tar.bz2 ..."
    tar xzf clang+llvm-3.1-x86_64-linux-ubuntu_12.04.tar.gz
    # Rename llvm
    mv clang+llvm-3.1-x86_64-linux-ubuntu_12.04 clang+llvm-3.1
fi

if [ "$PLATFORM"x = "linux"x ]; then
    bash $COCOS2DX_ROOT/install-deps-linux.sh
fi

if [ "$PLATFORM"x = "nacl"x ]; then
    sudo apt-get update
    sudo apt-get install libc6:i386
    echo "Download nacl_sdk ..."
    wget http://storage.googleapis.com/nativeclient-mirror/nacl/nacl_sdk/nacl_sdk.zip
    echo "Decompress nacl_sdk.zip" 
    unzip nacl_sdk.zip
    nacl_sdk/naclsdk update --force pepper_canary
fi

if [ "$PLATFORM"x = "android"x ]; then 
    install_android_ndk
fi



popd
