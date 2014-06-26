#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="`dirname $DIR`"
LUAJIT_SRC_DIR="$QUICK_V3_CORE_PATH/lib/cocos2dx/lua_extensions/LuaJIT-2.0.3"

cd $LUAJIT_SRC_DIR
make

echo ""
echo ""
echo Install LuaJIT, please enter your password.
echo ""
sudo make install
echo ""
echo "DONE."
echo ""
