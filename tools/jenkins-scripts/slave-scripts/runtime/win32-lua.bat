call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyLuaGame/frameworks/runtime-src/proj.win32/MyLuaGame.sln  /t:Build /p:VisualStudioVersion=12.0 /p:Platform="Win32" /p:Configuration="Release" /m
