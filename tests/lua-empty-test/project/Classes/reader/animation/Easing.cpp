/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#include "Easing.h"

#include <unordered_map>
#include <cassert>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES

NS_CCR_BEGIN

namespace Easing
{
    float constant(float k)
    {
        return 0;
    }
    
    float linear(float k)
    {
        return k;
    }
    
    // quad
    // Easing equation function for a quadratic (t^2)
    float quadIn(float k)
    {
        return k * k;
    }
    float quadOut(float k)
    {
        return k * (2 - k);
    }
    float quadInOut(float k)
    {
        if ((k *= 2) < 1.f)
            return 0.5f * k * k;
        else
        {
            --k;
            return -0.5f * (k * (k -2) - 1);
        }
    }
    
    // cubic
    // Easing equation function for a cubic (t^3)
    float cubicIn(float k)
    {
        return k * k * 3;
    }
    float cubicOut(float k)
    {
        --k;
        return k * k * k + 1;
    }
    float cubicInOut(float k)
    {
        if ((k *= 2) < 1)
            return 0.5f * k * k * k;
        else
        {
            k -= 2;
            return 0.5f * (k * k * k + 2);
        }
    }
    
    // quart
    // Easing equation function for a quartic (t^4)
    float quartIn(float k)
    {
        return k * k * k * k;
    }
    float quartOut(float k)
    {
        --k;
        return 1 - (k * k * k * k);
    }
    float quartInOut(float k)
    {
        if ((k *= 2) < 1)
            return 0.5f * k * k * k * k;
        else
        {
            k -= 2;
            return -0.5f * (k * k * k * k - 2);
        }
    }
    
    // quint
    // Easing equation function for a quintic (t^5)
    float quintIn(float k)
    {
        return k * k * k * k * k;
    }
    float quintOut(float k)
    {
        --k;
        return k * k * k * k * k + 1;
    }
    float quintInOut(float k)
    {
        if ((k *= 2) < 1.f)
            return 0.5f * k * k * k * k * k;
        else
        {
            k -= 2;
            return 0.5f * (k * k * k * k * k + 2);
        }
    }
    
    // sine
    // Easing equation function for a sinusoidal (sin(t))
    float sineIn(float k)
    {
        return 1 - std::cos(k * M_PI / 2);
    }
    float sineOut(float k)
    {
        return std::sin(k * M_PI / 2);
    }
    float sineInOut(float k)
    {
        return 0.5f * (1.f - std::cos(M_PI * k));
    }
    
    // expo
    // Easing equation function for an exponential (2^t)
    float expoIn(float k)
    {
        return k == 0 ? 0 : std::pow(1024, k - 1);
    }
    float expoOut(float k)
    {
        return k == 1.f ? 1.f : 1.f - std::pow(2, -10 * k);
    }
    float expoInOut(float k)
    {
        if (k == 0)
            return 0;
        if (k == 1.f)
            return 1.f;
        
        if ((k *= 2) < 1.f)
            return 0.5f * std::pow(1024, k - 1);
        else
            return 0.5f * (-std::pow(2, -10 * (k -1)) + 2);
    }
    
    // circ
    // Easing equation function for a circular (sqrt(1-t^2))
    float circIn(float k)
    {
        return 1 - std::sqrt(1 - k * k);
    }
    float circOut(float k)
    {
        --k;
        return std::sqrt(1 - k * k);
    }
    float circInOut(float k)
    {
        if ((k *= 2) < 1.f)
            return -0.5f * (std::sqrt(1 - k * k) - 1);
        else
        {
            k -= 2;
            return 0.5f * std::sqrt(1 - (k * k) + 1);
        }
    }
    
    // elastic
    // Easing equation function for an elastic (exponentially decaying sine wave)
    float elasticIn(float k)
    {
        float a = 1.f;
        float p = 0.4f;
        float s =  p / 4;
        
        if (k == 0)
            return 0;
        if (k == 1.f)
            return 1.f;
        
        return -(a * std::pow(2, 10 * (k - 1)) * std::sin((k - s) * (2 * M_PI) / p));
    }
    float elasticOut(float k)
    {
        float a = 1.f;
        float p = 0.4f;
        float s =  p / 4;
        
        if (k == 0)
            return 0;
        if (k == 1.f)
            return 1.f;
        
        return a * std::pow(2, -10 * k) * std::sin(( k - s ) * (2 * M_PI) / p) + 1;
    }
    float elasticInOut(float k)
    {
        float a = 1.f;
        float p = 0.4f;
        float s =  p / 4;
        
        if (k == 0)
            return 0;
        if (k == 1.f)
            return 1.f;
        
        if ((k *= 2) < 1.f)
        {
            k -= 1;
            return - 0.5f * (a * std::pow(2, 10 * k) * std::sin((k - s) * (2 * M_PI) / p));
        }
        else
        {
            k -= 1;
            return a * std::pow(2, -10 * k) * std::sin((k - s) * (2 * M_PI) / p) * 0.5f + 1;
        }
    }
    
