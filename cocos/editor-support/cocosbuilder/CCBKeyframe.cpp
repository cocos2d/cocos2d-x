#include "CCBKeyframe.h"

using namespace cocos2d;

namespace cocosbuilder {

CCBKeyframe::CCBKeyframe()
: _object(nullptr)
, _time(0.0f)
, _easingType(EasingType::INSTANT)
, _easingOpt(0.0f)
{}

CCBKeyframe::~CCBKeyframe()
{
    CC_SAFE_RELEASE(_object);
}

const Value& CCBKeyframe::getValue() const
{
    return _value;
}

void CCBKeyframe::setValue(const Value& value)
{
    _value = value;
}
    
Ref* CCBKeyframe::getObject() const
{
    return _object;
}

void CCBKeyframe::setObject(Ref* obj)
{
    CC_SAFE_RETAIN(obj);
    CC_SAFE_RELEASE(_object);
    _object = obj;
}

float CCBKeyframe::getTime()
{
    return _time;
}

void CCBKeyframe::setTime(float fTime)
{
    _time = fTime;
}

CCBKeyframe::EasingType CCBKeyframe::getEasingType()
{
    return _easingType;
}

void CCBKeyframe::setEasingType(CCBKeyframe::EasingType easingType)
{
    _easingType = easingType;
}

float CCBKeyframe::getEasingOpt()
{
    return _easingOpt;
}

void CCBKeyframe::setEasingOpt(float fEasingOpt)
{
    _easingOpt = fEasingOpt;
}

}
