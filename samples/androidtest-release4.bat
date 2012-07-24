::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::Here are the environment variables you should set.
::%ANT_HOME% %ANDROID_SDK% %JAVA_HOME% %CYGWIN%.
:: Don't change it until you know what you do.

::In order to prevent the problem of permission,make the current user group get the ownership of project.
::Set the current user name.
::set _USERNAME=Caidongyang
set _PROJECTLOCATION=C:\jenkins\jobs\Ant\workspace\cocos2d-x\samples
set _PROJECTNAME=TestCpp

cd %_PROJECTNAME%

::A command line that make the current user get the ownrship of project.
::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F

::Use cygwin compile the source code.
echo "%_PROJECTLOCATION%\%_PROjECTNAME%\proj.android/build_native.sh"|call %CYGWIN%\Cygwin.bat

::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F
::echo "%_PROJECTION%/proj.android/build_native.sh"|call %CYGWIN%\Cygwin.bat

::cacls proj.android\*.* /T /E /C /P %_USERNAME%:F
cd proj.android

for /f "delims=" %%a in ('findstr /i "target=android-" ant.properties') do set xx=%%a
echo %xx%
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="%xx%" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(release,API level:8).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::Change API level.(API level:10)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-8" (echo/target=android-10)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:10).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::Change API level.(API level:11)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-10" (echo/target=android-11)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:11).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::Change API level.(API level:12)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-11" (echo/target=android-12)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:12).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::Change API level.(API level:13)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-12" (echo/target=android-13)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:13).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::After all test versions completed,changed current API level to the original.(API level:8) 
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-13" (echo/target=android-8)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

goto success

:lis
if "%num%"=="" goto :eof
if "%num:~-1%"==" " set num=%num:~0,-1%&goto lis
echo %num%>>ant1.properties
goto :eof 

:error
echo Error.
pause
exit 1
goto end

:success
echo Success.
pause
exit 0
goto end

::End.
:end