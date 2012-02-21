/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

#include "CCTouchHandler.h"
#include "ccMacros.h"

namespace   cocos2d {

CCTouchDelegate* CCTouchHandler::getDelegate(void)
{
	return m_pDelegate;
}

void CCTouchHandler::setDelegate(CCTouchDelegate *pDelegate)
{
	if (pDelegate)
	{
		dynamic_cast<CCObject*>(pDelegate)->retain();
    }

	dynamic_cast<CCObject*>(pDelegate)->retain();

    if (m_pDelegate)
    {
		dynamic_cast<CCObject*>(m_pDelegate)->release();
    }

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

	if (pHandler)
	{
		if (pHandler->initWithDelegate(pDelegate, nPriority))
		{
			pHandler->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pHandler);
		}
	}
	
	return pHandler;
}

bool CCTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	CCAssert(pDelegate != NULL, "touch delegate should not be null");

	m_pDelegate = pDelegate; 

	dynamic_cast<CCObject*>(pDelegate)->retain();

	m_nPriority = nPriority;
	m_nEnabledSelectors = 0;

	return true;
}

CCTouchHandler::~CCTouchHandler(void)
{
	if (m_pDelegate)
	{
		dynamic_cast<CCObject*>(m_pDelegate)->release();
	}   
}

// implementation of CCStandardTouchHandler
bool CCStandardTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
	{
		return true;
	}

	return false;
}

CCStandardTouchHandler* CCStandardTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority)
{
	CCStandardTouchHandler* pHandler = new CCStandardTouchHandler();

	if (pHandler)
	{
		if (pHandler->initWithDelegate(pDelegate, nPriority))
		{
			pHandler->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pHandler);
		}
	}

	return pHandler;
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

CCSet* CCTargetedTouchHandler::getClaimedTouches(void)
{
	return m_pClaimedTouches;
}

CCTargetedTouchHandler* CCTargetedTouchHandler::handlerWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
	CCTargetedTouchHandler *pHandler = new CCTargetedTouchHandler();
	if (pHandler)
	{
		if (pHandler->initWithDelegate(pDelegate, nPriority, bSwallow))
		{
			pHandler->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pHandler);
		}
	}

	return pHandler;
}

bool CCTargetedTouchHandler::initWithDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallow)
{
	if (CCTouchHandler::initWithDelegate(pDelegate, nPriority))
	{
		m_pClaimedTouches = new CCSet();
		m_bSwallowsTouches = bSwallow;

		return true;
	}

	return false;
}

CCTargetedTouchHandler::~CCTargetedTouchHandler(void)
{
	CC_SAFE_RELEASE(m_pClaimedTouches);
}
}//namespace   cocos2d 
