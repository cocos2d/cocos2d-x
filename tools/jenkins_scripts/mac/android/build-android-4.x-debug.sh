#!/bin/bash
#This script is used to finish a android automated compiler.
#You should make sure have finished the environment setting.
#Here are the environment variables you should set.
#$COCOS2DX_ROOT $ANDROID_SDK_ROOT $ANDROID_NDK_ROOT $NDK_ROOT

antcompile()
{
	#Change API level.(API level:14)
	sed '/target=/s/=.*$/=android-14/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-14.apk
            cd ..
        fi

	#Change API level.(API level:15)
	sed '/target=/s/=.*$/=android-15/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-15.apk
            cd ..
        fi

	#After all test versions completed,changed current API level to the original.(API level:8)
	sed '/target=/s/=.*$/=android-8/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
}

#record the relevant catalog
compileresult=0
CUR=$(pwd)
cd ../../../..
ROOT=$(pwd)
IsTestCpp=1

#copy configuration files to target.
cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/TestCpp/proj.android
cd samples/TestCpp/proj.android
sh rootconfig-mac.sh TestCpp
sh build_native.sh

#update android project configuration files
cd ..
android update project -p proj.android
cd proj.android
antcompile

IsTestCpp=0

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/HelloCpp/proj.android 
cd ../../HelloCpp/proj.android
sh rootconfig-mac.sh HelloCpp
sh build_native.sh
cd ..
android update project -p proj.android
cd proj.android
antcompile

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/HelloLua/proj.android  
cd ../../HelloLua/proj.android
sh rootconfig-mac.sh HelloLua
sh build_native.sh
cd ..
android update project -p proj.android
cd proj.android
antcompile

#return the compileresult.
cd ../../..
if [ $compileresult != 0 ]; then
#    git checkout -f
#    git clean -df -x
    exit 1
else
#    git checkout -f
#    git clean -df -x
    exit 0
fi
