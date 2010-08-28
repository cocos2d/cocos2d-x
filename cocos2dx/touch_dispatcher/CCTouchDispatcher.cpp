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

#include "CCTouchDispatcher.h"
#include "CCTouchHandler.h"
#include "NSMutableArray.h"
#include "NSSet.h"
#include "CCTouch.h"
#include "CCTexture2D.h"
#include "support/data_support/ccArray.h"

#include <assert.h>
namespace   cocos2d {

bool CCTouchDispatcher::isDispatchEvents(void)
{
	return m_bDispatchEvents;
}

void CCTouchDispatcher::setDispatchEvents(bool bDispatchEvents)
{
	m_bDispatchEvents = bDispatchEvents;
}

static CCTouchDispatcher *pSharedDispatcher = NULL;

CCTouchDispatcher* CCTouchDispatcher::getSharedDispatcher(void)
{
	// synchronized ??
	if (pSharedDispatcher == NULL)
	{
		pSharedDispatcher = new CCTouchDispatcher();
		pSharedDispatcher->init();
	}

	return pSharedDispatcher;
}

/*
+(id) allocWithZone:(NSZone *)zone
{
	@synchronized(self) {
		NSAssert(sharedDispatcher == nil, @"Attempted to allocate a second instance of a singleton.");
		return [super allocWithZone:zone];
	}
	return nil; // on subsequent allocation attempts return nil
}
*/

CCTouchDispatcher* CCTouchDispatcher::init(void)
{
	m_bDispatchEvents = true;
 	m_pTargetedHandlers = new NSMutableArray<CCTouchHandler*>(8);
 	m_pStandardHandlers = new NSMutableArray<CCTouchHandler*>(4);
// 	m_pTargetedHandlers = ccCArrayNew(8);
// 	m_pStandardHandlers = ccCArrayNew(4);

 	m_pHandlersToAdd = new NSMutableArray<CCTouchHandler*>(8);
// 	m_pHandlersToRemove = new NSMutableArray<CCTouchDelegate*>(8);
    m_pHandlersToRemove = ccCArrayNew(8);

	m_bToRemove = false;
	m_bToAdd = false;
	m_bToQuit = false;
	m_bLocked = false;

	m_sHandlerHelperData[ccTouchBegan].m_type = ccTouchBegan;
	m_sHandlerHelperData[ccTouchMoved].m_type = ccTouchMoved;
	m_sHandlerHelperData[ccTouchEnded].m_type = ccTouchEnded;
	m_sHandlerHelperData[ccTouchCancelled].m_type = ccTouchCancelled;

	return this;
}

CCTouchDispatcher::~CCTouchDispatcher(void)
{
 	m_pTargetedHandlers->release();
 	m_pStandardHandlers->release();
 	m_pHandlersToAdd->release();
// 	m_pHandlersToRemove->release();
// 	ccCArrayFree(m_pTargetedHandlers);
// 	ccCArrayFree(m_pStandardHandlers);
// 	ccCArrayFree(m_pHandlersToAdd);
	ccCArrayFree(m_pHandlersToRemove);

    m_pTargetedHandlers = NULL;
    m_pStandardHandlers = NULL;
    m_pHandlersToAdd = NULL;
	m_pHandlersToRemove = NULL;
}

//
// handlers management
//
void CCTouchDispatcher::forceAddHandler(CCTouchHandler *pHandler, NSMutableArray<CCTouchHandler*> *pArray)
{
	unsigned int u = 0;

 	NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
 	for (iter = pArray->begin(); iter != pArray->end(); ++iter)
 	{
 		CCTouchHandler *h = *iter;
         if (h)
         {
 		    if (h->getPriority() < pHandler->getPriority())
 		    {
 			    ++u;
 		    }
 
 		    if (h->getDelegate() == pHandler->getDelegate())
 		    {
 			    assert(0);
 			    return;
 		    }
         }
 	}
// 	unsigned int num = pArray->num;
// 	for (unsigned int i = 0; i < num; ++i)
// 	{
// 		CCTouchHandler *h = (CCTouchHandler *)pArray->arr[i];
// 		if (h)
// 		{
// 			if (h->getPriority() < pHandler->getPriority())
// 			{
// 				++u;
// 			}
// 
// 			if (h->getDelegate() == pHandler->getDelegate())
// 			{
// 				assert(0);
// 				return;
// 			}
// 		}
// 	}

	pArray->insertObjectAtIndex(pHandler, u);
	/*ccCArrayInsertValueAtIndex(pArray, pHandler, u);*/
	pHandler->retain();
}

void CCTouchDispatcher::addStandardDelegate(CCStandardTouchDelegate *pDelegate, int nPriority)
{
	CCTouchHandler *pHandler = CCStandardTouchHandler::handlerWithDelegate(pDelegate, nPriority);
	if (! m_bLocked)
	{
		forceAddHandler(pHandler, m_pStandardHandlers);
	}
	else
	{
		m_pHandlersToAdd->addObject(pHandler);
		/*ccCArrayAppendValue(m_pHandlersToAdd, pHandler);*/
		/*pHandler->retain();*/
		m_bToAdd = true;
	}
}

void CCTouchDispatcher::addTargetedDelegate(CCTargetedTouchDelegate *pDelegate, int nPriority, bool bSwallowsTouches)
{
	CCTouchHandler *pHandler = CCTargetedTouchHandler::handlerWithDelegate(pDelegate, nPriority, bSwallowsTouches);
	if (! m_bLocked)
	{
		forceAddHandler(pHandler, m_pTargetedHandlers);
	}
	else
	{
		m_pHandlersToAdd->addObject(pHandler);
		/*ccCArrayAppendValue(m_pHandlersToAdd, pHandler);*/
		pHandler->retain();
		m_bToAdd = true;
	}
}

void CCTouchDispatcher::forceRemoveDelegate(CCTouchDelegate *pDelegate)
{
	// XXX: remove it from both handlers ???
//	if (dynamic_cast<CCStandardTouchDelegate*>(pDelegate))
	if (pDelegate->getTouchDelegateType() & ccTouchDelegateStandardBit)
	{
		// remove handler from m_pStandardHandlers
 		CCTouchHandler *pHandler;
 		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator  iter;
 		for (iter = m_pStandardHandlers->begin(); iter != m_pStandardHandlers->end(); ++iter)
 		{
 			pHandler = *iter;
 			if (pHandler && pHandler->getDelegate() == pDelegate)
 			{
 				m_pStandardHandlers->removeObject(pHandler);
 				break;
 			}
 		}
// 		CCTouchHandler *pHandler;
// 		for (unsigned int i = 0; i < m_pStandardHandlers->num; ++i)
// 		{
// 			pHandler = (CCTouchHandler *)m_pStandardHandlers->arr[i];
// 			if (pHandler && pHandler->getDelegate() == pDelegate)
// 			{
// 				ccCArrayRemoveValueAtIndex(m_pStandardHandlers, i);
// 				break;
// 			}
// 		}
	}

//	if (dynamic_cast<CCTargetedTouchDelegate*>(pDelegate))
	if (pDelegate->getTouchDelegateType() & ccTouchDelegateTargetedBit)
	{
		// remove handler from m_pTargetedHandlers
 		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
 		CCTouchHandler *pHandler;
 		for (iter = m_pTargetedHandlers->begin(); iter != m_pTargetedHandlers->end(); ++iter)
 		{
 			pHandler = *iter;
 			if (pHandler && pHandler->getDelegate() == pDelegate)
 			{
 				m_pTargetedHandlers->removeObject(pHandler);
 				break;
 			}
 		}
// 		CCTouchHandler *pHandler;
// 		for (unsigned int i = 0; i < m_pTargetedHandlers->num; ++i)
// 		{
// 			pHandler = (CCTouchHandler *)m_pTargetedHandlers->arr[i];
// 			if (pHandler && pHandler->getDelegate() == pDelegate)
// 			{
// 				ccCArrayRemoveValueAtIndex(m_pTargetedHandlers, i);
// 				break;
// 			}
// 		}
	}
}

void CCTouchDispatcher::removeDelegate(CCTouchDelegate *pDelegate)
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
		/*m_pHandlersToRemove->addObject(pDelegate);*/
		ccCArrayAppendValue(m_pHandlersToRemove, pDelegate);
		m_bToRemove = true;
	}
}

