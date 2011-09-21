#!/bin/bash
echo  $1 $2 $3
pwd
libDir=linux
modeDir=Debug
if  echo $3|grep -E "Android"; then
	libDir=android
fi
if  echo $3|grep -E "Release"; then
	modeDir=Release
fi
echo "mode: $modeDir"
echo "mode: $libDir"

if [ ! -d "lib" ]; then
mkdir "lib"
fi

if [ ! -d "lib/linux" ]; then
mkdir "lib/linux"
fi

if [ ! -d "lib/android" ]; then
mkdir "lib/android"
fi

if [ ! -d "lib/linux/Debug" ]; then
mkdir "lib/linux/Debug"
fi

if [ ! -d "lib/linux/Release" ]; then
mkdir "lib/linux/Release"
fi

if [ ! -d "lib/android/Debug" ]; then
mkdir "lib/android/Debug"
fi

if [ ! -d "lib/android/Release" ]; then
mkdir "lib/android/Release"
fi

test -e ../$3/lib$1.so&&  cp ../$3/lib$1.so ../../../lib/$libDir/$modeDir/lib$2.so 
