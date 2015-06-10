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

#ifndef __cocos2d_libs__CCCustomEvent__
#define __cocos2d_libs__CCCustomEvent__

#include <string>
#include "base/CCEvent.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/** @class EventCustom
 * @brief @~english Custom event.
 * @~chinese 用户自定义事件
 */
class CC_DLL EventCustom : public Event
{
public:
    /** 
     * @~english Constructor.
     * @~chinese 构造函数
     * @param eventName
     * @~english A given name of the custom event. 
     * @~chinese 设置一个自定义事件名称
     * @js ctor
     */
    EventCustom(const std::string& eventName);
    
    /**
     * @~english Sets user data. 
     * @~chinese 设置用户数据
     *
     * @param data
     * @~english  The user data pointer, it's a void*. 
     * @~chinese 用户数据指针。类型是void*
     */
    inline void setUserData(void* data) { _userData = data; };
    
    /**
     * @~english Gets user data. 
     * @~chinese 获取用户数据
     *
     * @return
     * @~english The user data pointer, it's a void*. 
     * @~chinese 用户数据指针。类型是void*
     */
    inline void* getUserData() const { return _userData; };
    
    /**
     *@~english Gets event name. 
     *@~chinese 获取事件名称
     *
     *
     * @return
     * @~english The name of the event. 
     * @~chinese 获取自定义事件名
     */
    inline const std::string& getEventName() const { return _eventName; };
protected:
    void* _userData;       ///< User data
    std::string _eventName;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCCustomEvent__) */
