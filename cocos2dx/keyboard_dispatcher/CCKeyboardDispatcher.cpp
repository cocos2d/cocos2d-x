/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#include "CCKeyboardDispatcher.h"
#include "CCKeyboardHandler.h"
#include "cocoa/CCArray.h"
#include "support/data_support/ccCArray.h"

#include <algorithm>

NS_CC_BEGIN

/**
 * Used for sort
 */
static int less(const CCObject* p1, const CCObject* p2)
{
    return ((CCKeyboardHandler*)p1)->getPriority() < ((CCKeyboardHandler*)p2)->getPriority();
}


//------------------------------------------------------------------
//
// CCKeypadDispatcher
//
//------------------------------------------------------------------
CCKeyboardDispatcher::CCKeyboardDispatcher()
: m_bLocked(false)
, m_bToAdd(false)
, m_bToRemove(false)
, m_pHandlers(NULL)
, m_pHandlersToAdd(NULL)
, m_pHandlersToRemove(NULL)
{
}

bool CCKeyboardDispatcher::init(void)
{
    m_bDispatchEvents = true;
    m_pHandlers = CCArray::createWithCapacity(8);
    m_pHandlers->retain();
    m_pHandlersToAdd = CCArray::createWithCapacity(8);
    m_pHandlersToAdd->retain();
    m_pHandlersToRemove = ccCArrayNew(8);
    
    m_bToRemove = false;
    m_bToAdd = false;
    m_bToQuit = false;
    m_bLocked = false;
    
    return true;
}

CCKeyboardDispatcher::~CCKeyboardDispatcher()
{
    CC_SAFE_RELEASE(m_pHandlers);
    CC_SAFE_RELEASE(m_pHandlersToAdd);
    
    if (m_pHandlersToRemove)
    {
        ccCArrayFree(m_pHandlersToRemove);
        m_pHandlersToRemove = NULL;
    }
}

void CCKeyboardDispatcher::removeDelegate(CCKeyboardDelegate* pDelegate)
{
    if (pDelegate == NULL)
    {
        return;
    }
    
    if (! m_bLocked)
    {
        forceRemoveDelegate(pDelegate);
    }
    else
    {
        /* If pHandler is contained in m_pHandlersToAdd, if so remove it from m_pHandlersToAdd and retrun.
         * Refer issue #752(cocos2d-x)
         */
        CCKeyboardHandler *pHandler = findHandler(m_pHandlersToAdd, pDelegate);
        if (pHandler)
        {
            m_pHandlersToAdd->removeObject(pHandler);
            return;
        }
        
        ccCArrayAppendValue(m_pHandlersToRemove, pDelegate);
        m_bToRemove = true;
    }
}

void CCKeyboardDispatcher::addDelegate(CCKeyboardDelegate *pDelegate, int nPriority)
{
    CCKeyboardHandler *pHandler = CCKeyboardHandler::handlerWithDelegate(pDelegate, nPriority);
    if (! m_bLocked)
    {
        forceAddHandler(pHandler, m_pHandlers);
    }
    else
    {
        /* If pHandler is contained in m_pHandlersToRemove, if so remove it from m_pHandlersToRemove and retrun.
         * Refer issue #752(cocos2d-x)
         */
        if (ccCArrayContainsValue(m_pHandlersToRemove, pDelegate))
        {
            ccCArrayRemoveValue(m_pHandlersToRemove, pDelegate);
            return;
        }
        
        m_pHandlersToAdd->addObject(pHandler);
        m_bToAdd = true;
    }
}

void CCKeyboardDispatcher::forceRemoveDelegate(CCKeyboardDelegate* pDelegate)
{
    CCKeyboardHandler *pHandler;
    
    // remove handler from m_pHandlers
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pHandlers, pObj)
    {
        pHandler = (CCKeyboardHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            m_pHandlers->removeObject(pHandler);
            break;
        }
    }
    
}

void CCKeyboardDispatcher::setDispatchEvents(bool bDispatchEvents)
{
    m_bDispatchEvents = bDispatchEvents;
}

void CCKeyboardDispatcher::keyDown(CCKeyboard* pEvent)
{
    if (m_bDispatchEvents)
    {
        m_bLocked = true;
        
        unsigned int uHandlersCount = m_pHandlers->count();
        
        if (uHandlersCount > 0)
        {
            CCKeyboardHandler *pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlers, pObj)
            {
                pHandler = (CCKeyboardHandler *)(pObj);
                
                if (! pHandler)
                {
                    break;
                }
                
                pHandler->getDelegate()->keyDown(pEvent);
            }
        }
        
        //
        // Optimization. To prevent a [handlers copy] which is expensive
        // the add/removes/quit is done after the iterations
        //
        m_bLocked = false;
        if (m_bToRemove)
        {
            m_bToRemove = false;
            for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
            {
                forceRemoveDelegate((CCKeyboardDelegate*)m_pHandlersToRemove->arr[i]);
            }
            ccCArrayRemoveAllValues(m_pHandlersToRemove);
        }
        
        if (m_bToAdd)
        {
            m_bToAdd = false;
            CCKeyboardHandler* pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlersToAdd, pObj)
            {
                pHandler = (CCKeyboardHandler*)pObj;
                if (! pHandler)
                {
                    break;
                }
                
                forceAddHandler(pHandler, m_pHandlers);
            }
            
            m_pHandlersToAdd->removeAllObjects();
        }
        
        if (m_bToQuit)
        {
            m_bToQuit = false;
            forceRemoveAllDelegates();
        }
    }
}

