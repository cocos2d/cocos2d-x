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
#include "CCProgressTimer.h"

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
	CCASSERT(false, "reverse() not supported in ProgressTo");
	return nullptr;
}

void ProgressTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _from = ((kProgressTimerCast)(target))->getPercentage();

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


ProgressFromTo* ProgressFromTo::reverse(void) const
{
    return ProgressFromTo::create(_duration, _to, _from);
}

void ProgressFromTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
}

void ProgressFromTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

NS_CC_END

