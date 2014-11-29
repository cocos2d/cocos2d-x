DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir $DIR/test

$QUICK_V3_ROOT/quick/bin/create_project.sh -p com.quick-x.samples.luajavabridge -o $DIR/test/LuaJavaBridge -r landscape -lt
rm -fr $DIR/test/LuaJavaBridge/runtime
rm -fr $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.ios_mac
rm -fr $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.win32
rm -fr $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.wp8-xaml
rm -fr $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.android
mv $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.android_no_anysdk $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.android
cp $DIR/AppActivity.java $DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.android/src/org/cocos2dx/lua/
rm -fr $DIR/test/LuaJavaBridge/res/
rm -fr $DIR/test/LuaJavaBridge/src/app
rm $DIR/test/LuaJavaBridge/src/*.lua
cp -rf $DIR/src/ $DIR/test/LuaJavaBridge/src/