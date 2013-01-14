/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

#include "CCScriptSupport.h"
#include "CCScheduler.h"

void CC_DLL cc_assert_script_compatible(bool cond, const char *msg)
{
    cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
    if (!cond && pEngine && pEngine->executeAssert(cond, msg))
    {
        return;
    }
}

NS_CC_BEGIN

// #pragma mark -
// #pragma mark CCScriptHandlerEntry

CCScriptHandlerEntry* CCScriptHandlerEntry::create(int nHandler)
{
    CCScriptHandlerEntry* entry = new CCScriptHandlerEntry(nHandler);
    entry->autorelease();
    return entry;
}

CCScriptHandlerEntry::~CCScriptHandlerEntry(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nHandler);
}

// #pragma mark -
// #pragma mark CCSchedulerScriptHandlerEntry

CCSchedulerScriptHandlerEntry* CCSchedulerScriptHandlerEntry::create(int nHandler, float fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = new CCSchedulerScriptHandlerEntry(nHandler);
    pEntry->init(fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool CCSchedulerScriptHandlerEntry::init(float fInterval, bool bPaused)
{
    m_pTimer = new CCTimer();
    m_pTimer->initWithScriptHandler(m_nHandler, fInterval);
    m_pTimer->autorelease();
    m_pTimer->retain();
    m_bPaused = bPaused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", m_nHandler, m_nEntryId);
    return true;
}

CCSchedulerScriptHandlerEntry::~CCSchedulerScriptHandlerEntry(void)
{
    m_pTimer->release();
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", m_nHandler, m_nEntryId);
}


// #pragma mark -
// #pragma mark CCTouchScriptHandlerEntry

CCTouchScriptHandlerEntry* CCTouchScriptHandlerEntry::create(int nHandler,
                                                             bool bIsMultiTouches,
                                                             int nPriority,
                                                             bool bSwallowsTouches)
{
    CCTouchScriptHandlerEntry* pEntry = new CCTouchScriptHandlerEntry(nHandler);
    pEntry->init(bIsMultiTouches, nPriority, bSwallowsTouches);
    pEntry->autorelease();
    return pEntry;
}

CCTouchScriptHandlerEntry::~CCTouchScriptHandlerEntry(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nHandler);
    LUALOG("[LUA] Remove touch event handler: %d", m_nHandler);
}

bool CCTouchScriptHandlerEntry::init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    m_bIsMultiTouches = bIsMultiTouches;
    m_nPriority = nPriority;
    m_bSwallowsTouches = bSwallowsTouches;
    
    return true;
}

// #pragma mark -
// #pragma mark CCScriptEngineManager

static CCScriptEngineManager* s_pSharedScriptEngineManager = NULL;


CCScriptEngineManager::~CCScriptEngineManager(void)
{
    removeScriptEngine();
}

void CCScriptEngineManager::setScriptEngine(CCScriptEngineProtocol *pScriptEngine)
{
    removeScriptEngine();
    m_pScriptEngine = pScriptEngine;
}

void CCScriptEngineManager::removeScriptEngine(void)
{
    if (m_pScriptEngine)
    {
        delete m_pScriptEngine;
        m_pScriptEngine = NULL;
    }
}

CCScriptEngineManager* CCScriptEngineManager::sharedManager(void)
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new CCScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}

void CCScriptEngineManager::purgeSharedManager(void)
{
    if (s_pSharedScriptEngineManager)
    {
        delete s_pSharedScriptEngineManager;
        s_pSharedScriptEngineManager = NULL;
    }
}

NS_CC_END
