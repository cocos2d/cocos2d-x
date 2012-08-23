#!/bin/bash
#This script is used to finished a android automated compiler in Mac OS.
#You'd better add "export PATH=$PATH:$ANDROID_HOME/platform-tools" and "export
#PATH=$PATH:$ANDROID_HOME/tools" to you bash_profile,it will be very convenient.

#Copy monkeyrunner python script to tools directory.
cd ../..
CUR=$(pwd)
cp $CUR/Monkeyrunner_TestsCpp.py $ANDROID_HOME/tools

cd ../..
cd samples/TestCpp/proj.android/bin

#Copy test apk to tools directory.
CUR=$(pwd)
cp $CUR/Tests-release-14.apk $ANDROID_HOME/tools
cp $CUR/Tests-release-15.apk $ANDROID_HOME/tools

#Enter tools directory.
cd $ANDROID_HOME

#If monkeyrunner test failed,it automatically exit and make ERRORLEVEL nonzero.

#Running monkeyrunner test(release,API level:14)
mv Tests-release-14.apk Tests-release.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-release.apk

#Running monkeyrunner test(release,API level:15)
mv Tests-release-15.apk Tests-release.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-release.apk

rm Monkeyrunner_TestsCpp.py

#Monkeyrunner success!
git checkout -f
git clean -df -x