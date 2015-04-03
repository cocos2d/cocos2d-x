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
#include "testResource.h"

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
        auto scaleBy = ScaleTo::create(1.0, -2.0);
        auto action = Sequence::create(moveTo,moveBack, rotateBy,scaleBy, NULL);

        
        Sprite *normalSprite1 = Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite1->setPosition(100, 270);
        normalSprite1->setFlippedY(true);
        

        this->addChild(normalSprite1);
        normalSprite1->runAction((FiniteTimeAction*)action->clone());
        
        ui::Scale9Sprite *normalSprite2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite2->setPosition(120, 270);
        normalSprite2->setScale9Enabled(false);
        normalSprite2->setOpacity(100);
        this->addChild(normalSprite2);
        normalSprite2->setColor(Color3B::GREEN);
        normalSprite2->runAction(action);
        
        auto action2 = action->clone();
        ui::Scale9Sprite *sp1 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp1->setPosition(100, 160);
        sp1->setScale(1.2f);
        sp1->setContentSize(Size(100,100));
        sp1->setColor(Color3B::GREEN);
        this->addChild(sp1);
        sp1->runAction((FiniteTimeAction*)action2);
        
        cocos2d::ui::Scale9Sprite *sp2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp2->setPosition(350, 160);
        sp2->setPreferredSize(sp1->getContentSize() * 1.2f);
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
        
        auto moveTo = MoveBy::create(1.0f, Vec2(30,0));
        auto moveBack = moveTo->reverse();
        auto rotateBy = RotateBy::create(1.0f, 180);
        auto fadeOut = FadeOut::create(2.0f);
        auto scaleTo = ScaleTo::create(1.0, 2.0);
        auto action = Sequence::create(moveTo,moveBack, rotateBy,fadeOut,scaleTo, NULL);
        
        Sprite *normalSprite1 = Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite1->setPosition(100, 270);
        normalSprite1->setCascadeColorEnabled(true);
        normalSprite1->setCascadeOpacityEnabled(true);
        normalSprite1->setColor(Color3B::GREEN);
        
        this->addChild(normalSprite1);
        normalSprite1->runAction((FiniteTimeAction*)action->clone());
        
        ui::Scale9Sprite *normalSprite2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        normalSprite2->setScale9Enabled(false);
        normalSprite2->setOpacity(100);
        normalSprite1->addChild(normalSprite2);
        
        auto action2 = action->clone();
        ui::Scale9Sprite *sp1 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp1->setPosition(200, 160);
        sp1->setScale(1.2f);
        sp1->setContentSize(Size(100,100));
        sp1->setColor(Color3B::GREEN);
        this->addChild(sp1);
        sp1->runAction((FiniteTimeAction*)action2);
        
        cocos2d::ui::Scale9Sprite *sp2 = ui::Scale9Sprite::create("cocosui/animationbuttonnormal.png");
        sp2->setPreferredSize(sp1->getContentSize() * 1.2f);
        sp2->setColor(Color3B::GREEN);
        sp2->setFlippedX(true);
        sp2->setContentSize(Size(100,100));
        
        sp1->addChild(sp2);
        
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
        sprite1->setPosition(origin+Vec2(size.width/2, size.height/2) + Vec2(-80, 80));
        containerForSprite1->addChild(sprite1);
        addChild(containerForSprite1, 10);
        
        auto sprite2 = ui::Scale9Sprite::create("Images/MagentaSquare.png");
        sprite2->setPosition(origin+Vec2(size.width/2, size.height/2));


        addChild(sprite2, 20);
        
        auto sprite3 = ui::Scale9Sprite::create("Images/YellowSquare.png");
        sprite3->setPosition(Vec2(0, 0));
        sprite3->setCascadeOpacityEnabled(false);
        sprite2->addChild(sprite3, 1);

        
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

bool UIS9BatchNodeBasic::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        
        auto sprite = Sprite::create("Images/blocks9.png");
        
        auto blocks = ui::Scale9Sprite::create();
        
        blocks->updateWithSprite(sprite, Rect(0, 0, 96, 96), false, Rect(0, 0, 96, 96));
        
        blocks->setPosition(Vec2(x, y));
        
        this->addChild(blocks);
        
        
        return true;
    }

    
    return false;
}

