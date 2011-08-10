/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
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

#include "CCActionManager.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "support/data_support/ccCArray.h"
#include "support/data_support/uthash.h"

namespace cocos2d {
//
// singleton stuff
//
static CCActionManager *gSharedManager = NULL;

typedef struct _hashElement
{
	struct _ccArray             *actions;
	CCObject					*target;
	unsigned int				actionIndex;
	CCAction					*currentAction;
	bool						currentActionSalvaged;
	bool						paused;
	UT_hash_handle				hh;
} tHashElement;

CCActionManager* CCActionManager::sharedManager(void)
{
	CCActionManager *pRet = gSharedManager;

	if (! gSharedManager)
	{
		pRet = gSharedManager = new CCActionManager();

		if (! gSharedManager->init())
		{
			// delete CCActionManager if init error
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}

	return pRet;
}

void CCActionManager::purgeSharedManager(void)
{
	CCScheduler::sharedScheduler()->unscheduleUpdateForTarget(this);
	CC_SAFE_RELEASE(gSharedManager);
}

void CCActionManager::selectorProtocolRetain()
{
	retain();
}

void CCActionManager::selectorProtocolRelease()
{
	release();
}

CCActionManager::CCActionManager(void)
: m_pTargets(NULL), 
  m_pCurrentTarget(NULL),
  m_bCurrentTargetSalvaged(false)
{
	assert(gSharedManager == NULL);
}

CCActionManager::~CCActionManager(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);

	removeAllActions();

	// ?? do not delete , is it because purgeSharedManager() delete it? 
	gSharedManager = NULL;
}

bool CCActionManager::init(void)
{
	CCScheduler::sharedScheduler()->scheduleUpdateForTarget(this, 0, false);
	m_pTargets = NULL;

	return true;
}

// private

void CCActionManager::deleteHashElement(tHashElement *pElement)
{
	ccArrayFree(pElement->actions);
	HASH_DEL(m_pTargets, pElement);
	pElement->target->release();
	free(pElement);
}

void CCActionManager::actionAllocWithHashElement(tHashElement *pElement)
{
	// 4 actions per Node by default
	if (pElement->actions == NULL)
	{
		pElement->actions = ccArrayNew(4);
	}else 
	if (pElement->actions->num == pElement->actions->max)
	{
		ccArrayDoubleCapacity(pElement->actions);
	}

}

void CCActionManager::removeActionAtIndex(unsigned int uIndex, tHashElement *pElement)
{
	CCAction *pAction = (CCAction*)pElement->actions->arr[uIndex];

	if (pAction == pElement->currentAction && (! pElement->currentActionSalvaged))
	{
		pElement->currentAction->retain();
		pElement->currentActionSalvaged = true;
	}

	ccArrayRemoveObjectAtIndex(pElement->actions, uIndex);

	// update actionIndex in case we are in tick. looping over the actions
	if (pElement->actionIndex >= uIndex)
	{
		pElement->actionIndex--;
	}

	if (pElement->actions->num == 0)
	{
		if (m_pCurrentTarget == pElement)
		{
			m_bCurrentTargetSalvaged = true;
		}
		else
		{
			deleteHashElement(pElement);
		}
	}
}

// pause / resume

void CCActionManager::pauseTarget(CCObject *pTarget)
{
	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);
	if (pElement)
	{
		pElement->paused = true;
	}
}

void CCActionManager::resumeTarget(CCObject *pTarget)
{
	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);
	if (pElement)
	{
		pElement->paused = false;
	}
}

// run

void CCActionManager::addAction(cocos2d::CCAction *pAction, CCNode *pTarget, bool paused)
{
	assert(pAction != NULL);
	assert(pTarget != NULL);

	tHashElement *pElement = NULL;
	// we should convert it to CCObject*, because we save it as CCObject*
	CCObject *tmp = pTarget;
	HASH_FIND_INT(m_pTargets, &tmp, pElement);
	if (! pElement)
	{
		pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
		pElement->paused = paused;
		pTarget->retain();
		pElement->target = pTarget;
		HASH_ADD_INT(m_pTargets, target, pElement);
	}

 	actionAllocWithHashElement(pElement);
 
 	assert(! ccArrayContainsObject(pElement->actions, pAction));
 	ccArrayAppendObject(pElement->actions, pAction);
 
 	pAction->startWithTarget(pTarget);
}

// remove

void CCActionManager::removeAllActions(void)
{
	for (tHashElement *pElement = m_pTargets; pElement != NULL; )
	{
		CCObject *pTarget = pElement->target;
		pElement = (tHashElement*)pElement->hh.next;
		removeAllActionsFromTarget(pTarget);
	}
}

