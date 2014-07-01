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

#ifndef __cocos2d_libs__EventListenerController__
#define __cocos2d_libs__EventListenerController__

#include "base/CCPlatformMacros.h"
#include "base/CCEventListener.h"

NS_CC_BEGIN

class Event;
class Controller;
class ControllerButtonInput;
class ControllerAxisInput;

class EventListenerController : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
	static EventListenerController* create();
    
    /// Overrides
    virtual bool checkAvailable() override;
    virtual EventListenerController* clone() override;
    
	std::function<void(Controller*, Event*)> onConnected;
	std::function<void(Controller*, Event*)> onDisconnected;
    
    std::function<void(Controller*, ControllerButtonInput*, Event*)> onButtonPressed;
    std::function<void(Controller*, ControllerButtonInput*, Event*)> onButtonReleased;
	std::function<void(Controller*, ControllerButtonInput*, Event*)> onButtonValueChanged;
    
	std::function<void(Controller*, ControllerAxisInput*, Event*)> onAxisValueChanged;
    
protected:
    bool init();
};

NS_CC_END

#endif /* defined(__cocos2d_libs__EventListenerController__) */
