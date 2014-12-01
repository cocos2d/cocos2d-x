@echo off
set DIR=%~dp0
%QUICK_V3_ROOT%\quick\bin\win32\php.exe "%QUICK_V3_ROOT%/quick/bin/lib/build_apk.php" -pdir %DIR% %*
