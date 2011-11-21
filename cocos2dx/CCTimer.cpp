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

#include "CCTimer.h"
#include "LuaEngine.h"

namespace cocos2d
{

CCTimer::CCTimer()
: m_pTarget(NULL)
, m_refID(0)
, m_fInterval(0.0f)
, m_fElapsed(0.0f)
, m_pfnSelector(NULL)
{
}

CCTimer::~CCTimer()
{
    if (m_refID)
    {
        LuaEngine::sharedEngine()->releaseRefID(m_refID);
    }
}

CCTimer* CCTimer::timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector)
{
    CCTimer *pTimer = new CCTimer();
    
    pTimer->initWithTarget(pTarget, pfnSelector);
    pTimer->autorelease();
    
    return pTimer;
}

CCTimer* CCTimer::timerWithScriptFunc(int refid, ccTime fSeconds)
{
    CCTimer *pTimer = new CCTimer();
    
    pTimer->initWithScriptFunc(refid, fSeconds);
    pTimer->autorelease();
    
    return pTimer;
}

CCTimer* CCTimer::timerWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds)
{
    CCTimer *pTimer = new CCTimer();
    
    pTimer->initWithTarget(pTarget, pfnSelector, fSeconds);
    pTimer->autorelease();
    
    return pTimer;
}

bool CCTimer::initWithScriptFunc(int newRefID, ccTime fSeconds)
{
    LuaEngine::sharedEngine()->retainRefID(newRefID);
    if (m_refID)
    {
        LuaEngine::sharedEngine()->releaseRefID(m_refID);
    }
    m_refID = newRefID;
    m_fInterval = fSeconds;
    m_fElapsed = -1;
    return true;
}


bool CCTimer::initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector)
{
    return initWithTarget(pTarget, pfnSelector, 0);
}

bool CCTimer::initWithTarget(SelectorProtocol *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds)
{
    m_pTarget = pTarget;
    m_pfnSelector = pfnSelector;
    m_fElapsed = -1;
    m_fInterval = fSeconds;
    return true;
}

void CCTimer::update(ccTime dt)
{
    if (m_fElapsed == -1)
    {
        m_fElapsed = 0;
    }
    else
    {
        m_fElapsed += dt;
    }
    
    if (m_fElapsed >= m_fInterval)
    {
        if (m_pfnSelector)
        {
            (m_pTarget->*m_pfnSelector)(m_fElapsed);
            m_fElapsed = 0;
        }
        if (m_refID)
        {
            LuaEngine::sharedEngine()->executeSchedule(m_refID, m_fElapsed);
            m_fElapsed = 0;
        }
    }
}

    
} // namespace cocos2d

