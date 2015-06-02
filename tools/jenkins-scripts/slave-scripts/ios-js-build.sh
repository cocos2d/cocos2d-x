#put xctool.sh into your PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../..
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_js_tests.xcodeproj -scheme "js-tests iOS"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" clean | xcpretty
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_js_tests.xcodeproj -scheme "js-tests iOS"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build | xcpretty
#the following commands must not be removed
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_js_tests.xcodeproj -scheme "js-tests iOS"  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
