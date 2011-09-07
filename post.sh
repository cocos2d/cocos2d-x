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

test -e ../$3/lib$1.so&&  cp ../$3/lib$1.so ../../../lib/$libDir/$modeDir/lib$2.so 
