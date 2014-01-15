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

#include "CCEventListenerMouse.h"

NS_CC_BEGIN

const std::string EventListenerMouse::LISTENER_ID = "__cc_mouse";

bool EventListenerMouse::checkAvailable()
{
    return true;
}

EventListenerMouse* EventListenerMouse::create()
{
    auto ret = new EventListenerMouse();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerMouse* EventListenerMouse::clone()
{
    auto ret = new EventListenerMouse();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->onMouseUp = onMouseUp;
        ret->onMouseDown = onMouseDown;
        ret->onMouseMove = onMouseMove;
        ret->onMouseScroll = onMouseScroll;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerMouse::EventListenerMouse()
: onMouseDown(nullptr)
, onMouseUp(nullptr)
, onMouseMove(nullptr)
, onMouseScroll(nullptr)
{
}

bool EventListenerMouse::init()
{
    auto listener = [this](Event* event){
        auto mouseEvent = static_cast<EventMouse*>(event);
        switch (mouseEvent->_mouseEventType)
        {
            case EventMouse::MouseEventType::MOUSE_DOWN:
                if(onMouseDown != nullptr)
                    onMouseDown(event);
                break;
            case EventMouse::MouseEventType::MOUSE_UP:
                if(onMouseUp != nullptr)
                    onMouseUp(event);
                break;
            case EventMouse::MouseEventType::MOUSE_MOVE:
                if(onMouseMove != nullptr)
                    onMouseMove(event);
                break;
            case EventMouse::MouseEventType::MOUSE_SCROLL:
                if(onMouseScroll != nullptr)
                    onMouseScroll(event);
                break;
            default:
                break;
        }
    };

    if (EventListener::init(Type::MOUSE, LISTENER_ID, listener))
    {
        return true;
    }

    return false;
}

NS_CC_END