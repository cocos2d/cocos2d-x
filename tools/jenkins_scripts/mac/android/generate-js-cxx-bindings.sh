#!/bin/bash

# Generate JS bindings for Cocos2D-X
# ... using Android NDK system headers

# Environment variables required
#  * $PYTHON_BIN
#  * $CLANG_ROOT
#  * $NDK_ROOT
#  * $COCOS2DX_ROOT

compileresult=0

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../../../ /bin/bash ../../../tojs/genbindings.sh

compileresult=$[$compileresult+$?]

# return the compileresult.
if [ $compileresult != 0 ]; then
    exit 1
else
    exit 0
fi
