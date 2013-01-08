@echo off

echo./*
echo.* Check VC++ environment...
echo.*/
echo.

set PATH=%PATH%;%cd%

if defined VS110COMNTOOLS (
	set VSTOOLS="%VS110COMNTOOLS%"
) else if defined VS100COMNTOOLS (
	set VSTOOLS="%VS100COMNTOOLS%"
)



set VSTOOLS=%VSTOOLS:"=%
set "VSTOOLS=%VSTOOLS:\=/%"

set VSVARS="%VSTOOLS%vsvars32.bat"

if not defined VSVARS (
    echo Can't find VC2010 or VC2012 installed!
    goto ERROR
)


set VS_ROOT=%VSTOOLS%/../..

:: set vs compilation environment
call %VSVARS%

set COCOS2DX_ROOT=%cd%/../..
set "COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/%"
set CXX_GENERATOR_ROOT=%COCOS2DX_ROOT%/tools/cxx-generator
set "CXX_GENERATOR_ROOT=%CXX_GENERATOR_ROOT:\=/%"

:: write userconf.ini

set _CONF_INI_FILE=%cd%\userconf.ini
if exist %_CONF_INI_FILE% del /Q %_CONF_INI_FILE%

echo 
echo generating userconf.ini...
echo ---
echo [DEFAULT] > %_CONF_INI_FILE%
echo cocosdir=%COCOS2DX_ROOT% >> %_CONF_INI_FILE%
echo cxxgeneratordir=%CXX_GENERATOR_ROOT% >> %_CONF_INI_FILE%
echo vs_headers="%VS_ROOT%/VC/include" >> %_CONF_INI_FILE%
echo vs_flags= >> %_CONF_INI_FILE%
echo ---

:: Generate bindings for cocos2dx
echo Generating bindings for cocos2dx...

python %CXX_GENERATOR_ROOT%/generator.py cocos2dx-win32.ini -s cocos2d-x -o %COCOS2DX_ROOT%/scripting/javascript/bindings/generated

echo Generating bindings successfully.

:ERROR
pause

