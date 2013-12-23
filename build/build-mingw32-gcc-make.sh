#!/bin/bash

# msys2 Pacman Manager for cocos2d-x

#/****************************************************************************
# Copyright (c) 2012-2013 Martell Malone
# 
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

set -e

THISDIR="$(dirname $0)"
test "$THISDIR" = "." && THISDIR=${PWD}
OSTYPE=${OSTYPE//[0-9.]/}
HOST_ARCH=$(uname -m)

if [ "${HOST_ARCH}" = "i686" ]; then
  BITS=32
elif [ "${HOST_ARCH}" = "x86_64" ]; then
  BITS=64
fi

if [ "${OSTYPE}" = "msys" ]; then

  CC=${HOST_ARCH}-w64-mingw32-gcc
  CXX=${HOST_ARCH}-w64-mingw32-g++
  PP=mingw-w64-${HOST_ARCH}
  
  MINGW_PACKAGES=(glfw glew libwebp libjpeg-turbo libpng freetype libiconv zlib curl
                  make gcc binutils headers cmake libxml2)

  MINGW_PACKAGES=(${MINGW_PACKAGES[@]/#/${PP}-})

  pacman -S --force --noconfirm --needed ${MINGW_PACKAGES[@]}

  mkdir -p mingw${BITS} && cd mingw${BITS}

  export PATH=/mingw${BITS}/bin:${PATH}

  cmake -G"MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="mingw32-make" \
  -DCMAKE_C_COMPILER="${CC}" -DCMAKE_CXX_COMPILER="${CXX}" ../..

  mingw32-make
fi