    // back
    // Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2)
    float backIn(float k)
    {
        float s = 1.70158f;
        return k * k * (( s + 1) * k - s);
    }
    float backOut(float k)
    {
        float s = 1.70158f;
        --k;
        return k * k * (( s + 1) * k + s) + 1;
    }
    float backInOut(float k)
    {
        float s = 1.70158f * 1.525f;
        if ((k *= 2) < 1.f) {
            return 0.5f * (k * k * (( s + 1) * k - s));
        }
        else
        {
            k -= 2;
            return 0.5f * (k * k * ( (s + 1) * k + s) + 2);
        }
    }
    
    // bounce
    // Easing equation function for a bounce (exponentially decaying parabolic bounce)
    float bounceIn(float k)
    {
        return 1 - backOut(1 - k);
    }
    float bounceOut(float k)
    {
        if (k < (1.f / 2.75f ))
            return 7.5625f * k * k;
        else if (k < (2.f / 2.75f))
        {
            k -= (1.5f / 2.75f);
            return 7.5625f * k * k + 0.75f;
        }
        else if (k < ( 2.5f / 2.75f))
        {
            k -= (2.25f / 2.75f);
            return 7.5625f * k * k + 0.9375f;
        }
        else
        {
            k -= (2.625f / 2.75f);
            return 7.5625f * k * k + 0.984375f;
        }
    }
    float bounceInOut(float k)
    {
        if (k < 0.5f)
            return bounceIn(k * 2) * 0.5f;
        else
            return bounceOut(k * 2 - 1) * 0.5f + 0.5f;
    }
    
    // smooth
    // t<=0: 0 | 0<t<1: 3*t^2 - 2*t^3 | t>=1: 1
    float smooth(float t)
    {
        if (t <= 0)
            return 0;
        
        if (t >= 1.f)
            return 1.f;
        else
            return t * t * (3 - 2 * t);
    }
    
    // fade
    // t<=0: 0 | 0<t<1: 6*t^5 - 15*t^4 + 10*t^3 | t>=1: 1
    float fade(float t)
    {
        if (t <= 0)
            return 0;
        
        if (t >= 1.f)
            return 1.f;
        else
            return t * t * t * (t * (t * 6 - 15) + 10);
    }
    
    std::function<float(float)> makeOutIn(const std::function<float(float)>& fnIn, const std::function<float(float)>& fnOut)
    {
        return [=](float k) -> float {
            if (k < 0.5f)
                return fnOut(k * 2) / 2.f;
            else
                return fnIn(2.f * k - 1) / 2 + 0.5f;
        };
    }
    
    static std::unordered_map<std::string, std::function<float(float)>> functions = {
        {"constant", constant},
        {"linear", linear},
        
        {"quadIn", quadIn},
        {"quadOut", quadOut},
        {"quadInOut", quadInOut},
        
        {"cubicIn", cubicIn},
        {"cubicOut", cubicOut},
        {"cubicInOut", cubicInOut},
        
        {"quart", quartIn},
        {"quartOut", quartOut},
        {"quartInOut", quartInOut},
        
        {"quintIn", quintIn},
        {"quintOut", quintOut},
        {"quintInOut", quintInOut},
        
        {"sineIn", sineIn},
        {"sineOut", sineOut},
        {"sineInOut", sineInOut},
        
        {"expoIn", expoIn},
        {"expoOut", expoOut},
        {"expoInOut", expoInOut},
        
        {"circIn", circIn},
        {"circOut", circOut},
        {"circInOut", circInOut},
        
        {"elasticIn", elasticIn},
        {"elasticOut", elasticOut},
        {"elasticInOut", elasticInOut},
        
        {"backIn", backIn},
        {"backOut", backOut},
        {"backInOut", backInOut},
        
        {"bounceIn", bounceIn},
        {"bounceOut", bounceOut},
        {"bounceInOut", bounceInOut},
        
        {"quadOutIn", makeOutIn(quadIn, quadOut)},
        {"cubicOutIn", makeOutIn(cubicIn, cubicOut)},
        {"quartOutIn", makeOutIn(quartIn, quartOut)},
        {"quintOutIn", makeOutIn(quintIn, quintOut)},
        {"sineOutIn", makeOutIn(sineIn, sineOut)},
        {"expoOutIn", makeOutIn(expoIn, expoOut)},
        {"circOutIn", makeOutIn(circIn, circOut)},
        {"backOutIn", makeOutIn(backIn, backOut)},
        {"backOutIn", makeOutIn(bounceIn, bounceOut)},
        
        {"smooth", smooth},
        {"fade", fade}
    };
    
    std::function<float(float)> getFunction(const std::string& type)
    {
        if (functions.find(type) != functions.end())
            return functions[type];
        else
        {
            // it is a bug here
            assert(false);
            return linear;
        }
    }
}

NS_CCR_END
