@echo off
set QUICK_V3_ROOT=%~dp0
set SETX=setx

echo.
echo config:
echo.
echo QUICK_V3_ROOT = "%QUICK_V3_ROOT%"
echo.

%SETX% QUICK_V3_ROOT %QUICK_V3_ROOT%

echo.

rem call %QUICK_V3_ROOT%quick\bin\make_framework_package.bat

rem call %QUICK_V3_ROOT%quick\bin\install_to_cocos.bat

pause
