#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.1
DESTDIR=$DIR/proj.ios
IXCODE=`xcode-select -print-path`
ISDK=$IXCODE/Platforms/iPhoneOS.platform/Developer
ISDKVER=iPhoneOS6.1.sdk
ISDKP=$ISDK/usr/bin/

rm "$DESTDIR"/*.a
cd $SRCDIR

make clean
ISDKF="-arch armv7 -isysroot $ISDK/SDKs/$ISDKVER"
make HOST_CC="gcc -m32 -arch i386" CROSS=$ISDKP TARGET_FLAGS="$ISDKF" TARGET_SYS=iOS
mv "$SRCDIR"/src/libluajit.a "$DESTDIR"/libluajit2-armv7.a

# make clean
# ISDKF="-arch armv7s -isysroot $ISDK/SDKs/$ISDKVER"
# make HOST_CC="gcc -m32 -arch i386" CROSS=$ISDKP TARGET_FLAGS="$ISDKF" TARGET_SYS=iOS
# mv "$SRCDIR"/src/libluajit.a "$DESTDIR"/libluajit2-armv7s.a

# make clean
# make CC="gcc -m32 -arch i386" clean all
# mv "$SRCDIR"/src/libluajit.a "$DESTDIR"/libluajit2-i386.a

# lipo -create "$DESTDIR"/libluajit2-*.a -output "$DESTDIR"/libluajit2.a
# rm "$DESTDIR"/libluajit2-*.a

# make clean
