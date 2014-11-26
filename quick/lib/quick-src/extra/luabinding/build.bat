@echo off
set DIR=%~dp0
set OUTPUT_DIR=%DIR%
set MAKE_LUABINDING="%QUICK_V3_ROOT%quick\bin\compile_luabinding.bat"
pushd
cd "%DIR%"
call %MAKE_LUABINDING% -E CCOBJECTS=CCHTTPRequest -pfx cc -d %OUTPUT_DIR% cocos2dx_extra_luabinding.tolua
echo.
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo.
call %MAKE_LUABINDING% -pfx cc -d %OUTPUT_DIR% cocos2dx_extra_ios_iap_luabinding.tolua
echo.
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo.
call %MAKE_LUABINDING% -pfx cc -d %OUTPUT_DIR% HelperFunc_luabinding.tolua
popd
