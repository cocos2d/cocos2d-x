#!/bin/bash
# This script will perform a clean linux build of all targets in both
# debug and release configurations.  It will also ensure that all the required
# packages are installed.  For day-to-day work on the linux port it is
# faster/better to simply use 'make' either at the top level or in the subpject
# you are working on.

# Exit of first error.
set -e

# Change directory to the location of this script
cd $(dirname ${BASH_SOURCE[0]})

[ -z "$COCOS2DX_USEAPT" ] && COCOS2DX_USEAPT=true

if $COCOS2DX_USEAPT; then
    ./install-deps-linux.sh
fi

export MAKEFLAGS=-j10

make PLATFORM=linux DEBUG=1 clean
make PLATFORM=linux DEBUG=0 clean

make PLATFORM=linux DEBUG=1 all
make PLATFORM=linux DEBUG=0 all
