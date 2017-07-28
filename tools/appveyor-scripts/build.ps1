& msbuild $env:APPVEYOR_BUILD_FOLDER\build\cocos2d-win32.sln /t:Build /p:Platform="Win32" /p:Configuration="Release" /m
if ($lastexitcode -ne 0) {throw}