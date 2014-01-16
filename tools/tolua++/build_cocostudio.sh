#!/bin/bash
#
# Invoked build.xml, overriding the lolua++ property

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TOLUA=`which tolua++`
if [ -z "${TOLUA}" ]; then
    TOLUA=`which tolua++5.1`
fi

if [ -z "${TOLUA}" ]; then
    echo "Unable to find tolua++ (or tolua++5.1) in your PATH."
    exit 1
fi

cd ${SCRIPT_DIR}
${TOLUA} -L basic_cocostudio.lua -o ../../scripting/lua/cocos2dx_support/LuaCocoStudio.cpp CocoStudio.pkg