void CCTouchDispatcher::forceRemoveAllDelegates(void)
{
 	m_pStandardHandlers->removeAllObjects();
 	m_pTargetedHandlers->removeAllObjects();
// 	ccCArrayRemoveAllValues(m_pStandardHandlers);
// 	ccCArrayRemoveAllValues(m_pTargetedHandlers);
}

void CCTouchDispatcher::removeAllDelegates(void)
{
	if (! m_bLocked)
	{
		forceRemoveAllDelegates();
	}
	else
	{
		m_bToQuit = true;
	}
}

void CCTouchDispatcher::setPriority(int nPriority, CCTouchDelegate *pDelegate)
{
	assert(0);
}

//
// dispatch events
//
void CCTouchDispatcher::touches(NSSet *pTouches, UIEvent *pEvent, unsigned int uIndex)
{
	assert(uIndex >= 0 && uIndex < 4);

	NSSet *pMutableTouches;
	m_bLocked = true;

	// optimization to prevent a mutable copy when it is not necessary
 	unsigned int uTargetedHandlersCount = m_pTargetedHandlers->count();
 	unsigned int uStandardHandlersCount = m_pStandardHandlers->count();
//     unsigned int uTargetedHandlersCount = m_pTargetedHandlers->num;
//     unsigned int uStandardHandlersCount = m_pStandardHandlers->num;
	bool bNeedsMutableSet = (uTargetedHandlersCount && uStandardHandlersCount);

	pMutableTouches = (bNeedsMutableSet ? pTouches->mutableCopy() : pTouches);

	struct ccTouchHandlerHelperData sHelper = m_sHandlerHelperData[uIndex];
	//
	// process the target handlers 1st
	//
	if (uTargetedHandlersCount > 0)
	{
        CCTouch *pTouch;
		NSSetIterator setIter;
		for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
		{
			pTouch = static_cast<CCTouch *>(*setIter);
			CCTargetedTouchHandler *pHandler;
			NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator arrayIter;
			for (arrayIter = m_pTargetedHandlers->begin(); arrayIter != m_pTargetedHandlers->end(); ++arrayIter)
			/*for (unsigned int i = 0; i < m_pTargetedHandlers->num; ++i)*/
			{
                pHandler = static_cast<CCTargetedTouchHandler *>(*arrayIter);
				/*pHandler = (CCTargetedTouchHandler *)m_pTargetedHandlers->arr[i];*/

                if (pHandler)
                {
				    bool bClaimed = false;
				    if (uIndex == ccTouchBegan)
				    {
					    bClaimed = ((CCTargetedTouchDelegate *)(pHandler->getDelegate()))->ccTouchBegan(pTouch, pEvent);
					    if (bClaimed)
					    {
						    pHandler->getClaimedTouches()->addObject(pTouch);
					    }
				    } else
				    if (pHandler->getClaimedTouches()->containsObject(pTouch))
				    {
					    // moved ended cancelled
					    bClaimed = true;
    					
					    switch (sHelper.m_type)
					    {
					    case ccTouchMoved:
						    ((CCTargetedTouchDelegate*)(pHandler->getDelegate()))->ccTouchMoved(pTouch, pEvent);
						    break;
					    case ccTouchEnded:
						    ((CCTargetedTouchDelegate*)(pHandler->getDelegate()))->ccTouchEnded(pTouch, pEvent);
							pHandler->getClaimedTouches()->removeObject(pTouch);
						    break;
					    case ccTouchCancelled:
						    ((CCTargetedTouchDelegate*)(pHandler->getDelegate()))->ccTouchCancelled(pTouch, pEvent);
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
	}

	//
	// process standard handlers 2nd
	//
	if (uStandardHandlersCount > 0 && pMutableTouches->count() > 0)
	{
		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
		CCStandardTouchHandler *pHandler;
		for (iter = m_pStandardHandlers->begin(); iter != m_pStandardHandlers->end(); ++iter)
		/*for (unsigned int i = 0; i < m_pStandardHandlers->num; ++i)*/
		{
			pHandler = static_cast<CCStandardTouchHandler*>(*iter);
			/*pHandler = (CCStandardTouchHandler*)m_pStandardHandlers->arr[i];*/

            if (pHandler)
            {
			    switch (sHelper.m_type)
			    {
			    case ccTouchBegan:
				    ((CCStandardTouchDelegate*)(pHandler->getDelegate()))->ccTouchesBegan(pMutableTouches, pEvent);
				    break;
			    case ccTouchMoved:
				    ((CCStandardTouchDelegate*)(pHandler->getDelegate()))->ccTouchesMoved(pMutableTouches, pEvent);
				    break;
			    case ccTouchEnded:
				    ((CCStandardTouchDelegate*)(pHandler->getDelegate()))->ccTouchesEnded(pMutableTouches, pEvent);
				    break;
			    case ccTouchCancelled:
				    ((CCStandardTouchDelegate*)(pHandler->getDelegate()))->ccTouchesCancelled(pMutableTouches, pEvent);
				    break;
			    }
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
	m_bLocked = false;
	if (m_bToRemove)
	{
		m_bToRemove = false;
// 		NSMutableArray<CCTouchDelegate*>::NSMutableArrayIterator iter;
// 		for (iter = m_pHandlersToRemove->begin(); iter != m_pHandlersToRemove->end(); ++iter)
// 		{
// 			forceRemoveDelegate(*iter);
// 		}
// 
// 		m_pHandlersToRemove->removeAllObjects();
		for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
		{
			forceRemoveDelegate((CCTouchDelegate*)m_pHandlersToRemove->arr[i]);
		}
		ccCArrayRemoveAllValues(m_pHandlersToRemove);
	}

	if (m_bToAdd)
	{
		m_bToAdd = false;
 		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
         CCTouchHandler *pHandler;
 		for (iter = m_pHandlersToAdd->begin(); iter != m_pHandlersToAdd->end(); ++iter)
 		{
 			pHandler = *iter;
            if (! pHandler)
            {
                break;
            }
 			if (dynamic_cast<CCStandardTouchDelegate*>(pHandler->getDelegate()))
 			{
 				forceAddHandler(pHandler, m_pStandardHandlers);
 			}
 			else
 			{
 				forceAddHandler(pHandler, m_pTargetedHandlers);
 			}
 		}
 
 		m_pHandlersToAdd->removeAllObjects();
//         CCTouchHandler *pHandler;
// 		for (unsigned int i = 0; i < m_pHandlersToAdd->num; ++i)
// 		{
// 			pHandler = (CCTouchHandler *)m_pHandlersToAdd->arr[i];
// 			if (pHandler->getDelegate()->getTouchDelegateType() & ccTouchDelegateStandardBit)
// 			{
//                 forceAddHandler(pHandler, m_pStandardHandlers);
// 			}
// 			else
// 			{
// 				forceAddHandler(pHandler, m_pTargetedHandlers);
// 			}
// 		}
// 		ccCArrayRemoveAllValues(m_pHandlersToAdd);		
	}

	if (m_bToQuit)
	{
		m_bToQuit = false;
		forceRemoveAllDelegates();
	}
}

void CCTouchDispatcher::touchesBegan(NSSet *touches, UIEvent *pEvent)
{
	if (m_bDispatchEvents)
	{
		this->touches(touches, pEvent, ccTouchBegan);
	}
}

void CCTouchDispatcher::touchesMoved(NSSet *touches, UIEvent *pEvent)
{
    if (m_bDispatchEvents)
	{
		this->touches(touches, pEvent, ccTouchMoved);
	}
}

void CCTouchDispatcher::touchesEnded(NSSet *touches, UIEvent *pEvent)
{
    if (m_bDispatchEvents)
	{
		this->touches(touches, pEvent, ccTouchEnded);
	}
}

void CCTouchDispatcher::touchesCancelled(NSSet *touches, UIEvent *pEvent)
{
    if (m_bDispatchEvents)
	{
		this->touches(touches, pEvent, ccTouchCancelled);
	}
}
}//namespace   cocos2d 
