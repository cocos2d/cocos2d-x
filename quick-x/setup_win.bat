@echo off
set QUICK_COCOS2DX_ROOT=%~dp0

set SETX=setx
ver | find "XP" > nul
if %ERRORLEVEL% == 0 (
    set SETX=%QUICK_COCOS2DX_ROOT%\bin\win32\setx.exe
)


echo.
echo config:
echo.
echo QUICK_COCOS2DX_ROOT = "%QUICK_COCOS2DX_ROOT%"
echo.

%SETX% QUICK_COCOS2DX_ROOT %QUICK_COCOS2DX_ROOT%

echo.

pause

