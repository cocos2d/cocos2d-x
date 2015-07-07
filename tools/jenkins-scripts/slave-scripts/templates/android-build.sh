mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1
if [ $1 = "cpp" ];then
    $mycocos compile -p android -s MyCppGame --android-studio -j4  --ndk-mode release --compile-script 0
elif [ $1 = "lua" ];then
    $mycocos compile -p android -s MyLuaGame --android-studio -j4 --ndk-mode release  --compile-script 0
elif [ $1 = "js" ];then
    $mycocos compile -p android -s MyJSGame --android-studio -j4 --ndk-mode release  --compile-script 0
fi
