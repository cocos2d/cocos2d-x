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
    TWEEN_EASING_MIN = -1,

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

    static float tweenTo(float from, float change, float time, float duration, CCTweenType tweenType);

    static float linear(float t, float b, float c, float d);

    static float sineEaseIn(float t, float b, float c, float d);
    static float sineEaseOut(float t, float b, float c, float d);
    static float sineEaseInOut(float t, float b, float c, float d);

    static float quadEaseIn(float t, float b, float c, float d);
    static float quadEaseOut(float t, float b, float c, float d);
    static float quadEaseInOut(float t, float b, float c, float d);

    static float cubicEaseIn(float t, float b, float c, float d);
    static float cubicEaseOut(float t, float b, float c, float d);
    static float cubicEaseInOut(float t, float b, float c, float d);

    static float quartEaseIn(float t, float b, float c, float d);
    static float quartEaseOut(float t, float b, float c, float d);
    static float quartEaseInOut(float t, float b, float c, float d);

    static float quintEaseIn(float t, float b, float c, float d);
    static float quintEaseOut(float t, float b, float c, float d);
    static float quintEaseInOut(float t, float b, float c, float d);

    static float expoEaseIn(float t, float b, float c, float d);
    static float expoEaseOut(float t, float b, float c, float d);
    static float expoEaseInOut(float t, float b, float c, float d);

    static float circEaseIn(float t, float b, float c, float d);
    static float circEaseOut(float t, float b, float c, float d);
    static float circEaseInOut(float t, float b, float c, float d);

    static float elasticEaseIn(float t, float b, float c, float d, float a = 0, float p = 0);
    static float elasticEaseOut(float t, float b, float c, float d, float a = 0, float p = 0);
    static float elasticEaseInOut(float t, float b, float c, float d, float a = 0, float p = 0);

    static float backEaseIn(float t, float b, float c, float d, float s = 0);
    static float backEaseOut(float t, float b, float c, float d, float s = 0);
    static float backEaseInOut(float t, float b, float c, float d, float s = 0);

    static float bounceEaseIn(float t, float b, float c, float d);
    static float bounceEaseOut(float t, float b, float c, float d);
    static float bounceEaseInOut(float t, float b, float c, float d);
};


NS_CC_EXT_END

#endif /*__CCTWEENFUNCTION_H__*/
