/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCAccelerationEventListener.h"
#include "CCAccelerationEvent.h"

NS_CC_BEGIN

AccelerationEventListener::AccelerationEventListener()
{

}

AccelerationEventListener::~AccelerationEventListener()
{
    CCLOGINFO("In the destructor of AccelerationEventListener. %p", this);
}

AccelerationEventListener* AccelerationEventListener::create(std::function<void(Acceleration*, Event* event)> callback)
{
    AccelerationEventListener* ret = new AccelerationEventListener();
    if (ret && ret->init(callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool AccelerationEventListener::init(std::function<void(Acceleration*, Event* event)> callback)
{
    auto listener = [this](Event* event){
        auto accEvent = static_cast<AccelerationEvent*>(event);
        this->onAccelerationEvent(&accEvent->acc, event);
    };
    
    if (EventListener::init(AccelerationEvent::EVENT_TYPE, listener))
    {
        onAccelerationEvent = callback;
        return true;
    }
    
    return false;
}

AccelerationEventListener* AccelerationEventListener::clone()
{
    auto ret = new AccelerationEventListener();
    
    if (ret && ret->init(onAccelerationEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool AccelerationEventListener::checkAvaiable()
{
    CCASSERT(onAccelerationEvent, "");
    
    return true;
}

NS_CC_END
