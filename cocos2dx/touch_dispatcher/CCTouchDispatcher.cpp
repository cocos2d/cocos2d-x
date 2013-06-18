/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Valentin Milea

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

#include "CCTouchDispatcher.h"
#include "CCTouchHandler.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCSet.h"
#include "CCTouch.h"
#include "textures/CCTexture2D.h"
#include "support/data_support/ccCArray.h"
#include "ccMacros.h"
#include <algorithm>

NS_CC_BEGIN

/**
 * Used for sort
 */
static int less(const CCObject* p1, const CCObject* p2)
{
    return ((CCTouchHandler*)p1)->getPriority() < ((CCTouchHandler*)p2)->getPriority();
}

bool CCTouchDispatcher::isDispatchEvents(void)
{
    return _dispatchEvents;
}

void CCTouchDispatcher::setDispatchEvents(bool bDispatchEvents)
{
    _dispatchEvents = bDispatchEvents;
}

/*
+(id) allocWithZone:(CCZone *)zone
{
    @synchronized(self) {
        CCAssert(sharedDispatcher == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super allocWithZone:zone];
    }
    return nil; // on subsequent allocation attempts return nil
}
*/

bool CCTouchDispatcher::init(void)
{
    _dispatchEvents = true;
    _targetedHandlers = CCArray::createWithCapacity(8);
    _targetedHandlers->retain();
     _standardHandlers = CCArray::createWithCapacity(4);
    _standardHandlers->retain();
    _handlersToAdd = CCArray::createWithCapacity(8);
    _handlersToAdd->retain();
    _handlersToRemove = ccCArrayNew(8);

    _toRemove = false;
    _toAdd = false;
    _toQuit = false;
    _locked = false;

    _handlerHelperData[CCTOUCHBEGAN]._type = CCTOUCHBEGAN;
    _handlerHelperData[CCTOUCHMOVED]._type = CCTOUCHMOVED;
    _handlerHelperData[CCTOUCHENDED]._type = CCTOUCHENDED;
    _handlerHelperData[CCTOUCHCANCELLED]._type = CCTOUCHCANCELLED;

    return true;
}

CCTouchDispatcher::~CCTouchDispatcher(void)
{
     CC_SAFE_RELEASE(_targetedHandlers);
     CC_SAFE_RELEASE(_standardHandlers);
     CC_SAFE_RELEASE(_handlersToAdd);
 
     ccCArrayFree(_handlersToRemove);
    _handlersToRemove = NULL;    
}

//
// handlers management
//
void CCTouchDispatcher::forceAddHandler(CCTouchHandler *pHandler, CCArray *pArray)
{
    unsigned int u = 0;

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
     {
         CCTouchHandler *h = (CCTouchHandler *)pObj;
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

void CCTouchDispatcher::addStandardDelegate(CCTouchDelegate *pDelegate, int nPriority)
{    
    CCTouchHandler *pHandler = CCStandardTouchHandler::handlerWithDelegate(pDelegate, nPriority);
    if (! _locked)
    {
        forceAddHandler(pHandler, _standardHandlers);
    }
    else
    {
        /* If pHandler is contained in _handlersToRemove, if so remove it from _handlersToRemove and return.
         * Refer issue #752(cocos2d-x)
         */
        if (ccCArrayContainsValue(_handlersToRemove, pDelegate))
        {
            ccCArrayRemoveValue(_handlersToRemove, pDelegate);
            return;
        }

        _handlersToAdd->addObject(pHandler);
        _toAdd = true;
    }
}

void CCTouchDispatcher::addTargetedDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallowsTouches)
{    
    CCTouchHandler *pHandler = CCTargetedTouchHandler::handlerWithDelegate(pDelegate, nPriority, bSwallowsTouches);
    if (! _locked)
    {
        forceAddHandler(pHandler, _targetedHandlers);
    }
    else
    {
        /* If pHandler is contained in _handlersToRemove, if so remove it from _handlersToRemove and return.
         * Refer issue #752(cocos2d-x)
         */
        if (ccCArrayContainsValue(_handlersToRemove, pDelegate))
        {
            ccCArrayRemoveValue(_handlersToRemove, pDelegate);
            return;
        }
        
        _handlersToAdd->addObject(pHandler);
        _toAdd = true;
    }
}

void CCTouchDispatcher::forceRemoveDelegate(CCTouchDelegate *pDelegate)
{
    CCTouchHandler *pHandler;

    // XXX: remove it from both handlers ???
    
    // remove handler from _standardHandlers
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_standardHandlers, pObj)
    {
        pHandler = (CCTouchHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            _standardHandlers->removeObject(pHandler);
            break;
        }
    }

    // remove handler from _targetedHandlers
    CCARRAY_FOREACH(_targetedHandlers, pObj)
    {
        pHandler = (CCTouchHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            _targetedHandlers->removeObject(pHandler);
            break;
        }
    }
}

