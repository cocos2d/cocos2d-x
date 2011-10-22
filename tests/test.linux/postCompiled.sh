#!/bin/bash
#arguments
#1 is the config name
#2 is the project name
#3 is the cocos2d sdk base folder

if [ $# -lt 3 ];then
	echo "usage sh postCompiled.sh confi-gname project-name cocos2dx-root"
	exit
fi


if [ ! -d "../../test.android/libs" ];then
	mkdir ../../test.android/libs
fi

if [ ! -d "../../test.android/libs/armeabi" ];then
	mkdir ../../test.android/libs/armeabi
fi

#move game lib into android/libs/armeabi
cp -f lib$2.so ../../test.android/libs/armeabi/

#move cocos2d lib into android/libs/armeabi
cp -f $3/cocos2dx/proj.linux/$1/lib*.so ../../test.android/libs/armeabi/
cp -f $3/CocosDenshion/proj.linux/$1/lib*.so ../../test.android/libs/armeabi/
cp -f $3/Box2D/proj.linux/$1/lib*.so ../../test.android/libs/armeabi/
cp -f $3/chipmunk/proj.linux/$1/lib*.so ../../test.android/libs/armeabi/

# copy resources, can not link. because we don't need some file

COCOS2DX_ROOT=../../..
TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

# make sure assets is exist
if [ -d $TESTS_ROOT/assets ]; then
    rm -rf $TESTS_ROOT/assets
fi

mkdir $TESTS_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT/tests/Res/*
do
    if [ -d $file ]; then
        cp -rf $file $TESTS_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $TESTS_ROOT/assets
    fi
done

# remove test_image_rgba4444.pvr.gz
rm -f $TESTS_ROOT/assets/Images/test_image_rgba4444.pvr.gz

