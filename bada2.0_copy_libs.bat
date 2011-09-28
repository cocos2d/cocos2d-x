@echo off
:: copy libs to HelloWorld project
copy Box2D\proj.bada\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy chipmunk\proj.bada\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy CocosDenshion\proj.bada\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug
copy cocos2dx\proj.bada\sdk2.0\.Target-Debug\*.a HelloWorld\bada\sdk2.0\lib\Target-Debug

copy Box2D\proj.bada\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy chipmunk\proj.bada\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy CocosDenshion\proj.bada\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\png\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\zlib\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release
copy cocos2dx\proj.bada\sdk2.0\.Target-Release\*.a HelloWorld\bada\sdk2.0\lib\Target-Release

:: copy libs to tests project
copy Box2D\proj.bada\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy chipmunk\proj.bada\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy CocosDenshion\proj.bada\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug
copy cocos2dx\proj.bada\sdk2.0\.Target-Debug\*.a tests\test.bada\sdk2.0\lib\Target-Debug

copy Box2D\proj.bada\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy chipmunk\proj.bada\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy CocosDenshion\proj.bada\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\png\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\zlib\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release
copy cocos2dx\proj.bada\sdk2.0\.Target-Release\*.a tests\test.bada\sdk2.0\lib\Target-Release

pause