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
