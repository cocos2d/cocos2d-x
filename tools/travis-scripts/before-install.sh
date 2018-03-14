#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
HOST_NAME=""

function install_android_ndk()
{
    if [ "$BUILD_TARGET" == "android" ] || [ "$BUILD_TARGET" == "android_lua" ] ; then
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    else
        python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py --ndk_only
    fi
}

function install_linux_environment()
{
    mkdir -p $HOME/bin
    pushd $HOME/bin

    echo "GCC version: `gcc --version`"
    # install new version cmake
    CMAKE_VERSION="3.7.2"
    CMAKE_DOWNLOAD_URL="https://cmake.org/files/v3.7/cmake-${CMAKE_VERSION}.tar.gz"
    echo "Download ${CMAKE_DOWNLOAD_URL}"
    curl -O ${CMAKE_DOWNLOAD_URL}
    tar -zxf "cmake-${CMAKE_VERSION}.tar.gz"
    cd "cmake-${CMAKE_VERSION}"
    ./configure > /dev/null
    make -j2 > /dev/null
    sudo make install > /dev/null
    echo "CMake Version: `cmake --version`"
    cd ..

    # install new version binutils
    BINUTILS_VERSION="2.27"
    BINUTILS_URL="http://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz"
    echo "Download ${BINUTILS_URL}"
    curl -O ${BINUTILS_URL}
    tar -zxf "binutils-${BINUTILS_VERSION}.tar.gz"
    cd "binutils-${BINUTILS_VERSION}"
    ./configure > /dev/null
    make -j2 > /dev/null
    sudo make install > /dev/null
    echo "ld Version: `ld --version`"
    echo "which ld: `which ld`"
    sudo rm /usr/bin/ld
    popd
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

function install_android_environment()
{
    # todo: cocos should add parameter to avoid promt
    sudo mkdir $HOME/.cocos
    sudo touch $HOME/.cocos/local_cfg.json
    echo '{"agreement_shown": true}' | sudo tee $HOME/.cocos/local_cfg.json
}

function install_python_module_for_osx()
{
    sudo easy_install pip
    sudo -H pip install PyYAML
    sudo -H pip install Cheetah
}

# fix error, URLError: <urlopen error [SSL: TLSV1_ALERT_PROTOCOL_VERSION]
function upgrade_openssl_for_osx()
{
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    brew update
    brew upgrade openssl
    ln -s /usr/local/opt/openssl/lib/libcrypto.1.0.0.dylib /usr/local/lib/
    ln -s /usr/local/opt/openssl/lib/libssl.1.0.0.dylib /usr/local/lib/
    ln -s /usr/local/opt/openssl/bin/openssl /usr/local/bin/openssl
    echo "macOS SSL: `openssl version`"

    brew unlink python
    brew install python2
    echo "python link: `ls -l /usr/local/bin/python`"
    echo "python SSL: `python -c "import ssl; print ssl.OPENSSL_VERSION"`"
}

# set up environment according os and target
function install_environement_for_pull_request()
{
    echo "Building pull request ..."

    if [ "$TRAVIS_OS_NAME" == "linux" ]; then
        if [ "$BUILD_TARGET" == "linux" ]; then
            install_linux_environment
        fi

        if [ "$BUILD_TARGET" == "android" ] || [ "$BUILD_TARGET" == "android_lua" ] ; then
            install_android_environment
        fi
    fi

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        upgrade_openssl_for_osx
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
        upgrade_openssl_for_osx
        install_python_module_for_osx
    fi

    echo "Building merge commit ..."
    install_android_ndk
    download_deps
}

if [ "$BUILD_TARGET" == "android_cocos_new_test" ]; then
    python $COCOS2DX_ROOT/tools/appveyor-scripts/setup_android.py
    exit 0
fi

if [ "$BUILD_TARGET" == "linux_cocos_new_test" ]; then
    download_deps
    install_linux_environment
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
