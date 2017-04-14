//
//  Bug-15594.cpp
//  cocos2d_tests
//
//  Created by Ricardo Quesada on 5/24/16.
//
//

// https://github.com/cocos2d/cocos2d-x/pull/15594

#include "Bug-15594.h"


USING_NS_CC;

bool Bug15594Layer::init()
{
    if (BugsTestBase::init())
    {
        auto sprite3d = Sprite3D::create("Images/bugs/bug15594.c3t", "Images/bugs/bug15594.jpg");
        addChild(sprite3d);
        auto size = Director::getInstance()->getWinSize();
        sprite3d->setPosition(size/2);

        auto animation = Animation3D::create("Images/bugs/bug15594.c3t");
        auto animate = Animate3D::create(animation);
        auto repeat = RepeatForever::create(animate);
        sprite3d->runAction(repeat);
        return true;
    }

    return false;
}
