//
//  Bug-1159.m
//  Z-Fighting in iPad 2
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=1159
//
//  Created by Greg Woods on 4/5/11.
//  Copyright 2011 Westlake Design. All rights reserved.
//

#include "Bug-1159.h"

USING_NS_CC;

bool Bug1159Layer::init()
{
    if (BugsTestBase::init())
    {
        auto s = Director::getInstance()->getWinSize();

        auto background = LayerColor::create(Color4B(255, 0, 255, 255));
        addChild(background);

        auto sprite_a = LayerColor::create(Color4B(255, 0, 0, 255), 700, 700);
        sprite_a->setAnchorPoint(Vec2(0.5f, 0.5f));
        sprite_a->ignoreAnchorPointForPosition(false);
        sprite_a->setPosition(0.0f, s.height/2);
        addChild(sprite_a);

        sprite_a->runAction(RepeatForever::create(Sequence::create(
                                                        MoveTo::create(1.0f, Vec2(1024.0f, 384.0f)),
                                                        MoveTo::create(1.0f, Vec2(0.0f, 384.0f)),
                                                        nullptr)));

        auto sprite_b = LayerColor::create(Color4B(0, 0, 255, 255), 400, 400);
        sprite_b->setAnchorPoint(Vec2(0.5f, 0.5f));
        sprite_b->ignoreAnchorPointForPosition(false);
        sprite_b->setPosition(s.width/2, s.height/2);
        addChild(sprite_b);

        auto label = MenuItemLabel::create(Label::createWithSystemFont("Flip Me", "Helvetica", 24), CC_CALLBACK_1(Bug1159Layer::callBack, this) );
        auto menu = Menu::create(label, nullptr);
        menu->setPosition(s.width - 200.0f, 50.0f);
        addChild(menu);

        return true;
    }

    return false;
}

void Bug1159Layer::callBack(Ref* sender)
{
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f, Bug1159Layer::create(), false));
}

void Bug1159Layer::onExit()
{
    BugsTestBase::onExit();
}
