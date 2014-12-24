@echo off
set DIR=%~dp0
if not exist %DIR%test mkdir %DIR%test

set CURDIR=%DIR%
call %QUICK_V3_ROOT%quick/bin/create_project.bat -p com.quick-x.samples.towerdefense -o %DIR%test\towerdefense -r landscape -lt
set DIR=%CURDIR%
rmdir /s /q %DIR%test\towerdefense\runtime
rmdir /s /q %DIR%test\towerdefense\frameworks\runtime-src\proj.ios_mac
rmdir /s /q %DIR%test\towerdefense\frameworks\runtime-src\proj.win32
rmdir /s /q %DIR%test\towerdefense\frameworks\runtime-src\proj.wp8-xaml
rmdir /s /q %DIR%test\towerdefense\frameworks\runtime-src\proj.android
move %DIR%test\towerdefense\frameworks\runtime-src\proj.android_no_anysdk %DIR%test\towerdefense\frameworks\runtime-src\proj.android
copy %DIR%AppActivity.java %DIR%test\towerdefense\frameworks\runtime-src\proj.android\src\org\cocos2dx\lua\
rmdir /s /q %DIR%test\towerdefense\res\fonts
del /q %DIR%test\towerdefense\res\*.*
rmdir /s /q %DIR%test\towerdefense\src\app
del /q %DIR%test\towerdefense\src\*.lua
xcopy /s /q %DIR%src\*.* %DIR%test\towerdefense\src\