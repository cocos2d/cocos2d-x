#include "CCBKeyframe.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCBKeyframe::CCBKeyframe()
: _value(NULL)
, _time(0.0f)
, _easingType(EasingType::INSTANT)
, _easingOpt(0.0f)
{}

CCBKeyframe::~CCBKeyframe()
{
    CC_SAFE_RELEASE_NULL(_value);
}

Object* CCBKeyframe::getValue()
{
    return _value;
}

void CCBKeyframe::setValue(Object *pValue)
{
    CC_SAFE_RELEASE(_value);
    _value = pValue;
    CC_SAFE_RETAIN(_value);
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

NS_CC_EXT_END
