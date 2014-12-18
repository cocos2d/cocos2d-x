@echo off
set DIR=%~dp0
if not exist %DIR%test mkdir %DIR%test

set CURDIR=%DIR%
call %QUICK_V3_ROOT%quick/bin/create_project.bat -p com.quick-x.samples.Homeland2_Map_Editor -o %DIR%test\Homeland2_Map_Editor -r landscape -lt
set DIR=%CURDIR%
rmdir /s /q %DIR%test\Homeland2_Map_Editor\runtime
rmdir /s /q %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.ios_mac
rmdir /s /q %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.win32
rmdir /s /q %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.wp8-xaml
rmdir /s /q %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.android
move %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.android_no_anysdk %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.android
copy %DIR%AppActivity.java %DIR%test\Homeland2_Map_Editor\frameworks\runtime-src\proj.android\src\org\cocos2dx\lua\
rmdir /s /q %DIR%test\Homeland2_Map_Editor\res\fonts
del /q %DIR%test\Homeland2_Map_Editor\res\*.*
rmdir /s /q %DIR%test\Homeland2_Map_Editor\src\app
del /q %DIR%test\Homeland2_Map_Editor\src\*.lua
xcopy /s /q %DIR%src\*.* %DIR%test\Homeland2_Map_Editor\src\