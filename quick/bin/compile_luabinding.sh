#!/bin/bash
export LUA_PATH="$QUICK_V3_ROOT/quick/bin/mac/?.lua;;"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
php $DIR/lib/compile_luabinding.php $*
