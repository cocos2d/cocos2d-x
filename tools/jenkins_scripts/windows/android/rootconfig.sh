#!/bin/bash
#This script is used to modify parameters in profile,so it will be convenient for ant to build different project.

#Change the path expression of current path to cygwin path.
#NDK_ROOT=$($CYGWIN/bin/cygpath.exe $ANDROID_NDK)
#echo $NDK_ROOT
CUR=$(pwd)
#tmp=$(pwd)
#COCOS2DX=$($CYGWIN/bin/cygpath.exe $tmp)
#echo $COCOS2DX

#var1=NDK_ROOT_LOCAL=
#_NDK_ROOT=${var1}${NDK_ROOT}

#var2=COCOS2DX_ROOT_LOCAL=
#_COCOS2DX_ROOT=${var2}${COCOS2DX}
#echo $_NDK_ROOT
#echo $_COCOS2DX_ROOT

#Modify the configuration files
#sed -i '3,4d' $CUR/build_native.sh
sed -i '13d' $CUR/project.properties
#sed -i "3 i\\$_NDK_ROOT" $CUR/build_native.sh
#sed -i "4 i\\$_COCOS2DX_ROOT" $CUR/build_native.sh

#Modify the project name
if [ $1 = TestCpp ]; then
	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="TestCpp" default="help">' $CUR/build.xml
elif [ $1 = HelloCpp ]; then
	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="HelloCpp" default="help">' $CUR/build.xml
elif [ $1 = HelloLua ]; then
	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="HelloLua" default="help">' $CUR/build.xml
elif [ $1 = TestLua ]; then
	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="TestLua" default="help">' $CUR/build.xml
elif [ $1 = TestJavascript ]; then
 	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="TestJavascript" default="help">' $CUR/build.xml
elif [ $1 = SimpleGame ]; then
 	sed -i '2d' $CUR/build.xml
	sed -i '2 i\<project name="SimpleGame" default="help">' $CUR/build.xml
fi