#!/bin/bash
mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1 -t runtime
if [ $1 = "cpp" ];then
    projectname="MyCppGame"
elif [ $1 = "lua" ];then
    projectname="MyLuaGame"
elif [ $1 = "js" ];then
    projectname="MyJSGame"
fi

$mycocos compile -p android -s $projectname --android-studio -j4  --ndk-mode release --compile-script 0
