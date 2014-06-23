@echo off
set DIR=%~dp0
cd "%DIR%.."
call %DIR%compile_scripts.bat -i framework -o lib\framework_precompiled\framework_precompiled.zip -p framework -m zip


echo.
echo ### UPDATING ###
echo.
echo updating all framework_precompiled.zip
echo.

dir /s/b samples | find "framework_precompiled.zip" > ___tmp___
dir /s/b template | find "framework_precompiled.zip" >> ___tmp___

for /f %%f in (___tmp___) do (
    echo %%f
    copy lib\framework_precompiled\framework_precompiled.zip %%f > NUL
)

del ___tmp___

echo.
echo DONE
echo.
