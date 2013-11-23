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

#include "CCTweenFunction.h"
#include "CCUtilMath.h"

NS_CC_EXT_BEGIN

float CCTweenFunction::tweenTo(float from, float change, float time, float duration, CCTweenType tweenType)
{
    float delta = 0;

    switch (tweenType)
    {
    case Linear:
        delta = linear(time, 0, 1, duration);
        break;

    case Sine_EaseIn:
        delta = sineEaseIn(time, 0, 1, duration);
        break;
    case Sine_EaseOut:
        delta = sineEaseOut(time, 0, 1, duration);
        break;
    case Sine_EaseInOut:
        delta = sineEaseInOut(time, 0, 1, duration);
        break;

    case Quad_EaseIn:
        delta = quadEaseIn(time, 0, 1, duration);
        break;
    case Quad_EaseOut:
        delta = quadEaseOut(time, 0, 1, duration);
        break;
    case Quad_EaseInOut:
        delta = quadEaseInOut(time, 0, 1, duration);
        break;

    case Cubic_EaseIn:
        delta = cubicEaseIn(time, 0, 1, duration);
        break;
    case Cubic_EaseOut:
        delta = cubicEaseOut(time, 0, 1, duration);
        break;
    case Cubic_EaseInOut:
        delta = cubicEaseInOut(time, 0, 1, duration);
        break;

    case Quart_EaseIn:
        delta = quartEaseIn(time, 0, 1, duration);
        break;
    case Quart_EaseOut:
        delta = quartEaseOut(time, 0, 1, duration);
        break;
    case Quart_EaseInOut:
        delta = quartEaseInOut(time, 0, 1, duration);
        break;

    case Quint_EaseIn:
        delta = quintEaseIn(time, 0, 1, duration);
        break;
    case Quint_EaseOut:
        delta = quintEaseOut(time, 0, 1, duration);
        break;
    case Quint_EaseInOut:
        delta = quintEaseInOut(time, 0, 1, duration);
        break;

    case Expo_EaseIn:
        delta = expoEaseIn(time, 0, 1, duration);
        break;
    case Expo_EaseOut:
        delta = expoEaseOut(time, 0, 1, duration);
        break;
    case Expo_EaseInOut:
        delta = expoEaseInOut(time, 0, 1, duration);
        break;

    case Circ_EaseIn:
        delta = circEaseIn(time, 0, 1, duration);
        break;
    case Circ_EaseOut:
        delta = circEaseOut(time, 0, 1, duration);
        break;
    case Circ_EaseInOut:
        delta = circEaseInOut(time, 0, 1, duration);
        break;

    case Elastic_EaseIn:
        delta = elasticEaseIn(time, 0, 1, duration);
        break;
    case Elastic_EaseOut:
        delta = elasticEaseOut(time, 0, 1, duration);
        break;
    case Elastic_EaseInOut:
        delta = elasticEaseInOut(time, 0, 1, duration);
        break;


    case Back_EaseIn:
        delta = backEaseIn(time, 0, 1, duration);
        break;
    case Back_EaseOut:
        delta = backEaseOut(time, 0, 1, duration);
        break;
    case Back_EaseInOut:
        delta = backEaseInOut(time, 0, 1, duration);
        break;

    case Bounce_EaseIn:
        delta = bounceEaseIn(time, 0, 1, duration);
        break;
    case Bounce_EaseOut:
        delta = bounceEaseOut(time, 0, 1, duration);
        break;
    case Bounce_EaseInOut:
        delta = bounceEaseInOut(time, 0, 1, duration);
        break;

    default:
        delta = sineEaseInOut(time, 0, 1, duration);
        break;
    }

    return delta;
}

float CCTweenFunction::linear(float t, float b, float c, float d)
{
    return c * t / d + b;
}

float CCTweenFunction::quadEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c * t * t + b;
}
float CCTweenFunction::quadEaseOut(float t, float b, float c, float d)
{
    t /= d;
    return -c * t * (t - 2) + b;
}
float CCTweenFunction::quadEaseInOut(float t, float b, float c, float d)
{
    t = t/d*2;
    if ((t) < 1)
        return c / 2 * t * t + b;
    --t;
    return -c / 2 * (t * (t - 2) - 1) + b;
}

float CCTweenFunction::cubicEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c * t * t * t + b;
}
float CCTweenFunction::cubicEaseOut(float t, float b, float c, float d)
{
    t = t / d - 1;
    return c * (t * t * t + 1) + b;
}
float CCTweenFunction::cubicEaseInOut(float t, float b, float c, float d)
{
    t = t/d*2;
    if ((t) < 1)
        return c / 2 * t * t * t + b;
    t -= 2;
    return c / 2 * (t * t * t + 2) + b;
}

float CCTweenFunction::quartEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c * t * t * t * t + b;
}
float CCTweenFunction::quartEaseOut(float t, float b, float c, float d)
{
    t = t / d - 1;
    return -c * (t * t * t * t - 1) + b;
}
float CCTweenFunction::quartEaseInOut(float t, float b, float c, float d)
{
    t = t/d*2;
    if ((t) < 1)
        return c / 2 * t * t * t * t + b;
    t -= 2;
    return -c / 2 * (t * t * t * t - 2) + b;
}

