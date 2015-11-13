call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyCppGame/proj.win32/MyCppGame.sln  /t:Build  /p:Platform="Win32" /p:Configuration="Release" /m