void CCTouchDispatcher::removeDelegate(CCTouchDelegate *pDelegate)
{
    if (pDelegate == NULL)
    {
        return;
    }

    if (! _locked)
    {
        forceRemoveDelegate(pDelegate);
    }
    else
    {
        /* If pHandler is contained in _handlersToAdd, if so remove it from _handlersToAdd and return.
         * Refer issue #752(cocos2d-x)
         */
        CCTouchHandler *pHandler = findHandler(_handlersToAdd, pDelegate);
        if (pHandler)
        {
            _handlersToAdd->removeObject(pHandler);
            return;
        }

        ccCArrayAppendValue(_handlersToRemove, pDelegate);
        _toRemove = true;
    }
}

void CCTouchDispatcher::forceRemoveAllDelegates(void)
{
     _standardHandlers->removeAllObjects();
     _targetedHandlers->removeAllObjects();
}

void CCTouchDispatcher::removeAllDelegates(void)
{
    if (! _locked)
    {
        forceRemoveAllDelegates();
    }
    else
    {
        _toQuit = true;
    }
}

CCTouchHandler* CCTouchDispatcher::findHandler(CCTouchDelegate *pDelegate)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_targetedHandlers, pObj)
    {
        CCTouchHandler* pHandler = (CCTouchHandler*)pObj;
        if (pHandler->getDelegate() == pDelegate)
        {
            return pHandler;
        }
    }

    CCARRAY_FOREACH(_standardHandlers, pObj)
    {
        CCTouchHandler* pHandler = (CCTouchHandler*)pObj;
        if (pHandler->getDelegate() == pDelegate)
        {
            return pHandler;
        }
    } 

    return NULL;
}

CCTouchHandler* CCTouchDispatcher::findHandler(CCArray* pArray, CCTouchDelegate *pDelegate)
{
    CCAssert(pArray != NULL && pDelegate != NULL, "");

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        CCTouchHandler* pHandle = (CCTouchHandler*)pObj;
        if (pHandle->getDelegate() == pDelegate)
        {
            return pHandle;
        }
    }

    return NULL;
}

void CCTouchDispatcher::rearrangeHandlers(CCArray *pArray)
{
    std::sort(pArray->data->arr, pArray->data->arr + pArray->data->num, less);
}

void CCTouchDispatcher::setPriority(int nPriority, CCTouchDelegate *pDelegate)
{
    CCAssert(pDelegate != NULL, "");

    CCTouchHandler *handler = NULL;

    handler = this->findHandler(pDelegate);

    CCAssert(handler != NULL, "");
	
    if (handler->getPriority() != nPriority)
    {
        handler->setPriority(nPriority);
        this->rearrangeHandlers(_targetedHandlers);
        this->rearrangeHandlers(_standardHandlers);
    }
}

