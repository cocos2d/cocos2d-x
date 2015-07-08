@echo on

set mycocos=tools/cocos2d-console/bin/cocos.bat
set language=%1
call %mycocos% new -l %language% -t runtime

set projectname=
if "%language%"=="cpp" set projectname=MyCppGame/proj.win32/MyCppGame.sln
if "%language%"=="lua" set projectname=MyLuaGame/frameworks/runtime-src/proj.win32/MyLuaGame.sln
if "%language%"=="js" set projectname=MyJSGame/frameworks/runtime-src/proj.win32/MyJSGame.sln

echo %projectname%
call "%VS120COMNTOOLS%vsvars32.bat"
msbuild %projectname% /t:Build  /m
