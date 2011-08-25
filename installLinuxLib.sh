#!/bin/bash
linuxLibFolder="Release"
if [ "$1" = "Debug" ];then
	echo "debug"
	linuxLibFolder="Debug"
fi
cp lib/linux/$linuxLibFolder/libcocos*.so /usr/lib/
if [ -d "/usr/include/cocos2dx" ];then
	echo "exist"
else
	echo "build cocos2dx folder"
	mkdir /usr/include/cocos2dx
fi

if [ "$2" = "move" ];then
cp cocos2dx/*.h /usr/include/cocos2dx/
cp -rf cocos2dx/include /usr/include/cocos2dx/
cp -f cocos2dx/platform/*.h /usr/include/cocos2dx/platform
cp -f cocos2dx/platform/Linux/*.h /usr/include/cocos2dx/platform/Linux/
fi
