#!/bin/bash
# Build script to build all components for emscripten.
#
# By default this script will build the 'all' target in
# both debug and release configurations.  Pass "clean" to
# clean all configuration.
#
# This script expects llvm-3.2 to be installed in 
# $HOME/bin/clang+llvm-3.2.

SCRIPT_DIR=$(dirname ${BASH_SOURCE})

set -e
set -x

cd $SCRIPT_DIR

export PYTHON=/usr/bin/python
export LLVM=$HOME/bin/clang+llvm-3.2/bin
export LLVM_ROOT=$LLVM

make PLATFORM=emscripten DEBUG=1 -j10 $*
make PLATFORM=emscripten DEBUG=0 -j10 $*
