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
    CCScene *pScene = CCScene::node();
    Bug1159Layer* layer = Bug1159Layer::node();
	pScene->addChild(layer);

    return pScene;
}

bool Bug1159Layer::init()
{
    if (BugsTestBaseLayer::init())
	{
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCLayerColor *background = CCLayerColor::layerWithColor(ccc4f(255, 0, 255, 255));
		addChild(background);

        CCLayerColor *sprite_a = CCLayerColor::layerWithColorWidthHeight(ccc4f(255, 0, 0, 255), 700, 700);
		sprite_a->setAnchorPoint(ccp(0.5f, 0.5f));
		sprite_a->setIsRelativeAnchorPoint(true);
		sprite_a->setPosition(ccp(0.0f, s.height/2));
		addChild(sprite_a);

        sprite_a->runAction(CCRepeatForever::actionWithAction((CCActionInterval*) CCSequence::actions(
                                                               CCMoveTo::actionWithDuration(1.0f, ccp(1024.0f, 384.0f)),
                                                               CCMoveTo::actionWithDuration(1.0f, ccp(0.0f, 384.0f)),
															   NULL)));

        CCLayerColor *sprite_b = CCLayerColor::layerWithColorWidthHeight(ccc4f(0, 0, 255, 255), 400, 400);
		sprite_b->setAnchorPoint(ccp(0.5f, 0.5f));
		sprite_b->setIsRelativeAnchorPoint(true);
		sprite_b->setPosition(ccp(s.width/2, s.height/2));
		addChild(sprite_b);

        CCMenuItemLabel *label = CCMenuItemLabel::itemWithLabel(CCLabelTTF::labelWithString("Flip Me", "Helvetica", 24), this, menu_selector(Bug1159Layer::callBack));
        CCMenu *menu = CCMenu::menuWithItems(label, NULL);
		menu->setPosition(ccp(s.width - 200.0f, 50.0f));
		addChild(menu);

        return true;
	}

	return false;
}

void Bug1159Layer::callBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::transitionWithDuration(1.0f, Bug1159Layer::scene(), false));
}
