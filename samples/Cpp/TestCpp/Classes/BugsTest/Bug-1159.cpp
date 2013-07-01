//
//  Bug-1159.m
//  Z-Fighting in iPad 2
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=1159
//
//  Created by Greg Woods on 4/5/11.
//  Copyright 2011 Westlake Design. All rights reserved.
//

#include "Bug-1159.h"

Scene* Bug1159Layer::scene()
{
    Scene *pScene = Scene::create();
    Bug1159Layer* layer = Bug1159Layer::create();
    pScene->addChild(layer);

    return pScene;
}

bool Bug1159Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        Director::sharedDirector()->setDepthTest(true);
        Size s = Director::sharedDirector()->getWinSize();

        LayerColor *background = LayerColor::create(ccc4(255, 0, 255, 255));
        addChild(background);

        LayerColor *sprite_a = LayerColor::create(ccc4(255, 0, 0, 255), 700, 700);
        sprite_a->setAnchorPoint(ccp(0.5f, 0.5f));
        sprite_a->ignoreAnchorPointForPosition(false);
        sprite_a->setPosition(ccp(0.0f, s.height/2));
        addChild(sprite_a);

        sprite_a->runAction(RepeatForever::create(Sequence::create(
                                                        MoveTo::create(1.0f, ccp(1024.0f, 384.0f)),
                                                        MoveTo::create(1.0f, ccp(0.0f, 384.0f)),
                                                        NULL)));

        LayerColor *sprite_b = LayerColor::create(ccc4(0, 0, 255, 255), 400, 400);
        sprite_b->setAnchorPoint(ccp(0.5f, 0.5f));
        sprite_b->ignoreAnchorPointForPosition(false);
        sprite_b->setPosition(ccp(s.width/2, s.height/2));
        addChild(sprite_b);

        MenuItemLabel *label = MenuItemLabel::create(LabelTTF::create("Flip Me", "Helvetica", 24), CC_CALLBACK_1(Bug1159Layer::callBack, this) );
        Menu *menu = Menu::create(label, NULL);
        menu->setPosition(ccp(s.width - 200.0f, 50.0f));
        addChild(menu);

        return true;
    }

    return false;
}

void Bug1159Layer::callBack(Object* pSender)
{
    Director::sharedDirector()->replaceScene(TransitionPageTurn::create(1.0f, Bug1159Layer::scene(), false));
}

void Bug1159Layer::onExit()
{
    Director::sharedDirector()->setDepthTest(false);
    BugsTestBaseLayer::onExit();
}
