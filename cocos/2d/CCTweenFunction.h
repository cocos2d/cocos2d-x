/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef __CCTWEENFUNCTION_H__
#define __CCTWEENFUNCTION_H__

/// @cond DO_NOT_SHOW

#include "platform/CCPlatformMacros.h"

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
    /**
     * @param time in seconds.
     */
    float CC_DLL easeIn(float time, float rate);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL easeOut(float time, float rate);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL easeInOut(float time, float rate);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL bezieratFunction( float a, float b, float c, float d, float t );
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadraticIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadraticOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadraticInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadraticInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL tweenTo(float time, TweenType type, float *easingParam);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL linear(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL sineEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL sineEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL sineEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quadEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL cubicEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL cubicEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL cubicEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quartEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quartEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quartEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quintEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL quintEaseOut(float time);
    
    /**
     @param time in seconds.
     */
    float CC_DLL quintEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL expoEaseIn(float time);
    
    /**
     @param time in seconds.
     */
    float CC_DLL expoEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL expoEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL circEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL circEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL circEaseInOut(float time);
    
    /**
     * @param time in seconds.
     * @param period in seconds.
     */
    float CC_DLL elasticEaseIn(float time, float period);
    
    /**
     * @param time in seconds.
     * @param period in seconds.
     */
    float CC_DLL elasticEaseOut(float time, float period);
    
    /**
     * @param time in seconds.
     * @param period in seconds.
     */
    float CC_DLL elasticEaseInOut(float time, float period);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL backEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL backEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL backEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL bounceEaseIn(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL bounceEaseOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL bounceEaseInOut(float time);
    
    /**
     * @param time in seconds.
     */
    float CC_DLL customEase(float time, float *easingParam);
}

NS_CC_END

/// @endcond
#endif /*__CCTWEENFUNCTION_H__*/
