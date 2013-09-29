@echo off

set APPNAME="HelloCpp"

set buildexternalsfromsource=
set PARALLEL_BUILD_FLAG=

goto :getopts

:usage
	echo Build C/C++ code for %APPNAME% using Android NDK
	echo OPTIONS:
	echo -s	Build externals from source
	echo -h	this help
	pause
  exit /b 1  
  
:def
	echo "NDK_ROOT not defined. Please define NDK_ROOT in your environment." 
	pause
	exit /b 1

:getopts 
	set "par=%~1"
	if "%par%"=="" (goto :L)
	if "%~1"=="-s" set /a buildexternalsfromsource=1 
	if "%~1"=="-h" goto :usage
	shift
	goto :getopts

:L
set NDK_ROOT=%NDK_ROOT%
if "%NDK_ROOT%"=="" goto:def

rem check toolchains
if exist %NDK_ROOT%\toolchains\arm-linux-androideabi-4.8 (goto :toolchains48)
if exist %NDK_ROOT%\toolchains\arm-linux-androideabi-4.7 (goto :toolchains47)
if exist %NDK_ROOT%\toolchains\arm-linux-androideabi-4.6 (goto :toolchains46)
echo "Couldn't find the gcc toolchain."
pause
exit /b 1

:toolchains48
	set NDK_TOOLCHAIN_VERSION=4.8
	goto :InitPath
:toolchains47
	set NDK_TOOLCHAIN_VERSION=4.7
	goto :InitPath
:toolchains46
	set NDK_TOOLCHAIN_VERSION=4.6

:InitPath

set COCOS2DX_ROOT=%~dp0..\..\..
set APP_ROOT=%~dp0..
set APP_ANDROID_ROOT=%~dp0

if "%buildexternalsfromsource%"=="1" (goto :MODULE1) else (goto :MODULE2)
:MODULE1
	echo "Building external dependencies from source"
	set NDK_MODULE_PATH=%COCOS2DX_ROOT%;%COCOS2DX_ROOT%\cocos2dx\platform\third_party\android\source
	goto :COPY_RES
:MODULE2
	echo "Using prebuilt externals"
	set NDK_MODULE_PATH=%COCOS2DX_ROOT%;%COCOS2DX_ROOT%\cocos2dx\platform\third_party\android\prebuilt

:COPY_RES
echo NDK_ROOT = %NDK_ROOT%
echo COCOS2DX_ROOT=%COCOS2DX_ROOT%
echo APP_ROOT=%APP_ROOT%
echo APP_ANDROID_ROOT=%APP_ANDROID_ROOT%
echo NDK_TOOLCHAIN_VERSION=%NDK_TOOLCHAIN_VERSION%

rem make sure assets is exist
if exist %APP_ANDROID_ROOT%\assets rd /q /s %APP_ANDROID_ROOT%\assets

mkdir %APP_ANDROID_ROOT%\assets
mkdir %APP_ANDROID_ROOT%\assets\res

rem copy Resources/* into assets' root
xcopy /e /q /r /y %APP_ROOT%\Resources\* %APP_ANDROID_ROOT%\assets

call %NDK_ROOT%\ndk-build.cmd NDK_LOG=0 V=0
pause