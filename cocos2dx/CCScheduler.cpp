/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "CCScheduler.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "support/data_support/utlist.h"
#include "support/data_support/ccCArray.h"
#include "cocoa/CCArray.h"
#include "script_support/CCScriptSupport.h"

using namespace std;

NS_CC_BEGIN

// data structures

// A list double-linked list used for "updates with priority"
typedef struct _listEntry
{
    struct _listEntry   *prev, *next;
    CCObject            *target;        // not retained (retained by hashUpdateEntry)
    int                 priority;
    bool                paused;
    bool                markedForDeletion; // selector will no longer be called and entry will be removed at end of the next tick
} tListEntry;

typedef struct _hashUpdateEntry
{
    tListEntry          **list;        // Which list does it belong to ?
    tListEntry          *entry;        // entry in the list
    CCObject            *target;        // hash key (retained)
    UT_hash_handle      hh;
} tHashUpdateEntry;

// Hash Element used for "selectors with interval"
typedef struct _hashSelectorEntry
{
    ccArray             *timers;
    CCObject            *target;    // hash key (retained)
    unsigned int        timerIndex;
    CCTimer             *currentTimer;
    bool                currentTimerSalvaged;
    bool                paused;
    UT_hash_handle      hh;
} tHashTimerEntry;

// implementation CCTimer

CCTimer::CCTimer()
: m_pTarget(NULL)
, m_fElapsed(-1)
, m_bRunForever(false)
, m_bUseDelay(false)
, m_uTimesExecuted(0)
, m_uRepeat(0)
, m_fDelay(0.0f)
, m_fInterval(0.0f)
, m_pfnSelector(NULL)
, m_nScriptHandler(0)
{
}

CCTimer* CCTimer::timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector)
{
    CCTimer *pTimer = new CCTimer();

    pTimer->initWithTarget(pTarget, pfnSelector, 0.0f, kCCRepeatForever, 0.0f);
    pTimer->autorelease();

    return pTimer;
}

CCTimer* CCTimer::timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds)
{
    CCTimer *pTimer = new CCTimer();

    pTimer->initWithTarget(pTarget, pfnSelector, fSeconds, kCCRepeatForever, 0.0f);
    pTimer->autorelease();

    return pTimer;
}

CCTimer* CCTimer::timerWithScriptHandler(int nHandler, float fSeconds)
{
    CCTimer *pTimer = new CCTimer();

    pTimer->initWithScriptHandler(nHandler, fSeconds);
    pTimer->autorelease();

    return pTimer;
}

bool CCTimer::initWithScriptHandler(int nHandler, float fSeconds)
{
    m_nScriptHandler = nHandler;
    m_fElapsed = -1;
    m_fInterval = fSeconds;

    return true;
}

bool CCTimer::initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector)
{
    return initWithTarget(pTarget, pfnSelector, 0, kCCRepeatForever, 0.0f);
}

bool CCTimer::initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds, unsigned int nRepeat, float fDelay)
{
    m_pTarget = pTarget;
    m_pfnSelector = pfnSelector;
    m_fElapsed = -1;
    m_fInterval = fSeconds;
    m_fDelay = fDelay;
    m_bUseDelay = (fDelay > 0.0f) ? true : false;
    m_uRepeat = nRepeat;
    m_bRunForever = (nRepeat == kCCRepeatForever) ? true : false;
    return true;
}

