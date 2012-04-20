// enable log
#define COCOS2D_DEBUG 1

#include "TextureCacheTest.h"

using namespace cocos2d;

TextureCacheTest::TextureCacheTest()
: m_nNumberOfSprites(20)
, m_nNumberOfLoadedSprites(0)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_pLabelLoading = CCLabelTTF::labelWithString("loading...", "Arial", 15);
    m_pLabelPercent = CCLabelTTF::labelWithString("%0", "Arial", 15);

    m_pLabelLoading->setPosition(CCPointMake(size.width / 2, size.height / 2 - 20));
    m_pLabelPercent->setPosition(CCPointMake(size.width / 2, size.height / 2 + 20));

    this->addChild(m_pLabelLoading);
    this->addChild(m_pLabelPercent);

    // load textrues
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/HelloWorld.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_01.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_02.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_03.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_04.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_05.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_06.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_07.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_08.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_09.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_10.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_11.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_12.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_13.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/grossini_dance_14.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/background1.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/background2.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/background3.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
    CCTextureCache::sharedTextureCache()->addImageAsync("Images/blocks.png", this, callfuncO_selector(TextureCacheTest::loadingCallBack));
}

void TextureCacheTest::loadingCallBack(CCObject *obj)
{
    ++m_nNumberOfLoadedSprites;
    char tmp[10];
    sprintf(tmp,"%%%d", (int)(((float)m_nNumberOfLoadedSprites / m_nNumberOfSprites) * 100));
    m_pLabelPercent->setString(tmp);

    if (m_nNumberOfLoadedSprites == m_nNumberOfSprites)
    {
        this->removeChild(m_pLabelLoading, true);
        this->removeChild(m_pLabelPercent, true);
        addSprite();
    }
}

void TextureCacheTest::addSprite()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // create sprites

    CCSprite *bg = CCSprite::spriteWithFile("Images/HelloWorld.png");
    bg->setPosition(CCPointMake(size.width / 2, size.height / 2));

    CCSprite *s1 = CCSprite::spriteWithFile("Images/grossini.png");
    CCSprite *s2 = CCSprite::spriteWithFile("Images/grossini_dance_01.png");
    CCSprite *s3 = CCSprite::spriteWithFile("Images/grossini_dance_02.png");
    CCSprite *s4 = CCSprite::spriteWithFile("Images/grossini_dance_03.png");
    CCSprite *s5 = CCSprite::spriteWithFile("Images/grossini_dance_04.png");
    CCSprite *s6 = CCSprite::spriteWithFile("Images/grossini_dance_05.png");
    CCSprite *s7 = CCSprite::spriteWithFile("Images/grossini_dance_06.png");
    CCSprite *s8 = CCSprite::spriteWithFile("Images/grossini_dance_07.png");
    CCSprite *s9 = CCSprite::spriteWithFile("Images/grossini_dance_08.png");
    CCSprite *s10 = CCSprite::spriteWithFile("Images/grossini_dance_09.png");
    CCSprite *s11 = CCSprite::spriteWithFile("Images/grossini_dance_10.png");
    CCSprite *s12 = CCSprite::spriteWithFile("Images/grossini_dance_11.png");
    CCSprite *s13 = CCSprite::spriteWithFile("Images/grossini_dance_12.png");
    CCSprite *s14 = CCSprite::spriteWithFile("Images/grossini_dance_13.png");
    CCSprite *s15 = CCSprite::spriteWithFile("Images/grossini_dance_14.png");

    // just loading textures to slow down
    CCSprite::spriteWithFile("Images/background1.png");
    CCSprite::spriteWithFile("Images/background2.png");
    CCSprite::spriteWithFile("Images/background3.png");
    CCSprite::spriteWithFile("Images/blocks.png");

    s1->setPosition(CCPointMake(50, 50));
    s2->setPosition(CCPointMake(60, 50));
    s3->setPosition(CCPointMake(70, 50));
    s4->setPosition(CCPointMake(80, 50));
    s5->setPosition(CCPointMake(90, 50));
    s6->setPosition(CCPointMake(100, 50));

    s7->setPosition(CCPointMake(50, 180));
    s8->setPosition(CCPointMake(60, 180));
    s9->setPosition(CCPointMake(70, 180));
    s10->setPosition(CCPointMake(80, 180));
    s11->setPosition(CCPointMake(90, 180));
    s12->setPosition(CCPointMake(100, 180));

    s13->setPosition(CCPointMake(50, 270));
    s14->setPosition(CCPointMake(60, 270));
    s15->setPosition(CCPointMake(70, 270));

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
    CCLayer* pLayer = new TextureCacheTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
