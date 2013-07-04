#include "ZwoptexTest.h"
#include "../testResource.h"

#define MAX_LAYER    1

static int sceneIdx = -1;

Layer* nextZwoptexTest();
Layer* backZwoptexTest();
Layer* restartZwoptexTest();

Layer* createZwoptexLayer(int nIndex)
{
    switch(nIndex)
    {
    case 0: return new ZwoptexGenericTest();
    }

    return NULL;
}

Layer* nextZwoptexTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createZwoptexLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backZwoptexTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    Layer* pLayer = createZwoptexLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartZwoptexTest()
{
    Layer* pLayer = createZwoptexLayer(sceneIdx);
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
    BaseTest::onEnter();
}

void ZwoptexTest::restartCallback(Object* pSender)
{
    Scene *s = ZwoptexTestScene::create();
    s->addChild(restartZwoptexTest());
    Director::sharedDirector()->replaceScene(s);
}

void ZwoptexTest::nextCallback(Object* pSender)
{
    Scene *s = ZwoptexTestScene::create();
    s->addChild(nextZwoptexTest());
    Director::sharedDirector()->replaceScene(s);
}

void ZwoptexTest::backCallback(Object* pSender)
{
    Scene *s = ZwoptexTestScene::create();
    s->addChild(backZwoptexTest());
    Director::sharedDirector()->replaceScene(s);
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

    Size s = Director::sharedDirector()->getWinSize();

    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini.plist");
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini-generic.plist");
    
    LayerColor *layer1 = LayerColor::create(ccc4(255, 0, 0, 255), 85, 121);
    layer1->setPosition(ccp(s.width/2-80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer1);

    sprite1 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grossini_dance_01.png"));
    sprite1->setPosition(ccp( s.width/2-80, s.height/2));
    addChild(sprite1);

    sprite1->setFlipX(false);
    sprite1->setFlipY(false);

    LayerColor *layer2 = LayerColor::create(ccc4(255, 0, 0, 255), 85, 121);
    layer2->setPosition(ccp(s.width/2+80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer2);
    
    sprite2 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grossini_dance_generic_01.png"));
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
    sprite1->setDisplayFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str1));
    sprite2->setDisplayFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str2));
}

ZwoptexGenericTest::~ZwoptexGenericTest()
{
    sprite1->release();
    sprite2->release();
    SpriteFrameCache *cache = SpriteFrameCache::sharedSpriteFrameCache();
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
    Layer* pLayer = nextZwoptexTest();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
