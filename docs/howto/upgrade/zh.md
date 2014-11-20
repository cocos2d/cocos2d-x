
升级到 quick-cocos2d-x 最新版
============================

## 从 2.2.5 升级到 3.3

下列函数或常量需要替换：

|                                         |                              |
|-----------------------------------------|------------------------------|
| CCLuaLog()                              | print()                      |
| CCFileUtils:sharedFileUtils()           | cc.FileUtils:getInstance()   |
| kCCTexture2DPixelFormat\_\*             | cc.TEXTURE2D_PIXEL_FORMAT\_\*|
| display.addSpriteFramesWithFile         | display.addSpriteFrames      |
| ccc3()                                  | cc.c3b()                     |
| ccc4()                                  | cc.c4b()                     |
| ccc4f()                                 | cc.c4f()                     |
| ccc4FFromccc4B()                        | cc.c4fFromc4b()              |
| getZOrder()                             | getLocalZOrder()             |
| setZOrder()                             | setLocalZOrder()             |
| setFlipX()                              | setFlippedX()                |
| setFlipY()                              | setFlippedY()                |


