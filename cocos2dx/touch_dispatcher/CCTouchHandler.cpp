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

#include "CCTouchHandler.h"
#include "ccMacros.h"
#include <assert.h>
namespace   cocos2d {

CCTouchDelegate* CCTouchHandler::getDelegate(void)
{
	return m_pDelegate;
}

void CCTouchHandler::setDelegate(CCTouchDelegate *pDelegate)
{
	m_pDelegate = pDelegate;
}

int CCTouchHandler::getPriority(void)
{
	return m_nPriority;
}

void CCTouchHandler::setPriority(int nPriority)
{
	m_nPriority = nPriority;
}

int CCTouchHandler::getEnabledSelectors(void)
{
	return m_nEnabledSelectors;
}

void CCTouchHandler::setEnalbedSelectors(int nValue)
{
	m_nEnabledSelectors = nValue;
}

CCTouchHandler* CCTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	CCTouchHandler *pHandler = new CCTouchHandler();
	pHandler->autorelease();

	return pHandler->initWithDelegate(pDelegate, nPriority);
}

CCTouchHandler* CCTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	assert(pDelegate != NULL);

	m_pDelegate = pDelegate; pDelegate->keep();
	m_nPriority = nPriority;
	m_nEnabledSelectors = 0;

	return this;
}

CCTouchHandler::~CCTouchHandler(void)
{
    m_pDelegate->destroy();
}

// implementation of CCStandardTouchHandler
CCTouchHandler* CCStandardTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
	{
		/*
		 * we can not do this in c++
		if( [del respondsToSelector:@selector(ccTouchesBegan:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorBeganBit;
		if( [del respondsToSelector:@selector(ccTouchesMoved:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorMovedBit;
		if( [del respondsToSelector:@selector(ccTouchesEnded:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorEndedBit;
		if( [del respondsToSelector:@selector(ccTouchesCancelled:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorCancelledBit;
		*/
	}

	return this;
}

CCStandardTouchHandler* CCStandardTouchHandler::handlerWithDelegate(CCStandardTouchDelegate *pDelegate, int nPriority)
{
	CCStandardTouchHandler* pTouchHandler = new CCStandardTouchHandler();

	pTouchHandler->initWithDelegate(pDelegate, nPriority);
	pTouchHandler->autorelease();

	return pTouchHandler;
}

// implementation of CCTargetedTouchHandler

bool CCTargetedTouchHandler::isSwallowsTouches(void)
{
	return m_bSwallowsTouches;
}

void CCTargetedTouchHandler::setSwallowsTouches(bool bSwallowsTouches)
{
	m_bSwallowsTouches = bSwallowsTouches;
}

NSMutableSet* CCTargetedTouchHandler::getClaimedTouches(void)
{
	return m_pClaimedTouches;
}

CCTargetedTouchHandler* CCTargetedTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
	CCTargetedTouchHandler *pTargetedHandler = new CCTargetedTouchHandler();
	pTargetedHandler->initWithDelegate(pDelegate, nPriority, bSwallow);
	pTargetedHandler->autorelease();

	return pTargetedHandler;
}

CCTouchHandler* CCTargetedTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
	if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
	{
		m_pClaimedTouches = new NSMutableSet();
		m_bSwallowsTouches = bSwallow;

		/*
		if( [aDelegate respondsToSelector:@selector(ccTouchBegan:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorBeganBit;
		if( [aDelegate respondsToSelector:@selector(ccTouchMoved:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorMovedBit;
		if( [aDelegate respondsToSelector:@selector(ccTouchEnded:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorEndedBit;
		if( [aDelegate respondsToSelector:@selector(ccTouchCancelled:withEvent:)] )
			enabledSelectors_ |= ccTouchSelectorCancelledBit;
		*/
	}

	return this;
}

CCTargetedTouchHandler::~CCTargetedTouchHandler(void)
{
	m_pClaimedTouches->release();
}
}//namespace   cocos2d 
