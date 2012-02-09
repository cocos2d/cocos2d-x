/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

NS_CC_BEGIN

CCSchedulerScriptHandlerEntry* CCSchedulerScriptHandlerEntry::entryWithHandler(int nHandler, ccTime fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = new CCSchedulerScriptHandlerEntry();
    pEntry->initWithHandler(nHandler, fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool CCSchedulerScriptHandlerEntry::initWithHandler(int nHandler, ccTime fInterval, bool bPaused)
{
    m_pTimer = new CCTimer();
    m_pTimer->initWithScriptHandler(nHandler, fInterval);
    m_pTimer->autorelease();
    m_pTimer->retain();
    m_nHandler = nHandler;
    m_bPaused = bPaused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", m_nHandler, m_entryID);
    return true;
}

CCSchedulerScriptHandlerEntry::CCSchedulerScriptHandlerEntry(void)
: m_pTimer(NULL)
, m_nHandler(0)
, m_bPaused(true)
, m_bMarkedForDeletion(false)
{
    static int nEntryCount = 0;
    m_nEntryID = ++nEntryCount;
}

CCSchedulerScriptHandlerEntry::~CCSchedulerScriptHandlerEntry(void)
{
    m_pTimer->release();
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeLuaHandler(m_nHandler);
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", m_nHandler, m_entryID);
}

// ----------------------------


CCTouchScriptHandlerEntry* CCTouchScriptHandlerEntry::entryWithHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    CCTouchScriptHandlerEntry* pEntry = new CCTouchScriptHandlerEntry();
    pEntry->initWithHandler(nHandler, bIsMultiTouches, nPriority, bSwallowsTouches);
    pEntry->autorelease();
    return pEntry;
}

CCTouchScriptHandlerEntry::CCTouchScriptHandlerEntry(void)
: m_nHandler(0)
, m_bIsMultiTouches(false)
, m_nPriority(0)
, m_bSwallowsTouches(false)
{
}

CCTouchScriptHandlerEntry::~CCTouchScriptHandlerEntry(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeLuaHandler(m_nHandler);
    LUALOG("[LUA] Remove touch event handler: %d", m_nHandler);
}

bool CCTouchScriptHandlerEntry::initWithHandler(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    m_nHandler = nHandler;
    m_bIsMultiTouches = bIsMultiTouches;
    m_nPriority = nPriority;
    m_bSwallowsTouches = bSwallowsTouches;
    
    return true;
}

// ----------------------------


static CCScriptEngineManager* s_pSharedScriptEngineManager = NULL;


CCScriptEngineManager::~CCScriptEngineManager(void)
{
    removeScriptEngine();
}

void CCScriptEngineManager::setScriptEngine(CCScriptEngineProtocol *pScriptEngine)
{
    removeScriptEngine();
	m_pScriptEngine = pScriptEngine;
    m_pScriptEngine->retain();
}

void CCScriptEngineManager::removeScriptEngine(void)
{
    if (m_pScriptEngine)
    {
        m_pScriptEngine->release();
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

NS_CC_END;
