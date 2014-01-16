/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCActionEaseEx.h"

NS_CC_EXT_BEGIN

static inline float bezieratFunction( float a, float b, float c, float d, float t )
{
	return (powf(1-t,3) * a + 
		3*t*(powf(1-t,2))*b + 
		3*powf(t,2)*(1-t)*c +
		powf(t,3)*d );
}

//
// EaseBezier
//

CCEaseBezierAction* CCEaseBezierAction::create(CCActionInterval* pAction)
{
	CCEaseBezierAction *pRet = new CCEaseBezierAction();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

void CCEaseBezierAction::setBezierParamer( float p0, float p1, float p2, float p3)
{
	m_p0 = p0;
	m_p1 = p1;
	m_p2 = p2;
	m_p3 = p3;
}

CCObject* CCEaseBezierAction::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseBezierAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseBezierAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseBezierAction();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseBezierAction::update(float time)
{
	m_pInner->update(bezieratFunction(m_p0,m_p1,m_p2,m_p3,time));
}

CCActionInterval* CCEaseBezierAction::reverse(void)
{
	CCEaseBezierAction* reverseAction = CCEaseBezierAction::create(m_pInner->reverse());
	reverseAction->setBezierParamer(m_p3,m_p2,m_p1,m_p0);
	return reverseAction;
}

//
// CCEaseQuadraticActionIn
//

CCEaseQuadraticActionIn* CCEaseQuadraticActionIn::create(CCActionInterval* pAction)
{
	CCEaseQuadraticActionIn *pRet = new CCEaseQuadraticActionIn();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuadraticActionIn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuadraticActionIn* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuadraticActionIn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuadraticActionIn();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuadraticActionIn::update(float time)
{
	m_pInner->update(powf(time,2));
}

CCActionInterval* CCEaseQuadraticActionIn::reverse(void)
{
	return CCEaseQuadraticActionIn::create(m_pInner->reverse());
}

//
// CCEaseQuadraticActionOut
//

CCEaseQuadraticActionOut* CCEaseQuadraticActionOut::create(CCActionInterval* pAction)
{
	CCEaseQuadraticActionOut *pRet = new CCEaseQuadraticActionOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuadraticActionOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuadraticActionOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuadraticActionOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuadraticActionOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuadraticActionOut::update(float time)
{	
	m_pInner->update(-time*(time-2));
}

CCActionInterval* CCEaseQuadraticActionOut::reverse(void)
{
	return CCEaseQuadraticActionOut::create(m_pInner->reverse());
}

//
// CCEaseQuadraticActionInOut
//

CCEaseQuadraticActionInOut* CCEaseQuadraticActionInOut::create(CCActionInterval* pAction)
{
	CCEaseQuadraticActionInOut *pRet = new CCEaseQuadraticActionInOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuadraticActionInOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuadraticActionInOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuadraticActionInOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuadraticActionInOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuadraticActionInOut::update(float time)
{
	float resultTime = time;
	time = time*2;
	if (time < 1)
	{
		resultTime = time * time * 0.5f;
	}
	else
	{
		--time;
		resultTime = -0.5f * (time * (time - 2) - 1);
	}

	m_pInner->update(resultTime);
}

CCActionInterval* CCEaseQuadraticActionInOut::reverse(void)
{
	return CCEaseQuadraticActionInOut::create(m_pInner->reverse());
}

//
// CCEaseQuarticActionIn
//

CCEaseQuarticActionIn* CCEaseQuarticActionIn::create(CCActionInterval* pAction)
{
	CCEaseQuarticActionIn *pRet = new CCEaseQuarticActionIn();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuarticActionIn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuarticActionIn* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuarticActionIn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuarticActionIn();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuarticActionIn::update(float time)
{
	m_pInner->update(powf(time,4.0f));
}

CCActionInterval* CCEaseQuarticActionIn::reverse(void)
{
	return CCEaseQuarticActionIn::create(m_pInner->reverse());
}

//
// CCEaseQuarticActionOut
//

CCEaseQuarticActionOut* CCEaseQuarticActionOut::create(CCActionInterval* pAction)
{
	CCEaseQuarticActionOut *pRet = new CCEaseQuarticActionOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuarticActionOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuarticActionOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuarticActionOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuarticActionOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuarticActionOut::update(float time)
{
	float tempTime = time -1;	
	m_pInner->update(1- powf(tempTime,4.0f));
}

CCActionInterval* CCEaseQuarticActionOut::reverse(void)
{
	return CCEaseQuarticActionOut::create(m_pInner->reverse());
}

//
// CCEaseQuarticActionInOut
//

CCEaseQuarticActionInOut* CCEaseQuarticActionInOut::create(CCActionInterval* pAction)
{
	CCEaseQuarticActionInOut *pRet = new CCEaseQuarticActionInOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuarticActionInOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuarticActionInOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuarticActionInOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuarticActionInOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuarticActionInOut::update(float time)
{
	float tempTime = time * 2;
	if (tempTime < 1)
		tempTime =  powf(tempTime,4.0f) * 0.5f;
	else
	{
		tempTime -= 2;
		tempTime = 1 - powf(tempTime,4.0f)* 0.5f;
	}

	m_pInner->update(tempTime);
}

CCActionInterval* CCEaseQuarticActionInOut::reverse(void)
{
	return CCEaseQuarticActionInOut::create(m_pInner->reverse());
}

//
// CCEaseQuinticActionIn
//

CCEaseQuinticActionIn* CCEaseQuinticActionIn::create(CCActionInterval* pAction)
{
	CCEaseQuinticActionIn *pRet = new CCEaseQuinticActionIn();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuinticActionIn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuinticActionIn* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuinticActionIn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuinticActionIn();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuinticActionIn::update(float time)
{
	m_pInner->update(powf(time,5.0f));
}

CCActionInterval* CCEaseQuinticActionIn::reverse(void)
{
	return CCEaseQuinticActionIn::create(m_pInner->reverse());
}

//
// CCEaseQuinticActionOut
//

CCEaseQuinticActionOut* CCEaseQuinticActionOut::create(CCActionInterval* pAction)
{
	CCEaseQuinticActionOut *pRet = new CCEaseQuinticActionOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuinticActionOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuinticActionOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuinticActionOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuinticActionOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuinticActionOut::update(float time)
{
	float tempTime = time -1;	
	m_pInner->update(1 + powf(tempTime,5.0f));
}

CCActionInterval* CCEaseQuinticActionOut::reverse(void)
{
	return CCEaseQuinticActionOut::create(m_pInner->reverse());
}

//
// CCEaseQuinticActionInOut
//

CCEaseQuinticActionInOut* CCEaseQuinticActionInOut::create(CCActionInterval* pAction)
{
	CCEaseQuinticActionInOut *pRet = new CCEaseQuinticActionInOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseQuinticActionInOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseQuinticActionInOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseQuinticActionInOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseQuinticActionInOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseQuinticActionInOut::update(float time)
{
	float tempTime = time * 2;
	if (tempTime < 1)
		tempTime =  powf(tempTime,5.0f) * 0.5f;
	else
	{
		tempTime -= 2;
		tempTime = 1 + powf(tempTime,5.0f)* 0.5f;
	}

	m_pInner->update(tempTime);
}

CCActionInterval* CCEaseQuinticActionInOut::reverse(void)
{
	return CCEaseQuinticActionInOut::create(m_pInner->reverse());
}

//
// CCEaseCircleActionIn
//

CCEaseCircleActionIn* CCEaseCircleActionIn::create(CCActionInterval* pAction)
{
	CCEaseCircleActionIn *pRet = new CCEaseCircleActionIn();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCircleActionIn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCircleActionIn* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCircleActionIn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCircleActionIn();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCircleActionIn::update(float time)
{
	m_pInner->update(1-sqrt(1-powf(time,2.0f)));
}

CCActionInterval* CCEaseCircleActionIn::reverse(void)
{
	return CCEaseCircleActionIn::create(m_pInner->reverse());
}

//
// CCEaseCircleActionOut
//

CCEaseCircleActionOut* CCEaseCircleActionOut::create(CCActionInterval* pAction)
{
	CCEaseCircleActionOut *pRet = new CCEaseCircleActionOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCircleActionOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCircleActionOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCircleActionOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCircleActionOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCircleActionOut::update(float time)
{
	float tempTime = time - 1;
	m_pInner->update(sqrt(1-powf(tempTime,2.0f)));
}

CCActionInterval* CCEaseCircleActionOut::reverse(void)
{
	return CCEaseCircleActionOut::create(m_pInner->reverse());
}

//
// CCEaseCircleActionInOut
//

CCEaseCircleActionInOut* CCEaseCircleActionInOut::create(CCActionInterval* pAction)
{
	CCEaseCircleActionInOut *pRet = new CCEaseCircleActionInOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCircleActionInOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCircleActionInOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCircleActionInOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCircleActionInOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCircleActionInOut::update(float time)
{
	float tempTime = time * 2;
	if (tempTime < 1)
		tempTime =  (1- sqrt(1 - powf(tempTime,2.0f))) * 0.5f;
	else
	{
		tempTime -= 2;
		tempTime = (1+ sqrt(1 - powf(tempTime,2.0f))) * 0.5f;
	}

	m_pInner->update(time);
}

CCActionInterval* CCEaseCircleActionInOut::reverse(void)
{
	return CCEaseCircleActionInOut::create(m_pInner->reverse());
}

//
// CCEaseCubicActionIn
//

CCEaseCubicActionIn* CCEaseCubicActionIn::create(CCActionInterval* pAction)
{
	CCEaseCubicActionIn *pRet = new CCEaseCubicActionIn();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCubicActionIn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCubicActionIn* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCubicActionIn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCubicActionIn();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCubicActionIn::update(float time)
{
	m_pInner->update(powf(time,3.0f));
}

CCActionInterval* CCEaseCubicActionIn::reverse(void)
{
	return CCEaseCubicActionIn::create(m_pInner->reverse());
}

//
// CCEaseCubicActionOut
//

CCEaseCubicActionOut* CCEaseCubicActionOut::create(CCActionInterval* pAction)
{
	CCEaseCubicActionOut *pRet = new CCEaseCubicActionOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCubicActionOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCubicActionOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCubicActionOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCubicActionOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCubicActionOut::update(float time)
{
    time -= 1;
	m_pInner->update(1+powf(time,3.0f));
}

CCActionInterval* CCEaseCubicActionOut::reverse(void)
{
	return CCEaseCubicActionOut::create(m_pInner->reverse());
}

//
// CCEaseCubicActionInOut
//

CCEaseCubicActionInOut* CCEaseCubicActionInOut::create(CCActionInterval* pAction)
{
	CCEaseCubicActionInOut *pRet = new CCEaseCubicActionInOut();
	if (pRet)
	{
		if (pRet->initWithAction(pAction))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pRet);
		}
	}

	return pRet; 
}

CCObject* CCEaseCubicActionInOut::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCEaseCubicActionInOut* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCEaseCubicActionInOut*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCEaseCubicActionInOut();
		pNewZone = new CCZone(pCopy);
	}

	pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCEaseCubicActionInOut::update(float time)
{
	float tempTime = time * 2;
	if (tempTime < 1)
		tempTime =  powf(tempTime,3.0f) * 0.5f;
	else
	{
		tempTime -= 2;
		tempTime = 1 + powf(tempTime,3.0f)* 0.5f;
	}
	m_pInner->update(time);
}

CCActionInterval* CCEaseCubicActionInOut::reverse(void)
{
	return CCEaseCubicActionInOut::create(m_pInner->reverse());
}
NS_CC_EXT_END