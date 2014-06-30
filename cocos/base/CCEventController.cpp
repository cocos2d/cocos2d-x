/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCEventController.h"

NS_CC_BEGIN

EventController::EventController(ControllerEventType type, Controller* controller, ControllerElement* element)
: Event(Type::GAME_CONTROLLER)
, _controllerEventType(type)
, _element(element)
, _controller(controller)
, _isConnected(true)
{
    
}

EventController::EventController(ControllerEventType type, Controller* controller, bool isConnected)
: Event(Type::GAME_CONTROLLER)
, _controllerEventType(type)
, _element(nullptr)
, _controller(controller)
, _isConnected(isConnected)
{
    
}

EventController::ControllerEventType EventController::getControllerEventType() const
{
    return _controllerEventType;
}

Controller* EventController::getController() const
{
    return _controller;
}

ControllerElement* EventController::getControllerElement() const
{
    return _element;
}

bool EventController::isConnected() const
{
    return _isConnected;
}

NS_CC_END
