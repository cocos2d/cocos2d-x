call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyCppGame/proj.win8.1-universal/MyCppGame.sln  /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
