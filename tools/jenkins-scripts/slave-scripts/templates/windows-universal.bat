@echo on

set mycocos=tools/cocos2d-console/bin/cocos.bat
set language=%1
call %mycocos% new -l %language%

set projectname=
if "%language%"=="cpp" set projectname=MyCppGame/proj.win8.1-universal/MyCppGame.sln 
if "%language%"=="lua" set projectname=MyLuaGame/frameworks/runtime-src/proj.win8.1-universal/MyLuaGame.sln
if "%language%"=="js" set projectname=MyJSGame/frameworks/runtime-src/proj.win8.1-universal/MyJSGame.sln

echo %projectname%
call "%VS120COMNTOOLS%vsvars32.bat"
msbuild %projectname% /t:Build
