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
		float ftmp;
		ftmp = min_inclusive;
		min_inclusive = max_inclusive;
		max_inclusive = min_inclusive;
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

CCPoint ccpCompOp(const CCPoint& p, float (*opFunc)(float)){
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
	CCPoint a2 = ccpNormalize(a);	CCPoint b2 = ccpNormalize(b);
	float angle = atan2f(a2.x * b2.y - a2.y * b2.x, ccpDot(a2, b2));
	if( fabs(angle) < kCCPointEpsilon ) return 0.f;
	return angle;
}

CCPoint ccpRotateByAngle(const CCPoint& v, const CCPoint& pivot, float angle) {
	CCPoint r = ccpSub(v, pivot);
	float t = r.x;
	float cosa = cosf(angle), sina = sinf(angle);
	r.x = t*cosa - r.y*sina;
	r.y = t*sina + r.y*cosa;
	r = ccpAdd(r, pivot);
	return r;
}

bool ccpLineIntersect(const CCPoint& p1, const CCPoint& p2, 
					  const CCPoint& p3, const CCPoint& p4,
					  float *s, float *t){
	CCPoint p13, p43, p21;
	float d1343, d4321, d1321, d4343, d2121;
	float numer, denom;
	
	p13 = ccpSub(p1, p3);
	
	p43 = ccpSub(p4, p3);
	
	//Roughly equal to zero but with an epsilon deviation for float 
	//correction
	if (ccpFuzzyEqual(p43, CCPointZero, kCCPointEpsilon))
		return false;
	
	p21 = ccpSub(p2, p1);
	
	//Roughly equal to zero
	if (ccpFuzzyEqual(p21,CCPointZero, kCCPointEpsilon))
		return false;
	
	d1343 = ccpDot(p13, p43);
	d4321 = ccpDot(p43, p21);
	d1321 = ccpDot(p13, p21);
	d4343 = ccpDot(p43, p43);
	d2121 = ccpDot(p21, p21);
	
	denom = d2121 * d4343 - d4321 * d4321;
	if (fabs(denom) < kCCPointEpsilon)
		return false;
	numer = d1343 * d4321 - d1321 * d4343;
	
	*s = numer / denom;
	*t = (d1343 + d4321 *(*s)) / d4343;
	
	return true;
}

float ccpAngle(const CCPoint& a, const CCPoint& b)
{
	float angle = acosf(ccpDot(ccpNormalize(a), ccpNormalize(b)));
	if( fabs(angle) < kCCPointEpsilon ) return 0.f;
	return angle;
}
}//namespace   cocos2d 
