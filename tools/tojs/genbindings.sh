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

# paths with defaults hardcoded to relative paths

if [ -z "${CXX_GENERATOR_ROOT+aaa}" ]; then
    CXX_GENERATOR_ROOT="$PWD/submodules/cxx-generator"
fi

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
    COCOS2DX_ROOT="$PWD/submodules/cocos2d-x"
fi

echo "CLANG_ROOT: $CLANG_ROOT"
echo "CXX_GENERATOR_ROOT: $CXX_GENERATOR_ROOT"
echo "COCOS2DX_ROOT: $COCOS2DX_ROOT"
echo "PYTHON_BIN: $PYTHON_BIN"

# Generate bindings for cocos2dx again
echo "Generating bindings for cocos2dx again..."
set -x
LD_LIBRARY_PATH=${CLANG_ROOT}/lib $PYTHON_BIN ${CXX_GENERATOR_ROOT}/generator.py ${APP_ANDROID_ROOT}/cocos2dx.ini -s cocos2d-x -o ${COCOS2DX_ROOT}/scripting/javascript/bindings/generated
