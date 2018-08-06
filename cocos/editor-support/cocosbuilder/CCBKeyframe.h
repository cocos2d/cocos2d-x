/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
