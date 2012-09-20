#ifndef __CCB_KEYFRAME_H__
#define __CCB_KEYFRAME_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class CCBKeyframe : public cocos2d::CCObject
{
private:
    cocos2d::CCObject *mValue;
    float mTime;
    int mEasingType;
    float mEasingOpt;
    
public:
    CCBKeyframe();
    ~CCBKeyframe();
    
    cocos2d::CCObject* getValue();
    void setValue(cocos2d::CCObject *pValue); // retain
    
    float getTime();
    void setTime(float fTime);
    
    int getEasingType();
    void setEasingType(int nEasingType);
    
    float getEasingOpt();
    void setEasingOpt(float fEasingOpt);
};

NS_CC_EXT_END

#endif // __CCB_KEYFRAME_H__
