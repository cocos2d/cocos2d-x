// enable log
#define COCOS2D_DEBUG 1

#include "TextureCacheTest.h"

USING_NS_CC;

TextureCacheTest::TextureCacheTest()
: _numberOfSprites(20)
, _numberOfLoadedSprites(0)
{
    Size size = Director::getInstance()->getWinSize();

    _labelLoading = LabelTTF::create("loading...", "Arial", 15);
    _labelPercent = LabelTTF::create("%0", "Arial", 15);

    _labelLoading->setPosition(Point(size.width / 2, size.height / 2 - 20));
    _labelPercent->setPosition(Point(size.width / 2, size.height / 2 + 20));

    this->addChild(_labelLoading);
    this->addChild(_labelPercent);

    // load textrues
    TextureCache::getInstance()->addImageAsync("Images/HelloWorld.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_01.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_02.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_03.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_04.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_05.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_06.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_07.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_08.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_09.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_10.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_11.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_12.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_13.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/grossini_dance_14.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/background1.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/background2.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/background3.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    TextureCache::getInstance()->addImageAsync("Images/blocks.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
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
    Size size = Director::getInstance()->getWinSize();

    // create sprites

    Sprite *bg = Sprite::create("Images/HelloWorld.png");
    bg->setPosition(Point(size.width / 2, size.height / 2));

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

    s1->setPosition(Point(50, 50));
    s2->setPosition(Point(60, 50));
    s3->setPosition(Point(70, 50));
    s4->setPosition(Point(80, 50));
    s5->setPosition(Point(90, 50));
    s6->setPosition(Point(100, 50));

    s7->setPosition(Point(50, 180));
    s8->setPosition(Point(60, 180));
    s9->setPosition(Point(70, 180));
    s10->setPosition(Point(80, 180));
    s11->setPosition(Point(90, 180));
    s12->setPosition(Point(100, 180));

    s13->setPosition(Point(50, 270));
    s14->setPosition(Point(60, 270));
    s15->setPosition(Point(70, 270));

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
    Layer* layer = new TextureCacheTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
