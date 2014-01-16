#!/bin/bash

# exit this script if any commmand fails
set -e

# read user.cfg if it exists and is readable

_CFG_FILE=$(dirname "$0")"/user.cfg"
if [ -f "$_CFG_FILE" ]
then
    [ -r "$_CFG_FILE" ] || die "Fatal Error: $_CFG_FILE exists but is unreadable"
    . "$_CFG_FILE"
fi

# paths

if [ -z "${NDK_ROOT+aaa}" ]; then
# ... if NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    NDK_ROOT="$HOME/bin/android-ndk"
fi

if [ -z "${CLANG_ROOT+aaa}" ]; then
# ... if CLANG_ROOT is not set, use "$HOME/bin/clang+llvm-3.1"
    CLANG_ROOT="$HOME/bin/clang+llvm-3.1"
fi

if [ -z "${PYTHON_BIN+aaa}" ]; then
# ... if PYTHON_BIN is not set, use "/usr/bin/python2.7"
    PYTHON_BIN="/usr/bin/python2.7"
fi

# find current dir
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# paths with defaults hardcoded to relative paths

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
    COCOS2DX_ROOT="$DIR/../../"
fi

if [ -z "${CXX_GENERATOR_ROOT+aaa}" ]; then
    CXX_GENERATOR_ROOT="$COCOS2DX_ROOT/tools/bindings-generator"
fi

if [ -z "${TOJS_ROOT+aaa}" ]; then
    TO_JS_ROOT="$COCOS2DX_ROOT/tools/tojs"
fi

echo "Paths"
echo "    NDK_ROOT: $NDK_ROOT"
echo "    CLANG_ROOT: $CLANG_ROOT"
echo "    PYTHON_BIN: $PYTHON_BIN"
echo "    COCOS2DX_ROOT: $COCOS2DX_ROOT"
echo "    CXX_GENERATOR_ROOT: $CXX_GENERATOR_ROOT"
echo "    TO_JS_ROOT: $TO_JS_ROOT"

# write userconf.ini

_CONF_INI_FILE="$PWD/userconf.ini"
if [ -f "$_CONF_INI_FILE" ]
then
    rm "$_CONF_INI_FILE"
fi

_CONTENTS=""
_CONTENTS+="[DEFAULT]"'\n'
_CONTENTS+="androidndkdir=$NDK_ROOT"'\n'
_CONTENTS+="clangllvmdir=$CLANG_ROOT"'\n'
_CONTENTS+="cocosdir=$COCOS2DX_ROOT"'\n'
_CONTENTS+="cxxgeneratordir=$CXX_GENERATOR_ROOT"'\n'
_CONTENTS+="extra_flags="'\n'

echo 
echo "generating userconf.ini..."
echo ---
echo -e "$_CONTENTS"
echo -e "$_CONTENTS" > "$_CONF_INI_FILE"
echo ---

# Generate bindings for cocos2dx
echo "Generating bindings for cocos2dx..."
set -x
LD_LIBRARY_PATH=${CLANG_ROOT}/lib $PYTHON_BIN ${CXX_GENERATOR_ROOT}/generator.py ${TO_JS_ROOT}/cocos2dx.ini -s cocos2d-x -o ${COCOS2DX_ROOT}/scripting/javascript/bindings/generated -n jsb_cocos2dx_auto

echo "Generating bindings for cocos2dx_extension..."
LD_LIBRARY_PATH=${CLANG_ROOT}/lib $PYTHON_BIN ${CXX_GENERATOR_ROOT}/generator.py ${TO_JS_ROOT}/cocos2dx_extension.ini -s cocos2dx_extension -o ${COCOS2DX_ROOT}/scripting/javascript/bindings/generated -n jsb_cocos2dx_extension_auto

echo "Generating bindings for cocos2dx_studio..."
LD_LIBRARY_PATH=${CLANG_ROOT}/lib $PYTHON_BIN ${CXX_GENERATOR_ROOT}/generator.py ${TO_JS_ROOT}/cocos2dx_studio.ini -s cocos2dx_studio -o ${COCOS2DX_ROOT}/scripting/javascript/bindings/generated -n jsb_cocos2dx_studio_auto
