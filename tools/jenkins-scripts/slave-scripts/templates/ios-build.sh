#!/bin/bash
mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1

if [ $1 = "cpp" ];then
    schemename="MyCppGame-mobile"
    projectpath="MyCppGame/proj.ios_mac/MyCppGame.xcodeproj"
elif [ $1 = "lua" ];then
    schemename="MyLuaGame-mobile"
    projectpath="MyLuaGame/frameworks/runtime-src/proj.ios_mac/MyLuaGame.xcodeproj"
elif [ $1 = "js" ];then
    schemename="MyJSGame-mobile"
    projectpath="MyJSGame/frameworks/runtime-src/proj.ios_mac/MyJSGame.xcodeproj"
fi

echo "start building..."
xcodebuild -project $projectpath -scheme "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" clean | xcpretty
xcodebuild -project $projectpath -scheme "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build | xcpretty
#the following commands must not be removed
xcodebuild -project $projectpath -scheme "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
