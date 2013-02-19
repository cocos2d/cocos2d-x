#include "ZwoptexTest.h"
#include "../testResource.h"

#define MAX_LAYER    1

static int sceneIdx = -1;

CCLayer* nextZwoptexTest();
CCLayer* backZwoptexTest();
CCLayer* restartZwoptexTest();

CCLayer* createZwoptexLayer(int nIndex)
{
    switch(nIndex)
    {
    case 0: return new ZwoptexGenericTest();
    }

    return NULL;
}

CCLayer* nextZwoptexTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createZwoptexLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backZwoptexTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    CCLayer* pLayer = createZwoptexLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartZwoptexTest()
{
    CCLayer* pLayer = createZwoptexLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 

//------------------------------------------------------------------
//
// ZwoptexTest
//
//------------------------------------------------------------------
void ZwoptexTest::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 26);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-50));
    
    std::string strSubTitle = subtitle();
    if (strSubTitle.length() > 0)
    {
        CCLabelTTF *l = CCLabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }
    
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ZwoptexTest::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ZwoptexTest::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ZwoptexTest::nextCallback) );
    
    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    addChild(menu, 1);
}

void ZwoptexTest::restartCallback(CCObject* pSender)
{
    CCScene *s = ZwoptexTestScene::create();
    s->addChild(restartZwoptexTest());
    CCDirector::sharedDirector()->replaceScene(s);
}

void ZwoptexTest::nextCallback(CCObject* pSender)
{
    CCScene *s = ZwoptexTestScene::create();
    s->addChild(nextZwoptexTest());
    CCDirector::sharedDirector()->replaceScene(s);
}

void ZwoptexTest::backCallback(CCObject* pSender)
{
    CCScene *s = ZwoptexTestScene::create();
    s->addChild(backZwoptexTest());
    CCDirector::sharedDirector()->replaceScene(s);
}

std::string ZwoptexTest::title()
{
    return "No title";
}

std::string ZwoptexTest::subtitle()
{
    return "";
}

//------------------------------------------------------------------
//
// ZwoptexGenericTest
//
//------------------------------------------------------------------
void ZwoptexGenericTest::onEnter()
{
    ZwoptexTest::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini-generic.plist");
    
    CCLayerColor *layer1 = CCLayerColor::create(ccc4(255, 0, 0, 255), 85, 121);
    layer1->setPosition(ccp(s.width/2-80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer1);

    sprite1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grossini_dance_01.png"));
    sprite1->setPosition(ccp( s.width/2-80, s.height/2));
    addChild(sprite1);

    sprite1->setFlipX(false);
    sprite1->setFlipY(false);

    CCLayerColor *layer2 = CCLayerColor::create(ccc4(255, 0, 0, 255), 85, 121);
    layer2->setPosition(ccp(s.width/2+80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer2);
    
    sprite2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grossini_dance_generic_01.png"));
    sprite2->setPosition(ccp( s.width/2 + 80, s.height/2));
    addChild(sprite2);

    sprite2->setFlipX(false);
    sprite2->setFlipY(false);

    schedule(schedule_selector(ZwoptexGenericTest::startIn05Secs), 1.0f);
    
    sprite1->retain();
    sprite2->retain();

    counter = 0;
}

void ZwoptexGenericTest::startIn05Secs(float dt)
{
    unschedule(schedule_selector(ZwoptexGenericTest::startIn05Secs));
    schedule(schedule_selector(ZwoptexGenericTest::flipSprites), 0.5f);
}

static int spriteFrameIndex = 0;
void ZwoptexGenericTest::flipSprites(float dt)
{
    counter++;

    bool fx = false;
    bool fy = false;
    int i = counter % 4;

    switch ( i )
    {
        case 0:
            fx = false;
            fy = false;
            break;
        case 1:
            fx = true;
            fy = false;
            break;
        case 2:
            fx = false;
            fy = true;
            break;
        case 3:
            fx = true;
            fy = true;
            break;
    }

    sprite1->setFlipX(fx);
    sprite2->setFlipX(fx);
    sprite1->setFlipY(fy);
    sprite2->setFlipY(fy);

    if(++spriteFrameIndex > 14)
    {
        spriteFrameIndex = 1;
    }

    char str1[32] = {0};
    char str2[32] = {0};
    sprintf(str1, "grossini_dance_%02d.png", spriteFrameIndex);
    sprintf(str2, "grossini_dance_generic_%02d.png", spriteFrameIndex);
    sprite1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str1));
    sprite2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str2));
}

ZwoptexGenericTest::~ZwoptexGenericTest()
{
    sprite1->release();
    sprite2->release();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->removeSpriteFramesFromFile("zwoptex/grossini.plist");
    cache->removeSpriteFramesFromFile("zwoptex/grossini-generic.plist");
}

std::string ZwoptexGenericTest::title()
{
    return "Zwoptex Tests";
}

std::string ZwoptexGenericTest::subtitle()
{
    return "Coordinate Formats, Rotation, Trimming, flipX/Y";
}

void ZwoptexTestScene::runThisTest()
{
    CCLayer* pLayer = nextZwoptexTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
