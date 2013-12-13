/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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


#include "CCArmatureDefine.h"
#include <math.h>

NS_CC_EXT_BEGIN

enum CCTweenType
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
/**
*   @js NA
*   @lua NA
*/
class  CCTweenFunction
{
public:

    static float tweenTo(float time, CCTweenType type, float *easingParam);

    static float linear(float time);

    static float sineEaseIn(float time);
    static float sineEaseOut(float time);
    static float sineEaseInOut(float time);

    static float quadEaseIn(float time);
    static float quadEaseOut(float time);
    static float quadEaseInOut(float time);

    static float cubicEaseIn(float time);
    static float cubicEaseOut(float time);
    static float cubicEaseInOut(float time);

    static float quartEaseIn(float time);
    static float quartEaseOut(float time);
    static float quartEaseInOut(float time);

    static float quintEaseIn(float time);
    static float quintEaseOut(float time);
    static float quintEaseInOut(float time);

    static float expoEaseIn(float time);
    static float expoEaseOut(float time);
    static float expoEaseInOut(float time);

    static float circEaseIn(float time);
    static float circEaseOut(float time);
    static float circEaseInOut(float time);

    static float elasticEaseIn(float time, float *easingParam);
    static float elasticEaseOut(float time, float *easingParam);
    static float elasticEaseInOut(float time, float *easingParam);

    static float backEaseIn(float time);
    static float backEaseOut(float time);
    static float backEaseInOut(float time);

    static float bounceEaseIn(float time);
    static float bounceEaseOut(float time);
    static float bounceEaseInOut(float time);

    static float customEase(float time, float *easingParam);
};


NS_CC_EXT_END

#endif /*__CCTWEENFUNCTION_H__*/
