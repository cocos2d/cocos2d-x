/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UIScale9SpriteTest.h"

// UIScale9SpriteTest
UIScale9SpriteTest::UIScale9SpriteTest()
{
    
}

UIScale9SpriteTest::~UIScale9SpriteTest()
{
}

bool UIScale9SpriteTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto moveTo = MoveBy::create(1.0, Vec2(30,0));
        auto moveBack = moveTo->reverse();
        auto rotateBy = RotateBy::create(1.0, 180);
        auto action = Sequence::create(moveTo,moveBack, rotateBy, NULL);

        
        Sprite *normalSprite1 = Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite1->setPosition(100, 270);
//        normalSprite1->setAnchorPoint(Vec2(0.5,0.5));
//        normalSprite1->setContentSize(Size(100,100));

        this->addChild(normalSprite1);
        normalSprite1->runAction((FiniteTimeAction*)action->clone());
        
        ui::Scale9Sprite *normalSprite2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite2->setPosition(120, 270);
        normalSprite2->setScale9Enabled(false);
//        normalSprite2->setContentSize(Size(100,100));
//        normalSprite2->setAnchorPoint(Vec2(0.5,0.5));
        normalSprite2->setOpacity(100);
        this->addChild(normalSprite2);
        normalSprite2->setColor(Color3B::GREEN);
        normalSprite2->runAction(action);
        
        auto action2 = action->clone();
        ui::Scale9Sprite *sp1 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp1->setPosition(100, 160);
        sp1->setScale(1.2);
        sp1->setContentSize(Size(100,100));
        sp1->setColor(Color3B::GREEN);
//        sp1->setScale9Enabled(false);
        this->addChild(sp1);
        sp1->runAction((FiniteTimeAction*)action2);
        
        cocos2d::ui::Scale9Sprite *sp2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp2->setPosition(350, 160);
        sp2->setPreferredSize(sp1->getContentSize() * 1.2);
        sp2->setColor(Color3B::GREEN);
        sp2->setContentSize(Size(100,100));

        this->addChild(sp2);
        auto action3 = action->clone();
        sp2->runAction((FiniteTimeAction*)action3);
               
        return true;
    }
    return false;
}
