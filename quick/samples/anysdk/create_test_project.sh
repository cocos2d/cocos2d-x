DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir $DIR/test

$QUICK_V3_ROOT/quick/bin/create_project.sh -p com.quick-x.samples.anysdk -o $DIR/test/anysdk -r landscape -lt
rm -fr $DIR/test/anysdk/runtime
rm -fr $DIR/test/anysdk/frameworks/runtime-src/proj.ios_mac
rm -fr $DIR/test/anysdk/frameworks/runtime-src/proj.win32
rm -fr $DIR/test/anysdk/frameworks/runtime-src/proj.wp8-xaml
rm -fr $DIR/test/anysdk/frameworks/runtime-src/proj.android_no_anysdk
rm -fr $DIR/test/anysdk/res/
rm -fr $DIR/test/anysdk/src/app
rm $DIR/test/anysdk/src/*.lua
cp -rf $DIR/res/ $DIR/test/anysdk/res/
cp -rf $DIR/src/ $DIR/test/anysdk/src/
