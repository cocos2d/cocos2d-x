#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../..
cd ${COCOS2DX_ROOT}
mkdir linux-build
cd linux-build
cmake ..
make -j4
