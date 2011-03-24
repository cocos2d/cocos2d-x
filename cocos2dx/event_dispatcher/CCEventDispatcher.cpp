/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada
 
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

#include "ccMacros.h"
#include "CCEventDispatcher.h"
#include "../support/data_support/uthash.h"	// hack: uthash needs to be imported before utlist to prevent warning
#include "../support/data_support/utlist.h"

namespace cocos2d {

static CCEventDispatcher *s_pEventDispatcher = NULL;

typedef struct _listEntry
{
    struct	_listEntry	*prev;
    struct	_listEntry	*next;
    CCObject*           pHandle;
    int                 priority;
} tListEntry;


#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD

    #define QUEUE_EVENT_MAX 128
    struct _eventQueue {
        SEL_EventHandler		selector;
        CCEvent	                *pEvent;
    };

    static struct _eventQueue eventQueue[QUEUE_EVENT_MAX];
    static int    s_nEventQueueCount = 0;

#endif // CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD

CCEventDispatcher* CCEventDispatcher::sharedDispatcher(void)
{
    // synchronized ??
    if (s_pEventDispatcher == NULL)
    {
        s_pEventDispatcher = new CCEventDispatcher();
        s_pEventDispatcher->init();
    }

    return s_pEventDispatcher;
}

bool CCEventDispatcher::init()
{
    m_bDispatchEvents = true;

    m_pKeyboardDelegates = NULL;
    m_pMouseDelegates = NULL;

#if	CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
    s_nEventQueueCount = 0;
#endif

    return true;
}

void CCEventDispatcher::addMouseDelegate(CCMouseEventDelegate* pDelegate, int priority)
{
    if (!pDelegate)
    {
        return;
    }

    CCMouseEventHandle* pHandle = CCMouseEventHandle::handlerWithDelegate(pDelegate);
    addDelegate(pHandle, priority, &m_pMouseDelegates);
}

/** removes a mouse delegate */
void CCEventDispatcher::removeMouseDelegate(CCMouseEventDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }

    tListEntry *entry, *tmp;
    DL_FOREACH_SAFE(m_pMouseDelegates, entry, tmp )
    {
        if (!(entry->pHandle))
        {
            continue;
        }

        CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
        if (pHandle->getDelegate() == pDelegate)
        {
            DL_DELETE(m_pMouseDelegates, entry );
            pHandle->release();
            free(entry);
            break;
        }
    }
}

/** Removes all mouse delegates, releasing all the delegates */
void CCEventDispatcher::removeAllMouseDelegates()
{
    removeAllDelegatesFromList(&m_pMouseDelegates);
}

void CCEventDispatcher::addKeyboardDelegate(CCKeyboardEventDelegate* pDelegate, int priority)
{
    if (!pDelegate)
    {
        return;
    }

    CCKeyboardEventHandle* pHandle = CCKeyboardEventHandle::handlerWithDelegate(pDelegate);
    addDelegate(pHandle, priority, &m_pKeyboardDelegates);
}

/** removes a mouse delegate */
void CCEventDispatcher::removeKeyboardDelegate(CCKeyboardEventDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }

    tListEntry *entry, *tmp;
    DL_FOREACH_SAFE(m_pKeyboardDelegates, entry, tmp )
    {
        if (!(entry->pHandle))
        {
            continue;
        }

        CCKeyboardEventHandle* pHandle = (CCKeyboardEventHandle*) entry->pHandle;
        if (pHandle->getDelegate() == pDelegate)
        {
            DL_DELETE(m_pKeyboardDelegates, entry );
            pHandle->release();
            free(entry);
            break;
        }
    }
}

/** Removes all mouse delegates, releasing all the delegates */
void CCEventDispatcher::removeAllKeyboardDelegates()
{
    removeAllDelegatesFromList(&m_pKeyboardDelegates);
}

void CCEventDispatcher::addDelegate(CCObject* pHandle, int priority, _listEntry** pList)
{
    if (! pHandle)
    {
        return;
    }

    tListEntry *listElement = (tListEntry*) malloc( sizeof(*listElement) );

    pHandle->retain();
    listElement->pHandle = pHandle;
    listElement->priority = priority;
    listElement->next = listElement->prev = NULL;

    // empty list ?
    if( ! *pList )
    {
        DL_APPEND( *pList, listElement );

    }
    else
    {
        bool added = false;		

        for( tListEntry *elem = *pList; elem ; elem = elem->next )
        {
            if( priority < elem->priority )
            {
                if( elem == *pList )
                {
                    DL_PREPEND(*pList, listElement);
                }
                else
                {
                    listElement->next = elem;
                    listElement->prev = elem->prev;

                    elem->prev->next = listElement;
                    elem->prev = listElement;
                }

                added = true;
                break;
            }
        }

        // Not added? priority has the higher value. Append it.
        if( !added )
        {
            DL_APPEND(*pList, listElement);
        }
    }
}

void CCEventDispatcher::removeAllDelegatesFromList(_listEntry** pList)
{
    tListEntry *entry, *tmp;

    DL_FOREACH_SAFE( *pList, entry, tmp )
    {
        DL_DELETE( *pList, entry );
        free(entry);
    }
}

