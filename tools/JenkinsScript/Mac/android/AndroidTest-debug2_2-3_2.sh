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
cp $CUR/Tests-debug-8.apk $ANDROID_HOME/tools
cp $CUR/Tests-debug-10.apk $ANDROID_HOME/tools
cp $CUR/Tests-debug-11.apk $ANDROID_HOME/tools
cp $CUR/Tests-debug-12.apk $ANDROID_HOME/tools
cp $CUR/Tests-debug-13.apk $ANDROID_HOME/tools

#Enter tools directory.
cd $ANDROID_HOME

#If monkeyrunner test failed,it automatically exit and make ERRORLEVEL nonzero.

#Running monkeyrunner test(debug,API level:8)
mv Tests-debug-8.apk Tests-debug.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-debug.apk

#Running monkeyrunner test(debug,API level:10)
mv Tests-debug-10.apk Tests-debug.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-debug.apk

#Running monkeyrunner test(debug,API level:11)
mv Tests-debug-11.apk Tests-debug.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-debug.apk

#Running monkeyrunner test(debug,API level:12)
mv Tests-debug-12.apk Tests-debug.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-debug.apk

#Running monkeyrunner test(debug,API level:13)
mv Tests-debug-13.apk Tests-debug.apk
monkeyrunner Monkeyrunner_TestsCpp.py
rm Tests-debug.apk

rm Monkeyrunner_TestsCpp.py

#Monkeyrunner success!
git checkout -f
git clean -df -x