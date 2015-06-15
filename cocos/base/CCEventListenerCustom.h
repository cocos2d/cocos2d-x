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

#ifndef __cocos2d_libs__CCCustomEventListener__
#define __cocos2d_libs__CCCustomEventListener__

#include "base/CCEventListener.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class EventCustom;

/** @class EventListenerCustom
 * @brief @~english Custom event listener.
 * @~chinese 自定义事件监听器。
 * @code Usage:@~english
 *        auto dispatcher = Director::getInstance()->getEventDispatcher();
 *     Adds a listener:
 *
 *        auto callback = [](EventCustom* event){ do_some_thing(); };
 *        auto listener = EventListenerCustom::create(callback);
 *        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
 *
 *     Dispatchs a custom event:
 *
 *        EventCustom event("your_event_type");
 *        dispatcher->dispatchEvent(&event);
 *
 *     Removes a listener
 *
 *        dispatcher->removeEventListener(listener);
 * \endcode
 * @js cc._EventListenerCustom
 */
class CC_DLL EventListenerCustom : public EventListener
{
public:
    /** @~english Creates an event listener with name and callback.
     * @~chinese 根据名称和事件回调创建一个事件监听器。
     * @param eventName @~english The name of the event.
     * @~chinese 事件的名称。
     * @param callback @~english The callback function when the specified event was emitted.
     * @~chinese 当事件被触发时，将会调用指定的回调函数。
     * @return @~english An autoreleased EventListenerCustom object.
     * @~chinese 一个自动释放的自定义事件对象。
     */
    static EventListenerCustom* create(const std::string& eventName, const std::function<void(EventCustom*)>& callback);
    
    /// Overrides
    virtual bool checkAvailable() override;
    virtual EventListenerCustom* clone() override;
    
CC_CONSTRUCTOR_ACCESS:
    /** @~english Constructor  @~chinese 构造函数*/
    EventListenerCustom();
    
    /** @~english Initializes event with callback function  @~chinese 根据回调函数,初始化事件*/
    bool init(const ListenerID& listenerId, const std::function<void(EventCustom*)>& callback);
    
protected:
    std::function<void(EventCustom*)> _onCustomEvent;
    
    friend class LuaEventListenerCustom;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCCustomEventListener__) */