void CCTimer::update(float dt)
{
    if (m_fElapsed == -1)
    {
        m_fElapsed = 0;
        m_uTimesExecuted = 0;
    }
    else
    {
        if (m_bRunForever && !m_bUseDelay)
        {//standard timer usage
            m_fElapsed += dt;
            if (m_fElapsed >= m_fInterval)
            {
                if (m_pTarget && m_pfnSelector)
                {
                    (m_pTarget->*m_pfnSelector)(m_fElapsed);
                }

                if (m_nScriptHandler)
                {
                    CCScriptEngineManager::sharedManager()->getScriptEngine()->executeSchedule(m_nScriptHandler, m_fElapsed);
                }
                m_fElapsed = 0;
            }
        }    
        else
        {//advanced usage
            m_fElapsed += dt;
            if (m_bUseDelay)
            {
                if( m_fElapsed >= m_fDelay )
                {
                    if (m_pTarget && m_pfnSelector)
                    {
                        (m_pTarget->*m_pfnSelector)(m_fElapsed);
                    }

                    if (m_nScriptHandler)
                    {
                        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeSchedule(m_nScriptHandler, m_fElapsed);
                    }

                    m_fElapsed = m_fElapsed - m_fDelay;
                    m_uTimesExecuted += 1;
                    m_bUseDelay = false;
                }
            }
            else
            {
                if (m_fElapsed >= m_fInterval)
                {
                    if (m_pTarget && m_pfnSelector)
                    {
                        (m_pTarget->*m_pfnSelector)(m_fElapsed);
                    }

                    if (m_nScriptHandler)
                    {
                        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeSchedule(m_nScriptHandler, m_fElapsed);
                    }

                    m_fElapsed = 0;
                    m_uTimesExecuted += 1;

                }
            }

            if (!m_bRunForever && m_uTimesExecuted > m_uRepeat)
            {    //unschedule timer
                CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(m_pfnSelector, m_pTarget);
            }
        }
    }
}

float CCTimer::getInterval() const
{
    return m_fInterval;
}

void CCTimer::setInterval(float fInterval)
{
    m_fInterval = fInterval;
}

SEL_SCHEDULE CCTimer::getSelector() const
{
    return m_pfnSelector;
}

// implementation of CCScheduler

CCScheduler::CCScheduler(void)
: m_fTimeScale(1.0f)
, m_pUpdatesNegList(NULL)
, m_pUpdates0List(NULL)
, m_pUpdatesPosList(NULL)
, m_pHashForUpdates(NULL)
, m_pHashForTimers(NULL)
, m_pCurrentTarget(NULL)
, m_bCurrentTargetSalvaged(false)
, m_bUpdateHashLocked(false)
, m_pScriptHandlerEntries(NULL)
{

}

CCScheduler::~CCScheduler(void)
{
    unscheduleAll();
    CC_SAFE_RELEASE(m_pScriptHandlerEntries);
}

void CCScheduler::removeHashElement(_hashSelectorEntry *pElement)
{

	cocos2d::CCObject *target = pElement->target;

    ccArrayFree(pElement->timers);
    HASH_DEL(m_pHashForTimers, pElement);
    free(pElement);

    // make sure the target is released after we have removed the hash element
    // otherwise we access invalid memory when the release call deletes the target
    // and the target calls removeAllSelectors() during its destructor
    target->release();

}

void CCScheduler::scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, float fInterval, bool bPaused)
{
    this->scheduleSelector(pfnSelector, pTarget, fInterval, kCCRepeatForever, 0.0f, bPaused);
}

void CCScheduler::scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, float fInterval, unsigned int repeat, float delay, bool bPaused)
{
    CCAssert(pfnSelector, "Argument selector must be non-NULL");
    CCAssert(pTarget, "Argument target must be non-NULL");

    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);

    if (! pElement)
    {
        pElement = (tHashTimerEntry *)calloc(sizeof(*pElement), 1);
        pElement->target = pTarget;
        if (pTarget)
        {
            pTarget->retain();
        }
        HASH_ADD_INT(m_pHashForTimers, target, pElement);

        // Is this the 1st element ? Then set the pause level to all the selectors of this target
        pElement->paused = bPaused;
    }
    else
    {
        CCAssert(pElement->paused == bPaused, "");
    }

    if (pElement->timers == NULL)
    {
        pElement->timers = ccArrayNew(10);
    }
    else 
    {
        for (unsigned int i = 0; i < pElement->timers->num; ++i)
        {
            CCTimer *timer = (CCTimer*)pElement->timers->arr[i];

            if (pfnSelector == timer->getSelector())
            {
                CCLOG("CCScheduler#scheduleSelector. Selector already scheduled. Updating interval from: %.4f to %.4f", timer->getInterval(), fInterval);
                timer->setInterval(fInterval);
                return;
            }        
        }
        ccArrayEnsureExtraCapacity(pElement->timers, 1);
    }

    CCTimer *pTimer = new CCTimer();
    pTimer->initWithTarget(pTarget, pfnSelector, fInterval, repeat, delay);
    ccArrayAppendObject(pElement->timers, pTimer);
    pTimer->release();    
}

