DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_samples.xcodeproj -scheme "build all samples Mac"  -destination "platform=OS X" clean
xcodebuild -project "$COCOS2DX_ROOT"/build/cocos2d_samples.xcodeproj -scheme "build all samples Mac"  -destination "platform=OS X" build
