@echo off

echo./*
echo. * Check VC++ environment...
echo. */
echo.

if defined VS110COMNTOOLS (
    set VSTOOLS="%VS110COMNTOOLS%"
    set VC_VER=110
) else if defined VS100COMNTOOLS (
    set VSTOOLS="%VS100COMNTOOLS%"
    set VC_VER=100
)



set VSTOOLS=%VSTOOLS:"=%
set "VSTOOLS=%VSTOOLS:\=/%"

set VSVARS="%VSTOOLS%vsvars32.bat"

if not defined VSVARS (
    echo Can't find VC2010 or VC2012 installed!
    goto ERROR
)

echo./*
echo. * Building cocos2d-x library binary, please wait a while...
echo. */
echo.

call %VSVARS%
if %VC_VER%==100 (
    msbuild cocos2d-win32.vc2010.sln /p:Configuration="Debug"
    msbuild cocos2d-win32.vc2010.sln /p:Configuration="Release"
) else if %VC_VER%==110 (
    msbuild cocos2d-win32.vc2012.sln /t:Clean
    msbuild cocos2d-win32.vc2012.sln /p:Configuration="Debug" /m
    msbuild cocos2d-win32.vc2012.sln /p:Configuration="Release" /m
) else (
    echo Script error.
    goto ERROR
)

echo./*
echo. * Check the cocos2d-win32 application "TestCpp.exe" ...
echo. */
echo.

pushd ".\Release.win32\"

set CC_TEST_BIN=TestCpp.exe

set CC_TEST_RES=..\samples\Cpp\TestCpp\Resources
set CC_HELLOWORLD_RES=..\samples\Cpp\HelloCpp\Resources
set CC_TESTLUA_RES=..\samples\Lua\TestLua\Resources
set CC_SIMPLEGAME_RES=..\samples\Cpp\SimpleGame\Resources
set CC_HELLOLUA_RES=..\samples\Lua\HelloLua\Resources
set CC_JSB_SOURCES=..\scripting\javascript\bindings\js
set CC_TESTJS_RES=..\samples\Javascript\Shared\tests
set CC_DRAGONJS_RES=..\samples\Javascript\Shared\games\CocosDragonJS\Published files iOS
set CC_MOONWARRIORS_RES=..\samples\Javascript\Shared\games\MoonWarriors
set CC_WATERMELONWITHME_RES=..\samples\Javascript\Shared\games\WatermelonWithMe


echo./*
echo. * Run cocos2d-win32 tests.exe and view Cocos2d-x Application Wizard for Visual Studio User Guide.
echo. */
echo.
xcopy  /E /Y /Q "%CC_TEST_RES%" .
xcopy  /E /Y /Q "%CC_HELLOWORLD_RES%" .
xcopy  /E /Y /Q "%CC_HELLOLUA_RES%" .
xcopy  /E /Y /Q "%CC_TESTLUA_RES%" .
xcopy  /E /Y /Q "%CC_SIMPLEGAME_RES%" .
xcopy  /E /Y /Q "%CC_JSB_SOURCES%" .
xcopy  /E /Y /Q "%CC_TESTJS_RES%" .
xcopy  /E /Y /Q "%CC_MOONWARRIORS_RES%" .
xcopy  /E /Y /Q "%CC_WATERMELONWITHME_RES%" .
xcopy  /E /Y /Q "%CC_DRAGONJS_RES%" .

if not exist "%CC_TEST_BIN%" (
    echo Can't find the binary "TestCpp.exe", is there build error?
    goto ERROR
)

call "%CC_TEST_BIN%"
popd
start http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Cocos2d-x_Application_Wizard_for_Visual_Studio_User_Guide
goto EOF

:ERROR
pause

:EOF
