call "%VS120COMNTOOLS%vsvars32.bat"
msbuild build\cocos2d-wp8.sln /t:Build /p:Platform="Win32" /p:Configuration="Debug" /m
msbuild build\cocos2d-win8.1-universal.sln /t:Build /p:Platform="Win32" /p:Configuration="Debug" /m
