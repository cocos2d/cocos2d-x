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

#ifndef __cocos2d_libs__CCEventListenerAssetsManagerEx__
#define __cocos2d_libs__CCEventListenerAssetsManagerEx__

#include "base/CCEventListener.h"
#include "base/CCEventListenerCustom.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

class EventAssetsManagerEx;
class AssetsManagerEx;

/**
 *  Usage:
 *        auto dispatcher = Director::getInstance()->getEventDispatcher();
 *        auto manager = AssetsManagerEx::create(manifestUrl, storagePath);
 *     Adds a listener:
 *
 *        auto callback = [](EventAssetsManagerEx* event){ do_some_thing(); };
 *        auto listener = EventListenerAssetsManagerEx::create(manager, callback);
 *        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
 *
 *     Removes a listener
 *
 *        dispatcher->removeEventListener(listener);
 */
class CC_EX_DLL EventListenerAssetsManagerEx : public cocos2d::EventListenerCustom
{
public:
    friend class AssetsManagerEx;
    
    /** Creates an event listener with type and callback.
     *  @param eventType The type of the event.
     *  @param callback The callback function when the specified event was emitted.
     */
    static EventListenerAssetsManagerEx* create(AssetsManagerEx *AssetsManagerEx, const std::function<void(EventAssetsManagerEx*)>& callback);
    
    /// Overrides
    virtual bool checkAvailable() override;
    virtual EventListenerAssetsManagerEx* clone() override;
    
CC_CONSTRUCTOR_ACCESS:
    /** Constructor */
    EventListenerAssetsManagerEx();
    
    /** Initializes event with type and callback function */
    bool init(const AssetsManagerEx *AssetsManagerEx, const std::function<void(EventAssetsManagerEx*)>& callback);
    
protected:
    static const std::string LISTENER_ID;
    
    std::function<void(EventAssetsManagerEx*)> _onAssetsManagerExEvent;
    
    const AssetsManagerEx *_AssetsManagerEx;
    
    //friend class luaEventListenerAssetsManagerEx;
};

NS_CC_EXT_END

#endif /* defined(__cocos2d_libs__CCEventListenerAssetsManagerEx__) */
