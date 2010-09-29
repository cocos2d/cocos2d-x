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

#ifndef __COCOS_CGGEMETRY_H__
#define __COCOS_CGGEMETRY_H__

#include "ccxCommon.h"
namespace   cocos2d {

typedef float CGFloat;

class CCX_DLL CGPoint
{
public:
	float x;
	float y;

public:

	CGPoint();
	CGPoint(float x, float y);

public:
	static bool CGPointEqualToPoint(const CGPoint& point1, const CGPoint& point2);
};

class CCX_DLL CGSize
{
public:
	float width;
	float height;

public:
	CGSize();
	CGSize(float width, float height);

public:
	static bool CGSizeEqualToSize(const CGSize& size1, const CGSize& size2);
};

class CCX_DLL CGRect
{
public:
	CGPoint origin;
	CGSize  size;

public:
	CGRect();	
	CGRect(float x, float y, float width, float height);

public:
	// return the leftmost x-value of 'rect'
	static CGFloat CGRectGetMinX(const CGRect& rect);

	// return the rightmost x-value of 'rect'
	static CGFloat CGRectGetMaxX(const CGRect& rect);

	// return the midpoint x-value of 'rect'
	static CGFloat CGRectGetMidX(const CGRect& rect);

	// Return the bottommost y-value of `rect'
	static CGFloat CGRectGetMinY(const CGRect& rect);

	// Return the topmost y-value of `rect'
	static CGFloat CGRectGetMaxY(const CGRect& rect);

	// Return the midpoint y-value of `rect'
	static CGFloat CGRectGetMidY(const CGRect& rect);

	static bool CGRectEqualToRect(const CGRect& rect1, const CGRect& rect2);

    static bool CGRectContainsPoint(const CGRect& rect, const CGPoint& point);

	static bool CGRectIntersectsRect(const CGRect& rectA, const CGRect& rectB);
};


#define CGPointMake(x, y) CGPoint((x), (y))
#define CGSizeMake(width, height) CGSize((width), (height))
#define CGRectMake(x, y, width, height) CGRect((x), (y), (width), (height))


const CGPoint CGPointZero = CGPointMake(0,0);

/* The "zero" size -- equivalent to CGSizeMake(0, 0). */ 
const CGSize CGSizeZero = CGSizeMake(0,0);

/* The "zero" rectangle -- equivalent to CGRectMake(0, 0, 0, 0). */ 
const CGRect CGRectZero = CGRectMake(0,0,0,0);

}//namespace   cocos2d 

#endif // __COCOS_CGGEMETRY_H__
