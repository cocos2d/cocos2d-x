#put xctool.sh into your PATH

#######
# Cmake build
####### 
# DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# COCOS2DX_ROOT="$DIR"/../../..
# cd ${COCOS2DX_ROOT}
# mkdir mac-build
# cd mac-build
# cmake ..
# make -j4

#######
# xcode build
####### 
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../..
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_tests.xcodeproj -scheme "build all tests Mac" clean | xcpretty
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_tests.xcodeproj -scheme "build all tests Mac" build | xcpretty
#xcpretty has a bug, some xcodebuid fails return value would be treated as 0.
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_tests.xcodeproj -scheme "build all tests Mac" build
