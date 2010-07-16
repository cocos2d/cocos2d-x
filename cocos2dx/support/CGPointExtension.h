/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __SUPPORT_CGPOINTEXTENSION_H__
#define __SUPPORT_CGPOINTEXTENSION_H__

/**
 @file
 CGPoint extensions based on Chipmunk's cpVect file.
 These extensions work both with CGPoint and cpVect.
 
 The "ccp" prefix means: "CoCos2d Point"
 
 Examples:
  - ccpAdd( ccp(1,1), ccp(2,2) ); // preferred cocos2d way
  - ccpAdd( CGPointMake(1,1), CGPointMake(2,2) ); // also ok but more verbose
  
  - cpvadd( cpv(1,1), cpv(2,2) ); // way of the chipmunk
  - ccpAdd( cpv(1,1), cpv(2,2) ); // mixing chipmunk and cocos2d (avoid)
  - cpvadd( CGPointMake(1,1), CGPointMake(2,2) ); // mixing chipmunk and CG (avoid)
 */

#include "cocoa/CGGeometry.h"

#include <math.h>

/** Helper macro that creates a CGPoint
 @return CGPoint
 @since v0.7.2
 */
#define ccp(__X__,__Y__) CGPointMake(__X__,__Y__)

/** Returns opposite of point.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpNeg(const CGPoint v)
{
	return ccp(-v.x, -v.y);
}

/** Calculates sum of two points.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpAdd(const CGPoint v1, const CGPoint v2)
{
	return ccp(v1.x + v2.x, v1.y + v2.y);
}

/** Calculates difference of two points.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpSub(const CGPoint v1, const CGPoint v2)
{
	return ccp(v1.x - v2.x, v1.y - v2.y);
}

/** Returns point multiplied by given factor.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpMult(const CGPoint v, const CGFloat s)
{
	return ccp(v.x*s, v.y*s);
}

/** Calculates midpoint between two points.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpMidpoint(const CGPoint v1, const CGPoint v2)
{
	return ccpMult(ccpAdd(v1, v2), 0.5f);
}

/** Calculates dot product of two points.
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
ccpDot(const CGPoint v1, const CGPoint v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

/** Calculates cross product of two points.
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
ccpCross(const CGPoint v1, const CGPoint v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpPerp(const CGPoint v)
{
	return ccp(-v.y, v.x);
}

/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpRPerp(const CGPoint v)
{
	return ccp(v.y, -v.x);
}

/** Calculates the projection of v1 over v2.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpProject(const CGPoint v1, const CGPoint v2)
{
	return ccpMult(v2, ccpDot(v1, v2)/ccpDot(v2, v2));
}

/** Rotates two points.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpRotate(const CGPoint v1, const CGPoint v2)
{
	return ccp(v1.x*v2.x - v1.y*v2.y, v1.x*v2.y + v1.y*v2.x);
}

/** Unrotates two points.
 @return CGPoint
 @since v0.7.2
 */
static inline CGPoint
ccpUnrotate(const CGPoint v1, const CGPoint v2)
{
	return ccp(v1.x*v2.x + v1.y*v2.y, v1.y*v2.x - v1.x*v2.y);
}

/** Calculates the square length of a CGPoint (not calling sqrt() )
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
ccpLengthSQ(const CGPoint v)
{
	return ccpDot(v, v);
}

/** Calculates distance between point an origin
 @return CGFloat
 @since v0.7.2
 */
CGFloat ccpLength(const CGPoint v);

/** Calculates the distance between two points
 @return CGFloat
 @since v0.7.2
 */
CGFloat ccpDistance(const CGPoint v1, const CGPoint v2);

/** Returns point multiplied to a length of 1.
 @return CGPoint
 @since v0.7.2
 */
CGPoint ccpNormalize(const CGPoint v);

/** Converts radians to a normalized vector.
 @return CGPoint
 @since v0.7.2
 */
CGPoint ccpForAngle(const CGFloat a);

/** Converts a vector to radians.
 @return CGFloat
 @since v0.7.2
 */
CGFloat ccpToAngle(const CGPoint v);


/** Clamp a value between from and to.
 @since v0.99.1
 */
float clampf(float value, float min_inclusive, float max_inclusive);

/** Clamp a point between from and to.
 @since v0.99.1
 */
CGPoint ccpClamp(CGPoint p, CGPoint from, CGPoint to);

/** Quickly convert CGSize to a CGPoint
 @since v0.99.1
 */
CGPoint ccpFromSize(CGSize s);

/** Run a math operation function on each point component
 * absf, fllorf, ceilf, roundf
 * any function that has the signature: float func(float);
 * For example: let's try to take the floor of x,y
 * ccpCompOp(p,floorf);
 @since v0.99.1
 */
CGPoint ccpCompOp(CGPoint p, float (*opFunc)(float));

/** Linear Interpolation between two points a and b
 @returns
	alpha == 0 ? a
	alpha == 1 ? b
	otherwise a value between a..b
 @since v0.99.1
 */
CGPoint ccpLerp(CGPoint a, CGPoint b, float alpha);


/** @returns if points have fuzzy equality which means equal with some degree of variance.
 @since v0.99.1
 */
bool ccpFuzzyEqual(CGPoint a, CGPoint b, float variance);


/** Multiplies a nd b components, a.x*b.x, a.y*b.y
 @returns a component-wise multiplication
 @since v0.99.1
 */
CGPoint ccpCompMult(CGPoint a, CGPoint b);

/** @returns the signed angle in radians between two vector directions
 @since v0.99.1
 */
float ccpAngleSigned(CGPoint a, CGPoint b);

/** @returns the angle in radians between two vector directions
 @since v0.99.1
*/
float ccpAngle(CGPoint a, CGPoint b);

/** Rotates a point counter clockwise by the angle around a pivot
 @param v is the point to rotate
 @param pivot is the pivot, naturally
 @param angle is the angle of rotation cw in radians
 @returns the rotated point
 @since v0.99.1
 */
CGPoint ccpRotateByAngle(CGPoint v, CGPoint pivot, float angle);

/** A general line-line intersection test
 @param p1 
	is the startpoint for the first line P1 = (p1 - p2)
 @param p2 
	is the endpoint for the first line P1 = (p1 - p2)
 @param p3 
	is the startpoint for the second line P2 = (p3 - p4)
 @param p4 
	is the endpoint for the second line P2 = (p3 - p4)
 @param s 
	is the range for a hitpoint in P1 (pa = p1 + s*(p2 - p1))
 @param t
	is the range for a hitpoint in P3 (pa = p2 + t*(p4 - p3))
 @return bool 
	indicating successful intersection of a line
	note that to truly test intersection for segments we have to make 
	sure that s & t lie within [0..1] and for rays, make sure s & t > 0
	the hit point is		p3 + t * (p4 - p3);
	the hit point also is	p1 + s * (p2 - p1);
 @since v0.99.1
 */
bool ccpLineIntersect(CGPoint p1, CGPoint p2, 
					  CGPoint p3, CGPoint p4,
					  float *s, float *t);


#endif // __SUPPORT_CGPOINTEXTENSION_H__

