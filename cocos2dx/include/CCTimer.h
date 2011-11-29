/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 
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

#ifndef __CCTIMER_H_
#define __CCTIMER_H_

#include "CCObject.h"
#include "selector_protocol.h"

namespace cocos2d
{
//
// CCTimer
//
/** @brief Light weight timer */
class CC_DLL CCTimer : public CCObject
{
public:
    CCTimer(void);
    ~CCTimer();
    
    /** get interval in seconds */
    inline ccTime getInterval(void) {
        return m_fInterval;
    }
    /** set interval in seconds */
    inline void setInterval(ccTime fInterval) {
        m_fInterval = fInterval;
    }
    
    /** Initializes a timer with a target and a selector. */
    bool initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);
    
    /** Initializes a timer with a target, a selector and an interval in seconds. */
    bool initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);
    
#if LUA_ENGINE
    bool initWithScriptFunc(int functionRefID, ccTime fSeconds);
#endif
    
    /** triggers the timer */
    void update(ccTime dt);
    
public:
    /** Allocates a timer with a target and a selector. */
    static CCTimer* timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector);
    
    /** Allocates a timer with a script function. */
    static CCTimer* timerWithScriptFunc(int refid, ccTime fSeconds);
    
    /** Allocates a timer with a target, a selector and an interval in seconds. */
    static CCTimer* timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds);
    
public:
    SEL_SCHEDULE m_pfnSelector;
    ccTime m_fInterval;
    
#if LUA_ENGINE
    int m_functionRefID;
#endif
    
protected:
    SelectorProtocol *m_pTarget;
    ccTime m_fElapsed;
};
    
} // namespace cocos2d

#endif // __CCTIMER_H_