bool UIS9FrameNameSpriteSheet::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        
        auto blocks = ui::Scale9Sprite::createWithSpriteFrameName("blocks9.png");
        
        blocks->setPosition(Vec2(x, y));
        
        this->addChild(blocks);

        
        return true;
    }
    
    return false;
}


bool UIS9FrameNameSpriteSheetRotated::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto blocks = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        blocks->setPosition(Vec2(x, y));
        
        this->addChild(blocks);
        
        return true;
    }
    
    return false;
}

bool UIS9FrameNameSpriteSheetCropped::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
        
        auto blocks = ui::Scale9Sprite::createWithSpriteFrameName("blocks9c.png");
        
        blocks->setPosition(Vec2(x, y));
        
        this->addChild(blocks);
        
        return true;
    }
    
    return false;
}

bool UIS9FrameNameSpriteSheetCroppedRotated::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
        
        auto blocks = ui::Scale9Sprite::createWithSpriteFrameName("blocks9cr.png");
        
        blocks->setPosition(Vec2(x, y));
        
        this->addChild(blocks);
        
        return true;
    }
    
    return false;
}


bool UIS9BatchNodeScaledNoInsets::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        // scaled without insets
        auto sprite_scaled = Sprite::create("Images/blocks9.png");
        
        auto blocks_scaled = ui::Scale9Sprite::create();
        blocks_scaled->updateWithSprite(sprite_scaled, Rect(0, 0, 96, 96), false, Rect(0, 0, 96, 96));
        
        blocks_scaled->setPosition(Vec2(x, y));
        
        blocks_scaled->setContentSize(Size(96 * 4, 96*2));
        
        this->addChild(blocks_scaled);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetScaledNoInsets::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
        
        auto blocks_scaled = ui::Scale9Sprite::createWithSpriteFrameName("blocks9.png");
        
        blocks_scaled->setPosition(Vec2(x, y));
        
        blocks_scaled->setContentSize(Size(96 * 4, 96*2));
        
        this->addChild(blocks_scaled);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetRotatedScaledNoInsets::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        
        auto blocks_scaled = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        blocks_scaled->setPosition(Vec2(x, y));
        
        blocks_scaled->setContentSize(Size(96 * 4, 96*2));
        
        this->addChild(blocks_scaled);
        
        return true;
    }
    return false;
}


bool UIS9BatchNodeScaleWithCapInsets::init()
{
    if (UIScene::init()) {
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        
        auto sprite_scaled_with_insets = Sprite::create("Images/blocks9.png");
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::create();
        
        blocks_scaled_with_insets->updateWithSprite(sprite_scaled_with_insets, Rect(0, 0, 96, 96), false, Rect(32, 32, 32, 32));
        
        blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
        
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_scaled_with_insets);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetInsets::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        
        auto blocks_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));
        
        blocks_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_with_insets);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetInsetsScaled::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));
        
        blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
        
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_scaled_with_insets);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetRotatedInsets::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto blocks_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png", Rect(32, 32, 32, 32));
        
        blocks_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_with_insets);
        return true;
    }
    return false;
}

bool UIS9_TexturePacker::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);
        
        float x = winSize.width / 4;
        float y = 0 + (winSize.height / 2);
        
        auto s = ui::Scale9Sprite::createWithSpriteFrameName("button_normal.png");
        
        s->setPosition(Vec2(x, y));
        
        s->setContentSize(Size(14 * 16, 10 * 16));
        
        this->addChild(s);
        
        x = winSize.width * 3/4;
        
        auto s2 = ui::Scale9Sprite::createWithSpriteFrameName("button_actived.png");
        
        s2->setPosition(Vec2(x, y));
        
        s2->setContentSize(Size(14 * 16, 10 * 16));
        
        this->addChild(s2);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetRotatedInsetsScaled::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));

        blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
        
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_scaled_with_insets);
        return true;
    }
    return false;
}

bool UIS9FrameNameSpriteSheetRotatedSetCapInsetLater::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        blocks_scaled_with_insets->setInsetLeft(32);
        blocks_scaled_with_insets->setInsetRight(32);
        
        blocks_scaled_with_insets->setPreferredSize(Size(32*5.5f, 32*4));
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        
        this->addChild(blocks_scaled_with_insets);
        return true;
    }
    return false;
}

