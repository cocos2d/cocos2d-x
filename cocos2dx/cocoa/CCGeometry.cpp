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
#include "ccMacros.h"

// implementation of CCPoint
NS_CC_BEGIN

CCPoint::CCPoint(void)
{
    setPoint(0.0f, 0.0f);
}

CCPoint::CCPoint(float x, float y)
{
    setPoint(x, y);
}

CCPoint::CCPoint(const CCPoint& other)
{
    setPoint(other.x, other.y);
}

CCPoint& CCPoint::operator= (const CCPoint& other)
{
    setPoint(other.x, other.y);
    return *this;
}

void CCPoint::setPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

CCObject* CCPoint::copyWithZone(CCZone* pZone)
{
    CCPoint* pRet = new CCPoint();
    pRet->setPoint(this->x, this->y);
    return pRet;
}

bool CCPoint::CCPointEqualToPoint(const CCPoint& point1, const CCPoint& point2)
{
    return ((point1.x == point2.x) && (point1.y == point2.y));
}

// implementation of CCSize

CCSize::CCSize(void)
{
    setSize(0.0f, 0.0f);
}

CCSize::CCSize(float width, float height)
{
    setSize(width, height);
}

CCSize::CCSize(const CCSize& other)
{
    setSize(other.width, other.height);
}

CCSize& CCSize::operator= (const CCSize& other)
{
    setSize(other.width, other.height);
    return *this;
}

void CCSize::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

CCObject* CCSize::copyWithZone(CCZone* pZone)
{
    CCSize* pRet = new CCSize();
    pRet->setSize(this->width, this->width);
    return pRet;
}

bool CCSize::CCSizeEqualToSize(const CCSize& size1, const CCSize& size2)
{
    return ((size1.width == size2.width) && (size1.height == size2.height));
}

// implementation of CCRect

CCRect::CCRect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

CCRect::CCRect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}

CCRect::CCRect(const CCRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

CCRect& CCRect::operator= (const CCRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void CCRect::setRect(float x, float y, float width, float height)
{
    // Only support that, the width and height > 0
    CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

CCObject* CCRect::copyWithZone(CCZone* pZone)
{
    CCRect* pRet = new CCRect();
    pRet->setRect(this->origin.x, this->origin.y, this->size.width, this->size.height);
    return pRet;
}

bool CCRect::CCRectEqualToRect(const CCRect& rect1, const CCRect& rect2)
{
    return (CCPoint::CCPointEqualToPoint(rect1.origin, rect2.origin)
        && CCSize::CCSizeEqualToSize(rect1.size, rect2.size));
}

CCFloat CCRect::CCRectGetMaxX(const CCRect& rect)
{
    return rect.origin.x + rect.size.width;
}

CCFloat CCRect::CCRectGetMidX(const CCRect& rect)
{
    return (float)(rect.origin.x + rect.size.width / 2.0);
}

CCFloat CCRect::CCRectGetMinX(const CCRect& rect)
{
    return rect.origin.x;
}

CCFloat CCRect::CCRectGetMaxY(const CCRect& rect)
{
    return rect.origin.y + rect.size.height;
}

CCFloat CCRect::CCRectGetMidY(const CCRect& rect)
{
    return (float)(rect.origin.y + rect.size.height / 2.0);
}

CCFloat CCRect::CCRectGetMinY(const CCRect& rect)
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

NS_CC_END
