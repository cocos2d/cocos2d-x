/****************************************************************************
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

#include "CCEventListenerAssetsManagerEx.h"
#include "CCEventAssetsManagerEx.h"
#include "AssetsManagerEx.h"
#include "base/ccUTF8.h"

NS_CC_EXT_BEGIN

const std::string EventListenerAssetsManagerEx::LISTENER_ID = "__cc_assets_manager_";

EventListenerAssetsManagerEx::EventListenerAssetsManagerEx()
: _onAssetsManagerExEvent(nullptr)
, _AssetsManagerEx(nullptr)
{
}

EventListenerAssetsManagerEx* EventListenerAssetsManagerEx::create(cocos2d::extension::AssetsManagerEx *AssetsManagerEx, const std::function<void(EventAssetsManagerEx*)>& callback)
{
    EventListenerAssetsManagerEx* ret = new (std::nothrow) EventListenerAssetsManagerEx();
    if (ret && ret->init(AssetsManagerEx, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerAssetsManagerEx::init(const AssetsManagerEx *AssetsManagerEx, const std::function<void(EventAssetsManagerEx*)>& callback)
{
    bool ret = false;
    
    _AssetsManagerEx = AssetsManagerEx;
    _onAssetsManagerExEvent = callback;
    
    auto func = [this](EventCustom *event) -> void
    {
        EventAssetsManagerEx *eventAssetsManagerEx = dynamic_cast<EventAssetsManagerEx*>(event);
        _onAssetsManagerExEvent(eventAssetsManagerEx);
    };
    std::string pointer = StringUtils::format("%p", AssetsManagerEx);
    if (EventListenerCustom::init(LISTENER_ID + pointer, func))
    {
        ret = true;
    }
    return ret;
}

EventListenerAssetsManagerEx* EventListenerAssetsManagerEx::clone()
{
    EventListenerAssetsManagerEx* ret = new (std::nothrow) EventListenerAssetsManagerEx();
    if (ret && ret->init(_AssetsManagerEx, _onAssetsManagerExEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerAssetsManagerEx::checkAvailable()
{
    bool ret = false;
    if (EventListener::checkAvailable() && _AssetsManagerEx != nullptr && _onAssetsManagerExEvent != nullptr)
    {
        ret = true;
    }
    return ret;
}

NS_CC_EXT_END
