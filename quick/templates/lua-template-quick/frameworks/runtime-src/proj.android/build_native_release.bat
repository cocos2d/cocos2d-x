@echo off

set DIR=%~dp0
set APP_ROOT=%DIR%..\..\..\
set APP_ANDROID_ROOT=%DIR%
set COCOS2DX_ROOT=%DIR%\..\..\cocos2d-x

echo - config:
echo   ANDROID_NDK_ROOT    = %ANDROID_NDK_ROOT%
echo   COCOS2DX_ROOT       = %COCOS2DX_ROOT%
echo   APP_ROOT            = %APP_ROOT%
echo   APP_ANDROID_ROOT    = %APP_ANDROID_ROOT%

echo - cleanup
if exist "%APP_ANDROID_ROOT%bin" rmdir /s /q "%APP_ANDROID_ROOT%bin"
mkdir "%APP_ANDROID_ROOT%bin"
if exist "%APP_ANDROID_ROOT%assets" rmdir /s /q "%APP_ANDROID_ROOT%assets"
mkdir "%APP_ANDROID_ROOT%assets"

echo - copy scripts
mkdir "%APP_ANDROID_ROOT%assets\src"
xcopy /s /q "%APP_ROOT%src\*.*" "%APP_ANDROID_ROOT%assets\src\"
echo - copy resources
mkdir "%APP_ANDROID_ROOT%assets\res"
xcopy /s /q "%APP_ROOT%res\*.*" "%APP_ANDROID_ROOT%assets\res\"
echo - copy config
copy "%APP_ROOT%config.json" "%APP_ANDROID_ROOT%assets\config.json"

rem echo COPY framework_precompiled.zip
rem echo FROM: %QUICK_V3_ROOT%quick\lib\framework_precompiled
rem echo TO: "%APP_ANDROID_ROOT%assets\res\"
rem copy %QUICK_V3_ROOT%quick\lib\framework_precompiled\framework_precompiled.zip "%APP_ANDROID_ROOT%assets\res\"

echo Using prebuilt externals
"%ANDROID_NDK_ROOT%\ndk-build" %ANDROID_NDK_BUILD_FLAGS% NDK_DEBUG=%NDK_DEBUG% %NDK_BUILD_FLAGS% -C %APP_ANDROID_ROOT% NDK_MODULE_PATH=%APP_ANDROID_ROOT%;%COCOS2DX_ROOT%;%COCOS2DX_ROOT%/cocos;%COCOS2DX_ROOT%/external;%COCOS2DX_ROOT%/cocos/scripting;%APP_ANDROID_ROOT%/../Classes
