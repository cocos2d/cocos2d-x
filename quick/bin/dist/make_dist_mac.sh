#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR="`dirname $DIR`"
DIR="`dirname $DIR`"
DIR="`dirname $DIR`"

QUICK_V3_ROOT=$DIR
VERSION=`cat $QUICK_V3_ROOT/VERSION`
DIST_WORKDIR=$QUICK_V3_ROOT/dist_workdir
WORKDIR=$DIST_WORKDIR/quick-$VERSION
CERT="CocoaChina (U7E7529TA5)"

echo ""
echo "QUICK_V3_ROOT = \"$QUICK_V3_ROOT\""
echo "VERSION = \"$VERSION\""
echo "WORKDIR = \"$WORKDIR\""
echo ""

if [ -d "$WORKDIR" ]; then
    rm -fr "$WORKDIR"
fi
mkdir -p "$WORKDIR"

cd "$QUICK_V3_ROOT"
git archive v3 | tar -x -C "$WORKDIR"

# cd quick/player/proj.mac

# cp -rf player3.xcodeproj/xcuserdata/USER.xcuserdatad/ player3.xcodeproj/xcuserdata/$USER.xcuserdatad/
# xcodebuild -configuration Debug \
#     CODE_SIGN_IDENTITY="Developer ID Application: $CERT" \
#     QUICK_V3_ROOT="$QUICK_V3_ROOT" \
#     -workspace player3.xcworkspace \
#     -scheme player3 \
#     -archivePath ./build \
#     archive

# mv ./build.xcarchive/Products/Applications/player3.app "$WORKDIR"
# rm -fr ./build.xcarchive
cp -rf player3.app "$WORKDIR"

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

# SRC_PKG=$DIST_WORKDIR/build/quick-cocos2d-x-$VERSION.mpkg
# DEST_PKG=$DIST_WORKDIR/build/Install.mpkg
# if [ -d "$DEST_PKG" ]; then
# 	rm -fr "$DEST_PKG"
# fi
# if [ -f "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg" ]; then
# 	rm -f "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg"
# fi

# productsign --sign "Developer ID Installer: $CERT" "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg" "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg"
# echo ""
# rm "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
# mv "$SRC_PKG/Contents/Packages/quickcocos2dx_signed.pkg" "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
# spctl -a -v --type install "$SRC_PKG/Contents/Packages/quickcocos2dx.pkg"
# echo ""
# echo "quickcocos2dx.pkg accepted"
# echo "source=Developer ID"
# echo "override=security disabled"
# echo ""
# echo "--------------------------"
# echo ""

# productsign --sign "Developer ID Application: $CERT" "$SRC_PKG" "$DEST_PKG"
# spctl -a -v --type install "$DEST_PKG"
# echo ""
# echo "DONE: Install.mpkg on $DIST_WORKDIR/build/"
# open "$DIST_WORKDIR/build/"
# echo ""
