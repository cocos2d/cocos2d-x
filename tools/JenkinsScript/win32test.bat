::This script is used to finish a android automated compiler.
::You should make sure have finished the environment setting.
::Here are the environment variables you should set.
::%VS100COMNTOOLS% %VS90COMNTOOLS%
:: Don't change it until you know what you do.
"%VS100COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\TestCpp\proj.win32\TestCpp.vcxproj" /Build "Debug|Win32"
set resulttest_10=%ERRORLEVEL%
"%VS90COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\TestCpp\proj.win32\TestCpp.vcxproj" /Build "Debug|Win32"
set resulttest_08=%ERRORLEVEL%
"%VS100COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\HelloCpp\proj.win32\HelloCpp.vcxproj" /Build "Debug|Win32"
set resulthello_10=%ERRORLEVEL%
"%VS90COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\HelloCpp\proj.win32\HelloCpp.vcxproj" /Build "Debug|Win32"
set resulthello_08=%ERRORLEVEL%
"%VS100COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\HelloLua\proj.win32\HelloLua.vcxproj" /Build "Debug|Win32"
set resulthellolua_10=%ERRORLEVEL%
"%VS90COMNTOOLS%..\IDE\devenv.com" "%WORKSPACE%\samples\HelloLua\proj.win32\HelloLua.vcxproj" /Build "Debug|Win32"
set resulthellolua_08=%ERRORLEVEL%

cd ..\..
set /a testresult=(resulttest_10+resulttest_08+resulthello_10+resulthello_08+resulthellolua_10+resulthellolua_08)
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