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

#include <algorithm>

#include "CCScriptEventDispatcher.h"
#include "base/CCScriptSupport.h"

NS_CC_BEGIN

CCScriptEventListenersForEvent CCScriptEventDispatcher::s_emptyListenersForEvent;
CCScriptEventListenersForDispatcher CCScriptEventDispatcher::s_emptyListeners;
int CCScriptEventDispatcher::s_nextScriptEventHandleIndex = 0;
int CCScriptEventDispatcher::s_removeTag = 0;

CCScriptEventDispatcher::CCScriptEventDispatcher()
: m_scriptEventListeners(NULL)
{
}

CCScriptEventDispatcher::~CCScriptEventDispatcher()
{
    if (m_scriptEventListeners)
    {
        removeAllScriptEventListeners();
        delete m_scriptEventListeners;
    }
}

int CCScriptEventDispatcher::addScriptEventListener(int event, int listener, int tag /* = 0 */, int priority /* = 0 */)
{
    if (!m_scriptEventListeners)
    {
        m_scriptEventListeners = new CCScriptEventListenersForDispatcher();
    }

    s_nextScriptEventHandleIndex++;
    CCScriptEventListenersForEvent &listeners = (*m_scriptEventListeners)[event];
    listeners.push_back(CCScriptHandlePair(s_nextScriptEventHandleIndex, listener, tag, priority));
    std::sort(listeners.begin(), listeners.end(), sortListenerCompare);

    return s_nextScriptEventHandleIndex;
}

void CCScriptEventDispatcher::removeScriptEventListener(int handle)
{
    if (!m_scriptEventListeners) return;

    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEventIterator it2 = it->second.begin();
        for (; it2 != it->second.end(); ++it2)
        {
            if (it2->index == handle)
            {
                ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(it2->listener);
                LUALOG("[LUA] Remove script event listener: %d", it2->listener);
                it->second.erase(it2);
                return;
            }
        }
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByEvent(int event)
{
    if (!m_scriptEventListeners) return;

    ScriptEngineProtocol *engine = ScriptEngineManager::sharedManager()->getScriptEngine();
    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->find(event);
    if (it != m_scriptEventListeners->end())
    {
        CCScriptEventListenersForEvent &listeners = it->second;
        CCScriptEventListenersForEventIterator it2 = listeners.begin();
        for (; it2 != listeners.end(); ++it2)
        {
            engine->removeScriptHandler(it2->listener);
            LUALOG("[LUA] Remove script event listener: %d", it2->listener);
        }
        m_scriptEventListeners->erase(it);
    }
}

void CCScriptEventDispatcher::removeScriptEventListenersByTag(int tag)
{
    if (!m_scriptEventListeners) return;

    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    s_removeTag = tag;
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEvent &listeners = it->second;
        remove_if(listeners.begin(), listeners.end(), removeListenerByTag);
    }
}

void CCScriptEventDispatcher::removeAllScriptEventListeners()
{
    if (!m_scriptEventListeners) return;

    ScriptEngineProtocol *engine = ScriptEngineManager::sharedManager()->getScriptEngine();
    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->begin();
    for (; it != m_scriptEventListeners->end(); ++it)
    {
        CCScriptEventListenersForEventIterator it2 = it->second.begin();
        for (; it2 != it->second.end(); ++it2)
        {
            engine->removeScriptHandler(it2->listener);
            LUALOG("[LUA] Remove script event listener: %d", it2->listener);
        }
    }
    m_scriptEventListeners->clear();
}

bool CCScriptEventDispatcher::hasScriptEventListener(int event)
{
    return m_scriptEventListeners && m_scriptEventListeners->find(event) != m_scriptEventListeners->end();
}

CCScriptEventListenersForEvent &CCScriptEventDispatcher::getScriptEventListenersByEvent(int event) const
{
    if (!m_scriptEventListeners) return s_emptyListenersForEvent;

    CCScriptEventListenersForDispatcherIterator it = m_scriptEventListeners->find(event);
    return  it != m_scriptEventListeners->end() ? it->second : s_emptyListenersForEvent;
}

CCScriptEventListenersForDispatcher &CCScriptEventDispatcher::getAllScriptEventListeners() const
{
    return m_scriptEventListeners ? *m_scriptEventListeners : s_emptyListeners;
}

bool CCScriptEventDispatcher::sortListenerCompare(const CCScriptHandlePair &a, const CCScriptHandlePair &b)
{
    return a.priority < b.priority;
}

bool CCScriptEventDispatcher::removeListenerByTag(CCScriptHandlePair &p)
{
    if (p.tag == s_removeTag)
    {
        ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(p.listener);
        return true;
    }
    else
    {
        return false;
    }
}

NS_CC_END
