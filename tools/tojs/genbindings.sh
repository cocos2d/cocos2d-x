# exit this script if any commmand fails
set -e

# read user.cfg if it exists and is readable

_CFG_FILE=$(dirname "$0")"/user.cfg"
if [ -e "$_CFG_FILE" ]
then
    [ -r "$_CFG_FILE" ] || die "Fatal Error: $_CFG_FILE exists but is unreadable"
    . "$_CFG_FILE"
fi

# paths

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
    CXX_GENERATOR_ROOT="$COCOS2DX_ROOT/tools/cxx-generator"
fi

if [ -z "${TOJS_ROOT+aaa}" ]; then
    TO_JS_ROOT="$COCOS2DX_ROOT/tools/tojs"
fi

echo "Paths"
echo "    CLANG_ROOT: $CLANG_ROOT"
echo "    PYTHON_BIN: $PYTHON_BIN"
echo "    COCOS2DX_ROOT: $COCOS2DX_ROOT"
echo "    CXX_GENERATOR_ROOT: $CXX_GENERATOR_ROOT"
echo "    TO_JS_ROOT: $TO_JS_ROOT"

# Generate bindings for cocos2dx
echo "Generating bindings for cocos2dx..."
set -x
LD_LIBRARY_PATH=${CLANG_ROOT}/lib $PYTHON_BIN ${CXX_GENERATOR_ROOT}/generator.py ${TO_JS_ROOT}/cocos2dx.ini -s cocos2d-x -o ${COCOS2DX_ROOT}/scripting/javascript/bindings/generated
