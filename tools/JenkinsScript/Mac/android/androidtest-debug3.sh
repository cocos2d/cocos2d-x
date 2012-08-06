#!/bin/bash
#This script is used to finish a android automated compiler.
#You should make sure have finished the environment setting.
#Here are the environment variables you should set.
#$COCOS2DX_ROOT $ANDROID_SDK_ROOT $ANDROID_NDK_ROOT $NDK_ROOT

antcompile()
{
	#Make sure the original target is android-8
	sed '/target=/s/=.*$/=android-8/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties

	#Android ant build(debug ,API level:8)
	ant debug
	#If build failed,make sure the Jenkins could get the errorlevel.
	compileresult=$[$compileresult+$?]

	#Change API level.(API level:10)
	sed '/target=/s/=.*$/=android-10/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]

	#Change API level.(API level:11)
	sed '/target=/s/=.*$/=android-11/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]

	#Change API level.(API level:12)
	sed '/target=/s/=.*$/=android-12/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]

	#Change API level.(API level:13)
	sed '/target=/s/=.*$/=android-13/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]

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

#copy configuration files to target.
cp $ROOT/tools/JenkinsScript/ant.properties $ROOT/samples/TestCpp/proj.android
cp $ROOT/tools/JenkinsScript/build.xml $ROOT/samples/TestCpp/proj.android
cp $$ROOT/tools/JenkinsScript/Mac/rootconfig-Mac.sh $ROOT/samples/TestCpp/proj.android 
cd samples/TestCpp/proj.android
sh rootconfig-Mac.sh TestCpp
sh build_native.sh

#update android project configuration files
cd ..
android update project -p proj.android
cd proj.android
antcompile

cp $ROOT/tools/JenkinsScript/ant.properties $ROOT/samples/HelloCpp/proj.android
cp $ROOT/tools/JenkinsScript/build.xml $ROOT/samples/HelloCpp/proj.android
cp $$ROOT/tools/JenkinsScript/Mac/rootconfig-Mac.sh $ROOT/samples/HelloCpp/proj.android 
cd ../../HelloCpp/proj.android
sh rootconfig-Mac.sh HelloCpp
sh build_native.sh
cd ..
android update project -p proj.android
cd proj.android
antcompile

cp $ROOT/tools/JenkinsScript/ant.properties $ROOT/samples/HelloLua/proj.android
cp $ROOT/tools/JenkinsScript/build.xml $ROOT/samples/HelloLua/proj.android
cp $$ROOT/tools/JenkinsScript/Mac/rootconfig-Mac.sh $ROOT/samples/HelloLua/proj.android 
cd ../../HelloLua/proj.android
sh rootconfig-Mac.sh HelloLua
sh build_native.sh
cd ..
android update project -p proj.android
cd proj.android
antcompile

#return the compileresult.
cd ../../..
if [ $compileresult != 0 ]; then
    git checkout -f
    git clean -df -x
    exit 1
else
    git checkout -f
    git clean -df -x
fi