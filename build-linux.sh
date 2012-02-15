#!/bin/sh
#p=$(dirname $_)
#echo "$p"

#path=$(dirname $0)
#path=${path/\./$(pwd)}
#echo $path
p=.

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

# copy cocosdenshino depended libs into lib/linux/Debug/
cp CocosDenshion/third_party/linux/fmod/api/lib/*.so lib/linux/Debug

if [ $# -ne 0 ]; then
	if [ $1 = "clean" ]; then
		cd $p/cocos2dx/proj.linux
		make clean

		cd ../../
		cd $p/CocosDenshion/proj.linux
		make clean

		cd ../..
		cd $p/Box2D/proj.linux
		make clean

		cd ../..
		cd $p/chipmunk/proj.linux
		make clean

		cd ../../
		rm -r lib/linux/Debug/*.so
	fi

else
	cd $p/cocos2dx/proj.linux
	echo "**********************building cocos2dx**************************"
	make
	cp -f libcocos2d.so ../../lib/linux/Debug

        echo "**********************building cocosdenshion*********************"
	cd ../../
	cd $p/CocosDenshion/proj.linux
	make
	cp -f libcocosdenshion.so ../../lib/linux/Debug

        echo "**********************building Box2D******************************"
	cd ../..
	cd $p/Box2D/proj.linux
	make
	cp -f libbox2d.a ../../lib/linux/Debug

        echo "**********************building chipmunk***************************"
	cd ../..
	cd $p/chipmunk/proj.linux
	make
	cp -f libchipmunk.a ../../lib/linux/Debug

	cd ../../
fi

