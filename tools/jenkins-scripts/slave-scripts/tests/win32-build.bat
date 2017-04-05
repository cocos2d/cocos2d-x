call "%VS120COMNTOOLS%vsvars32.bat"
msbuild build\cocos2d-win32.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
