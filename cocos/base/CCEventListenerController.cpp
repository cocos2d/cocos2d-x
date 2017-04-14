/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014-2017 Chukong Technologies Inc.
 
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

#include "base/CCEventListenerController.h"
#include "base/CCEventController.h"
#include "base/ccMacros.h"
#include "base/CCController.h"

NS_CC_BEGIN

const std::string EventListenerController::LISTENER_ID = "__cc_controller";

EventListenerController* EventListenerController::create()
{
    auto ret = new (std::nothrow) EventListenerController();
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

bool EventListenerController::init()
{
    auto listener = [this](Event* event){
        auto evtController = static_cast<EventController*>(event);
        switch (evtController->getControllerEventType())
        {
        case EventController::ControllerEventType::CONNECTION:
            if (evtController->isConnected())
            {
                if (this->onConnected)
                    this->onConnected(evtController->getController(), event);
            }
            else
            {
                if (this->onDisconnected)
                    this->onDisconnected(evtController->getController(), event);
            }
            break;
        case EventController::ControllerEventType::BUTTON_STATUS_CHANGED:
            {
                const auto&  keyStatus = evtController->_controller->_allKeyStatus[evtController->_keyCode];
                const auto&  keyPrevStatus = evtController->_controller->_allKeyPrevStatus[evtController->_keyCode];

                if (this->onKeyDown && keyStatus.isPressed && !keyPrevStatus.isPressed)
                {
                    this->onKeyDown(evtController->_controller, evtController->_keyCode, event);
                }
                else if (this->onKeyUp && !keyStatus.isPressed && keyPrevStatus.isPressed)
                {
                    this->onKeyUp(evtController->_controller, evtController->_keyCode, event);
                }
                else if (this->onKeyRepeat && keyStatus.isPressed && keyPrevStatus.isPressed)
                {
                    this->onKeyRepeat(evtController->_controller, evtController->_keyCode, event);
                }
            }
            break;
        case EventController::ControllerEventType::AXIS_STATUS_CHANGED:
            {
                if (this->onAxisEvent)
                {
                    this->onAxisEvent(evtController->_controller, evtController->_keyCode, event);
                }
            }
            break;
        default:
            CCASSERT(false, "Invalid EventController type");
            break;
        }
    };

    if (EventListener::init(EventListener::Type::GAME_CONTROLLER, LISTENER_ID, listener))
    {
        return true;
    }
    return false;
}

bool EventListenerController::checkAvailable()
{
    return true;
}

EventListenerController* EventListenerController::clone()
{
    return nullptr;
}

NS_CC_END