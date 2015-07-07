#put xctool.sh into your PATH
tools/cocos2d-console/bin/cocos new -l $1
# DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# COCOS2DX_ROOT="$DIR"/../../..
# cd ${COCOS2DX_ROOT}
# python build/android-build.py -p 10 cpp-tests lua-tests js-tests
if [ $1 == "cpp" ];then
    cocos compile -p android -s MyCppGame --android-studio -j4  --ndk-mode release --compile-script 0
elif [ $1 == "lua" ];then
    cocos compile -p android -s MyLuaGame --android-studio -j4 --ndk-mode release  --compile-script 0
elif [ $1 == "js" ];then
    cocos compile -p android -s MyJsGame --android-studio -j4 --ndk-mode release  --compile-script 0
fi
