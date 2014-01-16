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

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif

NS_CC_EXT_BEGIN

float CCTweenFunction::tweenTo(float time, CCTweenType type, float *easingParam)
{
    float delta = 0;

    switch (type)
    {
    case CUSTOM_EASING:
        delta = customEase(time, easingParam);
        break;

    case Linear:
        delta = linear(time);
        break;

    case Sine_EaseIn:
        delta = sineEaseIn(time);
        break;
    case Sine_EaseOut:
        delta = sineEaseOut(time);
        break;
    case Sine_EaseInOut:
        delta = sineEaseInOut(time);
        break;

    case Quad_EaseIn:
        delta = quadEaseIn(time);
        break;
    case Quad_EaseOut:
        delta = quadEaseOut(time);
        break;
    case Quad_EaseInOut:
        delta = quadEaseInOut(time);
        break;

    case Cubic_EaseIn:
        delta = cubicEaseIn(time);
        break;
    case Cubic_EaseOut:
        delta = cubicEaseOut(time);
        break;
    case Cubic_EaseInOut:
        delta = cubicEaseInOut(time);
        break;

    case Quart_EaseIn:
        delta = quartEaseIn(time);
        break;
    case Quart_EaseOut:
        delta = quartEaseOut(time);
        break;
    case Quart_EaseInOut:
        delta = quartEaseInOut(time);
        break;

    case Quint_EaseIn:
        delta = quintEaseIn(time);
        break;
    case Quint_EaseOut:
        delta = quintEaseOut(time);
        break;
    case Quint_EaseInOut:
        delta = quintEaseInOut(time);
        break;

    case Expo_EaseIn:
        delta = expoEaseIn(time);
        break;
    case Expo_EaseOut:
        delta = expoEaseOut(time);
        break;
    case Expo_EaseInOut:
        delta = expoEaseInOut(time);
        break;

    case Circ_EaseIn:
        delta = circEaseIn(time);
        break;
    case Circ_EaseOut:
        delta = circEaseOut(time);
        break;
    case Circ_EaseInOut:
        delta = circEaseInOut(time);
        break;

    case Elastic_EaseIn:
        delta = elasticEaseIn(time, easingParam);
        break;
    case Elastic_EaseOut:
        delta = elasticEaseOut(time, easingParam);
        break;
    case Elastic_EaseInOut:
        delta = elasticEaseInOut(time, easingParam);
        break;


    case Back_EaseIn:
        delta = backEaseIn(time);
        break;
    case Back_EaseOut:
        delta = backEaseOut(time);
        break;
    case Back_EaseInOut:
        delta = backEaseInOut(time);
        break;

    case Bounce_EaseIn:
        delta = bounceEaseIn(time);
        break;
    case Bounce_EaseOut:
        delta = bounceEaseOut(time);
        break;
    case Bounce_EaseInOut:
        delta = bounceEaseInOut(time);
        break;

    default:
        delta = sineEaseInOut(time);
        break;
    }

    return delta;
}

// Linear
float CCTweenFunction::linear(float time)
{
    return time;
}


// Sine Ease
float CCTweenFunction::sineEaseIn(float time)
{
    return -1 * cosf(time * (float)M_PI_2) + 1;
}
float CCTweenFunction::sineEaseOut(float time)
{
    return sinf(time * (float)M_PI_2);
}
float CCTweenFunction::sineEaseInOut(float time)
{
    return -0.5f * (cosf((float)M_PI * time) - 1);
}


// Quad Ease
float CCTweenFunction::quadEaseIn(float time)
{
    return time * time;
}
float CCTweenFunction::quadEaseOut(float time)
{
    return -1 * time * (time - 2);
}
float CCTweenFunction::quadEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time;
    --time;
    return -0.5f * (time * (time - 2) - 1);
}



// Cubic Ease
float CCTweenFunction::cubicEaseIn(float time)
{
    return time * time * time;
}
float CCTweenFunction::cubicEaseOut(float time)
{
    time -= 1;
    return (time * time * time + 1);
}
float CCTweenFunction::cubicEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time;
    time -= 2;
    return 0.5f * (time * time * time + 2);
}


// Quart Ease
float CCTweenFunction::quartEaseIn(float time)
{
    return time * time * time * time;
}
float CCTweenFunction::quartEaseOut(float time)
{
    time -= 1;
    return -(time * time * time * time - 1);
}
float CCTweenFunction::quartEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time * time;
    time -= 2;
    return -0.5f * (time * time * time * time - 2);
}


