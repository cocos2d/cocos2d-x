call "%VS120COMNTOOLS%vsvars32.bat"
msbuild build\cocos2d-win8.1-universal.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
