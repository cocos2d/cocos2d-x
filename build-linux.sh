#!/bin/sh

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



if [ $# -ne 0 ]; then
	if [ $1 = "clean" ]; then
		cd ./cocos2dx/proj.linux
		make clean

		cd ../../
		cd ./CocosDenshion/proj.linux
		make clean

		cd ../../
		cd ./HelloWorld/Linux
		make clean

		cd ../../
		cd ./tests/test.linux
		make clean

		cd ../../
		rm -r lib
	fi
	
else
	cd ./cocos2dx/proj.linux
	make

	cp -f libcocos2d.so ../../lib/linux/Debug
	cd ../../
	cd ./CocosDenshion/proj.linux
	make

	cp -f libCocosDenshion.so ../../lib/linux/Debug
	cd ../../
	cd ./HelloWorld/Linux
	make

	cd ../../
	cd ./tests/test.linux
	make

	cd ../../
fi

