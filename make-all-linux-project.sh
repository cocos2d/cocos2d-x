#!/bin/bash

TXTCOLOR_DEFAULT="\033[0;m"
TXTCOLOR_RED="\033[0;31m"
TXTCOLOR_GREEN="\033[0;32m"

COCOS2DX20_TRUNK=`pwd`
OUTPUT_DEBUG=$COCOS2DX20_TRUNK/lib/linux/Debug/

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

	DIR_SPIDERMONKEY_LINUX=$COCOS2DX20_TRUNK/scripting/javascript/spidermonkey-linux
	if ! test -d $DIR_SPIDERMONKEY_LINUX/js-1.8.5; then
		cd $DIR_SPIDERMONKEY_LINUX
		echo -e $TXTCOLOR_GREEN"building spidermonkey ..."$TXTCOLOR_DEFAULT;
		tar -zxf js185-1.0.0.tar.gz
		cd ./js-1.8.5/js/src
		./configure && make
	fi
fi

OUTPUT_DEBUG=$COCOS2DX20_TRUNK/lib/linux/Debug/
if ! test -d $OUTPUT_DEBUG; then
	mkdir $OUTPUT_DEBUG -p
fi

make -C $COCOS2DX20_TRUNK/external/Box2D/proj.linux
check_make_result
cp $COCOS2DX20_TRUNK/external/Box2D/proj.linux/libbox2d.a $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/external/chipmunk/proj.linux
check_make_result
cp $COCOS2DX20_TRUNK/external/chipmunk/proj.linux/libchipmunk.a $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/cocos2dx/proj.linux
check_make_result
cp $COCOS2DX20_TRUNK/cocos2dx/proj.linux/libcocos2d.so $OUTPUT_DEBUG

make -C $COCOS2DX20_TRUNK/CocosDenshion/proj.linux
check_make_result
cp $COCOS2DX20_TRUNK/CocosDenshion/proj.linux/libcocosdenshion.so $OUTPUT_DEBUG


make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/TestCpp/proj.linux
check_make_result
make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/HelloCpp/proj.linux
check_make_result
make -C $COCOS2DX20_TRUNK/samples/TestJavascript/proj.linux clean
make -C $COCOS2DX20_TRUNK/samples/TestJavascript/proj.linux
check_make_result

#cd $COCOS2DX20_TRUNK/tests/proj.linux
#./cocos2dx-test
#cd -
