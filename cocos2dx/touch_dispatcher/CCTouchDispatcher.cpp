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
static int less(const Object* p1, const Object* p2)
{
    return ((TouchHandler*)p1)->getPriority() < ((TouchHandler*)p2)->getPriority();
}

bool TouchDispatcher::isDispatchEvents(void)
{
    return _dispatchEvents;
}

void TouchDispatcher::setDispatchEvents(bool bDispatchEvents)
{
    _dispatchEvents = bDispatchEvents;
}

/*
+(id) allocWithZone:(Zone *)zone
{
    @synchronized(self) {
        CCASSERT(sharedDispatcher == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super allocWithZone:zone];
    }
    return nil; // on subsequent allocation attempts return nil
}
*/

bool TouchDispatcher::init(void)
{
    _dispatchEvents = true;
    _targetedHandlers = Array::createWithCapacity(8);
    _targetedHandlers->retain();
     _standardHandlers = Array::createWithCapacity(4);
    _standardHandlers->retain();
    _handlersToAdd = Array::createWithCapacity(8);
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

TouchDispatcher::~TouchDispatcher(void)
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
void TouchDispatcher::forceAddHandler(TouchHandler *pHandler, Array *pArray)
{
    unsigned int u = 0;

    Object* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
     {
         TouchHandler *h = static_cast<TouchHandler *>(pObj);
         if (h)
         {
             if (h->getPriority() < pHandler->getPriority())
             {
                 ++u;
             }
 
             if (h->getDelegate() == pHandler->getDelegate())
             {
                 CCASSERT(0, "");
                 return;
             }
         }
     }

    pArray->insertObject(pHandler, u);
}

void TouchDispatcher::addStandardDelegate(TouchDelegate *pDelegate, int nPriority)
{    
    TouchHandler *pHandler = StandardTouchHandler::handlerWithDelegate(pDelegate, nPriority);
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

void TouchDispatcher::addTargetedDelegate(TouchDelegate *pDelegate, int nPriority, bool bSwallowsTouches)
{    
    TouchHandler *pHandler = TargetedTouchHandler::handlerWithDelegate(pDelegate, nPriority, bSwallowsTouches);
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

void TouchDispatcher::forceRemoveDelegate(TouchDelegate *pDelegate)
{
    TouchHandler *pHandler;

    // XXX: remove it from both handlers ???
    
    // remove handler from _standardHandlers
    Object* pObj = NULL;
    CCARRAY_FOREACH(_standardHandlers, pObj)
    {
        pHandler = static_cast<TouchHandler*>(pObj);
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            _standardHandlers->removeObject(pHandler);
            break;
        }
    }

    // remove handler from _targetedHandlers
    CCARRAY_FOREACH(_targetedHandlers, pObj)
    {
        pHandler = static_cast<TouchHandler*>(pObj);
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            _targetedHandlers->removeObject(pHandler);
            break;
        }
    }
}

void TouchDispatcher::removeDelegate(TouchDelegate *pDelegate)
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
        TouchHandler *pHandler = findHandler(_handlersToAdd, pDelegate);
        if (pHandler)
        {
            _handlersToAdd->removeObject(pHandler);
            return;
        }

        ccCArrayAppendValue(_handlersToRemove, pDelegate);
        _toRemove = true;
    }
}

void TouchDispatcher::forceRemoveAllDelegates(void)
{
     _standardHandlers->removeAllObjects();
     _targetedHandlers->removeAllObjects();
}

void TouchDispatcher::removeAllDelegates(void)
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

TouchHandler* TouchDispatcher::findHandler(TouchDelegate *pDelegate)
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(_targetedHandlers, pObj)
    {
        TouchHandler* pHandler = static_cast<TouchHandler*>(pObj);
        if (pHandler->getDelegate() == pDelegate)
        {
            return pHandler;
        }
    }

    CCARRAY_FOREACH(_standardHandlers, pObj)
    {
        TouchHandler* pHandler = static_cast<TouchHandler*>(pObj);
        if (pHandler->getDelegate() == pDelegate)
        {
            return pHandler;
        }
    } 

    return NULL;
}

TouchHandler* TouchDispatcher::findHandler(Array* pArray, TouchDelegate *pDelegate)
{
    CCASSERT(pArray != NULL && pDelegate != NULL, "");

    Object* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        TouchHandler* pHandle = static_cast<TouchHandler*>(pObj);
        if (pHandle->getDelegate() == pDelegate)
        {
            return pHandle;
        }
    }

    return NULL;
}

void TouchDispatcher::rearrangeHandlers(Array *pArray)
{
    std::sort(pArray->data->arr, pArray->data->arr + pArray->data->num, less);
}

void TouchDispatcher::setPriority(int nPriority, TouchDelegate *pDelegate)
{
    CCASSERT(pDelegate != NULL, "");

    TouchHandler *handler = NULL;

    handler = this->findHandler(pDelegate);

    CCASSERT(handler != NULL, "");
	
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
void TouchDispatcher::touches(Set *pTouches, Event *pEvent, unsigned int uIndex)
{
    CCASSERT(uIndex >= 0 && uIndex < 4, "");

    Set *pMutableTouches;
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
        Touch *pTouch;
        SetIterator setIter;
        for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
        {
            pTouch = (Touch *)(*setIter);

            TargetedTouchHandler *pHandler = NULL;
            Object* pObj = NULL;
            CCARRAY_FOREACH(_targetedHandlers, pObj)
            {
                pHandler = static_cast<TargetedTouchHandler*>(pObj);

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
        StandardTouchHandler *pHandler = NULL;
        Object* pObj = nullptr;
        CCARRAY_FOREACH(_standardHandlers, pObj)
        {
            pHandler = static_cast<StandardTouchHandler*>(pObj);

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
            forceRemoveDelegate((TouchDelegate*)_handlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(_handlersToRemove);
    }

    if (_toAdd)
    {
        _toAdd = false;
        TouchHandler* pHandler = NULL;
        Object* pObj = nullptr;
        CCARRAY_FOREACH(_handlersToAdd, pObj)
         {
             pHandler = static_cast<TouchHandler*>(pObj);
            if (! pHandler)
            {
                break;
            }

            if (dynamic_cast<TargetedTouchHandler*>(pHandler) != NULL)
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

void TouchDispatcher::touchesBegan(Set *touches, Event *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHBEGAN);
    }
}

void TouchDispatcher::touchesMoved(Set *touches, Event *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHMOVED);
    }
}

void TouchDispatcher::touchesEnded(Set *touches, Event *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHENDED);
    }
}

void TouchDispatcher::touchesCancelled(Set *touches, Event *pEvent)
{
    if (_dispatchEvents)
    {
        this->touches(touches, pEvent, CCTOUCHCANCELLED);
    }
}

NS_CC_END
