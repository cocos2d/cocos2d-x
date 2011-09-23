#!/bin/bash
#arguments
#1 is the config name
#2 is the project name
#3 is the cocos2d sdk base folder
#4 is the resource folder name if it has

originRes="Resource"
echo $#
if [ $# > 2 ]; then
	echo "ok"
else
	echo "configname or proj name do not assign"
	exit
fi


if [ -d "../../android/libs" ];then
	echo "create libs"
else
	mkdir ../../android/libs
fi

if [ -d "../../android/libs/armeabi" ];then
	echo "create libs"
else
	mkdir ../../android/libs/armeabi
fi
#move game lib into android/libs/armeabi
cp -f lib$2.so ../../android/libs/armeabi/

#move cocos2d lib into android/libs/armeabi
cp -f $3/cocos2dx/proj.linux/$1/lib*.so ../../android/libs/armeabi/
cp -f $3/CocosDenshion/proj.linux/$1/lib*.so ../../android/libs/armeabi/

#link the resource folder
if [ -L ../../android/assets ];then
	exit
fi

if [ $# == '4' ];then
	originRes=$4
fi

echo `pwd`/../../$originRes
ln -s `pwd`/../../$originRes ../../android/assets

