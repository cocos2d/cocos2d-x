@echo off
:: copy libs to HelloWorld project
copy Box2D\proj.bada\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy chipmunk\proj.bada\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy CocosDenshion\proj.bada\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\proj.bada\sdk1.2\.Simulator-Debug\*.a HelloWorld\bada\sdk1.2\lib\Simulator-Debug

copy Box2D\proj.bada\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy chipmunk\proj.bada\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy CocosDenshion\proj.bada\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug
copy cocos2dx\proj.bada\sdk1.2\.Target-Debug\*.a HelloWorld\bada\sdk1.2\lib\Target-Debug

copy Box2D\proj.bada\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy chipmunk\proj.bada\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy CocosDenshion\proj.bada\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release
copy cocos2dx\proj.bada\sdk1.2\.Target-Release\*.a HelloWorld\bada\sdk1.2\lib\Target-Release

:: copy libs to tests project

copy Box2D\proj.bada\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy chipmunk\proj.bada\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy CocosDenshion\proj.bada\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug
copy cocos2dx\proj.bada\sdk1.2\.Simulator-Debug\*.a tests\test.bada\sdk1.2\lib\Simulator-Debug

copy Box2D\proj.bada\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy chipmunk\proj.bada\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy CocosDenshion\proj.bada\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug
copy cocos2dx\proj.bada\sdk1.2\.Target-Debug\*.a tests\test.bada\sdk1.2\lib\Target-Debug

copy Box2D\proj.bada\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy chipmunk\proj.bada\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy CocosDenshion\proj.bada\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\libjpeg\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\png\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy cocos2dx\platform\third_party\bada\src\zlib\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release
copy cocos2dx\proj.bada\sdk1.2\.Target-Release\*.a tests\test.bada\sdk1.2\lib\Target-Release

pause