bool UIS9CascadeOpacityAndColor::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        auto rgba = Layer::create();
        rgba->setCascadeColorEnabled(true);
        rgba->setCascadeOpacityEnabled(true);
        this->addChild(rgba);
        
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        
        rgba->addChild(blocks_scaled_with_insets);
        auto actions = Sequence::create(FadeIn::create(1),
                                        TintTo::create(1, 0, 255, 0),
                                        TintTo::create(1, 255, 0, 255),
                                        CallFunc::create([=](){
                                            rgba->setCascadeColorEnabled(false);
                                            rgba->setCascadeOpacityEnabled(false);
                                        }),
                                        nullptr);
        auto repeat = RepeatForever::create(actions);
        rgba->runAction(repeat);
        return true;
    }
    return false;
}

bool UIS9ZOrder::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto blocks_scaled_with_insets = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        blocks_scaled_with_insets->setPosition(Vec2(x, y));
        this->addChild(blocks_scaled_with_insets);
        
        Sprite *normalSprite = Sprite::createWithSpriteFrameName("blocks9r.png");
        normalSprite->setColor(Color3B::RED);
        blocks_scaled_with_insets->addChild(normalSprite);
        
        auto topLabel = Label::createWithSystemFont("I Must be On the Top", "Arial", 15);
        topLabel->setPosition(Vec2(20,20));
        blocks_scaled_with_insets->addChild(topLabel);
        
        auto bottomLabel = Label::createWithSystemFont("I Must be On the Bottom", "Arial", 15);
        bottomLabel->setPosition(Vec2(80,80));
        bottomLabel->setColor(Color3B::BLUE);
        blocks_scaled_with_insets->addChild(bottomLabel,-1);
        
        return true;
    }
    return false;
}

bool UIS9Flip::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);

        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2);
        
        auto statusLabel = Label::createWithSystemFont("Scale9Enabled", "Arial", 10);
        statusLabel->setPosition(Vec2(x, winSize.height - statusLabel->getContentSize().height - 40));
        this->addChild(statusLabel);
        
        auto normalSprite = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        normalSprite->setPosition(Vec2(x, y ));
        this->addChild(normalSprite);
        
        
        auto normalLabel = Label::createWithSystemFont("Normal Sprite","Arial",10);
        normalLabel->setPosition(normalSprite->getPosition() + Vec2(0, normalSprite->getContentSize().height/2 + 10));
        this->addChild(normalLabel);
        
        
        
        auto flipXSprite = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        flipXSprite->setPosition(Vec2(x - 120, y ));
        flipXSprite->setScale(1.2f);
        this->addChild(flipXSprite);
        flipXSprite->setFlippedX(false);
        
        auto flipXLabel = Label::createWithSystemFont("sprite is not flipped!","Arial",10);
        flipXLabel->setPosition(flipXSprite->getPosition() + Vec2(0, flipXSprite->getContentSize().height/2 + 10));
        this->addChild(flipXLabel);
        
        
        auto flipYSprite = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        
        flipYSprite->setPosition(Vec2(x + 120, y));
        this->addChild(flipYSprite);
        
        flipYSprite->setScale(0.8f);
        flipYSprite->setFlippedY(true);
        
        auto flipYLabel = Label::createWithSystemFont("sprite is flipped!","Arial",10);
        flipYLabel->setPosition(flipYSprite->getPosition() + Vec2(0, flipYSprite->getContentSize().height/2 + 10));
        this->addChild(flipYLabel);
        
        
        auto toggleFlipXButton = Button::create();
        toggleFlipXButton->setTitleText("Toggle FlipX");
        toggleFlipXButton->setPosition(flipXSprite->getPosition() + Vec2(0, - 20 - flipXSprite->getContentSize().height/2));
        toggleFlipXButton->addClickEventListener([=](Ref*){
            flipXSprite->setFlippedX(! flipXSprite->isFlippedX());
            if (flipXSprite->isFlippedX()) {
                flipXLabel->setString("sprite is flipped!");
            }
            else{
                flipXLabel->setString("sprite is not flipped!");
            }
        });
        this->addChild(toggleFlipXButton);
        
        auto toggleFlipYButton = Button::create();
        toggleFlipYButton->setTitleText("Toggle FlipY");
        toggleFlipYButton->setPosition(flipYSprite->getPosition() + Vec2(0, -20 - flipYSprite->getContentSize().height/2));
        toggleFlipYButton->addClickEventListener([=](Ref*){
            flipYSprite->setFlippedY(!flipYSprite->isFlippedY());
            if (flipYSprite->isFlippedY()) {
                flipYLabel->setString("sprite is flipped!");
            }
            else{
                flipYLabel->setString("sprpite is not flipped!");
            }
        });
        this->addChild(toggleFlipYButton);
        
        auto toggleScale9Button = Button::create();
        toggleScale9Button->setTitleText("Toggle Scale9");
        toggleScale9Button->setPosition(normalSprite->getPosition() + Vec2(0, -20 - normalSprite->getContentSize().height/2));
        toggleScale9Button->addClickEventListener([=](Ref*){
            flipXSprite->setScale9Enabled(!flipXSprite->isScale9Enabled());
            flipYSprite->setScale9Enabled(!flipYSprite->isScale9Enabled());
            if (flipXSprite->isScale9Enabled()) {
                statusLabel->setString("Scale9Enabled");
            }else{
                statusLabel->setString("Scale9Disabled");
            }
            
            CCLOG("scaleX = %f", flipXSprite->getScaleX());
            CCLOG("scaleY = %f", flipYSprite->getScale());
            if (flipXSprite->isFlippedX()) {
                CCLOG("xxxxxxx");
            }
            if (flipYSprite->isFlippedY()) {
                CCLOG("YYYYYY");
            }
            
            if (flipXSprite->isFlippedX()) {
                flipXLabel->setString("sprite is flipped!");
            }
            else{
                flipXLabel->setString("sprite is not flipped!");
            }
            
            if (flipYSprite->isFlippedY()) {
                flipYLabel->setString("sprite is flipped!");
            }
            else{
                flipYLabel->setString("sprpite is not flipped!");
            }
            
        });
        this->addChild(toggleScale9Button);
        
        return true;
    }
    return false;
}

