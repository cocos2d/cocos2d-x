#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../../..
cd ${COCOS2DX_ROOT}
python build/android-build.py -p 10 cpp-tests lua-tests js-tests
