/****************************************************************************
 Copyright (c) 2016 Google Inc.
 Copyright (c) 2016-2017 Chukong Technologies Inc.

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

#include "vr/CCVRDistortion.h"
#include <math.h>

NS_CC_BEGIN

Distortion::Distortion()
{
    _coefficients[0] = 0.441f;
    _coefficients[1] = 0.156f;
}

void Distortion::setCoefficients(float *coefficients)
{
    for (int i = 0; i < s_numberOfCoefficients; i++)
    {
        _coefficients[i] = coefficients[i];
    }
}

float *Distortion::coefficients()
{
    return _coefficients;
}

float Distortion::distortionFactor(float radius)
{
    float result = 1.0f;
    float rFactor = 1.0f;
    float squaredRadius = radius * radius;
    for (int i = 0; i < s_numberOfCoefficients; i++)
    {
        rFactor *= squaredRadius;
        result += _coefficients[i] * rFactor;
    }
    return result;
}

float Distortion::distort(float radius)
{
    return radius * distortionFactor(radius);
}

float Distortion::distortInverse(float radius)
{
    float r0 = radius / 0.9f;
    float r = radius * 0.9f;
    float dr0 = radius - distort(r0);
    while (fabsf(r - r0) > 0.0001f)
    {
        float dr = radius - distort(r);
        float r2 = r - dr * ((r - r0) / (dr - dr0));
        r0 = r;
        r = r2;
        dr0 = dr;
    }
    return r;
}

NS_CC_END
