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

#ifndef __cocos2d_libs__CCAccelerometerListener__
#define __cocos2d_libs__CCAccelerometerListener__

#include "base/CCEventListener.h"
#include "base/ccTypes.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/** @class EventListenerAcceleration
 * @brief @~english Acceleration event listener.
 * @~chinese 加速计事件监听器。
 * @js NA
 */
class CC_DLL EventListenerAcceleration : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** @~english Create a acceleration EventListener.
     *
     * @~chinese 创建一个加速计事件监听器。
     * 
     * @param callback @~english The acceleration callback method.
     * @~chinese 加速计事件的回调方法。
     * @return @~english An autoreleased EventListenerAcceleration object.
     * @~chinese 一个自动释放的加速计事件对象。
     */
    static EventListenerAcceleration* create(const std::function<void(Acceleration*, Event*)>& callback);
    
    /** @~english Destructor.
     * @~chinese 析构函数。
     */
    virtual ~EventListenerAcceleration();
    
    /// Overrides
    virtual EventListenerAcceleration* clone() override;
    virtual bool checkAvailable() override;
    
CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Constructor
     * @~chinese 
     * 构造函数
     * @js ctor
     */
    EventListenerAcceleration();

    /** @~english init a acceleration EventListener.
     *
     * @~chinese 初始化一个加速计事件监听器。
     * 
     * @param callback @~english The acceleration callback method.
     * @~chinese 加速计事件的回调方法。
     * @return @~english true is init successful.
     * @~chinese 初始化成功返回true
     */
    bool init(const std::function<void(Acceleration*, Event* event)>& callback);
    
private:
    std::function<void(Acceleration*, Event*)> onAccelerationEvent;
    
    friend class LuaEventListenerAcceleration;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCAccelerometerListener__) */
