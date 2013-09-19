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

#include "CCCustomEventListener.h"
#include "CCCustomEvent.h"

NS_CC_BEGIN

CustomEventListener::CustomEventListener()
: _onCustomEvent(nullptr)
{
}

CustomEventListener* CustomEventListener::create(const std::string& eventName, std::function<void(CustomEvent*)> callback)
{
    CustomEventListener* ret = new CustomEventListener();
    if (ret && ret->init(eventName, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool CustomEventListener::init(const std::string& eventName, std::function<void(CustomEvent*)>callback)
{
    bool ret = false;
    
    _onCustomEvent = callback;
    
    auto listener = [this](Event* event){
        if (_onCustomEvent != nullptr)
        {
            _onCustomEvent(static_cast<CustomEvent*>(event));
        }
    };
    
    if (EventListener::init(eventName, listener))
    {
        ret = true;
    }
    return ret;
}

CustomEventListener* CustomEventListener::clone()
{
    CustomEventListener* ret = new CustomEventListener();
    if (ret && ret->init(_type, _onCustomEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool CustomEventListener::checkAvaiable()
{
    bool ret = false;
    if (EventListener::checkAvaiable() && _onCustomEvent != nullptr)
    {
        ret = true;
    }
    return ret;
}

NS_CC_END
