::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::Here are the environment variables you should set.
::%ANT_HOME% %ANDROID_HOME% %JAVA_HOME% %CYGWIN% %GITBIN% %ANDROID_NDK% 
:: Don't change it until you know what you do.

if not exist "%CYGWIN%" echo Couldn't find Cygwin at "%CYGWIN%" and you should set like this "C:\cygwin"& pause & exit 1
if not exist "%GITBIN%" echo Couldn't find Gitbin at "%GITBIN%" and you should set like this "F:\Git\bin"& pause & exit 2
if not exist "%ANDROID_HOME%" echo Couldn't find ANDROID_HOME at "%ANDROID_HOME%" and you should set like this "D:\Windows7\android-sdk-windows"& pause & exit 3
if not exist "%ANDROID_NDK%" echo Couldn't find Cygwin at "%ANDROID_NDK%" and you should set like this "D:\Windows7\android-ndk-r8"& pause & exit 4
if not exist "%JAVA_HOME%" echo Couldn't find Cygwin at "%JAVA_HOME%" and you should set like this "C:\Program Files\Java\jdk1.7.0_05"& pause & exit 5

set _PROJECTNAME=TestCpp
cd ..\..\..\..

:project
::Copy build Configuration files to target directory
copy %cd%\tools\JenkinsScript\ant.properties %cd%\samples\%_PROJECTNAME%\proj.android
copy %cd%\tools\JenkinsScript\build.xml %cd%\samples\%_PROJECTNAME%\proj.android
copy %cd%\tools\JenkinsScript\Windows\android\rootconfig.sh %cd%\samples\%_PROJECTNAME%\proj.android

::Modify the configuration files
cd samples\%_PROJECTNAME%\proj.android
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
set result8=%ERROELEVEL%

::Change API level.(API level:10)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-8" (echo/target=android-10)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:10).
call ant debug
set result10=%ERRORLEVEL%

::Change API level.(API level:11)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-10" (echo/target=android-11)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:11).
call ant debug
set result11=%ERRORlEVEL%

::Change API level.(API level:12)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-11" (echo/target=android-12)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:12).
call ant debug
set result12=%ERRORLEVEL%

::Change API level.(API level:13)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-12" (echo/target=android-13)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:13).
call ant debug
set result13=%ERRORLEVEL%

::After all test versions completed,changed current API level to the original.(API level:8) 
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-13" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Calculate the errorlevel and change build target.
cd ..\..\..
IF "%_PROJECTNAME%"=="TestCpp" set /a testresult1=(result8+result10+result11+result12+result13) && set _PROJECTNAME=HelloCpp&& goto project
IF "%_PROJECTNAME%"=="HelloCpp" set /a testresult2=(result8+result10+result11+result12+result13) && set _PROJECTNAME=HelloLua&& goto project
IF "%_PROJECTNAME%"=="HelloLua" set /a testresult3=(result8+result10+result11+result12+result13)
set /a testresult=(testresult1+testresult2+testresult3)
IF %testresult% NEQ 0 goto error

goto success

:error
echo Error.
git checkout -f
git clean -df -x
pause
exit 1
goto end

:success
echo Success.
git checkout -f
git clean -df -x
pause
exit 0
goto end

::End.