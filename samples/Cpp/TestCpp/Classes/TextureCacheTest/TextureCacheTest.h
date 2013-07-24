#ifndef _TEXTURECACHE_TEST_H_
#define _TEXTURECACHE_TEST_H_


#include "cocos2d.h"
#include "../testBasic.h"

class TextureCacheTest : public Layer
{
public:
    TextureCacheTest();
    void addSprite();
    void loadingCallBack(cc::Object *obj);

private:
    cc::LabelTTF *_labelLoading;
    cc::LabelTTF *_labelPercent;
    int _numberOfSprites;
    int _numberOfLoadedSprites;
};

class TextureCacheTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _TEXTURECACHE_TEST_H_
