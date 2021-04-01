/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "UIWidgetAddNodeTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIWidgetAddNodeTests::UIWidgetAddNodeTests()
{
    ADD_TEST_CASE(UIWidgetAddNodeTest);
}

// UIWidgetAddNodeTest

UIWidgetAddNodeTest::UIWidgetAddNodeTest()
{
    
}

UIWidgetAddNodeTest::~UIWidgetAddNodeTest()
{
}

bool UIWidgetAddNodeTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create();
        alert->setString("Widget Add Node");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75));
        _uiLayer->addChild(alert);
        
        // Create the ui node container
        Widget* widget = Widget::create();
        widget->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(widget);
        
        Sprite* sprite = Sprite::create("cocosui/ccicon.png");
        sprite->setPosition(Vec2(0.0f, sprite->getBoundingBox().size.height / 4));
        widget->addChild(sprite);
        
        return true;
    }
    return false;
}