bool CCEventDispatcher::getIsDispatchEvents()
{
    return m_bDispatchEvents;
}

void CCEventDispatcher::setIsDispatchEvents(bool bDispatch)
{
    m_bDispatchEvents = bDispatch;
}

//
// Mouse events
//

//
// Left
//
void CCEventDispatcher::mouseDown(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccMouseDown(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::mouseMoved(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccMouseMoved(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::mouseDragged(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccMouseDragged(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::mouseUp(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccMouseUp(pEvent);
            if(bSwallows)
                break;
        }
    }
}

//
// Mouse Right
//
void CCEventDispatcher::rightMouseDown(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccRightMouseDown(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::rightMouseDragged(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccRightMouseDragged(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::rightMouseUp(CCEvent * pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccRightMouseUp(pEvent);
            if(bSwallows)
                break;
        }
    }
}

//
// Mouse Other
//
void CCEventDispatcher::otherMouseDown(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccOtherMouseDown(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::otherMouseDragged(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccOtherMouseDragged(pEvent);
            if(bSwallows)
                break;
        }
    }
}

void CCEventDispatcher::otherMouseUp(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccOtherMouseUp(pEvent);
            if(bSwallows)
                break;
        }
    }
}

//
// Scroll Wheel
//
void CCEventDispatcher::scrollWheel(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }

            bool bSwallows = pDelegate->ccScrollWheel(pEvent);
            if(bSwallows)
                break;
        }
    }
}

//
// Mouse enter / exit
void CCEventDispatcher::mouseExited(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }
            pDelegate->ccMouseEntered(pEvent);
        }
    }
}

void CCEventDispatcher::mouseEntered(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pMouseDelegates, entry, tmp )
        {
            CCMouseEventHandle* pHandle = (CCMouseEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCMouseEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }
            pDelegate->ccMouseExited(pEvent);
        }
    }
}


// Keyboard events
void CCEventDispatcher::keyDown(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pKeyboardDelegates, entry, tmp )
        {
            CCKeyboardEventHandle* pHandle = (CCKeyboardEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCKeyboardEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }
            bool bSwallows = pDelegate->ccKeyDown(pEvent);
            if (bSwallows)
            {
                break;
            }
        }
    }
}

void CCEventDispatcher::keyUp(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pKeyboardDelegates, entry, tmp )
        {
            CCKeyboardEventHandle* pHandle = (CCKeyboardEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCKeyboardEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }
            bool bSwallows = pDelegate->ccKeyUp(pEvent);
            if (bSwallows)
            {
                break;
            }
        }
    }
}

void CCEventDispatcher::flagsChanged(CCEvent *pEvent)
{
    if(m_bDispatchEvents)
    {
        tListEntry *entry, *tmp;

        DL_FOREACH_SAFE( m_pKeyboardDelegates, entry, tmp )
        {
            CCKeyboardEventHandle* pHandle = (CCKeyboardEventHandle*) entry->pHandle;
            if (!pHandle)
            {
                continue;
            }
            CCKeyboardEventDelegate* pDelegate = pHandle->getDelegate();
            if (!pDelegate)
            {
                continue;
            }
            bool bSwallows = pDelegate->ccFlagsChanged(pEvent);
            if (bSwallows)
            {
                break;
            }
        }
    }
}

void CCEventDispatcher::touchesBeganWithEvent(CCEvent *pEvent)
{
    if (m_bDispatchEvents )
    {
        CCLOG("Touch Events: Not supported yet");
    }
}

void CCEventDispatcher::touchesMovedWithEvent(CCEvent *pEvent)
{
    if (m_bDispatchEvents )
    {
        CCLOG("Touch Events: Not supported yet");
    }
}

void CCEventDispatcher::touchesEndedWithEvent(CCEvent *pEvent)
{
    if (m_bDispatchEvents )
    {
        CCLOG("Touch Events: Not supported yet");
    }
}

void CCEventDispatcher::touchesCancelledWithEvent(CCEvent *pEvent)
{
    if (m_bDispatchEvents )
    {
        CCLOG("Touch Events: Not supported yet");
    }
}

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD

void CCEventDispatcher::queueEvent(CCEvent* pEvent, SEL_EventHandler selector)
{
    CCAssert( s_nEventQueueCount < QUEUE_EVENT_MAX, "CCEventDispatcher: recompile. Increment QUEUE_EVENT_MAX value");

    eventQueue[s_nEventQueueCount].selector = selector;
    eventQueue[s_nEventQueueCount].pEvent   = (CCEvent*) (pEvent->copy());

    s_nEventQueueCount++;
}

void CCEventDispatcher::dispatchQueuedEvents()
{
    for( int i=0; i < s_nEventQueueCount; i++ )
    {
        // SEL_EventHandler sel = eventQueue[i].selector;
        CCEvent *pEvent = eventQueue[i].pEvent;

        
        //[self performSelector:sel withObject:event]; // @todo
        pEvent->release();
    }

    s_nEventQueueCount = 0;
}

#endif // CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD

} // namespace cocos2d
