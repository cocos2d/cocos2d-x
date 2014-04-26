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

#include "2d/CCTweenFunction.h"

NS_CC_BEGIN

namespace tweenfunc {
    

#ifndef M_PI_X_2
#define M_PI_X_2 (float)M_PI * 2.0f
#endif




float tweenTo(float time, TweenType type, float *easingParam)
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
        {
            float period = 0.3f;
            if (nullptr != easingParam) {
                period = easingParam[0];
            }
            delta = elasticEaseIn(time, period);
        }
            break;
        case Elastic_EaseOut:
        {
            float period = 0.3f;
            if (nullptr != easingParam) {
                period = easingParam[0];
            }
            delta = elasticEaseOut(time, period);
        }
            break;
        case Elastic_EaseInOut:
        {
            float period = 0.3f;
            if (nullptr != easingParam) {
                period = easingParam[0];
            }
            delta = elasticEaseInOut(time, period);
        }
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
float linear(float time)
{
    return time;
}


// Sine Ease
float sineEaseIn(float time)
{
    return -1 * cosf(time * (float)M_PI_2) + 1;
}
    
float sineEaseOut(float time)
{
    return sinf(time * (float)M_PI_2);
}
    
float sineEaseInOut(float time)
{
    return -0.5f * (cosf((float)M_PI * time) - 1);
}


// Quad Ease
float quadEaseIn(float time)
{
    return time * time;
}
    
float quadEaseOut(float time)
{
    return -1 * time * (time - 2);
}
    
float quadEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time;
    --time;
    return -0.5f * (time * (time - 2) - 1);
}



// Cubic Ease
float cubicEaseIn(float time)
{
    return time * time * time;
}
float cubicEaseOut(float time)
{
    time -= 1;
    return (time * time * time + 1);
}
float cubicEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time;
    time -= 2;
    return 0.5f * (time * time * time + 2);
}


// Quart Ease
float quartEaseIn(float time)
{
    return time * time * time * time;
}
    
float quartEaseOut(float time)
{
    time -= 1;
    return -(time * time * time * time - 1);
}
    
float quartEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time * time;
    time -= 2;
    return -0.5f * (time * time * time * time - 2);
}


// Quint Ease
float quintEaseIn(float time)
{
    return time * time * time * time * time;
}
    
float quintEaseOut(float time)
{
    time -=1;
    return (time * time * time * time * time + 1);
}
    
float quintEaseInOut(float time)
{
    time = time*2;
    if (time < 1)
        return 0.5f * time * time * time * time * time;
    time -= 2;
    return 0.5f * (time * time * time * time * time + 2);
}


// Expo Ease
float expoEaseIn(float time)
{
    return time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f;
}
float expoEaseOut(float time)
{
    return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1);
}
float expoEaseInOut(float time)
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
float circEaseIn(float time)
{
    return -1 * (sqrt(1 - time * time) - 1);
}
float circEaseOut(float time)
{
    time = time - 1;
    return sqrt(1 - time * time);
}
float circEaseInOut(float time)
{
    time = time * 2;
    if (time < 1)
        return -0.5f * (sqrt(1 - time * time) - 1);
    time -= 2;
    return 0.5f * (sqrt(1 - time * time) + 1);
}


// Elastic Ease
float elasticEaseIn(float time, float period)
{

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
float elasticEaseOut(float time, float period)
{

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
float elasticEaseInOut(float time, float period)
{

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
float backEaseIn(float time)
{
    float overshoot = 1.70158f;
    return time * time * ((overshoot + 1) * time - overshoot);
}
float backEaseOut(float time)
{
    float overshoot = 1.70158f;

    time = time - 1;
    return time * time * ((overshoot + 1) * time + overshoot) + 1;
}
float backEaseInOut(float time)
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
    }
    else if (time < 2 / 2.75)
    {
        time -= 1.5f / 2.75f;
        return 7.5625f * time * time + 0.75f;
    }
    else if(time < 2.5 / 2.75)
    {
        time -= 2.25f / 2.75f;
        return 7.5625f * time * time + 0.9375f;
    }

    time -= 2.625f / 2.75f;
    return 7.5625f * time * time + 0.984375f;
}
float bounceEaseIn(float time)
{
    return 1 - bounceTime(1 - time);
}

float bounceEaseOut(float time)
{
    return bounceTime(time);
}

float bounceEaseInOut(float time)
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
float customEase(float time, float *easingParam)
{
    if (easingParam)
    {
        float tt = 1-time;
        return easingParam[1]*tt*tt*tt + 3*easingParam[3]*time*tt*tt + 3*easingParam[5]*time*time*tt + easingParam[7]*time*time*time;
    }
    return time;
}

float easeIn(float time, float rate)
{
    return powf(time, rate);
}

float easeOut(float time, float rate)
{
    return powf(time, 1 / rate);
}
    
float easeInOut(float time, float rate)
{
    time *= 2;
    if (time < 1)
    {
        return 0.5f * powf(time, rate);
    }
    else
    {
        return (1.0f - 0.5f * powf(2 - time, rate));
    }
}
    
float quadraticIn(float time)
{
    return   powf(time,2);
}
    
float quadraticOut(float time)
{
    return -time*(time-2);
}
    
float quadraticInOut(float time)
{
    
    float resultTime = time;
    time = time*2;
    if (time < 1)
    {
        resultTime = time * time * 0.5f;
    }
    else
    {
        --time;
        resultTime = -0.5f * (time * (time - 2) - 1);
    }
    return resultTime;
}
    
float bezieratFunction( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a + 3*t*(powf(1-t,2))*b + 3*powf(t,2)*(1-t)*c + powf(t,3)*d );
}
    
}

NS_CC_END
