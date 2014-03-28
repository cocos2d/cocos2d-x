@echo off

:: This script is used to generate jsbinding glue codes.
:: You should modify PYTHON_ROOT and NDK_ROOT to work under your environment.
:: Android ndk version must be at least ndk-r8d.

set PYTHON_ROOT=%PYTHON_ROOT%
set NDK_ROOT=%NDK_ROOT%

set PATH=%PATH%;%cd%/win32;%PYTHON_ROOT%
set COCOS2DX_ROOT=%cd%/../..
set "COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/%"
set CXX_GENERATOR_ROOT=%COCOS2DX_ROOT%/tools/bindings-generator
set TO_JS_ROOT=%COCOS2DX_ROOT%/tools/tojs
set "CXX_GENERATOR_ROOT=%CXX_GENERATOR_ROOT:\=/%"
set OUTPUT_DIR=%COCOS2DX_ROOT%/scripting/javascript/bindings/generated
set "OUTPUT_DIR=%OUTPUT_DIR:/=\%"
set CLANG_ROOT=%NDK_ROOT%/toolchains/llvm-3.1/prebuilt/windows-x86_64

:: write userconf.ini

set _CONF_INI_FILE=%cd%\userconf.ini
if exist %_CONF_INI_FILE% del /Q %_CONF_INI_FILE%


echo 
echo generating userconf.ini...
echo ---
echo [DEFAULT] > %_CONF_INI_FILE%
echo androidndkdir=%NDK_ROOT% >> %_CONF_INI_FILE%
echo clangllvmdir=%CLANG_ROOT% >> %_CONF_INI_FILE%
echo cocosdir=%COCOS2DX_ROOT% >> %_CONF_INI_FILE%
echo cxxgeneratordir=%CXX_GENERATOR_ROOT% >> %_CONF_INI_FILE%
echo extra_flags=-D__ARM_EABI__ -D__GNUC__=2 >> %_CONF_INI_FILE%
echo ---



:: Generate bindings for cocos2dx
echo Generating bindings for cocos2dx...

python %CXX_GENERATOR_ROOT%/generator.py %TO_JS_ROOT%/cocos2dx.ini -s cocos2d-x -o %OUTPUT_DIR% -n jsb_cocos2dx_auto
if %errorlevel% neq 0 goto ERROR

echo "Generating bindings for cocos2dx_extension..."

python %CXX_GENERATOR_ROOT%/generator.py %TO_JS_ROOT%/cocos2dx_extension.ini -s cocos2dx_extension -o %OUTPUT_DIR% -n jsb_cocos2dx_extension_auto
if %errorlevel% neq 0 goto ERROR

echo "Generating bindings for cocos2dx_studio..."

python %CXX_GENERATOR_ROOT%/generator.py %TO_JS_ROOT%/cocos2dx_studio.ini -s cocos2dx_studio -o %OUTPUT_DIR% -n jsb_cocos2dx_studio_auto
if %errorlevel% neq 0 goto ERROR

:: Change the generated file format from DOS to UNIX.
pushd "%OUTPUT_DIR%"
dos2unix *
popd

echo ---------------------------------
echo Generating bindings succeeds.
echo ---------------------------------

goto QUIT

:ERROR
echo ---------------------------------
echo Generating bindings fails.
echo ---------------------------------
exit 1

:QUIT

::pause

