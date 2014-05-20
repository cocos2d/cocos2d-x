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

RenderTestLayer::RenderTestLayer()
: PerformBasicLayer(true, 1, 1)
{
}

RenderTestLayer::~RenderTestLayer()
{
}

Scene* RenderTestLayer::scene()
{
    auto scene = Scene::create();
    RenderTestLayer *layer = new RenderTestLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void RenderTestLayer::onEnter()
{
    PerformBasicLayer::onEnter();
    auto map = TMXTiledMap::create("TileMaps/map/sl.tmx");
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    addChild(map,-1);
    
    //map->setAnchorPoint( Vec2(0, 0) );
    //map->setPosition( Vec2(-20,-200) );
}

void RenderTestLayer::showCurrentTest()
{
    
}

void runRendererTest()
{
    auto scene = RenderTestLayer::scene();
    Director::getInstance()->replaceScene(scene);
}