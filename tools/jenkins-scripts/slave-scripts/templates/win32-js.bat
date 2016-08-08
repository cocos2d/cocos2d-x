call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyJSGame/frameworks/runtime-src/proj.win32/MyJSGame.sln  /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
