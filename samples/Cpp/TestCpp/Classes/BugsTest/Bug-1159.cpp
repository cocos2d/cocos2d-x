//
//  Bug-1159.m
//  Z-Fighting in iPad 2
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=1159
//
//  Created by Greg Woods on 4/5/11.
//  Copyright 2011 Westlake Design. All rights reserved.
//

#include "Bug-1159.h"

CCScene* Bug1159Layer::scene()
{
    CCScene *pScene = CCScene::create();
    Bug1159Layer* layer = Bug1159Layer::create();
    pScene->addChild(layer);

    return pScene;
}

bool Bug1159Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCLayerColor *background = CCLayerColor::create(ccc4(255, 0, 255, 255));
        addChild(background);

        CCLayerColor *sprite_a = CCLayerColor::create(ccc4(255, 0, 0, 255), 700, 700);
        sprite_a->setAnchorPoint(ccp(0.5f, 0.5f));
        sprite_a->ignoreAnchorPointForPosition(false);
        sprite_a->setPosition(ccp(0.0f, s.height/2));
        addChild(sprite_a);

        sprite_a->runAction(CCRepeatForever::create(CCSequence::create(
                                                        CCMoveTo::create(1.0f, ccp(1024.0f, 384.0f)),
                                                        CCMoveTo::create(1.0f, ccp(0.0f, 384.0f)),
                                                        NULL)));

        CCLayerColor *sprite_b = CCLayerColor::create(ccc4(0, 0, 255, 255), 400, 400);
        sprite_b->setAnchorPoint(ccp(0.5f, 0.5f));
        sprite_b->ignoreAnchorPointForPosition(false);
        sprite_b->setPosition(ccp(s.width/2, s.height/2));
        addChild(sprite_b);

        CCMenuItemLabel *label = CCMenuItemLabel::create(CCLabelTTF::create("Flip Me", "Helvetica", 24), this, menu_selector(Bug1159Layer::callBack));
        CCMenu *menu = CCMenu::create(label, NULL);
        menu->setPosition(ccp(s.width - 200.0f, 50.0f));
        addChild(menu);

        return true;
    }

    return false;
}

void Bug1159Layer::callBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.0f, Bug1159Layer::scene(), false));
}

void Bug1159Layer::onExit()
{
    CCDirector::sharedDirector()->setDepthTest(false);
    BugsTestBaseLayer::onExit();
}
