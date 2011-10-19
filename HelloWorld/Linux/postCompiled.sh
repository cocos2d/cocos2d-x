#!/bin/bash
#arguments
#1 is the config name
#2 is the project name
#3 is the cocos2dx sdk base folder

originRes="Resource"

if [ $# -lt 3 ]; then
	echo "usage sh postCompiled.sh confi-gname project-name cocos2dx-root"
	exit
fi


if [ ! -d "../../android/libs" ];then
	mkdir ../../android/libs
fi

if [ ! -d "../../android/libs/armeabi" ];then
	mkdir ../../android/libs/armeabi
fi
#move game lib into android/libs/armeabi
cp -f lib$2.so ../../android/libs/armeabi/

#move cocos2d lib into android/libs/armeabi
cp -f $3/cocos2dx/proj.linux/$1/lib*.so ../../android/libs/armeabi/
cp -f $3/CocosDenshion/proj.linux/$1/lib*.so ../../android/libs/armeabi/

#link the resource folder
if [ -d ../../android/assets ];then
	exit
fi

echo `pwd`/../../$originRes
ln -s `pwd`/../../$originRes ../../android/assets

