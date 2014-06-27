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


UIScale9SpriteHierarchialTest::UIScale9SpriteHierarchialTest()
{
    
}

UIScale9SpriteHierarchialTest::~UIScale9SpriteHierarchialTest()
{
}

bool UIScale9SpriteHierarchialTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto moveTo = MoveBy::create(1.0, Vec2(30,0));
        auto moveBack = moveTo->reverse();
        auto rotateBy = RotateBy::create(1.0, 180);
        auto fadeOut = FadeOut::create(2.0);
        auto action = Sequence::create(moveTo,moveBack, rotateBy,fadeOut, NULL);
        
        
        Sprite *normalSprite1 = Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite1->setPosition(100, 270);
        //        normalSprite1->setAnchorPoint(Vec2(0.5,0.5));
        //        normalSprite1->setContentSize(Size(100,100));
        
//        Sprite *childSprite = Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite1->setCascadeColorEnabled(true);
        normalSprite1->setCascadeOpacityEnabled(true);
        normalSprite1->setColor(Color3B::GREEN);

        
        
        this->addChild(normalSprite1);
        normalSprite1->runAction((FiniteTimeAction*)action->clone());
        
        ui::Scale9Sprite *normalSprite2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
//        normalSprite2->setPosition(120, 270);
        normalSprite2->setScale9Enabled(false);
        //        normalSprite2->setContentSize(Size(100,100));
        //        normalSprite2->setAnchorPoint(Vec2(0.5,0.5));
        normalSprite2->setOpacity(100);
        normalSprite1->addChild(normalSprite2);
        
        auto action2 = action->clone();
        ui::Scale9Sprite *sp1 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp1->setPosition(200, 160);
        sp1->setScale(1.2);
        sp1->setContentSize(Size(100,100));
        sp1->setColor(Color3B::GREEN);
        //        sp1->setScale9Enabled(false);
        this->addChild(sp1);
        sp1->runAction((FiniteTimeAction*)action2);
        
        cocos2d::ui::Scale9Sprite *sp2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
//        sp2->setPosition(350, 160);
        sp2->setPreferredSize(sp1->getContentSize() * 1.2);
        sp2->setColor(Color3B::GREEN);
        sp2->setContentSize(Size(100,100));
        
        sp1->addChild(sp2);
//        auto action3 = action->clone();
//        sp2->runAction((FiniteTimeAction*)action3);
        
        return true;
    }
    return false;
}

UIScale9SpriteTouchTest::UIScale9SpriteTouchTest()
{
    
}

UIScale9SpriteTouchTest::~UIScale9SpriteTouchTest()
{
}

bool UIScale9SpriteTouchTest::init()
{
    if (UIScene::init())
    {
    
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Size size = Director::getInstance()->getVisibleSize();
        
        auto containerForSprite1 = Node::create();
        auto sprite1 = cocos2d::ui::Scale9Sprite::create("Images/CyanSquare.png");
//        sprite1->setScale9Enabled(false);
        sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 80));
        containerForSprite1->addChild(sprite1);
        addChild(containerForSprite1, 10);
        
        auto sprite2 = ui::Scale9Sprite::create("Images/MagentaSquare.png");
        sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));
//        sprite2->setCascadeOpacityEnabled(false);
//        sprite2->setScale9Enabled(false);

        addChild(sprite2, 20);
        
        auto sprite3 = ui::Scale9Sprite::create("Images/YellowSquare.png");
        sprite3->setPosition(Vec2(0, 0));
        sprite3->setCascadeOpacityEnabled(false);
        sprite2->addChild(sprite3, 1);
//        sprite3->setScale9Enabled(false);

        
        // Make sprite1 touchable
        auto listener1 = EventListenerTouchOneByOne::create();
        listener1->setSwallowTouches(true);
        
        listener1->onTouchBegan = [](Touch* touch, Event* event){
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            if (rect.containsPoint(locationInNode))
            {
                log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
                target->setOpacity(180);
                return true;
            }
            return false;
        };
        
        listener1->onTouchMoved = [](Touch* touch, Event* event){
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            target->setPosition(target->getPosition() + touch->getDelta());
        };
        
        listener1->onTouchEnded = [=](Touch* touch, Event* event){
            auto target = static_cast<ui::Scale9Sprite*>(event->getCurrentTarget());
            log("sprite onTouchesEnded.. ");
            target->setOpacity(255);
            if (target == sprite2)
            {
                containerForSprite1->setLocalZOrder(100);
            }
            else if(target == sprite1)
            {
                containerForSprite1->setLocalZOrder(0);
            }
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
        
        return true;
    }
    return false;
}
