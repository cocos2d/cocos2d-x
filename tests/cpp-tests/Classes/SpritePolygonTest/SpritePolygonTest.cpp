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
}
void SpritePolygonTestDemo::initDefaultSprite(const std::string &filename)
{
    inst = experimental::SpritePolygon::create(filename);
    addChild(inst);
    auto s = Director::getInstance()->getWinSize();
    inst->setPosition(Vec2(s)/2);
}

SpritePolygonTest1::SpritePolygonTest1()
{
    initDefaultSprite(s_pathGrossini);
}