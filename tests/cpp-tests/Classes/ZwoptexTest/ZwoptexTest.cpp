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

    auto layer = createZwoptexLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backZwoptexTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    auto layer = createZwoptexLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartZwoptexTest()
{
    auto layer = createZwoptexLayer(sceneIdx);
    layer->autorelease();

    return layer;
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

void ZwoptexTest::restartCallback(Ref* sender)
{
    auto s = ZwoptexTestScene::create();
    s->addChild(restartZwoptexTest());
    Director::getInstance()->replaceScene(s);
}

void ZwoptexTest::nextCallback(Ref* sender)
{
    auto s = ZwoptexTestScene::create();
    s->addChild(nextZwoptexTest());
    Director::getInstance()->replaceScene(s);
}

void ZwoptexTest::backCallback(Ref* sender)
{
    auto s = ZwoptexTestScene::create();
    s->addChild(backZwoptexTest());
    Director::getInstance()->replaceScene(s);
}

std::string ZwoptexTest::title() const
{
    return "No title";
}

std::string ZwoptexTest::subtitle() const
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

    auto s = Director::getInstance()->getWinSize();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwoptex/grossini.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwoptex/grossini-generic.plist");
    
    auto layer1 = LayerColor::create(Color4B(255, 0, 0, 255), 85, 121);
    layer1->setPosition(Point(s.width/2-80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer1);

    sprite1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_01.png"));
    sprite1->setPosition(Point( s.width/2-80, s.height/2));
    addChild(sprite1);

    sprite1->setFlippedX(false);
    sprite1->setFlippedY(false);

    auto layer2 = LayerColor::create(Color4B(255, 0, 0, 255), 85, 121);
    layer2->setPosition(Point(s.width/2+80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer2);
    
    sprite2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_generic_01.png"));
    sprite2->setPosition(Point( s.width/2 + 80, s.height/2));
    addChild(sprite2);

    sprite2->setFlippedX(false);
    sprite2->setFlippedY(false);

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

    sprite1->setFlippedX(fx);
    sprite2->setFlippedX(fx);
    sprite1->setFlippedY(fy);
    sprite2->setFlippedY(fy);

    if(++spriteFrameIndex > 14)
    {
        spriteFrameIndex = 1;
    }

    char str1[32] = {0};
    char str2[32] = {0};
    sprintf(str1, "grossini_dance_%02d.png", spriteFrameIndex);
    sprintf(str2, "grossini_dance_generic_%02d.png", spriteFrameIndex);
    sprite1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str1));
    sprite2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str2));
}

ZwoptexGenericTest::~ZwoptexGenericTest()
{
    sprite1->release();
    sprite2->release();
    auto cache = SpriteFrameCache::getInstance();
    cache->removeSpriteFramesFromFile("zwoptex/grossini.plist");
    cache->removeSpriteFramesFromFile("zwoptex/grossini-generic.plist");
}

std::string ZwoptexGenericTest::title() const
{
    return "Zwoptex Tests";
}

std::string ZwoptexGenericTest::subtitle() const
{
    return "Coordinate Formats, Rotation, Trimming, flipX/Y";
}

void ZwoptexTestScene::runThisTest()
{
    auto layer = nextZwoptexTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