float CCTweenFunction::quintEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c * t * t * t * t * t + b;
}
float CCTweenFunction::quintEaseOut(float t, float b, float c, float d)
{
    t = t / d - 1;
    return c * (t * t * t * t * t + 1) + b;
}
float CCTweenFunction::quintEaseInOut(float t, float b, float c, float d)
{
    t = t/d*2;
    if ((t) < 1)
        return c / 2 * t * t * t * t * t + b;
    t -= 2;
    return c / 2 * (t * t * t * t * t + 2) + b;
}

float CCTweenFunction::sineEaseIn(float t, float b, float c, float d)
{
    return -c * cos(t / d * (M_PI / 2)) + c + b;
}
float CCTweenFunction::sineEaseOut(float t, float b, float c, float d)
{
    return c * sin(t / d * (M_PI / 2)) + b;
}
float CCTweenFunction::sineEaseInOut(float t, float b, float c, float d)
{
    return -c / 2 * (cos(M_PI * t / d) - 1) + b;
}

float CCTweenFunction::expoEaseIn(float t, float b, float c, float d)
{
    return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}
float CCTweenFunction::expoEaseOut(float t, float b, float c, float d)
{
    return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}
float CCTweenFunction::expoEaseInOut(float t, float b, float c, float d)
{
    if (t == 0)
        return b;
    if (t == d)
        return b + c;
    if ((t /= d/2) < 1)
        return c / 2 * pow(2, 10 * (t - 1)) + b;
    --t;
    return c / 2 * (-pow(2, -10 * t) + 2) + b;
}

float CCTweenFunction::circEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return -c * (sqrt(1 - t * t) - 1) + b;
}
float CCTweenFunction::circEaseOut(float t, float b, float c, float d)
{
    t = t / d - 1;
    return c * sqrt(1 - t * t) + b;
}
float CCTweenFunction::circEaseInOut(float t, float b, float c, float d)
{
    t = t / d * 2;
    if (t < 1)
        return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    t -= 2;
    return c / 2 * (sqrt(1 - t * t) + 1) + b;
}

float CCTweenFunction::elasticEaseIn(float t, float b, float c, float d, float a, float p)
{
    float s = 0;
    if (t == 0)
        return b;
    t /= d;
    if (t == 1)
        return b + c;
    if (!p)
        p = d * .3;
    if (!a || a < abs(c))
    {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * M_PI) * asin(c / a);
    t -= 1;
    return -(a * pow(2, 10 * t) * sin((t * d - s) * (2 * M_PI) / p)) + b;
}
float CCTweenFunction::elasticEaseOut(float t, float b, float c, float d, float a, float p)
{
    float s = 0;
    if (t == 0)
        return b;
    t /= d;
    if (t == 1)
        return b + c;
    if (!p)
        p = d * .3;
    if (!a || a < abs(c))
    {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * M_PI) * asin(c / a);
    return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * M_PI) / p) + c + b);
}
float CCTweenFunction::elasticEaseInOut(float t, float b, float c, float d, float a, float p)
{
    float s = 0;
    if (t == 0)
        return b;
    t = t / d * 2;
    if ((t) == 2)
        return b + c;
    if (!p)
        p = d * (.3 * 1.5);
    if (!a || a < abs(c))
    {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * M_PI) * asin(c / a);
    if (t < 1)
    {
        t -= 1;
        return -.5 * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * M_PI) / p)) + b;
    }
    t -= 1;
    return a * pow(2, -10 * t) * sin((t * d - s) * (2 * M_PI) / p) * .5 + c + b;
}

float CCTweenFunction::backEaseIn(float t, float b, float c, float d, float s)
{
    if (s == 0)
        s = 1.70158f;
    t /= d;
    return c * t * t * ((s + 1) * t - s) + b;
}
float CCTweenFunction::backEaseOut(float t, float b, float c, float d, float s)
{
    if (s == 0)
        s = 1.70158f;
    t = t / d - 1;
    return c * (t * t * ((s + 1) * t + s) + 1) + b;
}
float CCTweenFunction::backEaseInOut(float t, float b, float c, float d, float s)
{
    if (s == 0)
        s = 1.70158f;
    if ((t /= d / 2) < 1)
    {
        s *= (1.525f);
        return c / 2 * (t * t * ((s + 1) * t - s)) + b;
    }

    t -= 2;
    s *= (1.525f);
    return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
}

float CCTweenFunction::bounceEaseIn(float t, float b, float c, float d)
{
    return c - bounceEaseOut(d - t, 0, c, d) + b;
}

float CCTweenFunction::bounceEaseOut(float t, float b, float c, float d)
{
    t /= d;
    if (t < (1 / 2.75f))
    {
        return c * (7.5625f * t * t) + b;
    }
    else if (t < (2 / 2.75f))
    {
        t -= (1.5f / 2.75f);
        return c * (7.5625f * t * t + .75f) + b;
    }
    else if (t < (2.5f / 2.75f))
    {
        t -= (2.25f / 2.75f);
        return c * (7.5625f * t * t + .9375f) + b;
    }
    else
    {
        t -= (2.625f / 2.75f);
        return c * (7.5625f * t * t + .984375f) + b;
    }
}

float CCTweenFunction::bounceEaseInOut(float t, float b, float c, float d)
{
    if (t < d / 2)
        return bounceEaseIn(t * 2, 0, c, d) * .5 + b;
    else
        return bounceEaseOut(t * 2 - d, 0, c, d) * .5 + c * .5 + b;
}


NS_CC_EXT_END
