##This script is used to finish a android automated compiler.
#You should make sure have finished the environment setting.
#Here are the environment variables you should set.
#$COCOS2DX_ROOT $ANDROID_SDK_ROOT $ANDROID_NDK_ROOT $NDK_ROOT

cd TestCpp/proj.android
./build_native.sh

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
    NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $ANDROID_SDK_ROOT"aaa" != "aaa" ]; then
    echo "use global definition of ANDROID_SDK_ROOT: $ANDROID_SDK_ROOT"
    ANDROID_SDK_ROOT_LOCAL=$ANDROID_SDK_ROOT
fi

#Make sure the original target is android-8
sed '/target=/s/=.*$/=android-8/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties

#Android ant build(debug ,API level:8)
ant debug
#If build failed,make sure the Jenkins could get the errorlevel.
if [ $? != 0 ]; then
    exit 1
fi

#Change API level.(API level:10)
sed '/target=/s/=.*$/=android-10/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties
ant debug
if [ $? != 0 ]; then
    exit 1
fi

#Change API level.(API level:11)
sed '/target=/s/=.*$/=android-11/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties
ant debug
if [ $? != 0 ]; then
    exit 1
fi

#Change API level.(API level:12)
sed '/target=/s/=.*$/=android-12/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties
ant debug
if [ $? != 0 ]; then
    exit 1
fi

#Change API level.(API level:13)
sed '/target=/s/=.*$/=android-13/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties
ant debug
if [ $? != 0 ]; then
    exit 1
fi

#After all test versions completed,changed current API level to the original.(API level:8)
sed '/target=/s/=.*$/=android-8/' ant.properties > anttmp.properties
cp anttmp.properties ant.properties
rm anttmp.properties
