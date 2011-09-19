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

#include "CCCommon.h"

namespace   cocos2d {

typedef float CGFloat;

class CC_DLL CCPoint
{
public:
	float x;
	float y;

public:

	CCPoint();
	CCPoint(float x, float y);

public:
	static bool CCPointEqualToPoint(const CCPoint& point1, const CCPoint& point2);
};

class CC_DLL CCSize
{
public:
	float width;
	float height;

public:
	CCSize();
	CCSize(float width, float height);

public:
	static bool CCSizeEqualToSize(const CCSize& size1, const CCSize& size2);
};

class CC_DLL CCRect
{
public:
	CCPoint origin;
	CCSize  size;

public:
	CCRect();	
	CCRect(float x, float y, float width, float height);

public:
	//! return the leftmost x-value of 'rect'
	static CGFloat CCRectGetMinX(const CCRect& rect);

	//! return the rightmost x-value of 'rect'
	static CGFloat CCRectGetMaxX(const CCRect& rect);

	//! return the midpoint x-value of 'rect'
	static CGFloat CCRectGetMidX(const CCRect& rect);

	//! Return the bottommost y-value of `rect'
	static CGFloat CCRectGetMinY(const CCRect& rect);

	//! Return the topmost y-value of `rect'
	static CGFloat CCRectGetMaxY(const CCRect& rect);

	//! Return the midpoint y-value of `rect'
	static CGFloat CCRectGetMidY(const CCRect& rect);

	static bool CCRectEqualToRect(const CCRect& rect1, const CCRect& rect2);

    static bool CCRectContainsPoint(const CCRect& rect, const CCPoint& point);

	static bool CCRectIntersectsRect(const CCRect& rectA, const CCRect& rectB);
};


#define CCPointMake(x, y) CCPoint((x), (y))
#define CCSizeMake(width, height) CCSize((width), (height))
#define CCRectMake(x, y, width, height) CCRect((x), (y), (width), (height))


const CCPoint CCPointZero = CCPointMake(0,0);

/* The "zero" size -- equivalent to CCSizeMake(0, 0). */ 
const CCSize CCSizeZero = CCSizeMake(0,0);

/* The "zero" rectangle -- equivalent to CCRectMake(0, 0, 0, 0). */ 
const CCRect CCRectZero = CCRectMake(0,0,0,0);

}//namespace   cocos2d 

#endif // __COCOS_CGGEMETRY_H__
