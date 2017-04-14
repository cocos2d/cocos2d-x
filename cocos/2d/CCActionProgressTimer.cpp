/****************************************************************************
Copyright (C) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.
 
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
#include "2d/CCActionProgressTimer.h"
#include "2d/CCProgressTimer.h"

NS_CC_BEGIN

#define kProgressTimerCast ProgressTimer*

// implementation of ProgressTo

ProgressTo* ProgressTo::create(float duration, float percent)
{
    ProgressTo *progressTo = new (std::nothrow) ProgressTo();
    if (progressTo && progressTo->initWithDuration(duration, percent))
    {
        progressTo->autorelease();
        return progressTo;
    }
    
    delete progressTo;
    return nullptr;
}

bool ProgressTo::initWithDuration(float duration, float percent)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = percent;

        return true;
    }

    return false;
}

ProgressTo* ProgressTo::clone() const
{
    // no copy constructor
    return ProgressTo::create(_duration, _to);
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
}

void ProgressTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

// implementation of ProgressFromTo

ProgressFromTo* ProgressFromTo::create(float duration, float fromPercentage, float toPercentage)
{
    ProgressFromTo *progressFromTo = new (std::nothrow) ProgressFromTo();
    if (progressFromTo && progressFromTo->initWithDuration(duration, fromPercentage, toPercentage)) {
        progressFromTo->autorelease();
        return progressFromTo;
    }
    
    delete progressFromTo;
    return nullptr;
}

bool ProgressFromTo::initWithDuration(float duration, float fromPercentage, float toPercentage)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = toPercentage;
        _from = fromPercentage;

        return true;
    }

    return false;
}

ProgressFromTo* ProgressFromTo::clone() const
{
    // no copy constructor
    return ProgressFromTo::create(_duration, _from, _to);
}


ProgressFromTo* ProgressFromTo::reverse() const
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
