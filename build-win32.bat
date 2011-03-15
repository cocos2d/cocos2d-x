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
    vcbuild cocos2d-win32.vc2008.sln $ALL
) else if %VC_VER%==100 (
    msbuild cocos2d-win32.vc2010.sln /p:Configuration="Debug" 
    msbuild cocos2d-win32.vs2010.sln /p:Configuration="Release"
) else (
    echo Script error.
    goto ERROR
)

echo./*
echo.* Check the cocos2d-win32 application "tests.exe" ...
echo.*/
echo.

set CC_TEST_PATH=".\Release.win32\tests.exe"
if not exist %CC_TEST_PATH% (
    echo Can't find the binary "tests.exe", is there build error?
    goto ERROR
)

echo./*
echo.* Install Cocos2d-win32 application wizard...
echo.*/
echo.

set SCRIPT_LOG=InstallWizardLog.txt
set SCRIPT_DIR=.\template\msvc\

if exist %SCRIPT_LOG% del /Q %SCRIPT_LOG%
cscript "%SCRIPT_DIR%InstallWizardForVC2008Express.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVC2010Express.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVS2008.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVS2010.js" /quiet
if exist %SCRIPT_LOG% more %SCRIPT_LOG%
if exist %SCRIPT_LOG% del /Q %SCRIPT_LOG%

echo./*
echo.* Run cocos2d-win32 tests.exe and view Cocos2d-x Application Wizard for Visual Studio User Guide.
echo.*/
echo.
call %CC_TEST_PATH%
start http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Cocos2d-x_Application_Wizard_for_Visual_Studio_User_Guide
goto EOF

:ERROR
pause

:EOF
