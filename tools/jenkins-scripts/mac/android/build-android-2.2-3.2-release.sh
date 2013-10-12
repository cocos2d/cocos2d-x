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
	ant release
	#If build failed,make sure the Jenkins could get the errorlevel.
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-release.apk TestCpp-release-8.apk
            cd ..
        fi

	#Change API level.(API level:10)
	sed '/target=/s/=.*$/=android-10/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant release
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-release.apk TestCpp-release-10.apk
            cd ..
        fi

	#Change API level.(API level:11)
	sed '/target=/s/=.*$/=android-11/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant release
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-release.apk TestCpp-release-11.apk
            cd ..
        fi

	#Change API level.(API level:12)
	sed '/target=/s/=.*$/=android-12/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant release
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-release.apk TestCpp-release-12.apk
            cd ..
        fi

	#Change API level.(API level:13)
	sed '/target=/s/=.*$/=android-13/' ant.properties > anttmp.properties
	cp anttmp.properties ant.properties
	rm anttmp.properties
	ant release
	compileresult=$[$compileresult+$?]
        if [ $IsTestCpp == 1 ] && [ $? == 0 ]
        then
            cd bin
            mv TestCpp-release.apk TestCpp-release-13.apk
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
sed -i  '' '14d' $CUR/ant.properties
gsed -i "14 i\\key.store=$ANDROID_HOME/debug.keystore" $CUR/ant.properties
cp $CUR/../debug.keystore $ANDROID_HOME

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Cpp/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Cpp/TestCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Cpp/TestCpp/proj.android
cd samples/Cpp/TestCpp/proj.android
sh rootconfig-mac.sh TestCpp
sh build_native.sh

#update android project configuration files
cd ..
android update project -p proj.android
cd proj.android
antcompile

IsTestCpp=0

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Cpp/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Cpp/HelloCpp/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Cpp/HelloCpp/proj.android
cd ../../Cpp/HelloCpp/proj.android
sh rootconfig-mac.sh HelloCpp
sh build_native.sh
cd ..
android update project -p proj.android
cd proj.android
antcompile

cp $ROOT/tools/jenkins_scripts/ant.properties $ROOT/samples/Lua/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/build.xml $ROOT/samples/Lua/HelloLua/proj.android
cp $ROOT/tools/jenkins_scripts/mac/rootconfig-mac.sh $ROOT/samples/Lua/HelloLua/proj.android
cd ../../Lua/HelloLua/proj.android
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