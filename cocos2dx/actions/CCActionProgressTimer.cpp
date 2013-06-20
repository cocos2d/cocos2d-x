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

#define kProgressTimerCast ProgressTimer*

// implementation of ProgressTo

ProgressTo* ProgressTo::create(float duration, float fPercent)
{
    ProgressTo *pProgressTo = new ProgressTo();
    pProgressTo->initWithDuration(duration, fPercent);
    pProgressTo->autorelease();

    return pProgressTo;
}

bool ProgressTo::initWithDuration(float duration, float fPercent)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = fPercent;

        return true;
    }

    return false;
}

ProgressTo* ProgressTo::clone() const
{
	// no copy constructor	
	auto a = new ProgressTo();
    a->initWithDuration(_duration, _to);
	a->autorelease();
	return a;
}

ProgressTo* ProgressTo::reverse() const
{
	CCAssert(false, "reverse() not supported in ProgressTo");
	return nullptr;
}

Object* ProgressTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    ProgressTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (ProgressTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new ProgressTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _to);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void ProgressTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _from = ((kProgressTimerCast)(pTarget))->getPercentage();

    // XXX: Is this correct ?
    // Adding it to support Repeat
    if (_from == 100)
    {
        _from = 0;
    }
}

void ProgressTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

// implementation of ProgressFromTo

ProgressFromTo* ProgressFromTo::create(float duration, float fFromPercentage, float fToPercentage)
{
    ProgressFromTo *pProgressFromTo = new ProgressFromTo();
    pProgressFromTo->initWithDuration(duration, fFromPercentage, fToPercentage);
    pProgressFromTo->autorelease();

    return pProgressFromTo;
}

bool ProgressFromTo::initWithDuration(float duration, float fFromPercentage, float fToPercentage)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = fToPercentage;
        _from = fFromPercentage;

        return true;
    }

    return false;
}

ProgressFromTo* ProgressFromTo::clone() const
{
	// no copy constructor	
	auto a = new ProgressFromTo();
	a->initWithDuration(_duration, _from, _to);
	a->autorelease();
	return a;
}

Object* ProgressFromTo::copyWithZone(Zone *pZone)
{
    Zone* pNewZone = NULL;
    ProgressFromTo* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (ProgressFromTo*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new ProgressFromTo();
        pZone = pNewZone = new Zone(pCopy);
    }

    ActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _from, _to);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

ProgressFromTo* ProgressFromTo::reverse(void) const
{
    return ProgressFromTo::create(_duration, _to, _from);
}

void ProgressFromTo::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
}

void ProgressFromTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

NS_CC_END

