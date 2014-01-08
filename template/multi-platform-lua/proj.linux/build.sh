#!/bin/bash

# Exit on error
set -e

rm -rf ../bin
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#make global libs
cd ../cocos2d
#install depend libs
sudo ./build/install-deps-linux.sh
mkdir -p linux-build
cd linux-build
cmake .. -DBUILD_HelloCpp=OFF -DBUILD_TestCpp=OFF -DBUILD_HelloLua=OFF -DBUILD_TestLua=OFF
make -j4

#make bin
cd $DIR
rm -rf bin
mkdir -p build
cd build
cmake  ../..
make -j4
cd ..
mv ../bin bin
cp ../cocos2d/cocos/scripting/lua/script/* bin/Resources
