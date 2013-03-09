::This script is used to accomplish a vs project automated testing.
::You should make sure you have set %VS100COMNTOOLS%.

::Set the directory of qtp project.
set qtpproj=%cd%
cd ..\..\..\..\

::Compile vs project.
"%VS100COMNTOOLS%..\IDE\devenv.com" "%cd%\cocos2d-win32.vc2010.sln" /Build "Release|Win32"

::Set the directory of test project's resources.
set CC_TEST_RES=%cd%\samples\Cpp\TestCpp\Resources\*.*
set CC_HELLOWORLD_RES=%cd%\samples\Cpp\HelloCpp\Resources\*.*
set CC_HELLOLUA_RES=%cd%\samples\Lua\HelloLua\Resources\*.*
set CC_TESTJS_RES=%cd%\samples\Javascript\TestJavascript\Resources\*.*

cd Release.win32

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