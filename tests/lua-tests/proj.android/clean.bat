@echo off

set DIR=%~dp0
rmdir /s/q %DIR%obj
rmdir /s/q %DIR%libs\armeabi
rmdir /s/q %DIR%assets

