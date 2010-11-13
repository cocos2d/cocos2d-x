/*
 *  HelloWorld.cpp
 *  HelloWorld
 *
 *  Created by Walzer on 10-11-12.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "HelloWorld.h"

using namespace cocos2d;

class MyLayer : public CCLayer {
public:
    bool init()
    {
        if (! CCLayer::init())
        {
            return false;
        }
		
        this->setIsTouchEnabled(true);
		
        return true;
    }
	
    void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent)
    {
        CCDirector::sharedDirector()->end();
    }
	
    LAYER_NODE_FUNC(MyLayer);
};

HelloWorld::HelloWorld()
{
}

bool HelloWorld::initCocos2d()
{
    // init director
    CCDirector::sharedDirector()->setOpenGLView(new CCXEGLView());
    CCDirector::sharedDirector()->setDisplayFPS(true);
	
    // load image texture and get window size
    CCTexture2D *pTextrue = CCTextureCache::sharedTextureCache()->addImage("helloworld.png");
    CGSize size = CCDirector::sharedDirector()->getWinSize();
	
    // create sprite instance
    CCSprite *pSprite = CCSprite::spriteWithTexture(pTextrue);
    pSprite->setPosition(CGPoint(size.width / 2, size.height / 2));
	
    // create layer instance
    CCLayer *pLayer = MyLayer::node();
    pLayer->addChild(pSprite);
	
    // create scene and add layer to scene
    CCScene *pScene = CCScene::node();
    pScene->addChild(pLayer);
	
    // add scene to director
    CCDirector::sharedDirector()->runWithScene(pScene);
	
    return true;
}
