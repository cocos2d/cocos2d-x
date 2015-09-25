#!/bin/bash
mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1 -t runtime

if [ $1 = "cpp" ];then
    schemename="MyCppGame-desktop"
    projectpath="MyCppGame/proj.ios_mac/MyCppGame.xcodeproj"
elif [ $1 = "lua" ];then
    schemename="MyLuaGame-desktop"
    projectpath="MyLuaGame/frameworks/runtime-src/proj.ios_mac/MyLuaGame.xcodeproj"
elif [ $1 = "js" ];then
    schemename="MyJSGame-desktop"
    projectpath="MyJSGame/frameworks/runtime-src/proj.ios_mac/MyJSGame.xcodeproj"
fi

xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" clean | xcpretty
xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build | xcpretty
#the following commands must not be removed
xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
