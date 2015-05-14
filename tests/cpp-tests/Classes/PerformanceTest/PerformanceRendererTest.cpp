//
//  PerformanceRendererTest.cpp
//  cocos2d_samples
//
//  Created by Huabing on 1/10/14.
//
//

#include "PerformanceRendererTest.h"
#include "PerformanceTextureTest.h"
#include "../testResource.h"

USING_NS_CC;

PerformceRenderTests::PerformceRenderTests()
{
    ADD_TEST_CASE(RenderPerformceTest);
}

void RenderPerformceTest::onEnter()
{
    TestCase::onEnter();
    auto map = TMXTiledMap::create("TileMaps/map/sl.tmx");
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    addChild(map,-1);
}
