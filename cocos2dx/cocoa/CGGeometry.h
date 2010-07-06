/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

class CGPoint
{
public:
	float x;
	float y;

	CGPoint()
	{
		x = 0;
		y = 0;
	}

	CGPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class CGSize
{
public:
	float width;
	float height;

	CGSize()
	{
		width = 0;
		height = 0;
	}

	CGSize(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
};

class CGRect
{
public:
	CGPoint origin;
	CGSize size;

	CGRect()
	{
		origin.x = 0;
		origin.y = 0;

		size.width = 0;
		size.height = 0;
	}

	CGRect(float x, float y, float width, float height)
	{
		origin.x = x;
		origin.y = y;

		size.width = width;
		size.height = height;
	}
};

#define CGPointMake(x, y) CGPoint((x), (y));
#define CGSizeMake(width, height) CGSize((width), (height));
#define CGRectMake(x, y, width, height) CGRect((x), (y), (width), (height));

#endif // __COCOS_CGGEMETRY_H__
