/****************************************************************************
Copyright (c) 2009      lhunath (Maarten Billemont)
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "CCActionTween.h"

NS_CC_BEGIN

ActionTween* ActionTween::create(float aDuration, const std::string& key, float from, float to)
{
    ActionTween* ret = new ActionTween();
    if (ret && ret->initWithDuration(aDuration, key, from, to))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ActionTween::initWithDuration(float duration, const std::string& key, float from, float to)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _key    = key;
        _to       = to;
        _from     = from;
        return true;
    }

    return false;
}

ActionTween *ActionTween::clone() const
{
	// no copy constructor	
	auto a = new ActionTween();
	a->initWithDuration(_duration, _key.c_str(), _from, _to);
	a->autorelease();
	return a;
}

void ActionTween::startWithTarget(Node *target)
{
    CCASSERT(dynamic_cast<ActionTweenDelegate*>(target), "target must implement ActionTweenDelegate");
    ActionInterval::startWithTarget(target);
    _delta = _to - _from;
}

void ActionTween::update(float dt)
{
    dynamic_cast<ActionTweenDelegate*>(_target)->updateTweenAction(_to  - _delta * (1 - dt), _key.c_str());
}

ActionTween* ActionTween::reverse() const
{
    return ActionTween::create(_duration, _key.c_str(), _to, _from);
}


NS_CC_END