bool UIS9ChangeAnchorPoint::init()
{
    if (UIScene::init()) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
        
        auto winSize = Director::getInstance()->getWinSize();
        float x = winSize.width / 2;
        float y = 0 + (winSize.height / 2 + 50);
        
        
        auto normalSprite = ui::Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
        normalSprite->setPosition(Vec2(x, y ));
//        normalSprite->setScale9Enabled(false);
//        normalSprite->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);

        this->addChild(normalSprite);
        
        
        Button* button1 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button1->setPosition(Vec2(winSize.width/2 - 100,winSize.height/2 - 50));
        button1->setName("button2");
        button1->setTitleText("Vec(0,0)");
        button1->addTouchEventListener([=](Ref*, Widget::TouchEventType type)
                                       {
                                           if (type == Widget::TouchEventType::ENDED) {
                                               normalSprite->setAnchorPoint(Vec2::ZERO);
                                               normalSprite->setScale9Enabled(true);
                                               CCLOG("position = %f, %f,  anchor point = %f, %f", normalSprite->getPosition().x,
                                                     normalSprite->getPosition().y,
                                                     normalSprite->getAnchorPoint().x,
                                                     normalSprite->getAnchorPoint().y);
                                               CCLOG("tests:content size : width = %f, height = %f",
                                                     normalSprite->getContentSize().width,
                                                     normalSprite->getContentSize().height);
                                           }
                                       });
        this->addChild(button1);
        
        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setPosition(Vec2(winSize.width/2 + 100,winSize.height/2 - 50));
        button2->setName("button2");
        button2->setTitleText("Vec(1,1)");
        button2->addTouchEventListener([=](Ref*, Widget::TouchEventType type)
                                       {
                                           if (type == Widget::TouchEventType::ENDED) {
                                               normalSprite->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                                               normalSprite->setScale9Enabled(false);
                                               CCLOG("position = %f, %f,  anchor point = %f, %f", normalSprite->getPosition().x,
                                                     normalSprite->getPosition().y,
                                                     normalSprite->getAnchorPoint().x,
                                                     normalSprite->getAnchorPoint().y);
                                               CCLOG("tests:content size : width = %f, height = %f",
                                                     normalSprite->getContentSize().width,
                                                     normalSprite->getContentSize().height);
                                               
                                           }
                                       });
        this->addChild(button2);
        
        
        return true;
    }
    return false;
}