void CCScheduler::unscheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget)
{
    // explicity handle nil arguments when removing an object
    if (pTarget == 0 || pfnSelector == 0)
    {
        return;
    }

    //CCAssert(pTarget);
    //CCAssert(pfnSelector);

    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);

    if (pElement)
    {
        for (unsigned int i = 0; i < pElement->timers->num; ++i)
        {
            CCTimer *pTimer = (CCTimer*)(pElement->timers->arr[i]);

            if (pfnSelector == pTimer->getSelector())
            {
                if (pTimer == pElement->currentTimer && (! pElement->currentTimerSalvaged))
                {
                    pElement->currentTimer->retain();
                    pElement->currentTimerSalvaged = true;
                }

                ccArrayRemoveObjectAtIndex(pElement->timers, i, true);

                // update timerIndex in case we are in tick:, looping over the actions
                if (pElement->timerIndex >= i)
                {
                    pElement->timerIndex--;
                }

                if (pElement->timers->num == 0)
                {
                    if (m_pCurrentTarget == pElement)
                    {
                        m_bCurrentTargetSalvaged = true;
                    }
                    else
                    {
                        removeHashElement(pElement);
                    }
                }

                return;
            }
        }
    }
}

void CCScheduler::priorityIn(tListEntry **ppList, CCObject *pTarget, int nPriority, bool bPaused)
{
    tListEntry *pListElement = (tListEntry *)malloc(sizeof(*pListElement));

    pListElement->target = pTarget;
    pListElement->priority = nPriority;
    pListElement->paused = bPaused;
    pListElement->next = pListElement->prev = NULL;
    pListElement->markedForDeletion = false;

    // empty list ?
    if (! *ppList)
    {
        DL_APPEND(*ppList, pListElement);
    }
    else
    {
        bool bAdded = false;

        for (tListEntry *pElement = *ppList; pElement; pElement = pElement->next)
        {
            if (nPriority < pElement->priority)
            {
                if (pElement == *ppList)
                {
                    DL_PREPEND(*ppList, pListElement);
                }
                else
                {
                    pListElement->next = pElement;
                    pListElement->prev = pElement->prev;

                    pElement->prev->next = pListElement;
                    pElement->prev = pListElement;
                }

                bAdded = true;
                break;
            }
        }

        // Not added? priority has the higher value. Append it.
        if (! bAdded)
        {
            DL_APPEND(*ppList, pListElement);
        }
    }

    // update hash entry for quick access
    tHashUpdateEntry *pHashElement = (tHashUpdateEntry *)calloc(sizeof(*pHashElement), 1);
    pHashElement->target = pTarget;
    pTarget->retain();
    pHashElement->list = ppList;
    pHashElement->entry = pListElement;
    HASH_ADD_INT(m_pHashForUpdates, target, pHashElement);
}

void CCScheduler::appendIn(_listEntry **ppList, CCObject *pTarget, bool bPaused)
{
    tListEntry *pListElement = (tListEntry *)malloc(sizeof(*pListElement));

    pListElement->target = pTarget;
    pListElement->paused = bPaused;
    pListElement->markedForDeletion = false;

    DL_APPEND(*ppList, pListElement);

    // update hash entry for quicker access
    tHashUpdateEntry *pHashElement = (tHashUpdateEntry *)calloc(sizeof(*pHashElement), 1);
    pHashElement->target = pTarget;
    pTarget->retain();
    pHashElement->list = ppList;
    pHashElement->entry = pListElement;
    HASH_ADD_INT(m_pHashForUpdates, target, pHashElement);
}

