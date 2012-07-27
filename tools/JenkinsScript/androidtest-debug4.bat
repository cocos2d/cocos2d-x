::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::Here are the environment variables you should set.
::%ANT_HOME% %ANDROID_HOME% %JAVA_HOME% %CYGWIN% %GITBIN% %ANDROID_NDK% 
:: Don't change it until you know what you do.

::In order to prevent the problem of permission,make the current user group get the ownership of project.
::Set the current user name.
::set _USERNAME=

set _PROJECTNAME=TestCpp
cd ..\..

:project
::Copy build Configuration files to target directory
copy %cd%\tools\JenkinsScript\ant.properties %cd%\samples\%_PROJECTNAME%\proj.android
copy %cd%\tools\JenkinsScript\build.xml %cd%\samples\%_PROJECTNAME%\proj.android
copy %cd%\tools\JenkinsScript\rootconfig.sh %cd%\samples\%_PROJECTNAME%\proj.android

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

for /f "delims=" %%a in ('findstr /i "target=android-" ant.properties') do set xx=%%a
echo %xx%
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="%xx%" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Change API level.(API level:14)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-8" (echo/target=android-14)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:14).
call ant debug
set result14=%ERRORLEVEL%

::Change API level.(API level:15)
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-14" (echo/target=android-15)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Android ant build(debug,API level:15).
call ant debug
set result15=%ERRORLEVEL%

::After all test versions completed,changed current API level to the original.(API level:8) 
for /f "delims=" %%a in (ant.properties) do (
if "%%a"=="target=android-15" (echo/target=android-8)else echo/%%a 
)>>"anttmp.properties"
move anttmp.properties ant.properties

::Calculate the errorlevel and change build target.
cd ../../..
IF "%_PROJECTNAME%"=="TestCpp" set /a testresult1=(result8+result10+result11+result12+result13) && set _PROJECTNAME=HelloCpp&& goto project
IF "%_PROJECTNAME%"=="HelloCpp" set /a testresult2=(result8+result10+result11+result12+result13) && set _PROJECTNAME=HelloLua&& goto project
IF "%_PROJECTNAME%"=="HelloLua" set /a testresult3=(result8+result10+result11+result12+result13)
set /a testresult=(testresult1+result2+result3)
IF %testresult% NEQ 0 goto error

goto success

:error
echo Error.
git checkout -f|%GITBIN%\sh.exe --login
git clean -df -x|%GITBIN%\sh.exe --login
pause
exit 1
goto end

:success
echo Success.
git checkout -f|%GITBIN%\sh.exe --login
git clean -df|%GITBIN%\sh.exe --login
pause
exit 0
goto end

::End.