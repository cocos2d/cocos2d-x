DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir $DIR/test

$QUICK_V3_ROOT/quick/bin/create_project.sh -p com.quick-x.samples.Homeland2_Map_Editor -o $DIR/test/Homeland2_Map_Editor -r landscape -lt
rm -fr $DIR/test/Homeland2_Map_Editor/runtime
rm -fr $DIR/test/Homeland2_Map_Editor/frameworks/runtime-src/proj.win32
rm -fr $DIR/test/Homeland2_Map_Editor/frameworks/runtime-src/proj.wp8-xaml
rm -fr $DIR/test/Homeland2_Map_Editor/frameworks/runtime-src/proj.android
mv $DIR/test/Homeland2_Map_Editor/frameworks/runtime-src/proj.android_no_anysdk $DIR/test/Homeland2_Map_Editor/frameworks/runtime-src/proj.android
rm -fr $DIR/test/Homeland2_Map_Editor/res/
rm -fr $DIR/test/Homeland2_Map_Editor/src/app
rm $DIR/test/Homeland2_Map_Editor/src/*.lua
cp -rf $DIR/src/ $DIR/test/Homeland2_Map_Editor/src/
cp -rf $DIR/res/ $DIR/test/Homeland2_Map_Editor/res/
