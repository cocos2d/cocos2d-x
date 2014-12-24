@echo off
set DIR=%~dp0

if {"%VS120COMNTOOLS%"}=={""} goto no_vs120
set VS_TOOL_DIR=%VS120COMNTOOLS%
goto vs_ok

:no_vs120
if {"%VS110COMNTOOLS%"}=={""} goto no_vs
set VS_TOOL_DIR=%VS110COMNTOOLS%
goto vs_ok

:no_vs
echo --------------------------------------------------------
echo ERROR: VS is not found. Please install vs2012 or vs2013.
echo --------------------------------------------------------
goto end

:vs_ok
set VS_DIR="%VS_TOOL_DIR%..\..\"
set VC_BIN_DIR="%VS_DIR%VC\bin\"
call "%VC_BIN_DIR%vcvars32.bat"
cd %DIR%
cl /O2 /W3 /c /DLUA_BUILD_AS_DLL /DWIN32 *.c
del lua.obj
link /out:luac.exe *.obj

:end