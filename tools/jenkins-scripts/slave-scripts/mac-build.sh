#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../..
cd ${COCOS2DX_ROOT}
mkdir mac-build
cd mac-build
cmake ..
make -j4
