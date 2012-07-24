::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::Here are the environment variables you should set.
::%ANT_HOME% %ANDROID_SDK% %JAVA_HOME% %CYGWIN%.
:: Don't change it until you know what you do.

::In order to prevent the problem of permission,make the current user group get the ownership of project.
::Set the current user name.
::set _USERNAME=Caidongyang
set _PROJECTLOCATION=C:\jenkins\jobs\Ant\workspace\cocos2d-x
set _PROJECTNAME=Tests

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

::Change API level.(API level:14)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-8" (echo/target=android-14)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:14).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::Change API level.(API level:15)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-14" (echo/target=android-15)else echo/%%a 
)>>"ant1.properties"
move ant1.properties ant.properties

for /f "delims=" %%a in (ant.properties) do set num=%%a&call :lis
move ant1.properties ant.properties

::Android ant build(release,API level:15).
call ant release
IF %ERRORLEVEL% NEQ 0 goto error

::After all test versions completed,changed current API level to the original.(API level:8) 
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-15" (echo/target=android-8)else echo/%%a 
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