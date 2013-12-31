#include "Base.h"
#include "C3DAnimation.h"
#include "C3DAnimationChannel.h"

#include "C3DAnimationCurve.h"
#include "C3DBone.h"

namespace cocos2d
{

C3DAnimationChannel::C3DAnimationChannel(C3DAnimation* animation, C3DBone* bone, C3DAnimationCurve* curve, unsigned long duration)
    : _animation(animation), _bone(bone),  _curve(curve), _duration(duration)
{
    _curve->retain();
    _bone->addChannel(this);
    _animation->retain();
}


C3DAnimationChannel::~C3DAnimationChannel()
{
    SAFE_RELEASE(_curve);
    SAFE_RELEASE(_animation);
}

C3DAnimationCurve* C3DAnimationChannel::getCurve() const
{
    return _curve;
}


}
