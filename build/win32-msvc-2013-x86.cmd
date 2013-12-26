@echo off
SETLOCAL

:start
mkdir win32-msvc-vs2013-x86
cd win32-msvc-vs2013-x86
cmake -G "Visual Studio 12" ../..
pause
