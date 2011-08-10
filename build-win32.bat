@echo off

echo./*
echo.* Check VC++ environment...
echo.*/
echo.

if defined VS90COMNTOOLS (
    set VSVARS="%VS90COMNTOOLS%vsvars32.bat"
    set VC_VER=90
) else if defined VS100COMNTOOLS (
    set VSVARS="%VS100COMNTOOLS%vsvars32.bat"
    set VC_VER=100
)

if not defined VSVARS (
    echo Can't find VC2008 or VC2010 installed!
    goto ERROR
)

echo./*
echo.* Building cocos2d-x library binary, please wait a while...
echo.*/
echo.

call %VSVARS%
if %VC_VER%==90 (
    vcbuild /MP /M10 cocos2d-win32.vc2008.sln $ALL
) else if %VC_VER%==100 (
    msbuild cocos2d-win32.vc2010.sln /p:Configuration="Debug" 
    msbuild cocos2d-win32.vc2010.sln /p:Configuration="Release"
) else (
    echo Script error.
    goto ERROR
)

echo./*
echo.* Check the cocos2d-win32 application "tests.exe" ...
echo.*/
echo.

cd ".\Release.win32\"

set CC_TEST_BIN=tests.exe

set CC_TEST_RES=..\tests\Res\*.*
set CC_HELLOWORLD_RES=..\HelloWorld\Resource\*.*
set CC_HELLOLUA_RES=..\HelloLua\Resource\*.*

if not exist "%CC_TEST_BIN%" (
    echo Can't find the binary "tests.exe", is there build error?
    goto ERROR
)

echo./*
echo.* Run cocos2d-win32 tests.exe and view Cocos2d-x Application Wizard for Visual Studio User Guide.
echo.*/
echo.
xcopy  /E /Y /Q "%CC_TEST_RES%" .
xcopy  /E /Y /Q "%CC_HELLOWORLD_RES%" .
xcopy  /E /Y /Q "%CC_HELLOLUA_RES%" .
call "%CC_TEST_BIN%"
start http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Cocos2d-x_Application_Wizard_for_Visual_Studio_User_Guide
goto EOF

:ERROR
pause

:EOF