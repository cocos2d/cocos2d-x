#ifndef _TEXTURECACHE_TEST_H_
#define _TEXTURECACHE_TEST_H_


#include "cocos2d.h"
#include "../testBasic.h"
#include "platform/platform.h"

class TextureCacheTest : public CCLayer
{
public:
    TextureCacheTest();
    void addSprite();
    void loadingCallBack(cocos2d::CCObject *obj);

private:
    cocos2d::CCLabelTTF *_labelLoading;
    cocos2d::CCLabelTTF *_labelPercent;
    int _numberOfSprites;
    int _numberOfLoadedSprites;
};

class TextureCacheTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _TEXTURECACHE_TEST_H_
