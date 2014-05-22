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

#include "CCEventListenerAssetsManager.h"
#include "CCEventAssetsManager.h"
#include "AssetsManager.h"

NS_CC_EXT_BEGIN

const std::string EventListenerAssetsManager::LISTENER_ID = "__cc_assets_manager_";

EventListenerAssetsManager::EventListenerAssetsManager()
: _onAssetsManagerEvent(nullptr)
, _assetsManager(nullptr)
{
}

EventListenerAssetsManager* EventListenerAssetsManager::create(cocos2d::extension::AssetsManager *assetsManager, const std::function<void(EventAssetsManager*)>& callback)
{
    EventListenerAssetsManager* ret = new EventListenerAssetsManager();
    if (ret && ret->init(assetsManager, callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerAssetsManager::init(const AssetsManager *assetsManager, const std::function<void(EventAssetsManager*)>& callback)
{
    bool ret = false;
    
    _assetsManager = assetsManager;
    _onAssetsManagerEvent = callback;
    
    auto func = [this](EventCustom *event) -> void
    {
        EventAssetsManager *eventAssetsManager = dynamic_cast<EventAssetsManager*>(event);
        _onAssetsManagerEvent(eventAssetsManager);
    };
    std::string pointer = StringUtils::format("%p", assetsManager);
    if (EventListenerCustom::init(LISTENER_ID + pointer, func))
    {
        ret = true;
    }
    return ret;
}

EventListenerAssetsManager* EventListenerAssetsManager::clone()
{
    EventListenerAssetsManager* ret = new EventListenerAssetsManager();
    if (ret && ret->init(_assetsManager, _onAssetsManagerEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool EventListenerAssetsManager::checkAvailable()
{
    bool ret = false;
    if (EventListener::checkAvailable() && _assetsManager != nullptr && _onAssetsManagerEvent != nullptr)
    {
        ret = true;
    }
    return ret;
}

NS_CC_EXT_END