// Quint Ease
float CCTweenFunction::quintEaseIn(float time)
{
    return time * time * time * time * time;
}
float CCTweenFunction::quintEaseOut(float time)
{
    time -=1;
    return (time * time * time * time * time + 1);
}
float CCTweenFunction::quintEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time * time * time;
    time -= 2;
    return 0.5f * (time * time * time * time * time + 2);
}


// Expo Ease
float CCTweenFunction::expoEaseIn(float time)
{
    return time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f;
}
float CCTweenFunction::expoEaseOut(float time)
{
    return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1);
}
float CCTweenFunction::expoEaseInOut(float time)
{
    time /= 0.5f;
    if (time < 1)
    {
        time = 0.5f * powf(2, 10 * (time - 1));
    }
    else
    {
        time = 0.5f * (-powf(2, -10 * (time - 1)) + 2);
    }

    return time;
}


// Circ Ease
float CCTweenFunction::circEaseIn(float time)
{
    return -1 * (sqrt(1 - time * time) - 1);
}
float CCTweenFunction::circEaseOut(float time)
{
    time = time - 1;
    return sqrt(1 - time * time);
}
float CCTweenFunction::circEaseInOut(float time)
{
    time = time * 2;
    if (time < 1)
        return -0.5f * (sqrt(1 - time * time) - 1);
    time -= 2;
    return 0.5f * (sqrt(1 - time * time) + 1);
}


// Elastic Ease
float CCTweenFunction::elasticEaseIn(float time, float *easingParam)
{
    float period = 0.3f;

    if (easingParam != NULL)
    {
        period = easingParam[0];
    }

    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = period / 4;
        time = time - 1;
        newT = -powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / period);
    }

    return newT;
}
float CCTweenFunction::elasticEaseOut(float time, float *easingParam)
{
    float period = 0.3f;

    if (easingParam != NULL)
    {
        period = easingParam[0];
    }

    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        float s = period / 4;
        newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) + 1;
    }

    return newT;
}
float CCTweenFunction::elasticEaseInOut(float time, float *easingParam)
{
    float period = 0.3f;

    if (easingParam != NULL)
    {
        period = easingParam[0];
    }

    float newT = 0;
    if (time == 0 || time == 1)
    {
        newT = time;
    }
    else
    {
        time = time * 2;
        if (! period)
        {
            period = 0.3f * 1.5f;
        }

        float s = period / 4;

        time = time - 1;
        if (time < 0)
        {
            newT = -0.5f * powf(2, 10 * time) * sinf((time -s) * M_PI_X_2 / period);
        }
        else
        {
            newT = powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) * 0.5f + 1;
        }
    }
    return newT;
}


// Back Ease
float CCTweenFunction::backEaseIn(float time)
{
    float overshoot = 1.70158f;
    return time * time * ((overshoot + 1) * time - overshoot);
}
float CCTweenFunction::backEaseOut(float time)
{
    float overshoot = 1.70158f;

    time = time - 1;
    return time * time * ((overshoot + 1) * time + overshoot) + 1;
}
float CCTweenFunction::backEaseInOut(float time)
{
    float overshoot = 1.70158f * 1.525f;

    time = time * 2;
    if (time < 1)
    {
        return (time * time * ((overshoot + 1) * time - overshoot)) / 2;
    }
    else
    {
        time = time - 2;
        return (time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1;
    }
}



// Bounce Ease
float bounceTime(float time)
{
    if (time < 1 / 2.75)
    {
        return 7.5625f * time * time;
    } else 
        if (time < 2 / 2.75)
        {
            time -= 1.5f / 2.75f;
            return 7.5625f * time * time + 0.75f;
        } else
            if(time < 2.5 / 2.75)
            {
                time -= 2.25f / 2.75f;
                return 7.5625f * time * time + 0.9375f;
            }

            time -= 2.625f / 2.75f;
            return 7.5625f * time * time + 0.984375f;
}
float CCTweenFunction::bounceEaseIn(float time)
{
    return 1 - bounceTime(1 - time);
}

float CCTweenFunction::bounceEaseOut(float time)
{
    return bounceTime(time);
}

float CCTweenFunction::bounceEaseInOut(float time)
{
    float newT = 0;
    if (time < 0.5f)
    {
        time = time * 2;
        newT = (1 - bounceTime(1 - time)) * 0.5f;
    }
    else
    {
        newT = bounceTime(time * 2 - 1) * 0.5f + 0.5f;
    }

    return newT;
}


// Custom Ease
float CCTweenFunction::customEase(float time, float *easingParam)
{
    if (easingParam)
    {
        float tt = 1-time;
        return easingParam[1]*tt*tt*tt + 3*easingParam[3]*time*tt*tt + 3*easingParam[5]*time*time*tt + easingParam[7]*time*time*time;
    }
    return time;
}


NS_CC_EXT_END
