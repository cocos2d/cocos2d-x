# http://dualface.github.io/blog/2013/01/27/call-objectivec-from-lua/

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir $DIR/test

$QUICK_V3_ROOT/quick/bin/create_project.sh -p com.quick-x.samples.luaobjcbridge -o $DIR/test/LuaObjcBridge -r landscape -lt
rm -fr $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.win32
rm -fr $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.wp8-xaml
rm -fr $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.android
rm -fr $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.android_no_anysdk

cp -v $DIR/ios/AppController.h $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.ios_mac/ios/AppController.h
cp -v $DIR/ios/AppController.mm $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.ios_mac/ios/AppController.mm

cp -v $DIR/mac/SimulatorApp.h $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.ios_mac/mac/SimulatorApp.h
cp -v $DIR/mac/SimulatorApp.mm $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.ios_mac/mac/SimulatorApp.mm

rm -fr $DIR/test/LuaObjcBridge/src/app
rm $DIR/test/LuaObjcBridge/src/*.lua
cp -rfv $DIR/src/ $DIR/test/LuaObjcBridge/src/

open $DIR/test/LuaObjcBridge/frameworks/runtime-src/proj.ios_mac/luaobjcbridge.xcodeproj
