DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir $DIR/test

$QUICK_V3_ROOT/quick/bin/create_project.sh -p com.quick-x.samples.towerdefense -o $DIR/test/towerdefense -r landscape -lt
rm -fr $DIR/test/towerdefense/runtime
rm -fr $DIR/test/towerdefense/frameworks/runtime-src/proj.win32
rm -fr $DIR/test/towerdefense/frameworks/runtime-src/proj.wp8-xaml
rm -fr $DIR/test/towerdefense/frameworks/runtime-src/proj.android
mv $DIR/test/towerdefense/frameworks/runtime-src/proj.android_no_anysdk $DIR/test/towerdefense/frameworks/runtime-src/proj.android
rm -fr $DIR/test/towerdefense/res/
rm -fr $DIR/test/towerdefense/src/app
rm $DIR/test/towerdefense/src/*.lua
cp -rf $DIR/src/ $DIR/test/towerdefense/src/
cp -rf $DIR/res/ $DIR/test/towerdefense/res/