void CCScheduler::scheduleUpdateForTarget(CCObject *pTarget, int nPriority, bool bPaused)
{

    tHashUpdateEntry *pHashElement = NULL;
    HASH_FIND_INT(m_pHashForUpdates, &pTarget, pHashElement);
    if (pHashElement)
    {
#if COCOS2D_DEBUG >= 1
        CCAssert(pHashElement->entry->markedForDeletion,"");
#endif
        // TODO: check if priority has changed!

        pHashElement->entry->markedForDeletion = false;
        return;
    }

    // most of the updates are going to be 0, that's way there
    // is an special list for updates with priority 0
    if (nPriority == 0)
    {
        appendIn(&m_pUpdates0List, pTarget, bPaused);
    }
    else if (nPriority < 0)
    {
        priorityIn(&m_pUpdatesNegList, pTarget, nPriority, bPaused);
    }
    else
    {
        // priority > 0
        priorityIn(&m_pUpdatesPosList, pTarget, nPriority, bPaused);
    }
}

void CCScheduler::removeUpdateFromHash(struct _listEntry *entry)
{
    tHashUpdateEntry *element = NULL;

    HASH_FIND_INT(m_pHashForUpdates, &entry->target, element);
    if (element)
    {
        // list entry
        DL_DELETE(*element->list, element->entry);
        free(element->entry);

        // hash entry
        CCObject* pTarget = element->target;
        HASH_DEL(m_pHashForUpdates, element);
        free(element);

        // target#release should be the last one to prevent
        // a possible double-free. eg: If the [target dealloc] might want to remove it itself from there
        pTarget->release();
    }
}

void CCScheduler::unscheduleUpdateForTarget(const CCObject *pTarget)
{
    if (pTarget == NULL)
    {
        return;
    }

    tHashUpdateEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForUpdates, &pTarget, pElement);
    if (pElement)
    {
        if (m_bUpdateHashLocked)
        {
            pElement->entry->markedForDeletion = true;
        }
        else
        {
            this->removeUpdateFromHash(pElement->entry);
        }
    }
}

void CCScheduler::unscheduleAll(void)
{
    unscheduleAllWithMinPriority(kCCPrioritySystem);
}

void CCScheduler::unscheduleAllWithMinPriority(int nMinPriority)
{
    // Custom Selectors
    tHashTimerEntry *pElement = NULL;
    tHashTimerEntry *pNextElement = NULL;
    for (pElement = m_pHashForTimers; pElement != NULL;)
    {
        // pElement may be removed in unscheduleAllSelectorsForTarget
        pNextElement = (tHashTimerEntry *)pElement->hh.next;
        unscheduleAllForTarget(pElement->target);

        pElement = pNextElement;
    }

    // Updates selectors
    tListEntry *pEntry, *pTmp;
    if(nMinPriority < 0) 
    {
        DL_FOREACH_SAFE(m_pUpdatesNegList, pEntry, pTmp)
        {
            if(pEntry->priority >= nMinPriority) 
            {
                unscheduleUpdateForTarget(pEntry->target);
            }
        }
    }

    if(nMinPriority <= 0) 
    {
        DL_FOREACH_SAFE(m_pUpdates0List, pEntry, pTmp)
        {
            unscheduleUpdateForTarget(pEntry->target);
        }
    }

    DL_FOREACH_SAFE(m_pUpdatesPosList, pEntry, pTmp)
    {
        if(pEntry->priority >= nMinPriority) 
        {
            unscheduleUpdateForTarget(pEntry->target);
        }
    }

    if (m_pScriptHandlerEntries)
    {
        m_pScriptHandlerEntries->removeAllObjects();
    }
}

void CCScheduler::unscheduleAllForTarget(CCObject *pTarget)
{
    // explicit NULL handling
    if (pTarget == NULL)
    {
        return;
    }

    // Custom Selectors
    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);

    if (pElement)
    {
        if (ccArrayContainsObject(pElement->timers, pElement->currentTimer)
            && (! pElement->currentTimerSalvaged))
        {
            pElement->currentTimer->retain();
            pElement->currentTimerSalvaged = true;
        }
        ccArrayRemoveAllObjects(pElement->timers);

        if (m_pCurrentTarget == pElement)
        {
            m_bCurrentTargetSalvaged = true;
        }
        else
        {
            removeHashElement(pElement);
        }
    }

    // update selector
    unscheduleUpdateForTarget(pTarget);
}

