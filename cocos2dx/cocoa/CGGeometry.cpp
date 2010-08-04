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

#include "CGGeometry.h"

// implementation of CGPoint
namespace   cocos2d {

CGPoint::CGPoint(void)
{
	x = 0;
	y = 0;
}

CGPoint::CGPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool CGPoint::CGPointEqualToPoint(CGPoint point1, CGPoint point2)
{
	return ((point1.x == point2.x) && (point1.y == point2.y));
}

// implementation of CGSize

CGSize::CGSize(void)
{
	width = 0;
	height = 0;
}

CGSize::CGSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

bool CGSize::CGSizeEqualToSize(CGSize size1, CGSize size2)
{
	return ((size1.width == size2.width) && (size1.height == size2.height));
}

// implementation of CGRect

CGRect::CGRect(void)
{
	origin.x = 0;
	origin.y = 0;

	size.width = 0;
	size.height = 0;
}

CGRect::CGRect(float x, float y, float width, float height)
{
	origin.x = x;
	origin.y = y;

	size.width = width;
	size.height = height;
}

bool CGRect::CGRectEqualToRect(CGRect rect1, CGRect rect2)
{
	return (CGPoint::CGPointEqualToPoint(rect1.origin, rect2.origin)
		&& CGSize::CGSizeEqualToSize(rect1.size, rect2.size));
}

CGFloat CGRect::CGRectGetMaxX(CGRect rect)
{
	return rect.origin.x + rect.size.width;
}

CGFloat CGRect::CGRectGetMidX(CGRect rect)
{
	return (float)(rect.origin.x + rect.size.width / 2.0);
}

CGFloat CGRect::CGRectGetMinX(CGRect rect)
{
	return rect.origin.x;
}

CGFloat CGRect::CGRectGetMaxY(CGRect rect)
{
	return rect.origin.y + rect.size.height;
}

CGFloat CGRect::CGRectGetMidY(CGRect rect)
{
	return (float)(rect.origin.y + rect.size.height / 2.0);
}

CGFloat CGRect::CGRectGetMinY(CGRect rect)
{
	return rect.origin.y;
}

bool CGRect::CGRectContainsPoint(CGRect rect, CGPoint point)
{
    bool bRet = false;

	if (point.x >= CGRectGetMinX(rect) && point.x <= CGRectGetMaxX(rect)
		&& point.y >= CGRectGetMinY(rect) && point.y <= CGRectGetMaxY(rect))
	{
		bRet = true;
	}

	return bRet;
}
}//namespace   cocos2d {
