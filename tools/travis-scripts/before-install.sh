#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
HOST_NAME=""



function install_android_ndk()
{
    mkdir -p $HOME/bin
    cd $HOME/bin

    # Download android ndk
    if [ "$TRAVIS_OS_NAME" = "osx" ]; then
        HOST_NAME="darwin"
    else
        HOST_NAME="linux"
    fi

    FILE_NAME=android-ndk-r10d-${HOST_NAME}-x86_64.bin

    echo "Download ${FILE_NAME} ..."
    curl -O http://dl.google.com/android/ndk/${FILE_NAME}
    sudo chmod +x ./$FILE_NAME
    echo "Decompress ${FILE_NAME} ..."
    ./$FILE_NAME > /dev/null
    # Rename ndk
    mv android-ndk-r10d android-ndk
}

function install_linux_environment()
{
    bash $COCOS2DX_ROOT/build/install-deps-linux.sh
}

function download_deps()
{
    # install dpes
    pushd $COCOS2DX_ROOT
    python download-deps.py -r=yes
    popd
}

function install_android_environment()
{
    sudo apt-get install ant -y
    
    # todo: cocos should add parameter to avoid promt
    sudo mkdir $HOME/.cocos
    sudo touch $HOME/.cocos/local_cfg.json
    echo '{"agreement_shown": true}' | sudo tee $HOME/.cocos/local_cfg.json
}

function install_python_module_for_osx()
{
    sudo easy_install pip
    sudo pip install PyYAML
    sudo pip install Cheetah
}

# set up environment according os and target
function install_environement_for_pull_request()
{
    # use NDK's clang to generate binding codes
    install_android_ndk
    download_deps

    if [ "$TRAVIS_OS_NAME" == "linux" ]; then
        if [ "$BUILD_TARGET" == "linux" ]; then
            install_linux_environment
        fi

        if [ "$BUILD_TARGET" == "android" ]; then
            install_android_environment
        fi
    fi

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        install_python_module_for_osx
    fi
}

# should generate binding codes & cocos_files.json after merging
function install_environement_for_after_merge()
{
    install_android_ndk
    download_deps

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        install_python_module_for_osx
    fi
}

# build pull request
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    install_environement_for_pull_request
fi

# run after merging
# - make cocos robot to send PR to cocos2d-x for new binding codes
# - generate cocos_files.json for template
if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    # only one job need to send PR, linux virtual machine has better performance
    if [ $TRAVIS_OS_NAME == "linux" ] && [ $GEN_BINDING_AND_COCOSFILE == "true" ]; then
        install_environement_for_after_merge
    fi 
fi
