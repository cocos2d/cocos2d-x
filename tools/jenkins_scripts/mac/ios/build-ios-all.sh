# cpp
xcodebuild clean build -project ../../../../samples/HelloCpp/proj.ios/HelloCpp.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/HelloCpp/proj.ios/HelloCpp.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Release

xcodebuild clean build -project ../../../../samples/TestCpp/proj.ios/TestCpp.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/TestCpp/proj.ios/TestCpp.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Release

# lua
xcodebuild clean build -project ../../../../samples/HelloLua/proj.ios/HelloLua.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/HelloLua/proj.ios/HelloLua.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Release

xcodebuild clean build -project ../../../../samples/TestLua/proj.ios/TestLua.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/TestLua/proj.ios/TestLua.xcodeproj -alltargets -sdk iphonesimulator5.1-configuration Release

# javascript
xcodebuild clean build -project ../../../../samples/TestJavascript/proj.ios/TestJavascript.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/TestJavascript/proj.ios/TestJavascript.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Release

# other sample games
xcodebuild clean build -project ../../../../samples/SimpleGame/proj.ios/SimpleGame.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Debug
xcodebuild clean build -project ../../../../samples/SimpleGame/proj.ios/SimpleGame.xcodeproj -alltargets -sdk iphonesimulator5.1 -configuration Release
