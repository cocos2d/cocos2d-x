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

#include "LayoutComponentTest.h"

#include "testResource.h"

// UILayoutComponentBaiscTest
UILayoutComponentBaiscTest::UILayoutComponentBaiscTest()
{
    
}

UILayoutComponentBaiscTest::~UILayoutComponentBaiscTest()
{
}

bool UILayoutComponentBaiscTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        ImageView* imageView = ImageView::create("cocosui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(400, 240));
        imageView->setNormalizedPosition(Vec2(1,1));
        imageView->setAnchorPoint(Vec2(1,1));
        
       
        
        auto sprite = Sprite::create("cocosui/animationbuttonpressed.png");
//        sprite->setNormalizedPosition(Vec2::ANCHOR_TOP_RIGHT * 0.9);
        sprite->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
        auto layoutComponent = LayoutComponent::create();
        layoutComponent->setReferencePoint(LayoutComponent::ReferencePoint::RIGHT_TOP);
        sprite->addComponent(layoutComponent);
        layoutComponent->setPercentPosition(Vec2::ANCHOR_TOP_RIGHT * 0.9);

        
        imageView->addChild(sprite);


        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setAnchorPoint(Vec2::ZERO);
        button->setNormalizedPosition(Vec2::ZERO);
        button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            sprite->setNormalizedPosition(Vec2::ANCHOR_TOP_RIGHT);
        });
        imageView->addChild(button);
        
        this->addChild(imageView);
        
        return true;
    }
    return false;
}