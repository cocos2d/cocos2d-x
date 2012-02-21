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

#include "CCScheduler.h"
#include "ccMacros.h"
#include "support/data_support/utlist.h"
#include "support/data_support/ccCArray.h"
#include "CCArray.h"
#include "CCScriptSupport.h"

using namespace std;

namespace   cocos2d {

// data structures

// A list double-linked list used for "updates with priority"
typedef struct _listEntry
{
	struct	_listEntry	*prev, *next;
	CCObject	*target;		// not retained (retained by hashUpdateEntry)
	int				    priority;
	bool				paused;
	bool				markedForDeletion; // selector will no longer be called and entry will be removed at end of the next tick
	
} tListEntry;

typedef struct _hashUpdateEntry
{
	tListEntry			**list;		// Which list does it belong to ?
	tListEntry			*entry;		// entry in the list
	CCObject	*target;		// hash key (retained)
	UT_hash_handle		hh;
} tHashUpdateEntry;

// Hash Element used for "selectors with interval"
typedef struct _hashSelectorEntry
{
	ccArray          	        *timers;
	CCObject			*target;	// hash key (retained)
	unsigned int				timerIndex;
	CCTimer						*currentTimer;
	bool						currentTimerSalvaged;
	bool						paused;
	UT_hash_handle				hh;
} tHashSelectorEntry;

// implementation CCTimer

CCTimer::CCTimer()
: m_pfnSelector(NULL)
, m_fInterval(0.0f)
, m_pTarget(NULL)
, m_fElapsed(0.0f)
, m_nScriptHandler(0)
{

}

CCTimer* CCTimer::timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector)
{
	CCTimer *pTimer = new CCTimer();

	pTimer->initWithTarget(pTarget, pfnSelector);
	pTimer->autorelease();

	return pTimer;
}

CCTimer* CCTimer::timerWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds)
{
	CCTimer *pTimer = new CCTimer();

	pTimer->initWithTarget(pTarget, pfnSelector, fSeconds);
	pTimer->autorelease();

	return pTimer;
}

CCTimer* CCTimer::timerWithScriptHandler(int nHandler, ccTime fSeconds)
{
	CCTimer *pTimer = new CCTimer();

    pTimer->initWithScriptHandler(nHandler, fSeconds);
	pTimer->autorelease();

	return pTimer;
}

bool CCTimer::initWithScriptHandler(int nHandler, ccTime fSeconds)
{
    m_nScriptHandler = nHandler;
	m_fElapsed = -1;
    m_fInterval = fSeconds;

	return true;
}

bool CCTimer::initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector)
{
    return initWithTarget(pTarget, pfnSelector, 0);
}

bool CCTimer::initWithTarget(CCObject *pTarget, SEL_SCHEDULE pfnSelector, ccTime fSeconds)
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
        if (0 != m_pfnSelector)
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


// implementation of CCScheduler

static CCScheduler *pSharedScheduler;

CCScheduler::CCScheduler(void)
: m_fTimeScale(0.0)
, m_pUpdatesNegList(NULL)
, m_pUpdates0List(NULL)
, m_pUpdatesPosList(NULL)
, m_pHashForUpdates(NULL)
, m_pHashForSelectors(NULL)
, m_pCurrentTarget(NULL)
, m_bCurrentTargetSalvaged(false)
, m_pScriptHandlerEntries(NULL)
{
	CCAssert(pSharedScheduler == NULL, "");
}

CCScheduler::~CCScheduler(void)
{
	unscheduleAllSelectors();

	pSharedScheduler = NULL;
    CC_SAFE_RELEASE(m_pScriptHandlerEntries);
}

CCScheduler* CCScheduler::sharedScheduler(void)
{
	if (! pSharedScheduler)
	{
		pSharedScheduler = new CCScheduler();
		pSharedScheduler->init();
	}

	return pSharedScheduler;
}

bool CCScheduler::init(void)
{
	m_fTimeScale = 1.0f;

	// used to trigger CCTimer#update
	// m_pfnUpdateSelector = &CCScheduler::update;
	// impMethod = (TICK_IMP) [CCTimer instanceMethodForSelector:updateSelector];

	// updates with priority
	m_pUpdates0List = NULL;
	m_pUpdatesNegList = NULL;
	m_pUpdatesPosList = NULL;
	m_pHashForUpdates = NULL;

	// selectors with interval
	m_pCurrentTarget = NULL;
    m_bCurrentTargetSalvaged = false;
	m_pHashForSelectors = NULL;
	m_bUpdateHashLocked = false;

	return true;
}

void CCScheduler::removeHashElement(_hashSelectorEntry *pElement)
{
	ccArrayFree(pElement->timers);
	pElement->target->release();
	pElement->target = NULL;
	HASH_DEL(m_pHashForSelectors, pElement);
	free(pElement);
}

