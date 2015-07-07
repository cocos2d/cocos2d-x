mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1
if [ $1 = "cpp" ];then
    $mycocos compile -p linux -s MyCppGame -m release -j4 --compile-script 0
elif [ $1 = "lua" ];then
    $mycocos compile -p linux -s MyLuaGame -m release -j4 --compile-script 0
elif [ $1 = "js" ];then
    $mycocos compile -p linux -s MyJSGame -m release -j4 --compile-script 0
fi
