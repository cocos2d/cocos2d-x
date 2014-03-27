/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#include "CCScriptSupport.h"

#if CC_ENABLE_SCRIPT_BINDING

#include "CCScheduler.h"

bool CC_DLL cc_assert_script_compatible(const char *msg)
{
    cocos2d::ScriptEngineProtocol* engine = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine();
    if (engine && engine->handleAssert(msg))
    {
        return true;
    }
    return false;
}

NS_CC_BEGIN

// 
// // ScriptHandlerEntry

ScriptHandlerEntry* ScriptHandlerEntry::create(int handler)
{
    ScriptHandlerEntry* entry = new ScriptHandlerEntry(handler);
    entry->autorelease();
    return entry;
}

ScriptHandlerEntry::~ScriptHandlerEntry(void)
{
    if (_handler != 0 )
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_handler);
        LUALOG("[LUA] Remove event handler: %d", _handler);
        _handler = 0;
    }
}

// 
// // SchedulerScriptHandlerEntry

SchedulerScriptHandlerEntry* SchedulerScriptHandlerEntry::create(int handler, float interval, bool paused)
{
    SchedulerScriptHandlerEntry* entry = new SchedulerScriptHandlerEntry(handler);
    entry->init(interval, paused);
    entry->autorelease();
    return entry;
}

bool SchedulerScriptHandlerEntry::init(float interval, bool paused)
{
    _timer = new TimerScriptHandler();
    _timer->initWithScriptHandler(_handler, interval);
    _paused = paused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", _handler, _entryId);
    return true;
}

SchedulerScriptHandlerEntry::~SchedulerScriptHandlerEntry(void)
{
    _timer->release();
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", _handler, _entryId);
}


// 
// // TouchScriptHandlerEntry

TouchScriptHandlerEntry* TouchScriptHandlerEntry::create(int handler,
                                                             bool isMultiTouches,
                                                             int priority,
                                                             bool swallowsTouches)
{
    TouchScriptHandlerEntry* entry = new TouchScriptHandlerEntry(handler);
    entry->init(isMultiTouches, priority, swallowsTouches);
    entry->autorelease();
    return entry;
}

TouchScriptHandlerEntry::~TouchScriptHandlerEntry(void)
{
}

bool TouchScriptHandlerEntry::init(bool isMultiTouches, int priority, bool swallowsTouches)
{
    _isMultiTouches = isMultiTouches;
    _priority = priority;
    _swallowsTouches = swallowsTouches;
    
    return true;
}

// 
// // ScriptEngineManager

static ScriptEngineManager* s_pSharedScriptEngineManager = nullptr;


ScriptEngineManager::~ScriptEngineManager(void)
{
    removeScriptEngine();
}

void ScriptEngineManager::setScriptEngine(ScriptEngineProtocol *scriptEngine)
{
	if (_scriptEngine != scriptEngine)
	{
		removeScriptEngine();
		_scriptEngine = scriptEngine;
	}
}

void ScriptEngineManager::removeScriptEngine(void)
{
    if (_scriptEngine)
    {
        delete _scriptEngine;
        _scriptEngine = nullptr;
    }
}

ScriptEngineManager* ScriptEngineManager::getInstance()
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new ScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}

void ScriptEngineManager::destroyInstance()
{
    if (s_pSharedScriptEngineManager)
    {
        delete s_pSharedScriptEngineManager;
        s_pSharedScriptEngineManager = nullptr;
    }
}

NS_CC_END

#endif // #if CC_ENABLE_SCRIPT_BINDING
