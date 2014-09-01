/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "3d/CCSequence3D.h"

NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
Sequence3D* Sequence3D::variadicCreate(Animate3D *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Sequence3D *ret = Sequence3D::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#else
Sequence3D* Sequence3D::create(Animate3D *action1, ...)
{
    va_list params;
    va_start(params, action1);

    Sequence3D *ret = Sequence3D::createWithVariableList(action1, params);

    va_end(params);
    
    return ret;
}
#endif

Sequence3D* Sequence3D::createWithVariableList(Animate3D *action1, va_list args)
{
    Animate3D *now;

    Vector<Animate3D*> actions;
    while (action1)
    {
        now = va_arg(args, Animate3D*);
        if (now)
        {
            actions.pushBack(now);
        }
        else
            break;
    }
    
    return create(actions);
}

Sequence3D* Sequence3D::create(const Vector<Animate3D*>& arrayOfActions)
{
    Sequence3D* ret = nullptr;
    
    ret = new (std::nothrow) Sequence3D();
    if (ret->initWithActions(arrayOfActions))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_RELEASE(ret);
    return ret;
}

bool Sequence3D::initWithActions(const Vector<Animate3D*>& arrayOfActions)
{
    if (arrayOfActions.size() == 0)
        return false;
    
    _actions.clear();
    _startTime.clear();
    _endTime.clear();
    
    Animate3D* preAction = nullptr;
    float duration = 0.f, dur = 0.f;
    _startTime.push_back(duration);
    for (auto& it : arrayOfActions) {
        float d1 = 0.f;
        if (preAction)
            d1 = preAction->getDuration();
        
        float d2 = it->getDuration();
        if (d1 < Animate3D::getTransitionTime() || d2 < Animate3D::getTransitionTime())
            dur = d1 > d2 ? d1 : d2;
        else
            dur = d1 + d2 - Animate3D::getTransitionTime();
        
        preAction = it;
        _actions.pushBack(it);
        _startTime.push_back(dur);
        _endTime.push_back(dur);
        duration += dur;
    }
    _startTime.erase(_startTime.end() - 1);
    for (ssize_t i = 0; i < _startTime.size(); i++) {
        _startTime[i] /= duration;
        _endTime[i] /= duration;
    }
    setDuration(duration);
    _curActionIdx = -1;
    return true;
}

Sequence3D* Sequence3D::clone() const
{
	// no copy constructor
	auto seq3d = new (std::nothrow) Sequence3D();
    seq3d->initWithActions(_actions);
	seq3d->autorelease();
	return seq3d;
}

Sequence3D::Sequence3D()
: _curActionIdx(-1)
{
    
}

Sequence3D::~Sequence3D(void)
{
    _actions.clear();
}

void Sequence3D::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _curActionIdx = -1;
}

void Sequence3D::stop(void)
{
    for (auto& action : _actions) {
        action->stop();
    }

    ActionInterval::stop();
}

Sequence3D* Sequence3D::reverse() const
{
    Vector<Animate3D*> actions;
    for (auto it = _actions.rbegin(); it != _actions.rend(); ++it) {
        actions.pushBack(*it);
    }
    
    return create(actions);
}

void Sequence3D::update(float t)
{
    if (_target)
    {
        int nextIdx = _curActionIdx + 1;
        if (nextIdx < _actions.size())
        {
            if (t >= _startTime[nextIdx])
            {
                _actions.at(nextIdx)->startWithTarget(_target);
                _curActionIdx = nextIdx;
            }
        }
        //update action
        int preActionIdx = _curActionIdx - 1;
        if (preActionIdx >= 0 && _endTime[preActionIdx] > t)
        {
            float newt = (t - _startTime[preActionIdx]) / (_endTime[preActionIdx] - _startTime[preActionIdx]);
            _actions.at(preActionIdx)->update(newt);
        }
        if (_curActionIdx >= 0 && _curActionIdx < _actions.size())
        {
            float newt = (t - _startTime[_curActionIdx]) / (_endTime[_curActionIdx] - _startTime[_curActionIdx]);
            _actions.at(_curActionIdx)->update(newt);
        }
    }
}

NS_CC_END
