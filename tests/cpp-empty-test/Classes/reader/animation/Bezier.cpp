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

#include "Bezier.h"

#include <cmath>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES

NS_CCR_BEGIN

namespace
{
    float tau = 2 * M_PI;
    
    float crt (float v)
    {
        if (v < 0)
            return -std::pow(-v, 1.f / 3.f);
        else
            return std::pow(v, 1.f / 3.f);
    }
    
    float max(float v1, float v2, float v3)
    {
        return std::max(v1,
                        std::max(v2, v3));
    }
    
    // Modified from http://jsbin.com/yibipofeqi/1/edit, optimized for animations.
    // The origin Cardano's algorithm is based on http://www.trans4mind.com/personal_development/mathematics/polynomials/cubicAlgebra.htm
    float cardano (const std::vector<float>& curve, float x)
    {
        auto pa = x - 0;
        auto pb = x - curve[0];
        auto pc = x - curve[2];
        auto pd = x - 1;
        
        // to [t^3 + at^2 + bt + c] form:
        auto pa3 = pa * 3;
        auto pb3 = pb * 3;
        auto pc3 = pc * 3;
        auto d = (-pa + pb3 - pc3 + pd),
        rd = 1.f / d,
        r3 = 1.f / 3.f,
        a = (pa3 - 6 * pb + pc3) * rd,
        a3 = a * r3,
        b = (-pa3 + pb3) * rd,
        c = pa * rd,
        // then, determine p and q:
        p = (3 * b - a * a) * r3,
        p3 = p * r3,
        q = (2 * a * a * a - 9 * a * b + 27 * c) / 27.f,
        q2 = q / 2.f,
        // and determine the discriminant:
        discriminant = q2 * q2 + p3 * p3 * p3;
        // and some reserved variables
        float u1 = 0;
        float v1 = 0;
        float x1 = 0;
        float x2 = 0;
        float x3 = 0;
        
        // If the discriminant is negative, use polar coordinates
        // to get around square roots of negative numbers
        if (discriminant < 0)
        {
            auto mp3 = -p * r3;
            auto mp33 = mp3 * mp3 * mp3;
            auto r = std::sqrt(mp33);
            // compute cosphi corrected for IEEE float rounding:
            auto t = -q / (2 * r);
            auto cosphi = t < -1.f ? -1.f : t > 1.f ? 1.f : t;
            auto phi = std::acos(cosphi);
            auto crtr = crt(r);
            auto t1 = 2 * crtr;
            x1 = t1 * std::cos(phi * r3) - a3;
            x2 = t1 * std::cos((phi + tau) * r3) - a3;
            x3 = t1 * std::cos((phi + 2 * tau) * r3) - a3;
            
            // choose best percentage
            if (0 <= x1 && x1 <= 1.f)
            {
                if (0 <= x2 && x2 <= 1.f)
                {
                    if (0 <= x3 && x3 <= 1.f)
                        return max(x1, x2, x3);
                    else
                        return std::max(x1, x2);
                }
                else if (0 <= x3 && x3 <= 1.f)
                    return std::max(x1, x3);
                else
                    return x1;
            }
            else
            {
                if (0 <= x2 && x2 <= 1.f)
                {
                    if (0 <= x3 && x3 <= 1.f)
                        return std::max(x2, x3);
                    else
                        return x2;
                }
                else
                    return x3;
            }
        }
        else if (discriminant == 0)
        {
            u1 = q2 < 0 ? crt(-q2) : -crt(q2);
            x1 = 2 * u1 - a3;
            x2 = -u1 - a3;
            
            // choose best percentage
            if (0 <= x1 && x1 <= 1.f)
            {
                if (0 <= x2 && x2 <= 1.f)
                    return std::max(x1, x2);
                else
                    return x1;
            }
            else
                return x2;
        }
        // one real root, and two imaginary roots
        else
        {
            auto sd = std::sqrt(discriminant);
            u1 = crt(-q2 + sd);
            v1 = crt(q2 + sd);
            x1 = u1 - v1 - a3;
            return x1;
        }
    }
}

namespace Bazier
{
    float computeBezier(const std::vector<float>& controlPoints, float x)
    {
        float percent = cardano(controlPoints, x);    // t
        float p0y = 0;                // a
        float p1y = controlPoints[1]; // b
        float p2y = controlPoints[3]; // c
        float p3y = 1.f;                // d
        float t1 = 1.f - percent;
        return p0y * t1 * t1 * t1 +
               p1y * 3 * percent * t1 * t1 +
               p2y * 3 * percent * percent * t1 +
               p3y * percent * percent * percent;
    }
}

NS_CCR_END
