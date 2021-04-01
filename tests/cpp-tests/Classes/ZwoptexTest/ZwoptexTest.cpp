/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ZwoptexTest.h"
#include "../testResource.h"

USING_NS_CC;

ZwoptexTests::ZwoptexTests()
{
    ADD_TEST_CASE(ZwoptexGenericTest);
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
    layer1->setPosition(Vec2(s.width/2-80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer1);

    sprite1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_01.png"));
    sprite1->setPosition(Vec2( s.width/2-80, s.height/2));
    addChild(sprite1);

    sprite1->setFlippedX(false);
    sprite1->setFlippedY(false);

    auto layer2 = LayerColor::create(Color4B(255, 0, 0, 255), 85, 121);
    layer2->setPosition(Vec2(s.width/2+80 - (85.0f * 0.5f), s.height/2 - (121.0f * 0.5f)));
    addChild(layer2);
    
    sprite2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_generic_01.png"));
    sprite2->setPosition(Vec2( s.width/2 + 80, s.height/2));
    addChild(sprite2);

    sprite2->setFlippedX(false);
    sprite2->setFlippedY(false);

    schedule(CC_SCHEDULE_SELECTOR(ZwoptexGenericTest::startIn05Secs), 1.0f);
    
    sprite1->retain();
    sprite2->retain();

    counter = 0;
}

void ZwoptexGenericTest::startIn05Secs(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(ZwoptexGenericTest::startIn05Secs));
    schedule(CC_SCHEDULE_SELECTOR(ZwoptexGenericTest::flipSprites), 0.5f);
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