unsigned int CCScheduler::scheduleScriptFunc(unsigned int nHandler, float fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = CCSchedulerScriptHandlerEntry::create(nHandler, fInterval, bPaused);
    if (!m_pScriptHandlerEntries)
    {
        m_pScriptHandlerEntries = CCArray::createWithCapacity(20);
        m_pScriptHandlerEntries->retain();
    }
    m_pScriptHandlerEntries->addObject(pEntry);
    return pEntry->getEntryId();
}

void CCScheduler::unscheduleScriptEntry(unsigned int uScheduleScriptEntryID)
{
    for (int i = m_pScriptHandlerEntries->count() - 1; i >= 0; i--)
    {
        CCSchedulerScriptHandlerEntry* pEntry = static_cast<CCSchedulerScriptHandlerEntry*>(m_pScriptHandlerEntries->objectAtIndex(i));
        if (pEntry->getEntryId() == (int)uScheduleScriptEntryID)
        {
            pEntry->markedForDeletion();
            break;
        }
    }
}

void CCScheduler::resumeTarget(CCObject *pTarget)
{
    CCAssert(pTarget != NULL, "");

    // custom selectors
    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);
    if (pElement)
    {
        pElement->paused = false;
    }

    // update selector
    tHashUpdateEntry *pElementUpdate = NULL;
    HASH_FIND_INT(m_pHashForUpdates, &pTarget, pElementUpdate);
    if (pElementUpdate)
    {
        CCAssert(pElementUpdate->entry != NULL, "");
        pElementUpdate->entry->paused = false;
    }
}

void CCScheduler::pauseTarget(CCObject *pTarget)
{
    CCAssert(pTarget != NULL, "");

    // custom selectors
    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);
    if (pElement)
    {
        pElement->paused = true;
    }

    // update selector
    tHashUpdateEntry *pElementUpdate = NULL;
    HASH_FIND_INT(m_pHashForUpdates, &pTarget, pElementUpdate);
    if (pElementUpdate)
    {
        CCAssert(pElementUpdate->entry != NULL, "");
        pElementUpdate->entry->paused = true;
    }
}

bool CCScheduler::isTargetPaused(CCObject *pTarget)
{
    CCAssert( pTarget != NULL, "target must be non nil" );

    // Custom selectors
    tHashTimerEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForTimers, &pTarget, pElement);
    if( pElement )
    {
        return pElement->paused;
    }
    
    // We should check update selectors if target does not have custom selectors
	tHashUpdateEntry *elementUpdate = NULL;
	HASH_FIND_INT(m_pHashForUpdates, &pTarget, elementUpdate);
	if ( elementUpdate )
    {
		return elementUpdate->entry->paused;
    }
    
    return false;  // should never get here
}

CCSet* CCScheduler::pauseAllTargets()
{
    return pauseAllTargetsWithMinPriority(kCCPrioritySystem);
}

CCSet* CCScheduler::pauseAllTargetsWithMinPriority(int nMinPriority)
{
    CCSet* idsWithSelectors = new CCSet();// setWithCapacity:50];
    idsWithSelectors->autorelease();

    // Custom Selectors
    for(tHashTimerEntry *element = m_pHashForTimers; element != NULL;
        element = (tHashTimerEntry*)element->hh.next)
    {
        element->paused = true;
        idsWithSelectors->addObject(element->target);
    }

    // Updates selectors
    tListEntry *entry, *tmp;
    if(nMinPriority < 0) 
    {
        DL_FOREACH_SAFE( m_pUpdatesNegList, entry, tmp ) 
        {
            if(entry->priority >= nMinPriority) 
            {
                entry->paused = true;
                idsWithSelectors->addObject(entry->target);
            }
        }
    }

    if(nMinPriority <= 0) 
    {
        DL_FOREACH_SAFE( m_pUpdates0List, entry, tmp )
        {
            entry->paused = true;
            idsWithSelectors->addObject(entry->target);
        }
    }

    DL_FOREACH_SAFE( m_pUpdatesPosList, entry, tmp ) 
    {
        if(entry->priority >= nMinPriority) 
        {
            entry->paused = true;
            idsWithSelectors->addObject(entry->target);
        }
    }

    return idsWithSelectors;
}

