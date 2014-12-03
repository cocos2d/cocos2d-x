#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR="`dirname $DIR`"
DIR="`dirname $DIR`"
DIR="`dirname $DIR`"

QUICK_V3_ROOT=$DIR
VERSION=`cat $QUICK_V3_ROOT/VERSION`
DIST_WORKDIR=~/temp/dist_workdir
WORKDIR=$DIST_WORKDIR/quick-$VERSION
CERT="CocoaChina (U7E7529TA5)"

echo ""
echo "QUICK_V3_ROOT = \"$QUICK_V3_ROOT\""
echo "VERSION = \"$VERSION\""
echo "WORKDIR = \"$WORKDIR\""
echo ""

echo "Clean old work dir"
if [ -d "$WORKDIR" ]; then
    rm -fr "$WORKDIR"
fi
if [ -d "$WORKDIR-win" ]; then
    rm -fr "$WORKDIR-win"
fi
mkdir -p "$WORKDIR"

echo "Get Quick-x Packages"
cd "$QUICK_V3_ROOT"
git archive v3 | tar -x -C "$WORKDIR"
rm -fr $WORKDIR/quick/bin/dist

echo "Copy runtime's files"
cp -rf $QUICK_V3_ROOT/quick/templates/lua-template-quick/runtime/ $WORKDIR/quick/templates/lua-template-quick/runtime/

echo "Copy bindings-generator"
GTOOLSPATH="bindings-generator"
cd "$QUICK_V3_ROOT/../$GTOOLSPATH"
git archive develop | tar -x -C "$WORKDIR/tools/$GTOOLSPATH"
rm $WORKDIR/tools/$GTOOLSPATH/libclang/libclang.so
rm -fr $WORKDIR/tools/$GTOOLSPATH/backup
rm -fr $WORKDIR/tools/$GTOOLSPATH/targets/spidermonkey
cd "$QUICK_V3_ROOT"

echo "Copy to windows work dir"
cp -rf $WORKDIR $WORKDIR-win
rm $WORKDIR-win/.g*
rm $WORKDIR-win/.t*

echo "Clean windows file in work dir"
rm $WORKDIR/tools/$GTOOLSPATH/libclang/libclang.dll
rm -fr $WORKDIR/tools/$GTOOLSPATH/tools
rm -fr $WORKDIR/quick/templates/lua-template-quick/runtime/win32
rm $WORKDIR/player3.bat

echo "Clean mac&ios file in windows work dir"
rm $WORKDIR-win/tools/$GTOOLSPATH/libclang/libclang.dylib
rm -fr $WORKDIR-win/quick/templates/lua-template-quick/runtime/ios
rm -fr $WORKDIR-win/quick/templates/lua-template-quick/runtime/mac

echo "Compile mac player"

cd quick/player/proj.mac

# cp -rf player3.xcodeproj/USER.xcuserdata/xcuserdatad/ player3.xcodeproj/xcuserdata/$USER.xcuserdatad/
xcodebuild -configuration Debug \
    CODE_SIGN_IDENTITY="Developer ID Application: $CERT" \
    QUICK_V3_ROOT="$QUICK_V3_ROOT" \
    -workspace player3.xcodeproj/project.xcworkspace \
    --timestamp=none \
    -scheme player3 \
    -archivePath ./build \
    archive

echo "Copy mac player"
mv ./build.xcarchive/Products/Applications/player3.app "$WORKDIR"
rm -fr ./build.xcarchive

echo "Copy win player"
cd "$QUICK_V3_ROOT"
cp -rf quick/player/win32 "$WORKDIR-win/quick/player/"

spctl -a -v "$WORKDIR/player3.app/"
echo ""
echo "player3.app accepted"
echo "source=Developer ID"
echo "override=security disabled"
echo ""

rm -fr $DIST_WORKDIR/build/
sed "s/__QUICK_VERSION__/$VERSION/" < $QUICK_V3_ROOT/quick/bin/dist/quickcocos2dx.pkgproj > $DIST_WORKDIR/quickcocos2dx.pkgproj
packagesbuild -v $DIST_WORKDIR/quickcocos2dx.pkgproj

du -h -d 1 $DIST_WORKDIR/build
echo ""
echo "--------------------------"
echo ""

SRC_PKG=$DIST_WORKDIR/build/quick-cocos2d-x-$VERSION.mpkg
DEST_PKG=$DIST_WORKDIR/build/Install.mpkg
if [ -d "$DEST_PKG" ]; then
	rm -fr "$DEST_PKG"
fi
if [ -f "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg" ]; then
	rm -f "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg"
fi

productsign --sign "Developer ID Installer: $CERT" "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg" "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg"
echo ""
rm "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
mv "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg" "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
spctl -a -v --type install "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
echo ""
echo "quickcocos2dx.pkg accepted"
echo "source=Developer ID"
echo "override=security disabled"
echo ""
echo "--------------------------"
echo ""

productsign --sign "Developer ID Application: $CERT" "$SRC_PKG" "$DEST_PKG"
spctl -a -v --type install "$DEST_PKG"
echo ""
echo "DONE: Install.mpkg on $DIST_WORKDIR/build/"
open "$DIST_WORKDIR/build/"
echo ""
