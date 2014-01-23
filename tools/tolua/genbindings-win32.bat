@echo off

:: This script is used to generate jsbinding glue codes.
:: Android ndk version must be ndk-r9b.

setlocal
:: You should modify PYTHON_ROOT and NDK_ROOT to work under your environment.
:: or just uncomment the follow 2 lines and set them.

:: set PYTHON_ROOT=C:/Python27
:: set NDK_ROOT=G:/android/android-ndk-r9b

setlocal ENABLEEXTENSIONS
if %errorlevel% neq 0 (
    echo Unable to enable extensions
    exit /b 1
    )

if defined PYTHON_ROOT (echo PYTHON_ROOT is defined.) else (
    echo PYTHON_ROOT is NOT defined!
    exit /b 1
    )

if defined NDK_ROOT (echo NDK_ROOT is defined.) else (
    echo NDK_ROOT is NOT defined!
    exit /b 1
    )

:: Check use 32-bit or 64-bit
:: Assume 64-bit
set TEMP=windows-x86_64
if not exist "%NDK_ROOT%/toolchains/llvm-3.3/prebuilt/%TEMP%" set TEMP=
:: Otherwise fall back to 32-bit make
if "%TEMP%"=="" set TEMP=windows

set NDK_LLVM_ROOT=%NDK_ROOT%/toolchains/llvm-3.3/prebuilt/%TEMP%

set COCOS2DX_ROOT=%cd%/../..
set "COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/%"
set CXX_GENERATOR_ROOT=%COCOS2DX_ROOT%/tools/bindings-generator
set TO_LUA_ROOT=%COCOS2DX_ROOT%/tools/tolua
set "CXX_GENERATOR_ROOT=%CXX_GENERATOR_ROOT:\=/%"
set OUTPUT_DIR=%COCOS2DX_ROOT%/cocos/scripting/auto-generated/lua-bindings
set "OUTPUT_DIR=%OUTPUT_DIR:/=\%"

set PATH=%PATH%;%CXX_GENERATOR_ROOT%/libclang;%CXX_GENERATOR_ROOT%/tools/win32;%PYTHON_ROOT%

:: write userconf.ini

set _CONF_INI_FILE=%cd%\userconf.ini
if exist %_CONF_INI_FILE% del /Q %_CONF_INI_FILE%


echo 
echo generating userconf.ini...
echo ---
echo [DEFAULT] > %_CONF_INI_FILE%
echo androidndkdir=%NDK_ROOT% >> %_CONF_INI_FILE%
echo clangllvmdir=%NDK_LLVM_ROOT% >> %_CONF_INI_FILE%
echo cocosdir=%COCOS2DX_ROOT% >> %_CONF_INI_FILE%
echo cxxgeneratordir=%CXX_GENERATOR_ROOT% >> %_CONF_INI_FILE%
:: fixme: to fix parse error, we must difine __WCHAR_MAX__ and undefine __MINGW32__ .
echo extra_flags=-D__WCHAR_MAX__=0x7fffffff -U__MINGW32__ >> %_CONF_INI_FILE%
echo ---



:: Generate bindings for cocos2dx
echo Generating bindings for cocos2dx...
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx.ini -s cocos2d-x -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_auto
if %errorlevel% neq 0 goto ERROR

echo "Generating bindings for cocos2dx_extension..."
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx_extension.ini -s cocos2dx_extension -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_extension_auto
if %errorlevel% neq 0 goto ERROR

echo "Generating bindings for cocos2dx_gui..."
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx_gui.ini -s cocos2dx_gui -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_gui_auto
if %errorlevel% neq 0 goto ERROR


echo "Generating bindings for cocos2dx_studio..."
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx_studio.ini -s cocos2dx_studio -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_studio_auto
if %errorlevel% neq 0 goto ERROR


echo "Generating bindings for cocos2dx_spine..."
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx_spine.ini -s cocos2dx_spine -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_spine_auto
if %errorlevel% neq 0 goto ERROR


echo "Generating bindings for cocos2dx_physics..."
python %CXX_GENERATOR_ROOT%/generator.py %TO_LUA_ROOT%/cocos2dx_physics.ini -s cocos2dx_physics -t lua -o %OUTPUT_DIR% -n lua_cocos2dx_physics_auto
if %errorlevel% neq 0 goto ERROR


:: Change the generated file format from DOS to UNIX.
pushd "%OUTPUT_DIR%"
dos2unix *
popd

goto PASS

:PASS
echo ---------------------------------
echo Generating bindings succeeds.
echo ---------------------------------
endlocal
exit /b 0

:ERROR
echo ---------------------------------
echo Generating bindings fails.
echo ---------------------------------
endlocal
exit /b 1

