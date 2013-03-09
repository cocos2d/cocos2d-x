#!/bin/bash

# Exit of first error.
set -e

TXTCOLOR_DEFAULT="\033[0;m"
TXTCOLOR_GREEN="\033[0;32m"

COCOS2DX_ROOT=`pwd`

DEPENDS='libx11-dev'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libglfw-dev'
DEPENDS+=' g++'
DEPENDS+=' libzip-dev'
DEPENDS+=' libcurl4-gnutls-dev'
DEPENDS+=' libfontconfig1-dev'
DEPENDS+=' libsqlite3-dev'
DEPENDS+=' libglew*-dev'

for i in $DEPENDS; do
    PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $i | grep "install ok installed")
    echo Checking for $i: $PKG_OK
    if [ "" == "$PKG_OK" ]; then
        echo -e $TXTCOLOR_GREEN"No $i. Setting up $i, please enter your password:"$TXTCOLOR_DEFAULT
        sudo apt-get --force-yes --yes install $i
    fi
done

cd $COCOS2DX_ROOT

export MAKEFLAGS=-j10

make PROJECT=linux DEBUG=1 clean
make PROJECT=linux DEBUG=0 clean

make PROJECT=linux DEBUG=1 all
make PROJECT=linux DEBUG=0 all
