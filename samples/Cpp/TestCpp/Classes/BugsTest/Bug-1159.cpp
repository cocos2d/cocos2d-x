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
    Scene *scene = Scene::create();
    Bug1159Layer* layer = Bug1159Layer::create();
    scene->addChild(layer);

    return scene;
}

bool Bug1159Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
        Director::getInstance()->setDepthTest(true);
        Size s = Director::getInstance()->getWinSize();

        LayerColor *background = LayerColor::create(Color4B(255, 0, 255, 255));
        addChild(background);

        LayerColor *sprite_a = LayerColor::create(Color4B(255, 0, 0, 255), 700, 700);
        sprite_a->setAnchorPoint(Point(0.5f, 0.5f));
        sprite_a->ignoreAnchorPointForPosition(false);
        sprite_a->setPosition(Point(0.0f, s.height/2));
        addChild(sprite_a);

        sprite_a->runAction(RepeatForever::create(Sequence::create(
                                                        MoveTo::create(1.0f, Point(1024.0f, 384.0f)),
                                                        MoveTo::create(1.0f, Point(0.0f, 384.0f)),
                                                        NULL)));

        LayerColor *sprite_b = LayerColor::create(Color4B(0, 0, 255, 255), 400, 400);
        sprite_b->setAnchorPoint(Point(0.5f, 0.5f));
        sprite_b->ignoreAnchorPointForPosition(false);
        sprite_b->setPosition(Point(s.width/2, s.height/2));
        addChild(sprite_b);

        MenuItemLabel *label = MenuItemLabel::create(LabelTTF::create("Flip Me", "Helvetica", 24), CC_CALLBACK_1(Bug1159Layer::callBack, this) );
        Menu *menu = Menu::create(label, NULL);
        menu->setPosition(Point(s.width - 200.0f, 50.0f));
        addChild(menu);

        return true;
    }

    return false;
}

void Bug1159Layer::callBack(Object* sender)
{
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f, Bug1159Layer::scene(), false));
}

void Bug1159Layer::onExit()
{
    Director::getInstance()->setDepthTest(false);
    BugsTestBaseLayer::onExit();
}
