@echo off
set QUICK_V3_ROOT=%~dp0

set SETX=setx
ver | find "XP" > nul
if %ERRORLEVEL% == 0 (
    set SETX=%QUICK_V3_ROOT%\bin\win32\setx.exe
)


echo.
echo config:
echo.
echo QUICK_V3_ROOT = "%QUICK_V3_ROOT%"
echo.

%SETX% QUICK_V3_ROOT %QUICK_V3_ROOT%

echo.

pause

