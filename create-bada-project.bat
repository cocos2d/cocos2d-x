@echo off
:: This script is used to create an bada project.
:: Don't change it until you know what you do.

setlocal
setlocal enabledelayedexpansion

set COCOS2DX_ROOT=%cd%

set /p PROJECT_NAME=please input project name:

if not exist %PROJECT_NAME% md %PROJECT_NAME%

cd %PROJECT_NAME%

set PROJECT_ROOT=%COCOS2DX_ROOT%\%PROJECT_NAME%

echo project root = %PROJECT_ROOT%

if not exist bada (
    md Resource
    md bada\sdk1.0\Icons
    md bada\sdk1.0\Res
    md bada\sdk2.0\Icons
    md bada\sdk2.0\Res
    md bada\src
) else (
    echo "bada project exist!"
    pause
    exit
)

xcopy /y /s %COCOS2DX_ROOT%\HelloWorld\Resource\*.* Resource

copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\Icons bada\sdk1.0\Icons
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\.badaprj bada\sdk1.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\.cproject bada\sdk1.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\.project bada\sdk1.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\application.xml bada\sdk1.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk1.0\manifest.xml bada\sdk1.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\src bada\src

copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\Icons bada\sdk2.0\Icons
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\.badaprj bada\sdk2.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\.cproject bada\sdk2.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\.project bada\sdk2.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\application.xml bada\sdk2.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\sdk2.0\manifest.xml bada\sdk2.0
copy /y %COCOS2DX_ROOT%\HelloWorld\bada\src bada\src

if not exist Classes (
    md Classes
    xcopy /y /s %COCOS2DX_ROOT%\HelloWorld\Classes\*.* Classes
) else (
    echo "Classes folder exist!"
)

:: rename HelloWorldEntry.cpp
move bada\src\HelloWorldEntry.cpp bada\src\%PROJECT_NAME%Entry.cpp

cd bada\sdk1.0
call :replace .cproject
call :replace .project

cd ..\..\bada\sdk2.0
call :replace .cproject
call :replace .project

endlocal
pause
exit

:replace
for /f "tokens=1* delims=:" %%a in ('findstr /n .* "%1"') do (
  if "%%b"=="" (
    echo\>>tmp.txt
  ) else (
    set "var=%%b"
    set "var=!var:HelloWorld=%PROJECT_NAME%!"
    echo !var!>>tmp.txt
  )
)
move tmp.txt %1
