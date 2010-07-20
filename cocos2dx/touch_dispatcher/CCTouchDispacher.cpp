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
#include "cocoa/NSMutableArray.h"
#include "cocoa/NSSet.h"
#include "platform/CCTouch.h"
#include "CCTexture2D.h"

#include <assert.h>

bool CCTouchDispatcher::isDispatchEvents(void)
{
	return m_bDispatchEvents;
}

void CCTouchDispatcher::setDispatchEvents(bool bDispatchEvents)
{
	m_bDispatchEvents = bDispatchEvents;
}

static CCTouchDispatcher *pSharedDispatcher = NULL;

CCTouchDispatcher* CCTouchDispatcher::getSharedDispather(void)
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

	m_pHandlersToAdd = new NSMutableArray<CCTouchHandler*>(8);
	m_pHandlersToRemove = new NSMutableArray<CCTouchDelegate*>(8);

	m_bToRemove = false;
	m_bToAdd = false;
	m_bToQuit = false;
	m_bLocked = false;

	m_sHandlerHelperData[ccTouchBegan].m_type = ccTouchSelectorBeganBit;
	m_sHandlerHelperData[ccTouchMoved].m_type = ccTouchSelectorMovedBit;
	m_sHandlerHelperData[ccTouchEnded].m_type = ccTouchSelectorEndedBit;
	m_sHandlerHelperData[ccTouchCancelled].m_type = ccTouchSelectorCancelledBit;

	return this;
}

CCTouchDispatcher::~CCTouchDispatcher(void)
{
	m_pTargetedHandlers->release();
	m_pStandardHandlers->release();
	m_pHandlersToAdd->release();
	m_pHandlersToRemove->release();
}

//
// handlers management
//
void CCTouchDispatcher::forceAddHandler(CCTouchHandler *pHandler, NSMutableArray<CCTouchHandler*> *pArray)
{
	UINT32 u = 0;

	NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
	for (iter = pArray->begin(); iter != pArray->end(); ++iter)
	{
		CCTouchHandler *h = *iter;
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

	pArray->insertObjectAtIndex(pHandler, u);
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
		m_bToAdd = true;
	}
}

void CCTouchDispatcher::forceRemoveDelegate(CCTouchDelegate *pDelegate)
{
	// XXX: remove it from both handlers ???
	if (pDelegate->m_eType == kStandardTouchDelegate)
	{
		// remove handler from m_pStandardHandlers
		CCTouchHandler *pHandler;
		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator  iter;
		for (iter = m_pStandardHandlers->begin(); iter != m_pStandardHandlers->end(); ++iter)
		{
			pHandler = *iter;
			if (pHandler->getDelegate() == pDelegate)
			{
				m_pStandardHandlers->removeObject(pHandler);
				break;
			}
		}
	}
	else
	{
		// remove handler from m_pTargetedHandlers
		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
		CCTouchHandler *pHandler;
		for (iter = m_pTargetedHandlers->begin(); iter != m_pTargetedHandlers->end(); ++iter)
		{
			pHandler = *iter;
			if (pHandler->getDelegate() == pDelegate)
			{
				m_pTargetedHandlers->removeObject(pHandler);
				break;
			}
		}
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
		m_pHandlersToRemove->addObject(pDelegate);
		m_bToRemove = true;
	}
}

