#!/bin/sh -x

# Hacky script to re-compile all of Cocos2D-X's dependencies with Emscripten.
# TODO: paramaterize directories, download source code and run without user intervention.

EMSCRIPTEN=~/emscripten
TMP=`mktemp -d /tmp/cc-deps.XXXXXXX`

# Libtiff, from ftp://ftp.remotesensing.org/pub/libtiff/tiff-4.0.3.tar.gz
cd tiff-4.0.3
$EMSCRIPTEN/emconfigure ./configure --enable-static --prefix=`pwd`/../build CFLAGS=-DNDEBUG
$EMSCRIPTEN/emmake make clean
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install
cd ..

# Freetype. Build once natively, then again with Emscripten, so as to satisfy build time deps
# From http://download.savannah.gnu.org/releases/freetype/freetype-2.4.12.tar.gz
cd freetype-2.4.12
./configure --enable-static
make clean
make
# Copy build-time targets to /tmp
cp -v objs/apinames $TMP/apinames
$EMSCRIPTEN/emconfigure ./configure --enable-static --prefix=`pwd`/../build
$EMSCRIPTEN/emmake make clean
# Copy them back
cp -v $TMP/apinames objs/apinames
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install

# libpng, from http://sourceforge.net/projects/libpng/files/libpng14/1.4.12/libpng-1.4.12.tar.gz/download
cd libpng-1.4.12
$EMSCRIPTEN/emconfigure ./configure --enable-static --prefix=`pwd`/../build
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install
cd ..

# libjpeg, from http://www.ijg.org/files/jpegsrc.v9.tar.gz
cd jpeg-9
$EMSCRIPTEN/emconfigure ./configure --enable-static --prefix=`pwd`/../build
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install
cd ..

# libwebp, from https://webp.googlecode.com/files/libwebp-0.3.0.tar.gz
cd libwebp-0.3.0
# Generated autotools files don't work on my Mac. Re-build them here. Otherwise build fails.
./autogen.sh
$EMSCRIPTEN/emconfigure ./configure --disable-threading --prefix=`pwd`/../build --enable-static --disable-shared
$EMSCRIPTEN/emmake make clean
$EMSCRIPTEN/emmake make V=1
$EMSCRIPTEN/emmake make install
cd ..

# libz, from http://zlib.net/zlib-1.2.8.tar.gz
cd zlib-1.2.8
$EMSCRIPTEN/emconfigure ./configure --prefix=`pwd`/../build --static
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install
cd ..

# libxml2, from ftp://xmlsoft.org/libxml2/libxml2-2.9.1.tar.gz
cd libxml2-2.9.1
$EMSCRIPTEN/emconfigure ./configure --with-http=no --with-ftp=no --prefix=`pwd`/../build --with-python=no --with-threads=no --enable-static
$EMSCRIPTEN/emmake make
$EMSCRIPTEN/emmake make install
cd ..

