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

class ExtraAnimate3D : public FiniteTimeAction
{
public:
    static ExtraAnimate3D* create();
    virtual ExtraAnimate3D* clone() const;
    virtual ExtraAnimate3D* reverse(void) const;
    virtual void update(float time);
    virtual void step(float dt);
};

ExtraAnimate3D* ExtraAnimate3D::create()
{
    ExtraAnimate3D* ret = new ExtraAnimate3D();
    if (ret)
    {
        ret->autorelease();
    }
    return ret;
}
ExtraAnimate3D* ExtraAnimate3D::clone() const
{
	// no copy constructor
	auto a = new ExtraAnimate3D();
	a->autorelease();
	return a;
}

ExtraAnimate3D* ExtraAnimate3D::reverse() const
{
    return ExtraAnimate3D::create();
}

void ExtraAnimate3D::update(float time)
{
    CC_UNUSED_PARAM(time);
}

void ExtraAnimate3D::step(float dt)
{
    CC_UNUSED_PARAM(dt);
}

Sequence3D* Sequence3D::createWithTwoActions(Animate3D *actionOne, Animate3D *actionTwo)
{
    Sequence3D *sequence3d = new Sequence3D();
    sequence3d->initWithTwoActions(actionOne, actionTwo);
    sequence3d->autorelease();

    return sequence3d;
}

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
    Animate3D *prev = action1;
    bool bOneAction = true;

    while (action1)
    {
        now = va_arg(args, Animate3D*);
        if (now)
        {
            prev = (Animate3D*)createWithTwoActions(prev, now);
            bOneAction = false;
        }
        else
        {
            if (bOneAction)
            {
                prev = (Animate3D*)createWithTwoActions(prev, (Animate3D*)ExtraAnimate3D::create());
            }
            break;
        }
    }
    
    return ((Sequence3D*)prev);
}

Sequence3D* Sequence3D::create(const Vector<Animate3D*>& arrayOfActions)
{
    Sequence3D* ret = nullptr;
    do 
    {
        auto count = arrayOfActions.size();
        CC_BREAK_IF(count == 0);

        auto prev = arrayOfActions.at(0);

        if (count > 1)
        {
            for (int i = 1; i < count; ++i)
            {
                prev = (Animate3D*)createWithTwoActions(prev, arrayOfActions.at(i));
            }
        }
        else
        {
            prev = (Animate3D*)createWithTwoActions(prev,  (Animate3D*)ExtraAnimate3D::create());
        }
        ret = (Sequence3D*)prev;
    }while (0);
    return ret;
}

bool Sequence3D::initWithTwoActions(Animate3D *actionOne, Animate3D *actionTwo)
{
    CCASSERT(actionOne != nullptr, "");
    CCASSERT(actionTwo != nullptr, "");

    float d = actionOne->getDuration() + actionTwo->getDuration();
    ActionInterval::initWithDuration(d);

    _actions[0] = actionOne;
    actionOne->retain();

    _actions[1] = actionTwo;
    actionTwo->retain();

    return true;
}

Sequence3D* Sequence3D::clone() const
{
	// no copy constructor
	auto seq3d = new Sequence3D();
    seq3d->initWithTwoActions(_actions[0]->clone(), _actions[1]->clone() );
	seq3d->autorelease();
	return seq3d;
}

Sequence3D::Sequence3D()
: _blendTime(0.1f)
,_blendRemain(0.1f)
,_cutAnim(false)
,cut_t(0.0f)
{
    
}

Sequence3D::~Sequence3D(void)
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void Sequence3D::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _split = _actions[0]->getDuration() / _duration;
    _last = -1;
}

void Sequence3D::stop(void)
{
    if( _last != - 1)
    {
        _actions[_last]->stop();
    }

    ActionInterval::stop();
}

Sequence3D* Sequence3D::reverse() const
{
    return Sequence3D::createWithTwoActions(_actions[1]->reverse(), _actions[0]->reverse());
}

void Sequence3D::update(float t)
{
    int found = 0;
    float new_t = 0.0f;
    float blend_t = 0.0f;

    if( t < _split ) {
        // action[0]
        found = 0;
        if( _split != 0 )
            new_t = t / _split;
        else
            new_t = 1;

        if( found != _last  && found <= 0 )
            _actions[0]->startWithTarget(_target);

        _actions[0]->update(new_t);

    } 
    if(t >= (_split - _blendTime) && _cutAnim == false) 
    {
        // action[1]
        
        blend_t += 0.01f;
        Blend(blend_t);
        found = 1;
        if ( _split == 1 )
            new_t = 1;
        else
            new_t = (t-(_split - _blendTime)) / (1 - (_split - _blendTime));

        if( found != _last && found >= 1 )
            _actions[1]->startWithTarget(_target);

        _actions[1]->update(new_t);
    }
    if(_cutAnim == true)
    {
        blend_t += 0.01f;
        Blend(blend_t);
        found = 1;
        if(found != _last && found >= 1)
        {
            cut_t = t;
        }
        if ( _split == 1 )
            new_t = 1;
        else
            new_t = (t - cut_t) / (1 - cut_t);

        if( found != _last && found >= 1 )
            _actions[1]->startWithTarget(_target);

        _actions[1]->update(new_t);
    }
 //   if ( found==1 ) {

 //       if( _last == -1 ) {
 //           // action[0] was skipped, execute it.
 //           _actions[0]->startWithTarget(_target);
 //           _actions[0]->update(1.0f);
 //           _actions[0]->stop();
 //       }
 //       else if( _last == 0 )
 //       {
 //           // switching to action 1. stop action 0.
 //           _actions[0]->update(1.0f);
 //           _actions[0]->stop();
 //       }
 //   }
	//else if(found==0 && _last==1 )
	//{
	//	// Reverse mode ?
	//	// XXX: Bug. this case doesn't contemplate when _last==-1, found=0 and in "reverse mode"
	//	// since it will require a hack to know if an action is on reverse mode or not.
	//	// "step" should be overriden, and the "reverseMode" value propagated to inner Sequences.
	//	_actions[1]->update(0);
	//	_actions[1]->stop();
	//}
 //   // Last action found and it is done.
 //   if( found == _last && _actions[found]->isDone() )
 //   {
 //       return;
 //   }

 //   // Last action found and it is done
 //   if( found != _last )
 //   {
 //       //_actions[found]->startWithTarget(_target);
 //   }

    //_actions[found]->update(new_t);
    _last = found;
}

void Sequence3D::Blend(float timeElapse)
{
    _blendRemain -= timeElapse;
    bool bBlending = _blendRemain >= 0;
    if (bBlending)
    {
        float fSrcWeight = _blendRemain / _blendTime;
        _actions[0]->setWeight(fSrcWeight);
        _actions[1]->setWeight(1 - fSrcWeight);
    }
}

void Sequence3D::addAnimate3D(Animate3D* animate)
{
    if(this->_duration > 0)
    {
        if(_actions[1]->getDuration() <= 0)
        {
            _actions[1] = animate;
            _cutAnim = true;
            _duration += _actions[1]->getDuration();
            _split = _actions[0]->getDuration() / _duration;
        }
    }
    else
        return;
}

NS_CC_END
