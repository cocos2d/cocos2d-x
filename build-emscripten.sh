#!/bin/bash
# Build script to build all components for emscripten.
#
# By default this script will build the 'all' target in
# both debug and release configurations.  Pass "clean" to
# clean all configuration.

SCRIPT_DIR=$(dirname ${BASH_SOURCE})

set -e
set -x

cd $SCRIPT_DIR

if [ "$PYTHON" == "" ]; then
	command -v python >/dev/null 2>&1 || (echo "Please install python and set \$PYTHON" && exit 1)
	PYTHON=`which python`
fi

if [ "$LLVM" == "" ]; then
       	command -v clang >/dev/null 2>&1 || (echo "Please install LLVM and clang, and set \$LLVM" && exit 1)
        LLVM=$(dirname `which clang`)
fi

export LLVM_ROOT=$LLVM

make PLATFORM=emscripten DEBUG=1 -j10 $*
make PLATFORM=emscripten DEBUG=0 -j10 $*
