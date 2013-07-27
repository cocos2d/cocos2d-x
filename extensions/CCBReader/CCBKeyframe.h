#ifndef __CCB_KEYFRAME_H__
#define __CCB_KEYFRAME_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class CCBKeyframe : public Object
{
public:
    enum class EasingType
    {
        INSTANT,
        
        LINEAR,
        
        CUBIC_IN,
        CUBIC_OUT,
        CUBIC_INOUT,
        
        ELASTIC_IN,
        ELASTIC_OUT,
        ELASTIC_INOUT,
        
        BOUNCE_IN,
        BOUNCE_OUT,
        BOUNCE_INOUT,
        
        BACK_IN,
        BACK_OUT,
        BACK_INOUT,
    };
    
    CCBKeyframe();
    ~CCBKeyframe();
    
    Object* getValue();
    void setValue(Object *pValue); // retain
    
    float getTime();
    void setTime(float fTime);
    
    EasingType getEasingType();
    void setEasingType(EasingType easingType);
    
    float getEasingOpt();
    void setEasingOpt(float fEasingOpt);
    
private:
    Object *_value;
    float _time;
    EasingType _easingType;
    float _easingOpt;
};

NS_CC_EXT_END

#endif // __CCB_KEYFRAME_H__
