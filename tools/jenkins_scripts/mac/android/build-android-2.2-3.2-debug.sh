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
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-8.apk
            cd ..
        fi
        
	#Change API level.(API level:10)
	sed '/target=/s/=.*$/=android-10/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-10.apk
            cd ..
        fi

	#Change API level.(API level:11)
	sed '/target=/s/=.*$/=android-11/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-11.apk
            cd ..
        fi

	#Change API level.(API level:12)
	sed '/target=/s/=.*$/=android-12/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-12.apk
            cd ..
        fi

	#Change API level.(API level:13)
	sed '/target=/s/=.*$/=android-13/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant debug
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-debug.apk TestCpp-debug-13.apk
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
cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Cpp/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Cpp/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Cpp/TestCpp/proj.android
cd $ROOT/samples/Cpp/TestCpp/proj.android
sh rootconfig-mac.sh TestCpp
sh build_native.sh

#update android project configuration files
cd $ROOT/samples/Cpp/TestCpp
android update project -p proj.android
cd proj.android
antcompile

IsTestCpp=0

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Cpp/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Cpp/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Cpp/HelloCpp/proj.android
cd $ROOT/samples/Cpp/HelloCpp/proj.android
sh rootconfig-mac.sh HelloCpp
sh build_native.sh
cd $ROOT/samples/Cpp/HelloCpp
android update project -p proj.android
cd proj.android
antcompile

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Lua/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Lua/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Lua/HelloLua/proj.android
cd $ROOT/samples/Lua/HelloLua/proj.android
sh rootconfig-mac.sh HelloLua
sh build_native.sh
cd $ROOT/samples/Lua/HelloLua
android update project -p proj.android
cd proj.android
antcompile

#return the compileresult.
cd $ROOT
if [ $compileresult != 0 ]; then
#    git checkout -f
#    git clean -df -x
    exit 1
else
#    git checkout -f
#    git clean -df -x
    exit 0
fi