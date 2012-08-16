echo./*
echo.* Run cocos2d-win32 tests.exe
echo.*/
echo.

set qtpproj=%cd%
cd ..\..\..\..\

"%VS90COMNTOOLS%..\IDE\devenv.com" "%cd%\cocos2d-win32.vc2008.sln" /Build "Release|Win32"

set CC_TEST_BIN=TestCpp.exe

set CC_TEST_RES=%cd%\samples\TestCpp\Resources\*.*
set CC_HELLOWORLD_RES=%cd%\samples\HelloCpp\Resources\*.*
set CC_HELLOLUA_RES=%cd%\samples\HelloLua\Resources\*.*
set CC_TESTJS_RES=%cd%\samples\TestJavascript\Resources\*.*

cd Debug.win32

xcopy  /E /Y /Q "%CC_TEST_RES%" .
xcopy  /E /Y /Q "%CC_HELLOWORLD_RES%" .
xcopy  /E /Y /Q "%CC_HELLOLUA_RES%" .
xcopy  /E /Y /Q "%CC_TESTJS_RES%" .

cd ..
cd %qtpproj%\qtp_win32
cscript qtrunner.vbs

pause