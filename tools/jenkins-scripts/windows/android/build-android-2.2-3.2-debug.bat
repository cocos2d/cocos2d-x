::This script is used to accomplish a android automated compile.
::You should make sure have accomplished the environment settings.
:: Don't change it until you know what you do.

::Here are the environment variables you should set.
::%ANT_HOME% %ANDROID_HOME% %JAVA_HOME% %CYGWIN% %ANDROID_NDK% 
echo off
if not exist "%CYGWIN%" echo Couldn't find Cygwin at "%CYGWIN%" and you should set it like this "C:\cygwin"& pause & exit 1
if not exist "%ANDROID_HOME%" echo Couldn't find ANDROID_HOME at "%ANDROID_HOME%" and you should set it like this "D:\xx\android-sdk-windows"& pause & exit 2
if not exist "%ANDROID_NDK%" echo Couldn't find Cygwin at "%ANDROID_NDK%" and you should set it like this "D:\xx\android-ndk-r8"& pause & exit 3
if not exist "%JAVA_HOME%" echo Couldn't find Cygwin at "%JAVA_HOME%" and you should set it like it this "C:\xx\jdk1.7.0_05"& pause & exit 4
if not exist "%ANT_HOME%" echo Couldn't find Ant at "%ANT_HOME%" and you should set it like this "D:\xx\apache-ant-1.8.4" $ pause $ exit 5

set _PROJECTNAME=TestCpp
set _LANGUAGE_=Cpp
set _ROOT_=%cd%\..\..\..\..
cd %_ROOT_%

:project
::Copy build Configuration files to target directory
copy %_ROOT_%\tools\jenkins_scripts\ant.properties %_ROOT_%\samples\%_LANGUAGE_%\%_PROJECTNAME%\proj.android /Y
copy %_ROOT_%\tools\jenkins_scripts\build.xml %_ROOT_%\samples\%_LANGUAGE_%\%_PROJECTNAME%\proj.android /Y
copy %_ROOT_%\tools\jenkins_scripts\windows\android\rootconfig.sh %_ROOT_%\samples\%_LANGUAGE_%\%_PROJECTNAME%\proj.android /Y

::Modify the configuration files
cd %_ROOT_%\samples\%_LANGUAGE_%\%_PROJECTNAME%\proj.android
rootconfig.sh %_PROJECTNAME%
cd ..
set _PROJECTLOCATION=%cd%

::A command line that make the current user get the ownrship of project.
::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F

::Use cygwin compile the source code.
cygpath "%_PROJECTLOCATION%\proj.android\build_native.sh"|call %CYGWIN%\Cygwin.bat

::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F
::echo "%_PROJECTION%/proj.android/build_native.sh"|call %CYGWIN%\Cygwin.bat

::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F
call android update project -p proj.android
cd proj.android

::Make sure the original android build target is android-8
for /f "delims=" %%a in ('findstr /i "target=android-" ant.properties') do set xx=%%a
echo %xx%
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="%xx%" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:8).
call ant debug
set result8=%ERRORLEVEL%
if "%_PROJECTNAME%" NEQ "TestCpp" goto API_10
if %result8% NEQ 0 goto API_10
cd bin
ren TestCpp-debug.apk TestCpp-debug-8.apk
cd ..

:API_10
::Change API level.(API level:10)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-8" (echo/target=android-10)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:10).
call ant debug
set result10=%ERRORLEVEL%
if "%_PROJECTNAME%" NEQ "TestCpp" goto API_11
if %result10% NEQ 0 goto API_11
cd bin
ren TestCpp-debug.apk TestCpp-debug-10.apk
cd ..

:API_11
::Change API level.(API level:11)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-10" (echo/target=android-11)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:11).
call ant debug
set result11=%ERRORlEVEL%
if "%_PROJECTNAME%" NEQ "TestCpp" goto API_12
if %result11% NEQ 0 goto API_12
cd bin
ren TestCpp-debug.apk TestCpp-debug-11.apk
cd ..

:API_12
::Change API level.(API level:12)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-11" (echo/target=android-12)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:12).
call ant debug
set result12=%ERRORLEVEL%
if "%_PROJECTNAME%" NEQ "TestCpp" goto API_13
if %result12% NEQ 0 goto API_13
cd bin
ren TestCpp-debug.apk TestCpp-debug-12.apk
cd ..

:API_13
::Change API level.(API level:13)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-12" (echo/target=android-13)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:13).
call ant debug
set result13=%ERRORLEVEL%
if "%_PROJECTNAME%" NEQ "TestCpp" goto NEXTPROJ
if %result13% NEQ 0 goto NEXTPROJ
cd bin
ren TestCpp-debug.apk TestCpp-debug-13.apk
cd ..

:NEXTPROJ
::After all test versions completed,changed current API level to the original.(API level:8) 
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-13" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Calculate the errorlevel and change build target.
cd %_ROOT_%
if "%_PROJECTNAME%"=="TestCpp" set /a TestCpp_Result=(result8+result10+result11+result12+result13) && set _PROJECTNAME=HelloCpp&& goto project
if "%_PROJECTNAME%"=="HelloCpp" set /a HelloCpp_Result=(result8+result10+result11+result12+result13) && set _LANGUAGE_=Lua&& set _PROJECTNAME=HelloLua&& goto project
if "%_PROJECTNAME%"=="HelloLua" set /a HelloLua_Result=(result8+result10+result11+result12+result13)
set /a Compile_Result=(TestCpp_Result+HelloCpp_Result+HelloLua_Result)
if %Compile_Result% NEQ 0 goto error

goto success

:error
echo Compile Error!
echo %Compile_Result%
::git checkout -f
::git clean -df -x
exit 1

:success
echo Compile Success!
echo %Compile_Result%
::git checkout -f
::git clean -df -x
exit 0

::End.