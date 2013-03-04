#!/bin/bash
# Build script to build all components for Native Client.
#
# By default this script will only build debug versions.
# Pass "all" as an argument to build clean and also build
# release config.
#
# Before running this script you need to set NACL_SDK_ROOT
# and add the NaCl compiler bin folder to your path.
#
# There are several libraries from naclports that are
# prerequisite for building cocos2dx on NaCl.  The simplest
# way to build them is to checkout naclports and run:
# $ make png tiff freetype xml2 freealut jpeg vorbis ogg

if [ -z "$NACL_SDK_ROOT" ]; then
   echo "Please set \$NACL_SDK_ROOT"
   exit 1
fi

MAKEFLAGS=-j10
SCRIPT_DIR=$(dirname ${BASH_SOURCE})
OUTPUT_DEBUG=lib/nacl/Debug/
OUTPUT_RELEASE=lib/nacl/Release/

set -e
set -x

cd $SCRIPT_DIR

mkdir -p $OUTPUT_DEBUG
mkdir -p $OUTPUT_RELEASE


clean()
{
    make $MAKEFLAGS -C cocos2dx/proj.nacl $1 clean
    make $MAKEFLAGS -C CocosDenshion/proj.nacl $1 clean
    make $MAKEFLAGS -C external/chipmunk/proj.nacl $1 clean
    make $MAKEFLAGS -C external/Box2D/proj.nacl $1 clean
    make $MAKEFLAGS -C scripting/lua/proj.nacl $1 clean
    make $MAKEFLAGS -C samples/Cpp/HelloCpp/proj.nacl $1 clean
    make $MAKEFLAGS -C samples/Lua/HelloLua/proj.nacl $1 clean
    make $MAKEFLAGS -C samples/Cpp/TestCpp/proj.nacl $1 clean
    make $MAKEFLAGS -C samples/Lua/TestLua/proj.nacl $1 clean
    make $MAKEFLAGS -C samples/Cpp/SimpleGame/proj.nacl $1 clean
}

if [ "$1" = "clean" ]; then
    clean DEBUG=1
    clean DEBUG=0
    exit 0
fi

make $MAKEFLAGS -C cocos2dx/proj.nacl DEBUG=1
make $MAKEFLAGS -C CocosDenshion/proj.nacl DEBUG=1
make $MAKEFLAGS -C external/chipmunk/proj.nacl DEBUG=1
make $MAKEFLAGS -C external/Box2D/proj.nacl DEBUG=1
make $MAKEFLAGS -C scripting/lua/proj.nacl DEBUG=1
make $MAKEFLAGS -C samples/Cpp/HelloCpp/proj.nacl DEBUG=1
make $MAKEFLAGS -C samples/Lua/HelloLua/proj.nacl DEBUG=1
make $MAKEFLAGS -C samples/Cpp/TestCpp/proj.nacl DEBUG=1
make $MAKEFLAGS -C samples/Lua/TestLua/proj.nacl DEBUG=1
make $MAKEFLAGS -C samples/Cpp/SimpleGame/proj.nacl DEBUG=1

make $MAKEFLAGS -C cocos2dx/proj.nacl DEBUG=0
make $MAKEFLAGS -C CocosDenshion/proj.nacl DEBUG=0
make $MAKEFLAGS -C external/chipmunk/proj.nacl DEBUG=0
make $MAKEFLAGS -C external/Box2D/proj.nacl DEBUG=0
make $MAKEFLAGS -C scripting/lua/proj.nacl DEBUG=0
make $MAKEFLAGS -C samples/Cpp/HelloCpp/proj.nacl DEBUG=0
make $MAKEFLAGS -C samples/Lua/HelloLua/proj.nacl DEBUG=0
make $MAKEFLAGS -C samples/Cpp/TestCpp/proj.nacl DEBUG=0
make $MAKEFLAGS -C samples/Lua/TestLua/proj.nacl DEBUG=0
make $MAKEFLAGS -C samples/Cpp/SimpleGame/proj.nacl DEBUG=0
