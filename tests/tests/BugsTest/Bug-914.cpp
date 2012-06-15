//
//  HelloWorldLayer.m
//  EAGLViewBug
//
//  Created by Wylan Werth on 7/5/10.
//  Copyright BanditBear Games 2010. All rights reserved.
//

// Import the interfaces
#include"Bug-914.h"

CCScene* Bug914Layer::scene()
{
    // 'scene' is an autorelease object.
    CCScene *pScene = CCScene::create();
    // 'layer' is an autorelease object.
    Bug914Layer* layer = Bug914Layer::create();

    // add layer as a child to scene
    pScene->addChild(layer);

    // return the scene
    return pScene;
}

// on "init" you need to initialize your instance
bool Bug914Layer::init()
{
    // always call "super" init
    // Apple recommends to re-assign "self" with the "super" return value
    if (BugsTestBaseLayer::init())
    {
        setTouchEnabled(true);
        // ask director the the window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCLayerColor *layer;
        for( int i=0;i < 5;i++)
        {
            layer = CCLayerColor::create(ccc4(i*20, i*20, i*20,255));
            layer->setContentSize(CCSizeMake(i*100, i*100));
            layer->setPosition(ccp(size.width/2, size.height/2));
            layer->setAnchorPoint(ccp(0.5f, 0.5f));
            layer->ignoreAnchorPointForPosition(false);
            addChild(layer, -1-i);
        }

        // create and initialize a Label
        CCLabelTTF *label = CCLabelTTF::create("Hello World", "Marker Felt", 64);
        CCMenuItem *item1 = CCMenuItemFont::create("restart", this, menu_selector(Bug914Layer::restart));

        CCMenu *menu = CCMenu::create(item1, NULL);
        menu->alignItemsVertically();
        menu->setPosition(ccp(size.width/2, 100));
        addChild(menu);

        // position the label on the center of the screen
        label->setPosition(ccp( size.width /2 , size.height/2 ));

        // add the label as a child to this Layer
        addChild(label);
        return true;
    }
    return false;
}

void Bug914Layer::ccTouchesMoved(CCSet *touches, CCEvent * event)
{
    CCLog("Number of touches: %d", touches->count());
}

void Bug914Layer::ccTouchesBegan(CCSet *touches, CCEvent * event)
{
    ccTouchesMoved(touches, event);
}

void Bug914Layer::restart(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(Bug914Layer::scene());
}
