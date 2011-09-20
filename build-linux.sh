#!/bin/sh
#p=$(dirname $_)
#echo "$p"

path=$(dirname $0)
path=${path/\./$(pwd)}
echo $path

if [ ! -d "lib" ]; then
mkdir "lib"
fi

if [ ! -d "lib/linux" ]; then
mkdir "lib/linux"
fi

if [ ! -d "lib/linux/Debug" ]; then
mkdir "lib/linux/Debug"
fi

if [ ! -d "lib/linux/Release" ]; then
mkdir "lib/linux/Release"
fi

if [ $# -ne 0 ]; then
	if [ $1 = "clean" ]; then
		cd $p/cocos2dx/proj.linux
		make clean

		cd ../../
		cd $p/CocosDenshion/proj.linux
		make clean

		cd ../../
		rm -r lib/linux/Debug/*.so
	fi
	
else
	cd $p/cocos2dx/proj.linux
	make

	cp -f libcocos2d.so ../../lib/linux/Debug
	cd ../../
	cd $p/CocosDenshion/proj.linux
	make

	cp -f libCocosDenshion.so ../../lib/linux/Debug

	cd ../../
fi

