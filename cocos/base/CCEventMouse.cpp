/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "base/CCEventMouse.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

EventMouse::EventMouse(MouseEventType mouseEventCode)
: Event(Type::MOUSE)
, _mouseEventType(mouseEventCode)
, _mouseButton(MouseButton::BUTTON_UNSET)
, _x(0.0f)
, _y(0.0f)
, _scrollX(0.0f)
, _scrollY(0.0f)
, _startPointCaptured(false)
{
}

// returns the current touch location in screen coordinates
Vec2 EventMouse::getLocationInView() const 
{ 
    return _point; 
}

// returns the previous touch location in screen coordinates
Vec2 EventMouse::getPreviousLocationInView() const 
{ 
    return _prevPoint; 
}

// returns the start touch location in screen coordinates
Vec2 EventMouse::getStartLocationInView() const 
{ 
    return _startPoint; 
}

// returns the current touch location in OpenGL coordinates
Vec2 EventMouse::getLocation() const
{ 
    return Director::getInstance()->convertToGL(_point); 
}

// returns the previous touch location in OpenGL coordinates
Vec2 EventMouse::getPreviousLocation() const
{ 
    return Director::getInstance()->convertToGL(_prevPoint);  
}

// returns the start touch location in OpenGL coordinates
Vec2 EventMouse::getStartLocation() const
{ 
    return Director::getInstance()->convertToGL(_startPoint);  
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
Vec2 EventMouse::getDelta() const
{     
    return getLocation() - getPreviousLocation();
}
NS_CC_END