void CCKeyboardDispatcher::keyUp(CCKeyboard* pEvent)
{
    if (m_bDispatchEvents)
    {
        m_bLocked = true;
        
        unsigned int uHandlersCount = m_pHandlers->count();
        
        if (uHandlersCount > 0)
        {
            CCKeyboardHandler *pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlers, pObj)
            {
                pHandler = (CCKeyboardHandler *)(pObj);
                
                if (! pHandler)
                {
                    break;
                }
                
                pHandler->getDelegate()->keyUp(pEvent);
            }
        }
        
        //
        // Optimization. To prevent a [handlers copy] which is expensive
        // the add/removes/quit is done after the iterations
        //
        m_bLocked = false;
        if (m_bToRemove)
        {
            m_bToRemove = false;
            for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
            {
                forceRemoveDelegate((CCKeyboardDelegate*)m_pHandlersToRemove->arr[i]);
            }
            ccCArrayRemoveAllValues(m_pHandlersToRemove);
        }
        
        if (m_bToAdd)
        {
            m_bToAdd = false;
            CCKeyboardHandler* pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlersToAdd, pObj)
            {
                pHandler = (CCKeyboardHandler*)pObj;
                if (! pHandler)
                {
                    break;
                }
                
                forceAddHandler(pHandler, m_pHandlers);
            }
            
            m_pHandlersToAdd->removeAllObjects();
        }
        
        if (m_bToQuit)
        {
            m_bToQuit = false;
            forceRemoveAllDelegates();
        }
    }
}

void CCKeyboardDispatcher::flagsChanged(CCKeyboard* pEvent)
{
    if (m_bDispatchEvents)
    {
        m_bLocked = true;
        
        unsigned int uHandlersCount = m_pHandlers->count();
        
        if (uHandlersCount > 0)
        {
            CCKeyboardHandler *pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlers, pObj)
            {
                pHandler = (CCKeyboardHandler *)(pObj);
                
                if (! pHandler)
                {
                    break;
                }
                
                pHandler->getDelegate()->flagsChanged(pEvent);
            }
        }
        
        //
        // Optimization. To prevent a [handlers copy] which is expensive
        // the add/removes/quit is done after the iterations
        //
        m_bLocked = false;
        if (m_bToRemove)
        {
            m_bToRemove = false;
            for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
            {
                forceRemoveDelegate((CCKeyboardDelegate*)m_pHandlersToRemove->arr[i]);
            }
            ccCArrayRemoveAllValues(m_pHandlersToRemove);
        }
        
        if (m_bToAdd)
        {
            m_bToAdd = false;
            CCKeyboardHandler* pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(m_pHandlersToAdd, pObj)
            {
                pHandler = (CCKeyboardHandler*)pObj;
                if (! pHandler)
                {
                    break;
                }
                
                forceAddHandler(pHandler, m_pHandlers);
            }
            
            m_pHandlersToAdd->removeAllObjects();
        }
        
        if (m_bToQuit)
        {
            m_bToQuit = false;
            forceRemoveAllDelegates();
        }
    }
}

//
// handlers management
//
void CCKeyboardDispatcher::forceAddHandler(CCKeyboardHandler *pHandler, CCArray *pArray)
{
    unsigned int u = 0;
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        CCKeyboardHandler *h = (CCKeyboardHandler *)pObj;
        if (h)
        {
            if (h->getPriority() < pHandler->getPriority())
            {
                ++u;
            }
            
            if (h->getDelegate() == pHandler->getDelegate())
            {
                CCAssert(0, "");
                return;
            }
        }
    }
    
    pArray->insertObject(pHandler, u);
}

void CCKeyboardDispatcher::forceRemoveAllDelegates(void)
{
    m_pHandlers->removeAllObjects();
}

void CCKeyboardDispatcher::rearrangeHandlers(CCArray *pArray)
{
    std::sort(pArray->data->arr, pArray->data->arr + pArray->data->num, less);
}

CCKeyboardHandler* CCKeyboardDispatcher::findHandler(CCKeyboardDelegate *pDelegate)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pHandlers, pObj)
    {
        CCKeyboardHandler* pHandler = (CCKeyboardHandler*)pObj;
        if (pHandler->getDelegate() == pDelegate)
        {
            return pHandler;
        }
    }
    
    return NULL;
}

CCKeyboardHandler* CCKeyboardDispatcher::findHandler(CCArray* pArray, CCKeyboardDelegate *pDelegate)
{
    CCAssert(pArray != NULL && pDelegate != NULL, "");
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        CCKeyboardHandler* pHandle = (CCKeyboardHandler*)pObj;
        if (pHandle->getDelegate() == pDelegate)
        {
            return pHandle;
        }
    }
    
    return NULL;
}


NS_CC_END
