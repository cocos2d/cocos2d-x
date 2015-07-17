call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyCppGame/proj.win32/MyCppGame.sln  /t:Build /p:VisualStudioVersion=12.0 /p:Platform="Win32" /p:Configuration="Release" /m
