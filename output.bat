@echo off

REM export source code from dir %1 to dir %2

IF NOT DEFINED OUTPUT_BY_SVN GOTO AFTER_OUTPUT_BY_SVN
    svn export -r BASE --force %1 %2
    GOTO FILE_RETURN
:AFTER_OUTPUT_BY_SVN

IF NOT EXIST %2 MD %2
COPY /Y %1\*.* %2

:FILE_RETURN
