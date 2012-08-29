::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::You should add %ANDROID_HOME%\tools and %ANDROID_HOME%\platform-tools to Path

::Copy monkeyrunner python script to tools directory.
cd ..\..
copy %cd%\Monkeyrunner_TestsCpp.py %ANDROID_HOME%\tools

cd ..\..
cd samples\TestCpp\proj.android\bin

::Copy test apk to tools directory.
copy %cd%\TestCpp-debug-14.apk %ANDROID_HOME%\tools
copy %cd%\TestCpp-debug-15.apk %ANDROID_HOME%\tools

::Enter tools directory.
set ANDROID_ROOT=%ANDROID_HOME:~0,2%
%ANDROID_ROOT%
cd %ANDROID_HOME%\tools

::If monkeyrunner test failed,it automatically exit and make ERRORLEVEL nonzero.

::Running monkeyrunner test(debug,API level:14).
ren TestCpp-debug-14.apk TestCpp-debug.apk
monkeyrunner Monkeyrunner_TestCpp.py TestCpp-debug.apk
rm TestCpp-debug.apk

::Running monkeyrunner test(debug,API level:15).
ren TestCpp-debug-15.apk TestCpp-debug.apk
monkeyrunner Monkeyrunner_TestCpp.py TestCpp-debug.apk
rm TestCpp-debug.apk

rm Monkeyrunner_TestCpp.py

::Monkeyrunner success!
echo Monkeyrunner Test Success!
git checkout -f
git clean -df -x
exit 0

::End