void CCScheduler::scheduleSelector(SEL_SCHEDULE pfnSelector, CCObject *pTarget, float fInterval, bool bPaused)
{
	CCAssert(pfnSelector, "");
	CCAssert(pTarget, "");

	tHashSelectorEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);

	if (! pElement)
	{
		pElement = (tHashSelectorEntry *)calloc(sizeof(*pElement), 1);
		pElement->target = pTarget;
		if (pTarget)
		{
		    pTarget->retain();
		}
		HASH_ADD_INT(m_pHashForSelectors, target, pElement);

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

			if (pfnSelector == timer->m_pfnSelector)
			{
				CCLOG("CCSheduler#scheduleSelector. Selector already scheduled.");
				timer->m_fInterval = fInterval;
				return;
			}		
		}
		ccArrayEnsureExtraCapacity(pElement->timers, 1);
	}

	CCTimer *pTimer = new CCTimer();
	pTimer->initWithTarget(pTarget, pfnSelector, fInterval);
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

	tHashSelectorEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);

	if (pElement)
	{
		for (unsigned int i = 0; i < pElement->timers->num; ++i)
		{
			CCTimer *pTimer = (CCTimer*)(pElement->timers->arr[i]);

			if (pfnSelector == pTimer->m_pfnSelector)
			{
				if (pTimer == pElement->currentTimer && (! pElement->currentTimerSalvaged))
				{
					pElement->currentTimer->retain();
					pElement->currentTimerSalvaged = true;
				}

				ccArrayRemoveObjectAtIndex(pElement->timers, i );

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

	// empey list ?
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
	} else
	if (nPriority < 0)
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
		element->target->release();
		HASH_DEL(m_pHashForUpdates, element);
		free(element);
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

void CCScheduler::unscheduleAllSelectors(void)
{
	// Custom Selectors
    tHashSelectorEntry *pElement = NULL;
	tHashSelectorEntry *pNextElement = NULL;
	for (pElement = m_pHashForSelectors; pElement != NULL;)
	{
		// pElement may be removed in unscheduleAllSelectorsForTarget
		pNextElement = (tHashSelectorEntry *)pElement->hh.next;
		unscheduleAllSelectorsForTarget(pElement->target);

        pElement = pNextElement;
	}

	// Updates selectors
	tListEntry *pEntry, *pTmp;
	DL_FOREACH_SAFE(m_pUpdates0List, pEntry, pTmp)
	{
		unscheduleUpdateForTarget(pEntry->target);
	}
	DL_FOREACH_SAFE(m_pUpdatesNegList, pEntry, pTmp)
	{
        unscheduleUpdateForTarget(pEntry->target);
	}
	DL_FOREACH_SAFE(m_pUpdatesPosList, pEntry, pTmp)
	{
        unscheduleUpdateForTarget(pEntry->target);
	}

    if (m_pScriptHandlerEntries)
    {
        m_pScriptHandlerEntries->removeAllObjects();
    }
}

void CCScheduler::unscheduleAllSelectorsForTarget(CCObject *pTarget)
{
	// explicit NULL handling
	if (pTarget == NULL)
	{
		return;
	}

	// Custom Selectors
	tHashSelectorEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);

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

unsigned int CCScheduler::scheduleScriptFunc(unsigned int nHandler, ccTime fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = CCSchedulerScriptHandlerEntry::entryWithHandler(nHandler, fInterval, bPaused);
    if (!m_pScriptHandlerEntries)
    {
        m_pScriptHandlerEntries = CCArray::arrayWithCapacity(20);
        m_pScriptHandlerEntries->retain();
    }
    m_pScriptHandlerEntries->addObject(pEntry);
    return pEntry->getEntryID();
}

void CCScheduler::unscheduleScriptEntry(unsigned int uScheduleScriptEntryID)
{
    for (int i = m_pScriptHandlerEntries->count() - 1; i >= 0; i--)
    {
        CCSchedulerScriptHandlerEntry* pEntry = static_cast<CCSchedulerScriptHandlerEntry*>(m_pScriptHandlerEntries->objectAtIndex(i));
        if (pEntry->getEntryID() == uScheduleScriptEntryID)
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
	tHashSelectorEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);
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
	tHashSelectorEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);
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
    tHashSelectorEntry *pElement = NULL;
    HASH_FIND_INT(m_pHashForSelectors, &pTarget, pElement);
    if( pElement )
    {
        return pElement->paused;
    }
    return false;  // should never get here
}

// main loop
void CCScheduler::tick(ccTime dt)
{
	m_bUpdateHashLocked = true;

	if (m_fTimeScale != 1.0f)
	{
		dt *= m_fTimeScale;
	}

	// Iterate all over the Updates selectors
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

	// Interate all over the custom selectors
	for (tHashSelectorEntry *elt = m_pHashForSelectors; elt != NULL; )
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
		elt = (tHashSelectorEntry *)elt->hh.next;

		// only delete currentTarget if no actions were scheduled during the cycle (issue #481)
		if (m_bCurrentTargetSalvaged && m_pCurrentTarget->timers->num == 0)
		{
			removeHashElement(m_pCurrentTarget);
		}
	}

    // Interate all over the script callbacks
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

	// delete all updates that are morked for deletion
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

void CCScheduler::purgeSharedScheduler(void)
{
	pSharedScheduler->release();
	pSharedScheduler = NULL;
}
}//namespace   cocos2d 