//
// dispatch events
//
void CCTouchDispatcher::touches(CCSet *pTouches, CCEvent *pEvent, unsigned int uIndex)
{
    CCAssert(uIndex >= 0 && uIndex < 4, "");

    CCSet *pMutableTouches;
    _locked = true;

    // optimization to prevent a mutable copy when it is not necessary
     unsigned int uTargetedHandlersCount = _targetedHandlers->count();
     unsigned int uStandardHandlersCount = _standardHandlers->count();
    bool bNeedsMutableSet = (uTargetedHandlersCount && uStandardHandlersCount);

    pMutableTouches = (bNeedsMutableSet ? pTouches->mutableCopy() : pTouches);

    struct ccTouchHandlerHelperData sHelper = _handlerHelperData[uIndex];
    //
    // process the target handlers 1st
    //
    if (uTargetedHandlersCount > 0)
    {
        CCTouch *pTouch;
        CCSetIterator setIter;
        for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
        {
            pTouch = (CCTouch *)(*setIter);

            CCTargetedTouchHandler *pHandler = NULL;
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(_targetedHandlers, pObj)
            {
                pHandler = (CCTargetedTouchHandler *)(pObj);

                if (! pHandler)
                {
                   break;
                }

                bool bClaimed = false;
                if (uIndex == CCTOUCHBEGAN)
                {
                    bClaimed = pHandler->getDelegate()->ccTouchBegan(pTouch, pEvent);

                    if (bClaimed)
                    {
                        pHandler->getClaimedTouches()->addObject(pTouch);
                    }
                } else
                if (pHandler->getClaimedTouches()->containsObject(pTouch))
                {
                    // moved ended canceled
                    bClaimed = true;

                    switch (sHelper._type)
                    {
                    case CCTOUCHMOVED:
                        pHandler->getDelegate()->ccTouchMoved(pTouch, pEvent);
                        break;
                    case CCTOUCHENDED:
                        pHandler->getDelegate()->ccTouchEnded(pTouch, pEvent);
                        pHandler->getClaimedTouches()->removeObject(pTouch);
                        break;
                    case CCTOUCHCANCELLED:
                        pHandler->getDelegate()->ccTouchCancelled(pTouch, pEvent);
                        pHandler->getClaimedTouches()->removeObject(pTouch);
                        break;
                    }
                }

                if (bClaimed && pHandler->isSwallowsTouches())
                {
                    if (bNeedsMutableSet)
                    {
                        pMutableTouches->removeObject(pTouch);
                    }

                    break;
                }
            }
        }
    }

    //
    // process standard handlers 2nd
    //
    if (uStandardHandlersCount > 0 && pMutableTouches->count() > 0)
    {
        CCStandardTouchHandler *pHandler = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(_standardHandlers, pObj)
        {
            pHandler = (CCStandardTouchHandler*)(pObj);

            if (! pHandler)
            {
                break;
            }

            switch (sHelper._type)
            {
            case CCTOUCHBEGAN:
                pHandler->getDelegate()->ccTouchesBegan(pMutableTouches, pEvent);
                break;
            case CCTOUCHMOVED:
                pHandler->getDelegate()->ccTouchesMoved(pMutableTouches, pEvent);
                break;
            case CCTOUCHENDED:
                pHandler->getDelegate()->ccTouchesEnded(pMutableTouches, pEvent);
                break;
            case CCTOUCHCANCELLED:
                pHandler->getDelegate()->ccTouchesCancelled(pMutableTouches, pEvent);
                break;
            }
        }
    }

    if (bNeedsMutableSet)
    {
        pMutableTouches->release();
    }

    //
    // Optimization. To prevent a [handlers copy] which is expensive
    // the add/removes/quit is done after the iterations
    //
    _locked = false;
    if (_toRemove)
    {
        _toRemove = false;
        for (unsigned int i = 0; i < _handlersToRemove->num; ++i)
        {
            forceRemoveDelegate((CCTouchDelegate*)_handlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(_handlersToRemove);
    }

    if (_toAdd)
    {
        _toAdd = false;
        CCTouchHandler* pHandler = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(_handlersToAdd, pObj)
         {
             pHandler = (CCTouchHandler*)pObj;
            if (! pHandler)
            {
                break;
            }

            if (dynamic_cast<CCTargetedTouchHandler*>(pHandler) != NULL)
            {                
                forceAddHandler(pHandler, _targetedHandlers);
            }
            else
            {
                forceAddHandler(pHandler, _standardHandlers);
            }
         }
 
         _handlersToAdd->removeAllObjects();    
    }

    if (_toQuit)
    {
        _toQuit = false;
        forceRemoveAllDelegates();
    }
}

void CCTouchDispatcher::touchesBegan(CCSet *touches, CCEvent *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHBEGAN);
    }
}

void CCTouchDispatcher::touchesMoved(CCSet *touches, CCEvent *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHMOVED);
    }
}

void CCTouchDispatcher::touchesEnded(CCSet *touches, CCEvent *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHENDED);
    }
}

void CCTouchDispatcher::touchesCancelled(CCSet *touches, CCEvent *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHCANCELLED);
    }
}

NS_CC_END
