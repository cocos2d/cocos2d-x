/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
namespace   cocos2d {

#define kCCPointEpsilon FLT_EPSILON

CGFloat
ccpLength(const CCPoint& v)
{
	return sqrtf(ccpLengthSQ(v));
}

CGFloat
ccpDistance(const CCPoint& v1, const CCPoint& v2)
{
	return ccpLength(ccpSub(v1, v2));
}

CCPoint
ccpNormalize(const CCPoint& v)
{
	return ccpMult(v, 1.0f/ccpLength(v));
}

CCPoint
ccpForAngle(const CGFloat a)
{
	return ccp(cosf(a), sinf(a));
}

CGFloat
ccpToAngle(const CCPoint& v)
{
	return atan2f(v.y, v.x);
}

CCPoint ccpLerp(const CCPoint& a, const CCPoint& b, float alpha)
{
	return ccpAdd(ccpMult(a, 1.f - alpha), ccpMult(b, alpha));
}

float clampf(float value, float min_inclusive, float max_inclusive)
{
	if (min_inclusive > max_inclusive) {
        CC_SWAP(min_inclusive, max_inclusive, float);
	}
	return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
}

CCPoint ccpClamp(const CCPoint& p, const CCPoint& min_inclusive, const CCPoint& max_inclusive)
{
	return ccp(clampf(p.x,min_inclusive.x,max_inclusive.x), clampf(p.y, min_inclusive.y, max_inclusive.y));
}

CCPoint ccpFromSize(const CCSize& s)
{
	return ccp(s.width, s.height);
}

CCPoint ccpCompOp(const CCPoint& p, float (*opFunc)(float))
{
	return ccp(opFunc(p.x), opFunc(p.y));
}

bool ccpFuzzyEqual(const CCPoint& a, const CCPoint& b, float var)
{
	if(a.x - var <= b.x && b.x <= a.x + var)
		if(a.y - var <= b.y && b.y <= a.y + var)
			return true;
	return false;
}

CCPoint ccpCompMult(const CCPoint& a, const CCPoint& b)
{
	return ccp(a.x * b.x, a.y * b.y);
}

float ccpAngleSigned(const CCPoint& a, const CCPoint& b)
{
	CCPoint a2 = ccpNormalize(a);
    CCPoint b2 = ccpNormalize(b);
	float angle = atan2f(a2.x * b2.y - a2.y * b2.x, ccpDot(a2, b2));
	if( fabs(angle) < kCCPointEpsilon ) return 0.f;
	return angle;
}

CCPoint ccpRotateByAngle(const CCPoint& v, const CCPoint& pivot, float angle)
{
	CCPoint r = ccpSub(v, pivot);
    float cosa = cosf(angle), sina = sinf(angle);
	float t = r.x;
    r.x = t*cosa - r.y*sina + pivot.x;
    r.y = t*sina + r.y*cosa + pivot.y;
	return r;
}


bool ccpSegmentIntersect(const CCPoint& A, const CCPoint& B, const CCPoint& C, const CCPoint& D)
{
    float S, T;

    if( ccpLineIntersect(A, B, C, D, &S, &T )
        && (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f) )
        return true;

    return false;
}

CCPoint ccpIntersectPoint(const CCPoint& A, const CCPoint& B, const CCPoint& C, const CCPoint& D)
{
    float S, T;

    if( ccpLineIntersect(A, B, C, D, &S, &T) )
    {
        // Point of intersection
        CCPoint P;
        P.x = A.x + S * (B.x - A.x);
        P.y = A.y + S * (B.y - A.y);
        return P;
    }

    return CCPointZero;
}

bool ccpLineIntersect(const CCPoint& A, const CCPoint& B, 
					  const CCPoint& C, const CCPoint& D,
					  float *S, float *T)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    const float BAx = B.x - A.x;
    const float BAy = B.y - A.y;
    const float DCx = D.x - C.x;
    const float DCy = D.y - C.y;
    const float ACx = A.x - C.x;
    const float ACy = A.y - C.y;

    const float denom = DCy*BAx - DCx*BAy;

    *S = DCx*ACy - DCy*ACx;
    *T = BAx*ACy - BAy*ACx;

    if (denom == 0)
    {
        if (*S == 0 || *T == 0)
        { 
            // Lines incident
            return true;   
        }
        // Lines parallel and not incident
        return false;
    }

    *S = *S / denom;
    *T = *T / denom;

    // Point of intersection
    // CGPoint P;
    // P.x = A.x + *S * (B.x - A.x);
    // P.y = A.y + *S * (B.y - A.y);

    return true;
}

float ccpAngle(const CCPoint& a, const CCPoint& b)
{
	float angle = acosf(ccpDot(ccpNormalize(a), ccpNormalize(b)));
	if( fabs(angle) < kCCPointEpsilon ) return 0.f;
	return angle;
}
}//namespace   cocos2d 
