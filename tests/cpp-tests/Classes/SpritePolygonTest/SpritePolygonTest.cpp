//
//  SpritePolygonTest.cpp
//  cocos2d_tests
//
//  Created by WuHao on 15/4/23.
//
//

#include "SpritePolygonTest.h"
#include "2d/SpritePolygon.h"
#include "../testResource.h"

USING_NS_CC;

SpritePolygonTest::SpritePolygonTest()
{
    ADD_TEST_CASE(SpritePolygonTest1);
    ADD_TEST_CASE(SpritePolygonTest2);
}
void SpritePolygonTestDemo::initDefaultSprite(const std::string &filename, cocos2d::experimental::SpritePolygon * inst)
{
    Director::getInstance()->setClearColor(Color4F(102./255, 184./255, 204./255, 255.));
    
    
    spp = inst;
    addChild(spp);
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    spp->setPosition(Vec2(s)/2 + offset);

    
    sp = Sprite::create(filename);
    addChild(sp);
    sp->setPosition(Vec2(s)/2 - offset);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event){
        spp->showDebug(true);
        debugForNormalSprite->setVisible(true);
        return 1;
    };
    touchListener->onTouchMoved = [&](Touch* touch, Event* event){
            auto pos = touch->getDelta();
            float newScale = clampf(spp->getScale()+pos.x*0.01, 0.1, 2);
            spp->setScale(newScale);
            sp->setScale(newScale);
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        spp->showDebug(false);
        debugForNormalSprite->setVisible(false);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    debugForNormalSprite = DrawNode::create();
    sp->addChild(debugForNormalSprite);
    
    auto positions = new Vec2[4];
    auto spSize = sp->getContentSize();
    positions[0] = Vec2(0, spSize.height);
    positions[1] = Vec2(spSize);
    positions[2] = Vec2(spSize.width, 0);
    positions[3] = Vec2(0,0);
    debugForNormalSprite->drawPoints(positions, 4, 8, Color4F{0.0,1.0,1.0,1.0});
    debugForNormalSprite->drawLine(positions[0], positions[1], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[1], positions[2], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[2], positions[3], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[3], positions[0], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[0], positions[2], Color4F::GREEN);
    debugForNormalSprite->setVisible(false);
    
    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    sp->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)spp->getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)spp->getArea()).asString()+vertCount);
    spp->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
}
void SpritePolygonTestDemo::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}


SpritePolygonTest1::SpritePolygonTest1()
{
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\")";
    auto s = experimental::SpritePolygon::create(s_pathGrossini);
    initDefaultSprite(s_pathGrossini, s);
}

SpritePolygonTest2::SpritePolygonTest2()
{
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\")";
    auto s = experimental::SpritePolygon::create(s_pathGrossini);
    initDefaultSprite(s_pathGrossini, s);
}