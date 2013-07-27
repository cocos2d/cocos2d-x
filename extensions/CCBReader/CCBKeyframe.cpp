#include "CCBKeyframe.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCBKeyframe::CCBKeyframe()
: mValue(NULL)
, mTime(0.0f)
, mEasingType(EasingType::INSTANT)
, mEasingOpt(0.0f)
{}

CCBKeyframe::~CCBKeyframe()
{
    CC_SAFE_RELEASE_NULL(mValue);
}

Object* CCBKeyframe::getValue()
{
    return mValue;
}

void CCBKeyframe::setValue(Object *pValue)
{
    CC_SAFE_RELEASE(mValue);
    mValue = pValue;
    CC_SAFE_RETAIN(mValue);
}

float CCBKeyframe::getTime()
{
    return mTime;
}

void CCBKeyframe::setTime(float fTime)
{
    mTime = fTime;
}

CCBKeyframe::EasingType CCBKeyframe::getEasingType()
{
    return mEasingType;
}

void CCBKeyframe::setEasingType(CCBKeyframe::EasingType easingType)
{
    mEasingType = easingType;
}

float CCBKeyframe::getEasingOpt()
{
    return mEasingOpt;
}

void CCBKeyframe::setEasingOpt(float fEasingOpt)
{
    mEasingOpt = fEasingOpt;
}

NS_CC_EXT_END
