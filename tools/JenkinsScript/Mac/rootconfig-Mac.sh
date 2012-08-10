#!/bin/bash
#get params for build_native.sh
CUR=$(pwd)
cd ../../..
#COCOS2DX=$(pwd)

#var1=NDK_ROOT_LOCAL=
#_NDK_ROOT=${var1}${ANDROID_NDK}

#var2=COCOS2DX_ROOT_LOCAL=
#_COCOS2DX_ROOT=${var2}${COCOS2DX}
#echo $_NDK_ROOT
#echo $_COCOS2DX_ROOT

#Modify the configuration files
#sed -i  '' '3,4d' $CUR/build_native.sh
sed -i  '' '13d' $CUR/project.properties
#gsed -i "3 i\\$_NDK_ROOT" $CUR/build_native.sh
#gsed -i "4 i\\$_COCOS2DX_ROOT" $CUR/build_native.sh

#Modify the xml file
if [ $1 = TestCpp ]; then
	gsed -i '2d' $CUR/build.xml
	gsed -i '2 i\<project name="TestCpp" default="help">' $CUR/build.xml
elif [ $1 = HelloCpp ]; then
	gsed -i '2d' $CUR/build.xml
	gsed -i '2 i\<project name="HelloCpp" default="help">' $CUR/build.xml
else
	gsed -i '2d' $CUR/build.xml
	gsed -i '2 i\<project name="HelloLua" default="help">' $CUR/build.xml
fi
