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

#include "CCGeometry.h"

// implementation of CCPoint
namespace   cocos2d {

CCPoint::CCPoint(void)
{
	x = 0;
	y = 0;
}

CCPoint::CCPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool CCPoint::CCPointEqualToPoint(const CCPoint& point1, const CCPoint& point2)
{
	return ((point1.x == point2.x) && (point1.y == point2.y));
}

// implementation of CCSize

CCSize::CCSize(void)
{
	width = 0;
	height = 0;
}

CCSize::CCSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

bool CCSize::CCSizeEqualToSize(const CCSize& size1, const CCSize& size2)
{
	return ((size1.width == size2.width) && (size1.height == size2.height));
}

// implementation of CCRect

CCRect::CCRect(void)
{
	origin.x = 0;
	origin.y = 0;

	size.width = 0;
	size.height = 0;
}

CCRect::CCRect(float x, float y, float width, float height)
{
	// Only support that, the width and height > 0
	CC_ASSERT(width >= 0 && height >= 0);

	origin.x = x;
	origin.y = y;

	size.width = width;
	size.height = height;
}

bool CCRect::CCRectEqualToRect(const CCRect& rect1, const CCRect& rect2)
{
	return (CCPoint::CCPointEqualToPoint(rect1.origin, rect2.origin)
		&& CCSize::CCSizeEqualToSize(rect1.size, rect2.size));
}

CGFloat CCRect::CCRectGetMaxX(const CCRect& rect)
{
	return rect.origin.x + rect.size.width;
}

CGFloat CCRect::CCRectGetMidX(const CCRect& rect)
{
	return (float)(rect.origin.x + rect.size.width / 2.0);
}

CGFloat CCRect::CCRectGetMinX(const CCRect& rect)
{
	return rect.origin.x;
}

CGFloat CCRect::CCRectGetMaxY(const CCRect& rect)
{
	return rect.origin.y + rect.size.height;
}

CGFloat CCRect::CCRectGetMidY(const CCRect& rect)
{
	return (float)(rect.origin.y + rect.size.height / 2.0);
}

CGFloat CCRect::CCRectGetMinY(const CCRect& rect)
{
	return rect.origin.y;
}

bool CCRect::CCRectContainsPoint(const CCRect& rect, const CCPoint& point)
{
    bool bRet = false;

	if (point.x >= CCRectGetMinX(rect) && point.x <= CCRectGetMaxX(rect)
		&& point.y >= CCRectGetMinY(rect) && point.y <= CCRectGetMaxY(rect))
	{
		bRet = true;
	}

	return bRet;
}

bool CCRect::CCRectIntersectsRect(const CCRect& rectA, const CCRect& rectB)
{
	return !(CCRectGetMaxX(rectA) < CCRectGetMinX(rectB)||
			CCRectGetMaxX(rectB) < CCRectGetMinX(rectA)||
			CCRectGetMaxY(rectA) < CCRectGetMinY(rectB)||
			CCRectGetMaxY(rectB) < CCRectGetMinY(rectA));
}

}//namespace   cocos2d {
