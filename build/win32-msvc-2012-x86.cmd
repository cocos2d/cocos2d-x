@echo off
SETLOCAL

:start
mkdir win32-msvc-vs2012-x86
cd win32-msvc-vs2012-x86
cmake -G "Visual Studio 11" ../..
pause
