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

bool CC_DLL cc_assert_script_compatible(const char *msg)
{
    cocos2d::ScriptEngineProtocol* pEngine = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine();
    if (pEngine && pEngine->handleAssert(msg))
    {
        return true;
    }
    return false;
}

NS_CC_BEGIN

// #pragma mark -
// #pragma mark ScriptHandlerEntry

ScriptHandlerEntry* ScriptHandlerEntry::create(int nHandler)
{
    ScriptHandlerEntry* entry = new ScriptHandlerEntry(nHandler);
    entry->autorelease();
    return entry;
}

ScriptHandlerEntry::~ScriptHandlerEntry(void)
{
    ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_handler);
}

// #pragma mark -
// #pragma mark SchedulerScriptHandlerEntry

SchedulerScriptHandlerEntry* SchedulerScriptHandlerEntry::create(int nHandler, float fInterval, bool bPaused)
{
    SchedulerScriptHandlerEntry* pEntry = new SchedulerScriptHandlerEntry(nHandler);
    pEntry->init(fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool SchedulerScriptHandlerEntry::init(float fInterval, bool bPaused)
{
    _timer = new Timer();
    _timer->initWithScriptHandler(_handler, fInterval);
    _timer->autorelease();
    _timer->retain();
    _paused = bPaused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", _handler, _entryId);
    return true;
}

SchedulerScriptHandlerEntry::~SchedulerScriptHandlerEntry(void)
{
    _timer->release();
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", _handler, _entryId);
}


// #pragma mark -
// #pragma mark TouchScriptHandlerEntry

TouchScriptHandlerEntry* TouchScriptHandlerEntry::create(int nHandler,
                                                             bool bIsMultiTouches,
                                                             int nPriority,
                                                             bool bSwallowsTouches)
{
    TouchScriptHandlerEntry* pEntry = new TouchScriptHandlerEntry(nHandler);
    pEntry->init(bIsMultiTouches, nPriority, bSwallowsTouches);
    pEntry->autorelease();
    return pEntry;
}

TouchScriptHandlerEntry::~TouchScriptHandlerEntry(void)
{
    ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_handler);
    LUALOG("[LUA] Remove touch event handler: %d", _handler);
}

bool TouchScriptHandlerEntry::init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    _isMultiTouches = bIsMultiTouches;
    _priority = nPriority;
    _swallowsTouches = bSwallowsTouches;
    
    return true;
}

// #pragma mark -
// #pragma mark ScriptEngineManager

static ScriptEngineManager* s_pSharedScriptEngineManager = NULL;


ScriptEngineManager::~ScriptEngineManager(void)
{
    removeScriptEngine();
}

void ScriptEngineManager::setScriptEngine(ScriptEngineProtocol *pScriptEngine)
{
    removeScriptEngine();
    _scriptEngine = pScriptEngine;
}

void ScriptEngineManager::removeScriptEngine(void)
{
    if (_scriptEngine)
    {
        delete _scriptEngine;
        _scriptEngine = NULL;
    }
}

ScriptEngineManager* ScriptEngineManager::sharedManager(void)
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new ScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}

void ScriptEngineManager::purgeSharedManager(void)
{
    if (s_pSharedScriptEngineManager)
    {
        delete s_pSharedScriptEngineManager;
        s_pSharedScriptEngineManager = NULL;
    }
}

NS_CC_END
