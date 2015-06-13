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

#ifndef __cocos2d_libs__CCTouchEventListener__
#define __cocos2d_libs__CCTouchEventListener__

#include "base/CCEventListener.h"
#include <vector>

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Touch;

/** @class EventListenerTouchOneByOne
 * @brief @~english Single touch event listener.
 * @~chinese 单点触摸事件监听器。
 * @js cc._EventListenerTouchOneByOne
 */
class CC_DLL EventListenerTouchOneByOne : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** @~english Create a one by one touch event listener.
     * @~chinese 创建单点触摸事件监听器。
     * @return @~english An autoreleased EventListenerTouchOneByOne object.
     * @~chinese 一个自动释放的单点触摸监听器对象。
     */
    static EventListenerTouchOneByOne* create();
    
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     */
    virtual ~EventListenerTouchOneByOne();
    
    /** @~english Whether or not to swall touches.
     *
     * @~chinese 是否吞噬触摸事件。
     * 
     * @param needSwallow @~english True if needs to swall touches.
     * @~chinese 设置为true则吞噬触摸事件。
     */
    void setSwallowTouches(bool needSwallow);
    /** @~english Is swall touches or not.
     *
     * @~chinese Is swall touches the or not.
     * 
     * @return @~english True if needs to swall touches.
     * @~chinese 是否吞噬触摸事件。
     */
    bool isSwallowTouches();
    
    /// Overrides
    virtual EventListenerTouchOneByOne* clone() override;
    virtual bool checkAvailable() override;
    //

public:

    typedef std::function<bool(Touch*, Event*)> ccTouchBeganCallback;
    typedef std::function<void(Touch*, Event*)> ccTouchCallback;

    ccTouchBeganCallback onTouchBegan;
    ccTouchCallback onTouchMoved;
    ccTouchCallback onTouchEnded;
    ccTouchCallback onTouchCancelled;
    
CC_CONSTRUCTOR_ACCESS:
    EventListenerTouchOneByOne();
    bool init();
    
private:
    std::vector<Touch*> _claimedTouches;
    bool _needSwallow;
    
    friend class EventDispatcher;
};

/** @class EventListenerTouchAllAtOnce
 * @brief @~english Multiple touches event listener.
 * @~chinese 多点触摸事件监听器。
 */
class CC_DLL EventListenerTouchAllAtOnce : public EventListener
{
public:
    static const std::string LISTENER_ID;
    
    /** @~english Create a all at once event listener.
     *
     * @~chinese 创建多点触摸事件监听器。
     * 
     * @return @~english An autoreleased EventListenerTouchAllAtOnce object.
     * @~chinese 一个自动释放的多点触摸监听器对象。
     */
    static EventListenerTouchAllAtOnce* create();
    /** @~english Destructor.
     * @~chinese 析构函数。
     * @js NA
     */
    virtual ~EventListenerTouchAllAtOnce();
    
    /// Overrides
    virtual EventListenerTouchAllAtOnce* clone() override;
    virtual bool checkAvailable() override;
    //
public:

    typedef std::function<void(const std::vector<Touch*>&, Event*)> ccTouchesCallback;

    ccTouchesCallback onTouchesBegan;
    ccTouchesCallback onTouchesMoved;
    ccTouchesCallback onTouchesEnded;
    ccTouchesCallback onTouchesCancelled;
    
CC_CONSTRUCTOR_ACCESS:
    EventListenerTouchAllAtOnce();
    bool init();
private:
    
    friend class EventDispatcher;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCTouchEventListener__) */