void CCTouchDispatcher::forceRemoveAllDelegates(void)
{
	m_pStandardHandlers->removeAllObjects();
	m_pTargetedHandlers->removeAllObjects();
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
void CCTouchDispatcher::touches(NSSet *pTouches, UIEvent *pEvent, UInt32 uIndex)
{
	assert(uIndex > 0 && uIndex < 4);

	NSSet *pMutableTouches;
	m_bLocked = true;

	// optimization to prevent a mutable copy when it is not necessary
	UINT32 uTargetedHandlersCount = m_pTargetedHandlers->count();
	UINT32 uStandardHandlersCount = m_pStandardHandlers->count();
	bool bNeedsMutableSet = (uTargetedHandlersCount && uStandardHandlersCount);

	pMutableTouches = (bNeedsMutableSet ? pTouches->mutableCopy() : pTouches);

	struct ccTouchHandlerHelperData sHelper = m_sHandlerHelperData[uIndex];
	//
	// process the target handlers 1st
	//
	if (uTargetedHandlersCount > 0)
	{
        UITouch *pTouch;
		NSSetIterator setIter;
		for (setIter = pTouches->begin(); setIter != pTouches->end(); ++setIter)
		{
			pTouch = static_cast<UITouch *>(*setIter);
			CCTargetedTouchHandler *pHandler;
			NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator arrayIter;
			for (arrayIter = m_pTargetedHandlers->begin(); arrayIter != m_pTargetedHandlers->end(); ++arrayIter)
			{
                pHandler = static_cast<CCTargetedTouchHandler *>(*arrayIter);

				bool bClaimed = false;
				if (uIndex == ccTouchBegan)
				{
					bClaimed = static_cast<CCTargetedTouchDelegate*>(pHandler->getDelegate())->ccTouchBegan(pTouch, pEvent);
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
						static_cast<CCTargetedTouchDelegate*>(pHandler->getDelegate())->ccTouchMoved(pTouch, pEvent);
						break;
					case ccTouchEnded:
						static_cast<CCTargetedTouchDelegate*>(pHandler->getDelegate())->ccTouchEnded(pTouch, pEvent);
						break;
					case ccTouchCancelled:
						static_cast<CCTargetedTouchDelegate*>(pHandler->getDelegate())->ccTouchCancelled(pTouch, pEvent);
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
		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
		CCStandardTouchHandler *pHandler;
		for (iter = m_pStandardHandlers->begin(); iter != m_pStandardHandlers->end(); ++iter)
		{
			pHandler = static_cast<CCStandardTouchHandler*>(*iter);

			switch (sHelper.m_type)
			{
			case ccTouchBegan:
				(static_cast<CCStandardTouchDelegate*>(pHandler->getDelegate()))->ccTouchesBegan(pMutableTouches, pEvent);
				break;
			case ccTouchMoved:
				(static_cast<CCStandardTouchDelegate*>(pHandler->getDelegate()))->ccTouchesMoved(pMutableTouches, pEvent);
				break;
			case ccTouchEnded:
				(static_cast<CCStandardTouchDelegate*>(pHandler->getDelegate()))->ccTouchesEnded(pMutableTouches, pEvent);
				break;
			case ccTouchCancelled:
				(static_cast<CCStandardTouchDelegate*>(pHandler->getDelegate()))->ccTouchesCancelled(pMutableTouches, pEvent);
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
	m_bLocked = false;
	if (m_bToRemove)
	{
		m_bToRemove = false;
		NSMutableArray<CCTouchDelegate*>::NSMutableArrayIterator iter;
		for (iter = m_pHandlersToRemove->begin(); iter != m_pHandlersToRemove->end(); ++iter)
		{
			forceRemoveDelegate(*iter);
		}

		m_pHandlersToRemove->removeAllObjects();
	}

	if (m_bToAdd)
	{
		m_bToAdd = false;
		NSMutableArray<CCTouchHandler*>::NSMutableArrayIterator iter;
        CCTouchHandler *pHandler;
		for (iter = m_pHandlersToAdd->begin(); iter != m_pHandlersToAdd->end(); ++iter)
		{
			pHandler = *iter;
			if (pHandler->getDelegate()->m_eType == kStandardTouchDelegate)
			{
				forceAddHandler(pHandler, m_pStandardHandlers);
			}
			else
			{
				forceAddHandler(pHandler, m_pTargetedHandlers);
			}
		}

		m_pHandlersToAdd->removeAllObjects();
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
