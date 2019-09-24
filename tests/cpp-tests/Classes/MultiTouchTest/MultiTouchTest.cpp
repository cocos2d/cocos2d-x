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

#include "MultiTouchTest.h"

USING_NS_CC;

MultiTouchTests::MultiTouchTests()
{
    ADD_TEST_CASE(MultiTouchTest);
}

static const Color3B* s_TouchColors[5] = {
    &Color3B::YELLOW,
    &Color3B::BLUE,
    &Color3B::GREEN,
    &Color3B::RED,
    &Color3B::MAGENTA
};

class TouchPoint : public Node
{
public:
    TouchPoint(const Vec2 &touchPoint, const Color3B &touchColor)
    {
        DrawNode* drawNode = DrawNode::create();
        auto s = Director::getInstance()->getWinSize();
        Color4F color(touchColor.r/255.0f, touchColor.g/255.0f, touchColor.b/255.0f, 1.0f);
        drawNode->drawLine(Vec2(0.0f, touchPoint.y), Vec2(s.width, touchPoint.y), color);
        drawNode->drawLine(Vec2(touchPoint.x, 0.0f), Vec2(touchPoint.x, s.height), color);
        drawNode->drawDot(touchPoint, 3, color);
        addChild(drawNode);
    }

    static TouchPoint* touchPointWithParent(Node* pParent, const Vec2 &touchPoint, const Color3B &touchColor)
    {
        auto pRet = new (std::nothrow) TouchPoint(touchPoint, touchColor);
        pRet->setContentSize(pParent->getContentSize());
        pRet->setAnchorPoint(Vec2(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }
};

bool MultiTouchTest::init()
{
    if (TestCase::init())
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(MultiTouchTest::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(MultiTouchTest::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(MultiTouchTest::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        auto title = Label::createWithSystemFont("Please touch the screen!", "", 24);
        title->setPosition(VisibleRect::top()+Vec2(0.0f, -40.0f));
        addChild(title);
        
        return true;
    }
    return false;
}

static Map<int, TouchPoint*> s_map;

void MultiTouchTest::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocation();
        auto touchPoint = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID()%5]);

        addChild(touchPoint);
        s_map.insert(touch->getID(), touchPoint);
    }
}

void MultiTouchTest::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    for( auto &item: touches)
    {
        auto touch = item;
        auto pTP = s_map.at(touch->getID());
        auto location = touch->getLocation();
        
        removeChild(pTP, true);
        s_map.erase(touch->getID());
        
        auto touchPointNew = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID()%5]);
        addChild(touchPointNew);
        s_map.insert(touch->getID(), touchPointNew);
    }
}

void MultiTouchTest::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto pTP = s_map.at(touch->getID());
        removeChild(pTP, true);
        s_map.erase(touch->getID());
    }
}

void MultiTouchTest::onTouchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
    onTouchesEnded(touches, event);
}
