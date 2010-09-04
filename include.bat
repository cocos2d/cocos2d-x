@echo off

mkdir d:\include

cd d:\work7\cocos2dx\cocos2dx\include
copy *.h d:\include

cd d:\work7\cocos2dx\cocos2dx\platform\uphone
setlocal enabledelayedexpansion
for %%i in (*_uphone.h) do (
	set filename=%%~ni
	copy "%%i" "d:\include\!filename:~0,-7!%%~xi
)
endlocal

pause