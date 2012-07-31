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

bool CCPoint::isEqualTo(const CCPoint& point) const
{
    return ((this->x == point.x) && (this->y == point.y));
}

// to be deprecated
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

bool CCSize::isEqualTo(const CCSize& size) const
{
    return ((this->width == size.width) && (this->height == size.height));
}

// to be deprecated
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

float CCRect::getMaxX() const
{
    return (float)(origin.x + size.width);
}

float CCRect::getMidX() const
{
    return (float)(origin.x + size.width / 2.0);
}

float CCRect::getMinX() const
{
    return origin.x;
}

float CCRect::getMaxY() const
{
    return (float)(origin.y + size.height);
}

float CCRect::getMidY() const
{
    return (float)(origin.y + size.height / 2.0);
}

float CCRect::getMinY() const
{
    return origin.y;
}

bool CCRect::isEqualTo(const CCRect& target) const
{    
    return ( origin.isEqualTo(target.origin) &&
             size.isEqualTo(target.size) );
}

bool CCRect::isContainPoint(const CCPoint& point) const
{
    bool bRet = false;
    
    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }
    
    return bRet;
}

bool CCRect::isIntersectRect(const CCRect& target) const
{
    return !(this->getMaxX() < target.getMinX()||
             target.getMaxX() < this->getMinX()||
             this->getMaxY() < target.getMinY()||
             target.getMaxY() < this->getMinY());
}

// to be deprecated
bool CCRect::CCRectEqualToRect(const CCRect& rect1, const CCRect& rect2)
{
    return (CCPoint::CCPointEqualToPoint(rect1.origin, rect2.origin)
        && CCSize::CCSizeEqualToSize(rect1.size, rect2.size));
}


bool CCRect::CCRectContainsPoint(const CCRect& rect, const CCPoint& point)
{
    return rect.isContainPoint(point);
}

bool CCRect::CCRectIntersectsRect(const CCRect& rectA, const CCRect& rectB)
{
    return rectA.isIntersectRect(rectB);
}

NS_CC_END
