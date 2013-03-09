
echo./*
echo.* Install Cocos2d-win32 application wizard...
echo.*/
echo.

set SCRIPT_LOG=InstallWizardLog.txt
set SCRIPT_DIR=.\template\msvc\

if exist %SCRIPT_LOG% del /Q %SCRIPT_LOG%
cscript "%SCRIPT_DIR%InstallWizardForVC2010Express.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVS2010.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVS2012.js" /quiet
cscript "%SCRIPT_DIR%InstallWizardForVS2012Express.js" /quiet
if exist %SCRIPT_LOG% more %SCRIPT_LOG%
if exist %SCRIPT_LOG% del /Q %SCRIPT_LOG%
