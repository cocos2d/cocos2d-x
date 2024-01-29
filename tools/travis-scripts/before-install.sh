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
    if [ "$BUILD_TARGET" == "android_cpp_ndk-build" ]\
        || [ "$BUILD_TARGET" == "android_lua_ndk-build" ]\
        || [ "$BUILD_TARGET" == "android_cpp_cmake" ]\
        || [ "$BUILD_TARGET" == "android_js_cmake" ]\
        || [ "$BUILD_TARGET" == "android_lua_cmake" ] ; then
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    else
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py --ndk_only
    fi
}

function install_linux_environment()
{
    echo "Installing linux dependence packages ..."
    echo -e "y" | bash $COCOS2DX_ROOT/build/install-deps-linux.sh
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
        if [ "$BUILD_TARGET" == "linux_clang_tidy" ]; then
            install_linux_environment
        fi
    fi

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        install_latest_python
        install_python_module_for_osx
    fi

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

if [ "$BUILD_TARGET" == "android_cocos_new_cpp_test" ]; then
    sudo apt-get update
    sudo apt-get install ninja-build
    ninja --version
    download_deps
    sudo python -m pip install retry
    python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    exit 0
fi

if [ "$BUILD_TARGET" == "linux_cocos_new_lua_test" ]; then
    download_deps
    install_linux_environment
    sudo python -m pip install retry
    # set android ndk environment by setup_android.py
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
