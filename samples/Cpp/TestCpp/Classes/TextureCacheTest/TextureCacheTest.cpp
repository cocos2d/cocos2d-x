// enable log
#define COCOS2D_DEBUG 1

#include "TextureCacheTest.h"

USING_NS_CC;

TextureCacheTest::TextureCacheTest()
: _numberOfSprites(20)
, _numberOfLoadedSprites(0)
{
    Size size = Director::sharedDirector()->getWinSize();

    _labelLoading = LabelTTF::create("loading...", "Arial", 15);
    _labelPercent = LabelTTF::create("%0", "Arial", 15);

    _labelLoading->setPosition(ccp(size.width / 2, size.height / 2 - 20));
    _labelPercent->setPosition(ccp(size.width / 2, size.height / 2 + 20));

    this->addChild(_labelLoading);
    this->addChild(_labelPercent);

    // load textrues
    TextureCache::sharedTextureCache()->addImageAsync("Images/HelloWorld.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_01.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_02.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_03.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_04.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_05.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_06.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_07.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_08.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_09.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_10.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_11.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_12.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_13.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_14.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/background1.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/background2.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/background3.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::sharedTextureCache()->addImageAsync("Images/blocks.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
}

void TextureCacheTest::loadingCallBack(Object *obj)
{
    ++_numberOfLoadedSprites;
    char tmp[10];
    sprintf(tmp,"%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
    _labelPercent->setString(tmp);

    if (_numberOfLoadedSprites == _numberOfSprites)
    {
        this->removeChild(_labelLoading, true);
        this->removeChild(_labelPercent, true);
        addSprite();
    }
}

void TextureCacheTest::addSprite()
{
    Size size = Director::sharedDirector()->getWinSize();

    // create sprites

    Sprite *bg = Sprite::create("Images/HelloWorld.png");
    bg->setPosition(ccp(size.width / 2, size.height / 2));

    Sprite *s1 = Sprite::create("Images/grossini.png");
    Sprite *s2 = Sprite::create("Images/grossini_dance_01.png");
    Sprite *s3 = Sprite::create("Images/grossini_dance_02.png");
    Sprite *s4 = Sprite::create("Images/grossini_dance_03.png");
    Sprite *s5 = Sprite::create("Images/grossini_dance_04.png");
    Sprite *s6 = Sprite::create("Images/grossini_dance_05.png");
    Sprite *s7 = Sprite::create("Images/grossini_dance_06.png");
    Sprite *s8 = Sprite::create("Images/grossini_dance_07.png");
    Sprite *s9 = Sprite::create("Images/grossini_dance_08.png");
    Sprite *s10 = Sprite::create("Images/grossini_dance_09.png");
    Sprite *s11 = Sprite::create("Images/grossini_dance_10.png");
    Sprite *s12 = Sprite::create("Images/grossini_dance_11.png");
    Sprite *s13 = Sprite::create("Images/grossini_dance_12.png");
    Sprite *s14 = Sprite::create("Images/grossini_dance_13.png");
    Sprite *s15 = Sprite::create("Images/grossini_dance_14.png");

    // just loading textures to slow down
    Sprite::create("Images/background1.png");
    Sprite::create("Images/background2.png");
    Sprite::create("Images/background3.png");
    Sprite::create("Images/blocks.png");

    s1->setPosition(ccp(50, 50));
    s2->setPosition(ccp(60, 50));
    s3->setPosition(ccp(70, 50));
    s4->setPosition(ccp(80, 50));
    s5->setPosition(ccp(90, 50));
    s6->setPosition(ccp(100, 50));

    s7->setPosition(ccp(50, 180));
    s8->setPosition(ccp(60, 180));
    s9->setPosition(ccp(70, 180));
    s10->setPosition(ccp(80, 180));
    s11->setPosition(ccp(90, 180));
    s12->setPosition(ccp(100, 180));

    s13->setPosition(ccp(50, 270));
    s14->setPosition(ccp(60, 270));
    s15->setPosition(ccp(70, 270));

    this->addChild(bg);
   
    this->addChild(s1);
    this->addChild(s2);
    this->addChild(s3);
    this->addChild(s4);
    this->addChild(s5);
    this->addChild(s6);
    this->addChild(s7);
    this->addChild(s8);
    this->addChild(s9);
    this->addChild(s10);
    this->addChild(s11);
    this->addChild(s12);
    this->addChild(s13);
    this->addChild(s14);
    this->addChild(s15);
}


void TextureCacheTestScene::runThisTest()
{
    Layer* pLayer = new TextureCacheTest();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
    pLayer->release();
}
