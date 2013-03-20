#!/bin/bash
# This script will perform a clean linux build of all targets in both
# debug and release configurations.  It will also ensure that all the required
# packages are installed.  For day-to-day work on the linux port it is
# faster/better to simply use 'make' either at the top level or in the subpject
# you are working on.

# Exit of first error.
set -e

[ -z "$COCOS2DX_USEAPT" ] && COCOS2DX_USEAPT=true

if $COCOS2DX_USEAPT; then
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

    MISSING=
    echo "Checking for missing packages ..."
    for i in $DEPENDS; do
        if ! dpkg-query -W --showformat='${Status}\n' $i | grep "install ok installed" > /dev/null; then
            MISSING+="$i "
        fi
    done

    if [ -n "$MISSING" ]; then
        TXTCOLOR_DEFAULT="\033[0;m"
        TXTCOLOR_GREEN="\033[0;32m"
        echo -e $TXTCOLOR_GREEN"Missing packages: $MISSING.\nYou may be asked for your password for package installation."$TXTCOLOR_DEFAULT
        sudo apt-get --force-yes --yes install $MISSING
    fi
fi

# Change directory to the location of this script
cd $(dirname ${BASH_SOURCE[0]})

export MAKEFLAGS=-j10

make PROJECT=linux DEBUG=1 clean
make PROJECT=linux DEBUG=0 clean

make PROJECT=linux DEBUG=1 all
make PROJECT=linux DEBUG=0 all
