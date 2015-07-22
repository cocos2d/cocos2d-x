#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../../..
cd ${COCOS2DX_ROOT}
python tools/framework-compile/bin/gen_cocos_libs.py -c --mac | xcpretty
