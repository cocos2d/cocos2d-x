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

#ifndef __cocos2d_libs__CCTouchEventListener__
#define __cocos2d_libs__CCTouchEventListener__

#include "CCEventListener.h"
#include "CCTouch.h"

#include <vector>

NS_CC_BEGIN

class EventListenerTouchOneByOne : public EventListener
{
public:
    static EventListenerTouchOneByOne* create();
    
    virtual ~EventListenerTouchOneByOne();
    
    void setSwallowTouches(bool needSwallow);
    
    /// Overrides
    virtual EventListenerTouchOneByOne* clone() override;
    virtual bool checkAvailable() override;
    //

public:
    std::function<bool(Touch*, Event*)> onTouchBegan;
    std::function<void(Touch*, Event*)> onTouchMoved;
    std::function<void(Touch*, Event*)> onTouchEnded;
    std::function<void(Touch*, Event*)> onTouchCancelled;
    
private:
    EventListenerTouchOneByOne();
    bool init();
    
    std::vector<Touch*> _claimedTouches;
    bool _needSwallow;
    
    friend class EventDispatcher;
};


class EventListenerTouchAllAtOnce : public EventListener
{
public:
    static const ListenerID ID = static_cast<ListenerID>(Type::TOUCH_ALL_AT_ONCE);

    static EventListenerTouchAllAtOnce* create();
    virtual ~EventListenerTouchAllAtOnce();
    
    /// Overrides
    virtual EventListenerTouchAllAtOnce* clone() override;
    virtual bool checkAvailable() override;
    //
public:
    std::function<void(const std::vector<Touch*>&, Event*)> onTouchesBegan;
    std::function<void(const std::vector<Touch*>&, Event*)> onTouchesMoved;
    std::function<void(const std::vector<Touch*>&, Event*)> onTouchesEnded;
    std::function<void(const std::vector<Touch*>&, Event*)> onTouchesCancelled;
    
private:
    EventListenerTouchAllAtOnce();
    bool init();
private:
    
    friend class EventDispatcher;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCTouchEventListener__) */
