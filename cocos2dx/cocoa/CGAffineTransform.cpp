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
#include "CGAffineTransform.h"
#include <algorithm>
#include <math.h>

using namespace std;


namespace   cocos2d {

CGAffineTransform __CGAffineTransformMake(CGFloat a, CGFloat b, CGFloat c, CGFloat d, CGFloat tx, CGFloat ty)
{
  CGAffineTransform t;
  t.a = a; t.b = b; t.c = c; t.d = d; t.tx = tx; t.ty = ty;
  return t;
}

CGPoint __CGPointApplyAffineTransform(CGPoint point, CGAffineTransform t)
{
  CGPoint p;
  p.x = (CGFloat)((double)t.a * point.x + (double)t.c * point.y + t.tx);
  p.y = (CGFloat)((double)t.b * point.x + (double)t.d * point.y + t.ty);
  return p;
}

CGSize __CGSizeApplyAffineTransform(CGSize size, CGAffineTransform t)
{
  CGSize s;
  s.width = (CGFloat)((double)t.a * size.width + (double)t.c * size.height);
  s.height = (CGFloat)((double)t.b * size.width + (double)t.d * size.height);
  return s;
}


CGAffineTransform CGAffineTransformMakeIdentity()
{
	return __CGAffineTransformMake(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

extern const CGAffineTransform CGAffineTransformIdentity = CGAffineTransformMakeIdentity();


CGRect CGRectApplyAffineTransform(CGRect rect, CGAffineTransform anAffineTransform)
{
	CGFloat top = CGRect::CGRectGetMinY(rect);
    CGFloat left = CGRect::CGRectGetMinX(rect);
	CGFloat right = CGRect::CGRectGetMaxX(rect);
	CGFloat bottom = CGRect::CGRectGetMaxY(rect);
	
	CGPoint topLeft = CGPointApplyAffineTransform(CGPointMake(left, top), anAffineTransform);
    CGPoint topRight = CGPointApplyAffineTransform(CGPointMake(right, top), anAffineTransform);
    CGPoint bottomLeft = CGPointApplyAffineTransform(CGPointMake(left, bottom), anAffineTransform);
    CGPoint bottomRight = CGPointApplyAffineTransform(CGPointMake(right, bottom), anAffineTransform);

    CGFloat minX = min(min(topLeft.x, topRight.x), min(bottomLeft.x, bottomRight.x));
    CGFloat maxX = max(max(topLeft.x, topRight.x), max(bottomLeft.x, bottomRight.x));
    CGFloat minY = min(min(topLeft.y, topRight.y), min(bottomLeft.y, bottomRight.y));
    CGFloat maxY = max(max(topLeft.y, topRight.y), max(bottomLeft.y, bottomRight.y));
        
    return CGRectMake(minX, minY, (maxX - minX), (maxY - minY));
}

CGAffineTransform CGAffineTransformTranslate(CGAffineTransform t, float tx, float ty)
{
	return __CGAffineTransformMake(t.a, t.b, t.c, t.d, t.tx + t.a * tx + t.c * ty, t.ty + t.b * tx + t.d * ty);
}

CGAffineTransform CGAffineTransformScale(CGAffineTransform t, CGFloat sx, CGFloat sy)
{
	return __CGAffineTransformMake(t.a * sx, t.b * sx, t.c * sy, t.d * sy, t.tx, t.ty);
}

CGAffineTransform CGAffineTransformRotate(CGAffineTransform t, CGFloat anAngle)
{
    float fSin = sin(anAngle);
    float fCos = cos(anAngle);

	return __CGAffineTransformMake(	t.a * fCos + t.c * fSin,
									t.b * fCos + t.d * fSin,
									t.c * fCos - t.a * fSin,
									t.d * fCos - t.b * fSin,
									t.tx,
									t.ty);
}

/* Concatenate `t2' to `t1' and return the result:
     t' = t1 * t2 */
CGAffineTransform CGAffineTransformConcat(CGAffineTransform t1,CGAffineTransform t2)
{
	return __CGAffineTransformMake(	t1.a * t2.a + t1.b * t2.c, t1.a * t2.b + t1.b * t2.d, //a,b
									t1.c * t2.a + t1.d * t2.c, t1.c * t2.b + t1.d * t2.d, //c,d
									t1.tx * t2.a + t1.ty * t2.c + t2.tx,				  //tx
									t1.tx * t2.b + t1.ty * t2.d + t2.ty);				  //ty
}

/* Return true if `t1' and `t2' are equal, false otherwise. */
bool CGAffineTransformEqualToTransform(CGAffineTransform t1,CGAffineTransform t2)
{
	return (t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d == t2.d && t1.tx == t2.tx && t1.ty == t2.ty);
}

CGAffineTransform CGAffineTransformInvert(CGAffineTransform t)
{
    float determinant = 1 / (t.a * t.d - t.b * t.c);

    return __CGAffineTransformMake(determinant * t.d, -determinant * t.b, -determinant * t.c, determinant * t.a,
							determinant * (t.c * t.ty - t.d * t.tx), determinant * (t.b * t.tx - t.a * t.ty) );
}
}//namespace   cocos2d 
