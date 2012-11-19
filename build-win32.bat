@echo off

echo./*
echo.* Check VC++ environment...
echo.*/
echo.

if defined VS110COMNTOOLS (
    set VSVARS="%VS110COMNTOOLS%vsvars32.bat"
    set VC_VER=110
) else if defined VS100COMNTOOLS (
    set VSVARS="%VS100COMNTOOLS%vsvars32.bat"
    set VC_VER=100
)

if not defined VSVARS (
    echo Can't find VC2010 or VC2012 installed!
    goto ERROR
)

echo./*
echo.* Building cocos2d-x library binary, please wait a while...
echo.*/
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
echo.* Check the cocos2d-win32 application "TestCpp.exe" ...
echo.*/
echo.

cd ".\Release.win32\"

set CC_TEST_BIN=TestCpp.exe

set CC_TEST_RES=..\samples\TestCpp\Resources\*.*
set CC_HELLOWORLD_RES=..\samples\HelloCpp\Resources\*.*
set CC_HELLOLUA_RES=..\samples\HelloLua\Resources\*.*
set CC_TESTJS_RES=..\samples\TestJavascript\Resources\*.*

if not exist "%CC_TEST_BIN%" (
    echo Can't find the binary "TestCpp.exe", is there build error?
    goto ERROR
)

echo./*
echo.* Run cocos2d-win32 tests.exe and view Cocos2d-x Application Wizard for Visual Studio User Guide.
echo.*/
echo.
xcopy  /E /Y /Q "%CC_TEST_RES%" .
xcopy  /E /Y /Q "%CC_HELLOWORLD_RES%" .
xcopy  /E /Y /Q "%CC_HELLOLUA_RES%" .
xcopy  /E /Y /Q "%CC_TESTJS_RES%" .

call "%CC_TEST_BIN%"
start http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Cocos2d-x_Application_Wizard_for_Visual_Studio_User_Guide
goto EOF

:ERROR
pause

:EOF
