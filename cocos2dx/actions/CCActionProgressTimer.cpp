/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2010      Lam Pham
 
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
#include "CCActionProgressTimer.h"
#include "misc_nodes/CCProgressTimer.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN

#define kProgressTimerCast CCProgressTimer*

// implementation of CCProgressTo

CCProgressTo* CCProgressTo::create(float duration, float fPercent)
{
    CCProgressTo *pProgressTo = new CCProgressTo();
    pProgressTo->initWithDuration(duration, fPercent);
    pProgressTo->autorelease();

    return pProgressTo;
}

bool CCProgressTo::initWithDuration(float duration, float fPercent)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _to = fPercent;

        return true;
    }

    return false;
}

CCProgressTo* CCProgressTo::clone() const
{
	// no copy constructor	
	auto a = new CCProgressTo();
    a->initWithDuration(_duration, _to);
	a->autorelease();
	return a;
}

CCProgressTo* CCProgressTo::reverse() const
{
	CCAssert(false, "reverse() not supported in CCProgressTo");
	return nullptr;
}

CCObject* CCProgressTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCProgressTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCProgressTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCProgressTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _to);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCProgressTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _from = ((kProgressTimerCast)(pTarget))->getPercentage();

    // XXX: Is this correct ?
    // Adding it to support CCRepeat
    if (_from == 100)
    {
        _from = 0;
    }
}

void CCProgressTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

// implementation of CCProgressFromTo

CCProgressFromTo* CCProgressFromTo::create(float duration, float fFromPercentage, float fToPercentage)
{
    CCProgressFromTo *pProgressFromTo = new CCProgressFromTo();
    pProgressFromTo->initWithDuration(duration, fFromPercentage, fToPercentage);
    pProgressFromTo->autorelease();

    return pProgressFromTo;
}

bool CCProgressFromTo::initWithDuration(float duration, float fFromPercentage, float fToPercentage)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _to = fToPercentage;
        _from = fFromPercentage;

        return true;
    }

    return false;
}

CCProgressFromTo* CCProgressFromTo::clone() const
{
	// no copy constructor	
	auto a = new CCProgressFromTo();
	a->initWithDuration(_duration, _from, _to);
	a->autorelease();
	return a;
}

CCObject* CCProgressFromTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCProgressFromTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCProgressFromTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCProgressFromTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _from, _to);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCProgressFromTo* CCProgressFromTo::reverse(void) const
{
    return CCProgressFromTo::create(_duration, _to, _from);
}

void CCProgressFromTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
}

void CCProgressFromTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

NS_CC_END

