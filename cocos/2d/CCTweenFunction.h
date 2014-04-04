/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCTWEENFUNCTION_H__
#define __CCTWEENFUNCTION_H__

#include "CCPlatformMacros.h"
#include "ccMacros.h"
#include <math.h>

NS_CC_BEGIN

namespace tweenfunc {
    enum TweenType
    {
        CUSTOM_EASING = -1,
        
        Linear,
        
        Sine_EaseIn,
        Sine_EaseOut,
        Sine_EaseInOut,
        
        
        Quad_EaseIn,
        Quad_EaseOut,
        Quad_EaseInOut,
        
        Cubic_EaseIn,
        Cubic_EaseOut,
        Cubic_EaseInOut,
        
        Quart_EaseIn,
        Quart_EaseOut,
        Quart_EaseInOut,
        
        Quint_EaseIn,
        Quint_EaseOut,
        Quint_EaseInOut,
        
        Expo_EaseIn,
        Expo_EaseOut,
        Expo_EaseInOut,
        
        Circ_EaseIn,
        Circ_EaseOut,
        Circ_EaseInOut,
        
        Elastic_EaseIn,
        Elastic_EaseOut,
        Elastic_EaseInOut,
        
        Back_EaseIn,
        Back_EaseOut,
        Back_EaseInOut,
        
        Bounce_EaseIn,
        Bounce_EaseOut,
        Bounce_EaseInOut,
        
        TWEEN_EASING_MAX = 10000
    };
    
    
    //tween functions for CCActionEase
    float easeIn(float time, float rate);
    float easeOut(float time, float rate);
    float easeInOut(float time, float rate);
    
    float bezieratFunction( float a, float b, float c, float d, float t );
    
    float quadraticIn(float time);
    float quadraticOut(float time);
    float quadraticInOut(float time);
    
    
    float tweenTo(float time, TweenType type, float *easingParam);
    
    float linear(float time);
    
    
    float sineEaseIn(float time);
    float sineEaseOut(float time);
    float sineEaseInOut(float time);
    
    float quadEaseIn(float time);
    float quadEaseOut(float time);
    float quadEaseInOut(float time);
    
    float cubicEaseIn(float time);
    float cubicEaseOut(float time);
    float cubicEaseInOut(float time);
    
    float quartEaseIn(float time);
    float quartEaseOut(float time);
    float quartEaseInOut(float time);
    
    float quintEaseIn(float time);
    float quintEaseOut(float time);
    float quintEaseInOut(float time);
    
    float expoEaseIn(float time);
    float expoEaseOut(float time);
    float expoEaseInOut(float time);
    
    float circEaseIn(float time);
    float circEaseOut(float time);
    float circEaseInOut(float time);
    
    float elasticEaseIn(float time, float period);
    float elasticEaseOut(float time, float period);
    float elasticEaseInOut(float time, float period);
    
    float backEaseIn(float time);
    float backEaseOut(float time);
    float backEaseInOut(float time);
    
    float bounceEaseIn(float time);
    float bounceEaseOut(float time);
    float bounceEaseInOut(float time);
    
    float customEase(float time, float *easingParam);
}

NS_CC_END

#endif /*__CCTWEENFUNCTION_H__*/
