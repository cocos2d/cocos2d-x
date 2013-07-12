/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2007      Scott Lembcke
Copyright (c) 2010      Lam Pham

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

#include "CCPointExtension.h"
#include "ccMacros.h" // FLT_EPSILON
#include <stdio.h>

NS_CC_BEGIN

#define kPointEpsilon FLT_EPSILON

float
ccpLength(const Point& v)
{
    return v.getLength();
}

float
ccpDistance(const Point& v1, const Point& v2)
{
    return v1.getDistance(v2);
}

Point
ccpNormalize(const Point& v)
{
    return v.normalize();
}

Point
ccpForAngle(const float a)
{
    return Point::forAngle(a);
}

float
ccpToAngle(const Point& v)
{
    return v.getAngle();
}

Point ccpLerp(const Point& a, const Point& b, float alpha)
{
    return a.lerp(b, alpha);
}

Point ccpClamp(const Point& p, const Point& min_inclusive, const Point& max_inclusive)
{
    return p.getClampPoint(min_inclusive, max_inclusive);
}

Point ccpFromSize(const Size& s)
{
    return Point(s);
}

Point ccpCompOp(const Point& p, float (*opFunc)(float))
{
    return p.compOp(opFunc);
}

bool ccpFuzzyEqual(const Point& a, const Point& b, float var)
{
	return a.fuzzyEquals(b, var);
}

Point ccpCompMult(const Point& a, const Point& b)
{
    return Point(a.x * b.x, a.y * b.y);
}

float ccpAngleSigned(const Point& a, const Point& b)
{
	return a.getAngle(b);
}

Point ccpRotateByAngle(const Point& v, const Point& pivot, float angle)
{
	return v.rotateByAngle(pivot, angle);
}


bool ccpSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D)
{
    return Point::isSegmentIntersect(A, B, C, D);
}

Point ccpIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D)
{
    return Point::getIntersectPoint(A, B, C, D);
}

bool ccpLineIntersect(const Point& A, const Point& B, 
                      const Point& C, const Point& D,
                      float *S, float *T)
{
    return Point::isLineIntersect(A, B, C, D, S, T);
}

float ccpAngle(const Point& a, const Point& b)
{
    return a.getAngle(b);
}

NS_CC_END
