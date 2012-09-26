#!/bin/bash

TXTCOLOR_DEFAULT="\033[0;m"
TXTCOLOR_RED="\033[0;31m"
TXTCOLOR_GREEN="\033[0;32m"

COCOS2DX20_TRUNK=`pwd`
OUTPUT_DEBUG=$COCOS2DX20_TRUNK/lib/linux/Debug/
OUTPUT_RELEASE=$COCOS2DX20_TRUNK/lib/linux/Release/

check_make_result()
{
	if [ 0 != $? ]; then
	    exit 1
   	fi
}

DIR_GLEW170=$COCOS2DX20_TRUNK/cocos2dx/platform/third_party/linux/glew-1.7.0/
if ! test -d $DIR_GLEW170/glew-1.7.0/; then
	echo -e $TXTCOLOR_GREEN"it is the first time you run this linux project, some depends lib should be install"$TXTCOLOR_DEFAULT;
	DEPENDS='libx11-dev'
	DEPENDS+=' libxmu-dev'
	DEPENDS+=' libglu1-mesa-dev'
	DEPENDS+=' libgl2ps-dev'
	DEPENDS+=' libxi-dev'
	DEPENDS+=' libglfw-dev'
	DEPENDS+=' g++'
	DEPENDS+=' libzip-dev'
	DEPENDS+=' libcurl4-gnutls-dev'
	DEPENDS+=' libfontconfig1-dev'
	for i in $DEPENDS; do
		echo -e $TXTCOLOR_GREEN"sudo apt-get install $i, please enter your password:"$TXTCOLOR_DEFAULT
		sudo apt-get install $i
	done

#	DIR_GLEW170=$COCOS2DX20_TRUNK/cocos2dx/platform/third_party/linux/glew-1.7.0/
	if ! test -d $DIR_GLEW170/glew-1.7.0/; then
		cd $DIR_GLEW170
		echo -e $TXTCOLOR_GREEN"building glew-1.7.0 ..."$TXTCOLOR_DEFAULT;
		tar -zxf glew-1.7.0.tgz
		make -C ./glew-1.7.0/
		cd -
	fi
fi

#OUTPUT_DEBUG=$COCOS2DX20_TRUNK/lib/linux/Debug/
#if ! test -d $OUTPUT_DEBUG; then
#	mkdir $OUTPUT_DEBUG -p
#fi
mkdir -p $OUTPUT_DEBUG
mkdir -p $OUTPUT_RELEASE

make -C $COCOS2DX20_TRUNK/external/Box2D/proj.linux clean
make -C $COCOS2DX20_TRUNK/external/Box2D/proj.linux debug
check_make_result
cp $COCOS2DX20_TRUNK/external/Box2D/proj.linux/libbox2d.a $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/external/Box2D/proj.linux clean
make -C $COCOS2DX20_TRUNK/external/Box2D/proj.linux release
check_make_result
cp $COCOS2DX20_TRUNK/external/Box2D/proj.linux/libbox2d.a $OUTPUT_RELEASE

make -C $COCOS2DX20_TRUNK/external/chipmunk/proj.linux clean
make -C $COCOS2DX20_TRUNK/external/chipmunk/proj.linux debug
check_make_result
cp $COCOS2DX20_TRUNK/external/chipmunk/proj.linux/libchipmunk.a $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/external/chipmunk/proj.linux clean
make -C $COCOS2DX20_TRUNK/external/chipmunk/proj.linux release
check_make_result
cp $COCOS2DX20_TRUNK/external/chipmunk/proj.linux/libchipmunk.a $OUTPUT_RELEASE

make -C $COCOS2DX20_TRUNK/cocos2dx/proj.linux clean
make -C $COCOS2DX20_TRUNK/cocos2dx/proj.linux debug
check_make_result
cp $COCOS2DX20_TRUNK/cocos2dx/proj.linux/libcocos2d.so $OUTPUT_DEBUG
rm $COCOS2DX20_TRUNK/cocos2dx/proj.linux/libcocos2d.so

make -C $COCOS2DX20_TRUNK/cocos2dx/proj.linux clean
make -C $COCOS2DX20_TRUNK/cocos2dx/proj.linux release
check_make_result
cp $COCOS2DX20_TRUNK/cocos2dx/proj.linux/libcocos2d.so $OUTPUT_RELEASE
rm $COCOS2DX20_TRUNK/cocos2dx/proj.linux/libcocos2d.so

make -C $COCOS2DX20_TRUNK/CocosDenshion/proj.linux clean
make -C $COCOS2DX20_TRUNK/CocosDenshion/proj.linux debug
check_make_result
cp $COCOS2DX20_TRUNK/CocosDenshion/proj.linux/libcocosdenshion.so $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/CocosDenshion/proj.linux clean
make -C $COCOS2DX20_TRUNK/CocosDenshion/proj.linux release
check_make_result
cp $COCOS2DX20_TRUNK/CocosDenshion/proj.linux/libcocosdenshion.so $OUTPUT_RELEASE

make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux debug
check_make_result
make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux release
check_make_result

make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux debug
check_make_result
make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux release
check_make_result