void CCScheduler::resumeTargets(CCSet* pTargetsToResume)
{
    CCSetIterator iter;
    for (iter = pTargetsToResume->begin(); iter != pTargetsToResume->end(); ++iter)
    {
        resumeTarget(*iter);
    }
}

// main loop
void CCScheduler::update(float dt)
{
    m_bUpdateHashLocked = true;

    if (m_fTimeScale != 1.0f)
    {
        dt *= m_fTimeScale;
    }

    // Iterate over all the Updates' selectors
    tListEntry *pEntry, *pTmp;

    // updates with priority < 0
    DL_FOREACH_SAFE(m_pUpdatesNegList, pEntry, pTmp)
    {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }

    // updates with priority == 0
    DL_FOREACH_SAFE(m_pUpdates0List, pEntry, pTmp)
    {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }

    // updates with priority > 0
    DL_FOREACH_SAFE(m_pUpdatesPosList, pEntry, pTmp)
    {
        if ((! pEntry->paused) && (! pEntry->markedForDeletion))
        {
            pEntry->target->update(dt);
        }
    }

    // Iterate over all the custom selectors
    for (tHashTimerEntry *elt = m_pHashForTimers; elt != NULL; )
    {
        m_pCurrentTarget = elt;
        m_bCurrentTargetSalvaged = false;

        if (! m_pCurrentTarget->paused)
        {
            // The 'timers' array may change while inside this loop
            for (elt->timerIndex = 0; elt->timerIndex < elt->timers->num; ++(elt->timerIndex))
            {
                elt->currentTimer = (CCTimer*)(elt->timers->arr[elt->timerIndex]);
                elt->currentTimerSalvaged = false;

                elt->currentTimer->update(dt);

                if (elt->currentTimerSalvaged)
                {
                    // The currentTimer told the remove itself. To prevent the timer from
                    // accidentally deallocating itself before finishing its step, we retained
                    // it. Now that step is done, it's safe to release it.
                    elt->currentTimer->release();
                }

                elt->currentTimer = NULL;
            }
        }

        // elt, at this moment, is still valid
        // so it is safe to ask this here (issue #490)
        elt = (tHashTimerEntry *)elt->hh.next;

        // only delete currentTarget if no actions were scheduled during the cycle (issue #481)
        if (m_bCurrentTargetSalvaged && m_pCurrentTarget->timers->num == 0)
        {
            removeHashElement(m_pCurrentTarget);
        }
    }

    // Iterate over all the script callbacks
    if (m_pScriptHandlerEntries)
    {
        for (int i = m_pScriptHandlerEntries->count() - 1; i >= 0; i--)
        {
            CCSchedulerScriptHandlerEntry* pEntry = static_cast<CCSchedulerScriptHandlerEntry*>(m_pScriptHandlerEntries->objectAtIndex(i));
            if (pEntry->isMarkedForDeletion())
            {
                m_pScriptHandlerEntries->removeObjectAtIndex(i);
            }
            else if (!pEntry->isPaused())
            {
                pEntry->getTimer()->update(dt);
            }
        }
    }

    // delete all updates that are marked for deletion
    // updates with priority < 0
    DL_FOREACH_SAFE(m_pUpdatesNegList, pEntry, pTmp)
    {
        if (pEntry->markedForDeletion)
        {
            this->removeUpdateFromHash(pEntry);
        }
    }

    // updates with priority == 0
    DL_FOREACH_SAFE(m_pUpdates0List, pEntry, pTmp)
    {
        if (pEntry->markedForDeletion)
        {
            this->removeUpdateFromHash(pEntry);
        }
    }

    // updates with priority > 0
    DL_FOREACH_SAFE(m_pUpdatesPosList, pEntry, pTmp)
    {
        if (pEntry->markedForDeletion)
        {
            this->removeUpdateFromHash(pEntry);
        }
    }

    m_bUpdateHashLocked = false;

    m_pCurrentTarget = NULL;
}


NS_CC_END
