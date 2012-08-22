::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::You should add %ANDROID_HOME%\tools and %ANDROID_HOME%\platform-tools to Path

::Copy monkeyrunner python script to tools directory.
copy %cd%\Monkeyrunner_TestsCpp.py %ANDROID_HOME%\tools

cd ..\..\..\..
cd samples\TestCpp\proj.android\bin

::Copy test apk to tools directory.
copy %cd%\Tests-release-14.apk %ANDROID_HOME%\tools
copy %cd%\Tests-release-15.apk %ANDROID_HOME%\tools

::Enter tools directory.
set ANDROID_ROOT=%ANDROID_HOME:~0,2%
%ANDROID_ROOT%
cd %ANDROID_HOME%\tools

::If monkeyrunner test failed,it automatically exit and make ERRORLEVEL nonzero.

::Running monkeyrunner test(release,API level:14).
ren Tests-release-14.apk Tests-release.apk
monkeyrunner Monkeyrunner_TestCpp.py
rm Tests-release.apk

::Running monkeyrunner test(release,API level:15).
ren Tests-release-15.apk Tests-release.apk
monkeyrunner Monkeyrunner_TestCpp.py
rm Tests-release.apk

rm Monkeyrunner_TestCpp.py

::Monkeyrunner success!
echo Monkeyrunner Test Success!
git checkout -f
git clean -df -x
exit 0

::End