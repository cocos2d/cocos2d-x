#include "CCBKeyframe.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCBKeyframe::CCBKeyframe()
: mValue(NULL)
, mTime(0.0f)
, mEasingType(0)
, mEasingOpt(0.0f)
{}

CCBKeyframe::~CCBKeyframe()
{
    CC_SAFE_RELEASE_NULL(mValue);
}

CCObject* CCBKeyframe::getValue()
{
    return mValue;
}

void CCBKeyframe::setValue(CCObject *pValue)
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

int CCBKeyframe::getEasingType()
{
    return mEasingType;
}

void CCBKeyframe::setEasingType(int nEasingType)
{
    mEasingType = nEasingType;
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
