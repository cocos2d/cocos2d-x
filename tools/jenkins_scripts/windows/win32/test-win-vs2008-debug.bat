::This script is used to accomplish a vs project automated testing.
::You should make sure you have set %VS90COMNTOOLS%.

::Set the directory of qtp project.
set qtpproj=%cd%
cd ..\..\..\..\

::Compile vs project.
"%VS90COMNTOOLS%..\IDE\devenv.com" "%cd%\cocos2d-win32.vc2008.sln" /Build "Debug|Win32"

::Set the directory of test project's resources.
set CC_TEST_RES=%cd%\samples\TestCpp\Resources\*.*
set CC_HELLOWORLD_RES=%cd%\samples\HelloCpp\Resources\*.*
set CC_HELLOLUA_RES=%cd%\samples\HelloLua\Resources\*.*
set CC_TESTJS_RES=%cd%\samples\TestJavascript\Resources\*.*

cd Debug.win32

::Copy resources to destination directory.
xcopy  /E /Y /Q "%CC_TEST_RES%" .
xcopy  /E /Y /Q "%CC_HELLOWORLD_RES%" .
xcopy  /E /Y /Q "%CC_HELLOLUA_RES%" .
xcopy  /E /Y /Q "%CC_TESTJS_RES%" .

::Run qtp test.
cd ..
cd %qtpproj%\qtp_win32

::Call automated test script.
cscript qtrunner.vbs

pause