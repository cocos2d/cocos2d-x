#ifndef _TEXTURECACHE_TEST_H_
#define _TEXTURECACHE_TEST_H_


#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(TextureCacheTests);

class TextureCacheTest : public TestCase
{
public:
    CREATE_FUNC(TextureCacheTest);

    TextureCacheTest();

    void addSprite();
    void loadingCallBack(cocos2d::Texture2D *texture);

    virtual float getDuration() const override { return 3.5f; }
private:
    cocos2d::Label *_labelLoading;
    cocos2d::Label *_labelPercent;
    int _numberOfSprites;
    int _numberOfLoadedSprites;
};

#endif // _TEXTURECACHE_TEST_H_
