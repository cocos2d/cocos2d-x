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

#include "MouseTest.h"

USING_NS_CC;

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

MouseTests::MouseTests()
{
    ADD_TEST_CASE(MouseEventTest);
    ADD_TEST_CASE(HideMouseTest);
    ADD_TEST_CASE(CursorTest);
}

//------------------------------------------------------------------
//
// MouseEventTest
//
//------------------------------------------------------------------
MouseEventTest::MouseEventTest()
{
    auto s = Director::getInstance()->getWinSize();

    //Create a label to display the mouse action
    _labelAction = Label::createWithTTF("Click mouse button and see this change", "fonts/arial.ttf", 22);
    _labelAction->setPosition(Vec2(s.width/2, s.height*2/3));
    addChild(_labelAction, 0);

    //Create a label to display the mouse position
    _labelPosition = Label::createWithTTF("Mouse not supported on this device", "fonts/arial.ttf", 22);
    _labelPosition->setPosition(Vec2(s.width/2, s.height/3));
    addChild(_labelPosition);


    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseEventTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseEventTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseEventTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseEventTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

MouseEventTest::~MouseEventTest()
{
    _eventDispatcher->removeEventListener(_mouseListener);
}

void MouseEventTest::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += tostr(static_cast<int>(e->getMouseButton()));
    _labelAction->setString(str.c_str());
}

void MouseEventTest::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += tostr(static_cast<int>(e->getMouseButton()));
    _labelAction->setString(str.c_str());
}

void MouseEventTest::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
    _labelPosition->setString(str.c_str());
}

void MouseEventTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
    _labelAction->setString(str.c_str());
}

std::string MouseEventTest::title() const
{
    return "Mouse Event Test";
}

std::string MouseEventTest::subtitle() const
{
    return "This tests the mouse events";
}

//------------------------------------------------------------------
//
// HideMouseTest
//
//------------------------------------------------------------------

HideMouseTest::HideMouseTest()
{
    
    _lis = EventListenerMouse::create();
    _lis->onMouseDown = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(false);
    };
    
    _lis->onMouseUp = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(true);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);
}

HideMouseTest::~HideMouseTest()
{
    _eventDispatcher->removeEventListener(_lis);
}

std::string HideMouseTest::title() const
{
    return "Hide/Show Mouse";
}

std::string HideMouseTest::subtitle() const
{
    return "Click to hide mouse";
}

//------------------------------------------------------------------
//
// CursorTest
//
//------------------------------------------------------------------

CursorTest::CursorTest()
{
    _cursor = 0;
    _lis = EventListenerMouse::create();
    _lis->onMouseDown = [this](Event* e){
        _cursor = (_cursor + 1) % 3;
        switch (_cursor) {
            case 1:
                Director::getInstance()->getOpenGLView()->setCursor("InputTest/cursor1.png");
                break;
            case 2:
                Director::getInstance()->getOpenGLView()->setCursor("InputTest/cursor2.png", Point::ANCHOR_MIDDLE);
                break;
            default:
                Director::getInstance()->getOpenGLView()->setDefaultCursor();
                break;
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);
}

CursorTest::~CursorTest()
{
    _eventDispatcher->removeEventListener(_lis);
}

std::string CursorTest::title() const
{
    return "Custom Mouse Cursor";
}

std::string CursorTest::subtitle() const
{
    return "Click to change cursor";
}

