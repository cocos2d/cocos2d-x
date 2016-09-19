#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../../..
cd ${COCOS2DX_ROOT}
mkdir linux-build
cd linux-build
cmake ..
if [ ! $? = 0 ]; then
    echo "cmake generate error"
    exit 1
fi
make -j4
