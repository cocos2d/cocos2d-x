call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyJSGame/frameworks/runtime-src/proj.win8.1-universal/MyJSGame.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
