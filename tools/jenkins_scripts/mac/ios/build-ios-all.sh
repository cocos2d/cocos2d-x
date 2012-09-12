# cpp
xcodebuild clean build -project ../../../../samples/HelloCpp/proj.ios/HelloCpp.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/HelloCpp/proj.ios/HelloCpp.xcodeproj -alltargets -configuration Release

xcodebuild clean build -project ../../../../samples/TestCpp/proj.ios/TestCpp.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/TestCpp/proj.ios/TestCpp.xcodeproj -alltargets -configuration Release

# lua
xcodebuild clean build -project ../../../../samples/HelloLua/proj.ios/HelloLua.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/HelloLua/proj.ios/HelloLua.xcodeproj -alltargets -configuration Release

xcodebuild clean build -project ../../../../samples/TestLua/proj.ios/TestLua.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/TestLua/proj.ios/TestLua.xcodeproj -alltargets -configuration Release

# javascript
xcodebuild clean build -project ../../../../samples/TestJavascript/proj.ios/TestJavascript.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/TestJavascript/proj.ios/TestJavascript.xcodeproj -alltargets -configuration Release

# other sample games
xcodebuild clean build -project ../../../../samples/SimpleGame/proj.ios/SimpleGame.xcodeproj -alltargets -configuration Debug
xcodebuild clean build -project ../../../../samples/SimpleGame/proj.ios/SimpleGame.xcodeproj -alltargets -configuration Release
