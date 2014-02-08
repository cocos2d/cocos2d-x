@echo off

::!/bin/bash

:: Generate JS and Lua bindings for Cocos2D-X
:: ... using Android NDK system headers
:: ... and automatically update submodule references
:: ... and push these changes to remote repos

:: Dependencies
::
:: For bindings generator:
:: (see ../../../tojs/genbindings.sh and ../../../tolua/genbindings-win32.bat
:: ... for the defaults used if the environment is not customized)
::
::  * $PYTHON_BIN
::  * $CLANG_ROOT
::  * $NDK_ROOT
::
echo "[test]start generate js binding..."
set COCOS2DX_ROOT=%cd%/../..
set "COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/%"
set TO_JS_ROOT=%COCOS2DX_ROOT%/tools/tojs
set TO_LUA_ROOT=%COCOS2DX_ROOT%/tools/tolua
set GENERATED_WORKTREE=%COCOS2DX_ROOT%/cocos/scripting/auto-generated
set "GENERATED_WORKTREE=%GENERATED_WORKTREE:/=\%"

:: Run to_js genbindings
call %TO_JS_ROOT%/genbindings-win32.bat

:: Run to_lua genbindings
call %TO_LUA_ROOT%/genbindings-win32.bat

echo
echo Bindings generated successfully
echo