void CCActionManager::removeAllActionsFromTarget(CCObject *pTarget)
{
	// explicit null handling
	if (pTarget == NULL)
	{
		return;
	}

	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);
	if (pElement)
	{
		if (ccArrayContainsObject(pElement->actions, pElement->currentAction) && (! pElement->currentActionSalvaged))
		{
			pElement->currentAction->retain();
			pElement->currentActionSalvaged = true;
		}

		ccArrayRemoveAllObjects(pElement->actions);
		if (m_pCurrentTarget == pElement)
		{
			m_bCurrentTargetSalvaged = true;
		}
		else
		{
			deleteHashElement(pElement);
		}
	}
	else
	{
		CCLOG("cocos2d: removeAllActionsFromTarget: Target not found");
	}
}

void CCActionManager::removeAction(cocos2d::CCAction *pAction)
{
	// explicit null handling
	if (pAction == NULL)
	{
		return;
	}

	tHashElement *pElement = NULL;
	CCObject *pTarget = pAction->getOriginalTarget();
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);
	if (pElement)
	{
		unsigned int i = ccArrayGetIndexOfObject(pElement->actions, pAction);
		if (UINT_MAX != i)
		{
			removeActionAtIndex(i, pElement);
		}
	}
	else
	{
		CCLOG("cocos2d: removeAction: Target not found");
	}
}

void CCActionManager::removeActionByTag(unsigned int tag, CCObject *pTarget)
{
	assert(tag != kCCActionTagInvalid);
	assert(pTarget != NULL);

	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);

	if (pElement)
	{
		unsigned int limit = pElement->actions->num;
		for (unsigned int i = 0; i < limit; ++i)
		{
			CCAction *pAction = (CCAction*)pElement->actions->arr[i];

			if (pAction->getTag() == tag && pAction->getOriginalTarget() == pTarget)
			{
				removeActionAtIndex(i, pElement);
				break;
			}
		}
	}
}

// get

CCAction* CCActionManager::getActionByTag(unsigned int tag, CCObject *pTarget)
{
	assert(tag != kCCActionTagInvalid);

	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);

	if (pElement)
	{
		if (pElement->actions != NULL)
		{
			unsigned int limit = pElement->actions->num;
			for (unsigned int i = 0; i < limit; ++i)
			{
				CCAction *pAction = (CCAction*)pElement->actions->arr[i];

				if (pAction->getTag() == tag)
				{
					return pAction;
				}
			}
		}
		CCLOG("cocos2d : getActionByTag: Action not found");
	}
	else
	{
        CCLOG("cocos2d : getActionByTag: Target not found");
	}

	return NULL;
}

unsigned int CCActionManager::numberOfRunningActionsInTarget(CCObject *pTarget)
{
	tHashElement *pElement = NULL;
	HASH_FIND_INT(m_pTargets, &pTarget, pElement);
	if (pElement)
	{
		return pElement->actions ? pElement->actions->num : 0;
	}

	return 0;
}

// main loop
void CCActionManager::update(cocos2d::ccTime dt)
{
	for (tHashElement *elt = m_pTargets; elt != NULL; )
	{
		m_pCurrentTarget = elt;
		m_bCurrentTargetSalvaged = false;

		if (! m_pCurrentTarget->paused)
		{
			// The 'actions' CCMutableArray may change while inside this loop.
			for (m_pCurrentTarget->actionIndex = 0; m_pCurrentTarget->actionIndex < m_pCurrentTarget->actions->num;
				m_pCurrentTarget->actionIndex++)
			{
				m_pCurrentTarget->currentAction = (CCAction*)m_pCurrentTarget->actions->arr[m_pCurrentTarget->actionIndex];
				if (m_pCurrentTarget->currentAction == NULL)
				{
					continue;
				}

				m_pCurrentTarget->currentActionSalvaged = false;

				m_pCurrentTarget->currentAction->step(dt);

				if (m_pCurrentTarget->currentActionSalvaged)
				{
					// The currentAction told the node to remove it. To prevent the action from
					// accidentally deallocating itself before finishing its step, we retained
					// it. Now that step is done, it's safe to release it.
					m_pCurrentTarget->currentAction->release();
				} else
				if (m_pCurrentTarget->currentAction->isDone())
				{
					m_pCurrentTarget->currentAction->stop();

					CCAction *pAction = m_pCurrentTarget->currentAction;
					// Make currentAction nil to prevent removeAction from salvaging it.
					m_pCurrentTarget->currentAction = NULL;
					removeAction(pAction);
				}

				m_pCurrentTarget->currentAction = NULL;
			}
		}

		// elt, at this moment, is still valid
		// so it is safe to ask this here (issue #490)
		elt = (tHashElement*)(elt->hh.next);

		// only delete currentTarget if no actions were scheduled during the cycle (issue #481)
		if (m_bCurrentTargetSalvaged && m_pCurrentTarget->actions->num == 0)
		{
			deleteHashElement(m_pCurrentTarget);
		}
	}

	// issue #635
	m_pCurrentTarget = NULL;
}

}
