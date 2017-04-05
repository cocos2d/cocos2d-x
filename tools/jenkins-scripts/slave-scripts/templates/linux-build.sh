#!/bin/bash 
mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1

if [ $1 = "cpp" ]; then
    projectname="MyCppGame"
elif [ $1 = "lua" ]; then
    projectname="MyLuaGame"
elif [ $1 = "js" ]; then
    projectname="MyJSGame"
fi

$mycocos compile -p linux -s $projectname -m release -j4 --compile-script 0
