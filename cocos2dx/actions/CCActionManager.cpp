/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "base_nodes/CCNode.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "support/data_support/ccCArray.h"
#include "support/data_support/uthash.h"
#include "cocoa/CCSet.h"

NS_CC_BEGIN
//
// singleton stuff
//
typedef struct _hashElement
{
    struct _ccArray             *actions;
    CCObject                    *target;
    unsigned int                actionIndex;
    CCAction                    *currentAction;
    bool                        currentActionSalvaged;
    bool                        paused;
    UT_hash_handle                hh;
} tHashElement;

CCActionManager::CCActionManager(void)
: _targets(NULL), 
  _currentTarget(NULL),
  _currentTargetSalvaged(false)
{

}

CCActionManager::~CCActionManager(void)
{
    CCLOGINFO("cocos2d: deallocing %p", this);

    removeAllActions();
}

// private

void CCActionManager::deleteHashElement(tHashElement *pElement)
{
    ccArrayFree(pElement->actions);
    HASH_DEL(_targets, pElement);
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

    ccArrayRemoveObjectAtIndex(pElement->actions, uIndex, true);

    // update actionIndex in case we are in tick. looping over the actions
    if (pElement->actionIndex >= uIndex)
    {
        pElement->actionIndex--;
    }

    if (pElement->actions->num == 0)
    {
        if (_currentTarget == pElement)
        {
            _currentTargetSalvaged = true;
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
    HASH_FIND_INT(_targets, &pTarget, pElement);
    if (pElement)
    {
        pElement->paused = true;
    }
}

void CCActionManager::resumeTarget(CCObject *pTarget)
{
    tHashElement *pElement = NULL;
    HASH_FIND_INT(_targets, &pTarget, pElement);
    if (pElement)
    {
        pElement->paused = false;
    }
}

CCSet* CCActionManager::pauseAllRunningActions()
{
    CCSet *idsWithActions = new CCSet();
    idsWithActions->autorelease();
    
    for (tHashElement *element=_targets; element != NULL; element = (tHashElement *)element->hh.next) 
    {
        if (! element->paused) 
        {
            element->paused = true;
            idsWithActions->addObject(element->target);
        }
    }    
    
    return idsWithActions;
}

void CCActionManager::resumeTargets(cocos2d::CCSet *targetsToResume)
{    
    CCSetIterator iter;
    for (iter = targetsToResume->begin(); iter != targetsToResume->end(); ++iter)
    {
        resumeTarget(*iter);
    }
}

// run

void CCActionManager::addAction(CCAction *pAction, CCNode *pTarget, bool paused)
{
    CCAssert(pAction != NULL, "");
    CCAssert(pTarget != NULL, "");

    tHashElement *pElement = NULL;
    // we should convert it to CCObject*, because we save it as CCObject*
    CCObject *tmp = pTarget;
    HASH_FIND_INT(_targets, &tmp, pElement);
    if (! pElement)
    {
        pElement = (tHashElement*)calloc(sizeof(*pElement), 1);
        pElement->paused = paused;
        pTarget->retain();
        pElement->target = pTarget;
        HASH_ADD_INT(_targets, target, pElement);
    }

     actionAllocWithHashElement(pElement);
 
     CCAssert(! ccArrayContainsObject(pElement->actions, pAction), "");
     ccArrayAppendObject(pElement->actions, pAction);
 
     pAction->startWithTarget(pTarget);
}

// remove

void CCActionManager::removeAllActions(void)
{
    for (tHashElement *pElement = _targets; pElement != NULL; )
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
    HASH_FIND_INT(_targets, &pTarget, pElement);
    if (pElement)
    {
        if (ccArrayContainsObject(pElement->actions, pElement->currentAction) && (! pElement->currentActionSalvaged))
        {
            pElement->currentAction->retain();
            pElement->currentActionSalvaged = true;
        }

        ccArrayRemoveAllObjects(pElement->actions);
        if (_currentTarget == pElement)
        {
            _currentTargetSalvaged = true;
        }
        else
        {
            deleteHashElement(pElement);
        }
    }
    else
    {
//        CCLOG("cocos2d: removeAllActionsFromTarget: Target not found");
    }
}

void CCActionManager::removeAction(CCAction *pAction)
{
    // explicit null handling
    if (pAction == NULL)
    {
        return;
    }

    tHashElement *pElement = NULL;
    CCObject *pTarget = pAction->getOriginalTarget();
    HASH_FIND_INT(_targets, &pTarget, pElement);
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
    CCAssert((int)tag != kCCActionTagInvalid, "");
    CCAssert(pTarget != NULL, "");

    tHashElement *pElement = NULL;
    HASH_FIND_INT(_targets, &pTarget, pElement);

    if (pElement)
    {
        unsigned int limit = pElement->actions->num;
        for (unsigned int i = 0; i < limit; ++i)
        {
            CCAction *pAction = (CCAction*)pElement->actions->arr[i];

            if (pAction->getTag() == (int)tag && pAction->getOriginalTarget() == pTarget)
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
    CCAssert((int)tag != kCCActionTagInvalid, "");

    tHashElement *pElement = NULL;
    HASH_FIND_INT(_targets, &pTarget, pElement);

    if (pElement)
    {
        if (pElement->actions != NULL)
        {
            unsigned int limit = pElement->actions->num;
            for (unsigned int i = 0; i < limit; ++i)
            {
                CCAction *pAction = (CCAction*)pElement->actions->arr[i];

                if (pAction->getTag() == (int)tag)
                {
                    return pAction;
                }
            }
        }
        CCLOG("cocos2d : getActionByTag(tag = %d): Action not found", tag);
    }
    else
    {
        // CCLOG("cocos2d : getActionByTag: Target not found");
    }

    return NULL;
}

unsigned int CCActionManager::numberOfRunningActionsInTarget(CCObject *pTarget)
{
    tHashElement *pElement = NULL;
    HASH_FIND_INT(_targets, &pTarget, pElement);
    if (pElement)
    {
        return pElement->actions ? pElement->actions->num : 0;
    }

    return 0;
}

// main loop
void CCActionManager::update(float dt)
{
    for (tHashElement *elt = _targets; elt != NULL; )
    {
        _currentTarget = elt;
        _currentTargetSalvaged = false;

        if (! _currentTarget->paused)
        {
            // The 'actions' CCMutableArray may change while inside this loop.
            for (_currentTarget->actionIndex = 0; _currentTarget->actionIndex < _currentTarget->actions->num;
                _currentTarget->actionIndex++)
            {
                _currentTarget->currentAction = (CCAction*)_currentTarget->actions->arr[_currentTarget->actionIndex];
                if (_currentTarget->currentAction == NULL)
                {
                    continue;
                }

                _currentTarget->currentActionSalvaged = false;

                _currentTarget->currentAction->step(dt);

                if (_currentTarget->currentActionSalvaged)
                {
                    // The currentAction told the node to remove it. To prevent the action from
                    // accidentally deallocating itself before finishing its step, we retained
                    // it. Now that step is done, it's safe to release it.
                    _currentTarget->currentAction->release();
                } else
                if (_currentTarget->currentAction->isDone())
                {
                    _currentTarget->currentAction->stop();

                    CCAction *pAction = _currentTarget->currentAction;
                    // Make currentAction nil to prevent removeAction from salvaging it.
                    _currentTarget->currentAction = NULL;
                    removeAction(pAction);
                }

                _currentTarget->currentAction = NULL;
            }
        }

        // elt, at this moment, is still valid
        // so it is safe to ask this here (issue #490)
        elt = (tHashElement*)(elt->hh.next);

        // only delete currentTarget if no actions were scheduled during the cycle (issue #481)
        if (_currentTargetSalvaged && _currentTarget->actions->num == 0)
        {
            deleteHashElement(_currentTarget);
        }
    }

    // issue #635
    _currentTarget = NULL;
}

NS_CC_END
