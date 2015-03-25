call "%VS120COMNTOOLS%vsvars32.bat"
msbuild build\cocos2d-wp8.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
