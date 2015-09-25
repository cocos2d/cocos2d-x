#!/bin/bash
mycocos=tools/cocos2d-console/bin/cocos
$mycocos new -l $1

if [ $1 = "cpp" ];then
    schemename="MyCppGame-mobile"
    projectpath="MyCppGame/proj.ios_mac/MyCppGame.xcodeproj"
    cocos_project_path="MyCppGame"
elif [ $1 = "lua" ];then
    schemename="MyLuaGame-mobile"
    projectpath="MyLuaGame/frameworks/runtime-src/proj.ios_mac/MyLuaGame.xcodeproj"
    cocos_project_path="MyLuaGame"
elif [ $1 = "js" ];then
    schemename="MyJSGame-mobile"
    projectpath="MyJSGame/frameworks/runtime-src/proj.ios_mac/MyJSGame.xcodeproj"
    cocos_project_path="MyJSGame"
fi

echo "start building..."
cocos compile -p ios -s $cocos_project_path | xcpretty
cocos compile -p ios -s $cocos_project_path
# xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" clean | xcpretty
# xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build | xcpretty
# #the following commands must not be removed
# xcodebuild -project $projectpath -target "${schemename}"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
