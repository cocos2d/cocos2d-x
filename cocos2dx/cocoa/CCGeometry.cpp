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

CCPoint::CCPoint(void) : x(0), y(0)
{
}

CCPoint::CCPoint(float x, float y) : x(x), y(y)
{
}

CCPoint::CCPoint(const CCPoint& other) : x(other.x), y(other.y)
{
}

CCPoint::CCPoint(const CCSize& size) : x(size.width), y(size.height)
{
}

CCPoint& CCPoint::operator= (const CCPoint& other)
{
    setPoint(other.x, other.y);
    return *this;
}

CCPoint& CCPoint::operator= (const CCSize& size)
{
    setPoint(size.width, size.height);
    return *this;
}

CCPoint CCPoint::operator+(const CCPoint& right) const
{
    return CCPoint(this->x + right.x, this->y + right.y);
}

CCPoint CCPoint::operator-(const CCPoint& right) const
{
    return CCPoint(this->x - right.x, this->y - right.y);
}

CCPoint CCPoint::operator-() const
{
	return CCPoint(-x, -y);
}

CCPoint CCPoint::operator*(float a) const
{
    return CCPoint(this->x * a, this->y * a);
}

CCPoint CCPoint::operator/(float a) const
{
	CCAssert(a, "CCPoint division by 0.");
    return CCPoint(this->x / a, this->y / a);
}

void CCPoint::setPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool CCPoint::equals(const CCPoint& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
        && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool CCPoint::fuzzyEquals(const CCPoint& b, float var) const
{
    if(x - var <= b.x && b.x <= x + var)
        if(y - var <= b.y && b.y <= y + var)
            return true;
    return false;
}

float CCPoint::getAngle(const CCPoint& other) const
{
    CCPoint a2 = normalize();
    CCPoint b2 = other.normalize();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}

CCPoint CCPoint::rotateByAngle(const CCPoint& pivot, float angle) const
{
    return pivot + (*this - pivot).rotate(CCPoint::forAngle(angle));
}

// implementation of CCSize

CCSize::CCSize(void) : width(0), height(0)
{
}

CCSize::CCSize(float width, float height) : width(width), height(height)
{
}

CCSize::CCSize(const CCSize& other) : width(other.width), height(other.height)
{
}

CCSize::CCSize(const CCPoint& point) : width(point.x), height(point.y)
{
}

CCSize& CCSize::operator= (const CCSize& other)
{
    setSize(other.width, other.height);
    return *this;
}

CCSize& CCSize::operator= (const CCPoint& point)
{
    setSize(point.x, point.y);
    return *this;
}

CCSize CCSize::operator+(const CCSize& right) const
{
    return CCSize(this->width + right.width, this->height + right.height);
}

CCSize CCSize::operator-(const CCSize& right) const
{
    return CCSize(this->width - right.width, this->height - right.height);
}

CCSize CCSize::operator*(float a) const
{
    return CCSize(this->width * a, this->height * a);
}

CCSize CCSize::operator/(float a) const
{
	CCAssert(a, "CCSize division by 0.");
    return CCSize(this->width / a, this->height / a);
}

void CCSize::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

bool CCSize::equals(const CCSize& target) const
{
    return (fabs(this->width  - target.width)  < FLT_EPSILON)
        && (fabs(this->height - target.height) < FLT_EPSILON);
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
    // CGRect can support width<0 or height<0
    // CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool CCRect::equals(const CCRect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
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
    return origin.y + size.height;
}

float CCRect::getMidY() const
{
    return (float)(origin.y + size.height / 2.0);
}

float CCRect::getMinY() const
{
    return origin.y;
}

bool CCRect::containsPoint(const CCPoint& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool CCRect::intersectsRect(const CCRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

NS_CC_END
