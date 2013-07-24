#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.1
DESTDIR=$DIR/mac
MACOSX_DEPLOYMENT_TARGET="10.6"

rm "$DESTDIR"/*.a

cd $SRCDIR
make clean
make CC="gcc -m32 -arch i386" clean all

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit_32.a
fi;

make clean
make CC="gcc -m64 -arch x86_64" clean all

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit_64.a
fi;

make clean

# create lipo library
lipo -create -output $DESTDIR/libluajit.a $DESTDIR/libluajit_32.a $DESTDIR/libluajit_64.a

rm $DESTDIR/libluajit_32.a $DESTDIR/libluajit_64.a

# strip
strip -S $DESTDIR/libluajit.a

# info
lipo -info $DESTDIR/libluajit.a

