@echo off
set DIR=%~dp0

if not exist %DIR%test\LuaJavaBridge (call %DIR%create_test_project.bat)
    
call %DIR%test\LuaJavaBridge\frameworks\runtime-src\proj.android\build_apk.bat -bldm release