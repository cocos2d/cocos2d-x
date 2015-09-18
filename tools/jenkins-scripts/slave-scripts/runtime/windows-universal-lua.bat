call "%VS120COMNTOOLS%vsvars32.bat"
msbuild MyLuaGame/frameworks/runtime-src/proj.win8.1-universal/MyLuaGame.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
