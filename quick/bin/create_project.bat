@echo off
set DIR=%~dp0
rem call %DIR%_setenv.bat
set TEMPLATE_ROOT=%DIR%..\templates
%DIR%win32\php.exe "%DIR%lib\create_project.php" -t "%TEMPLATE_ROOT%\lua-template-quick" %*
