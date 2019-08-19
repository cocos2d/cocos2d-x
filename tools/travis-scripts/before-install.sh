#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
HOST_NAME=""
CURL="curl --retry 999 --retry-max-time 0"

function install_android_ndk()
{
    sudo python -m pip install retry
    if [ "$BUILD_TARGET" == "android_cmake" ]\
        || [ "$BUILD_TARGET" == "android_lua_cmake" ] ; then
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    else
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py --ndk_only
    fi
}

function install_linux_environment()
{
    echo "Installing linux dependence packages ..."
    echo -e "y" | bash $COCOS2DX_ROOT/install-deps-linux.sh
    echo "Installing linux dependence packages finished!"
}

function download_deps()
{
    # install dpes
    pushd $COCOS2DX_ROOT
    python download-deps.py -r=yes
    popd
    echo "Downloading cocos2d-x dependence finished!"
}

function install_python_module_for_osx()
{
    pip install PyYAML
    sudo pip install Cheetah
}

function install_latest_python()
{
    python -V
    eval "$(pyenv init -)"
    pyenv install 2.7.14
    pyenv global 2.7.14
    python -V
}

# update cmake version to 3.14
function update_cmake_to_314()
{

    # build with source code
    echo "downloading cmake 3.14.0"
    curl https://cmake.org/files/v3.14/cmake-3.14.0.tar.gz > ./cmake-3.14.0.tar.gz
    echo "extract cmake 3.14.0"
    tar -xzf cmake-3.14.0.tar.gz > /dev/null
    cd cmake-3.14.0
    echo "build and install cmake 3.14.0"
    cmake . > /dev/null
    make > /dev/null
    make install


    # if [ "$TRAVIS_OS_NAME" == "osx" ]; then
    #     curl https://cmake.org/files/v3.14/cmake-3.14.0-Darwin-x86_64.tar.gz -O
    #     tar -xzf cmake-3.14.0-Darwin-x86_64.tar.gz
    #     sudo mv cmake-3.14.0-Darwin-x86_64.tar.gz/CMake.app /Applications
    #     sudo /Applications/CMake.app/Contents/bin/cmake-gui --install
    # else
    #     # linux system
    #     sudo apt purge --auto-remove cmake
    #     mkdir ~/temp
    #     cd ~/temp
    #     wget https://cmake.org/files/v3.14/cmake-3.14.0-Linux-x86_64.sh 
    #     sudo mkdir /opt/cmake
    #     sudo sh cmake-3.14.0-Linux-x86_64.sh --prefix=/opt/cmake
    # fi
}

# set up environment according os and target
function install_environement_for_pull_request()
{
    echo "Building pull request ..."

    if [ "$TRAVIS_OS_NAME" == "linux" ]; then
        sudo apt-get update
        sudo apt-get install ninja-build
        ninja --version
        if [ "$BUILD_TARGET" == "linux" ]; then
            install_linux_environment
        fi
    fi

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        install_latest_python
        install_python_module_for_osx
    fi

    update_cmake_to_314

    # use NDK's clang to generate binding codes
    install_android_ndk
    download_deps
}

# should generate binding codes & cocos_files.json after merging
function install_environement_for_after_merge()
{
    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        install_latest_python
        install_python_module_for_osx
    fi

    echo "Building merge commit ..."
    install_android_ndk
    download_deps
}

if [ "$BUILD_TARGET" == "android_cocos_new_test" ]; then
    sudo apt-get update
    sudo apt-get install ninja-build
    ninja --version
    download_deps
    sudo python -m pip install retry
    python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    exit 0
fi

if [ "$BUILD_TARGET" == "linux_cocos_new_test" ]; then
    download_deps
    install_linux_environment
    # linux new lua project, so need to install
    sudo python -m pip install retry
    python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py --ndk_only
    exit 0
fi

# build pull request
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    install_environement_for_pull_request
fi

# run after merging
# - make cocos robot to send PR to cocos2d-x for new binding codes
# - generate cocos_files.json for template
if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    # only one job need to send PR, linux virtual machine has better performance
    if [ $TRAVIS_OS_NAME == "linux" ] && [ x$GEN_BINDING_AND_COCOSFILE == x"true" ]; then
        install_environement_for_after_merge
    fi 
fi

echo "before-install.sh execution finished!"
