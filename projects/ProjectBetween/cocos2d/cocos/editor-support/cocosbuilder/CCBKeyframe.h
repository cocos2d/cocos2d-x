#ifndef __CCB_KEYFRAME_H__
#define __CCB_KEYFRAME_H__

#include "base/CCRef.h"
#include "base/CCValue.h"


namespace cocosbuilder {

class CC_DLL CCBKeyframe : public cocos2d::Ref
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
    /**
     * @js ctor
     */
    CCBKeyframe();
    /**
     * @js NA
     * @lua NA
     */
    ~CCBKeyframe();
    
    const cocos2d::Value& getValue() const;
    void setValue(const cocos2d::Value& value);
    
    cocos2d::Ref* getObject() const;
    void setObject(cocos2d::Ref* obj);
    
    float getTime();
    void setTime(float fTime);
    
    EasingType getEasingType();
    void setEasingType(EasingType easingType);
    
    float getEasingOpt();
    void setEasingOpt(float fEasingOpt);
    
private:
    cocos2d::Value _value;
    cocos2d::Ref* _object;
    float _time;
    EasingType _easingType;
    float _easingOpt;
};

}

#endif // __CCB_KEYFRAME_H__
