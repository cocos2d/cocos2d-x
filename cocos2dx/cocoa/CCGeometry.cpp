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

// implementation of Point
NS_CC_BEGIN

Point::Point(void) : x(0), y(0)
{
}

Point::Point(float xx, float yy) : x(xx), y(yy)
{
}

Point::Point(const Point& other) : x(other.x), y(other.y)
{
}

Point::Point(const Size& size) : x(size.width), y(size.height)
{
}

Point& Point::operator= (const Point& other)
{
    setPoint(other.x, other.y);
    return *this;
}

Point& Point::operator= (const Size& size)
{
    setPoint(size.width, size.height);
    return *this;
}

Point Point::operator+(const Point& right) const
{
    return Point(this->x + right.x, this->y + right.y);
}

Point Point::operator-(const Point& right) const
{
    return Point(this->x - right.x, this->y - right.y);
}

Point Point::operator-() const
{
	return Point(-x, -y);
}

Point Point::operator*(float a) const
{
    return Point(this->x * a, this->y * a);
}

Point Point::operator/(float a) const
{
	CCASSERT(a!=0, "CCPoint division by 0.");
    return Point(this->x / a, this->y / a);
}

void Point::setPoint(float xx, float yy)
{
    this->x = xx;
    this->y = yy;
}

bool Point::equals(const Point& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
        && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool Point::fuzzyEquals(const Point& b, float var) const
{
    if(x - var <= b.x && b.x <= x + var)
        if(y - var <= b.y && b.y <= y + var)
            return true;
    return false;
}

float Point::getAngle(const Point& other) const
{
    Point a2 = normalize();
    Point b2 = other.normalize();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}

Point Point::rotateByAngle(const Point& pivot, float angle) const
{
    return pivot + (*this - pivot).rotate(Point::forAngle(angle));
}

bool Point::isLineIntersect(const Point& A, const Point& B,
                            const Point& C, const Point& D,
                            float *S, float *T)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    const float BAx = B.x - A.x;
    const float BAy = B.y - A.y;
    const float DCx = D.x - C.x;
    const float DCy = D.y - C.y;
    const float ACx = A.x - C.x;
    const float ACy = A.y - C.y;
    
    const float denom = DCy*BAx - DCx*BAy;
    
    *S = DCx*ACy - DCy*ACx;
    *T = BAx*ACy - BAy*ACx;
    
    if (denom == 0)
    {
        if (*S == 0 || *T == 0)
        {
            // Lines incident
            return true;
        }
        // Lines parallel and not incident
        return false;
    }
    
    *S = *S / denom;
    *T = *T / denom;
    
    // Point of intersection
    // CGPoint P;
    // P.x = A.x + *S * (B.x - A.x);
    // P.y = A.y + *S * (B.y - A.y);
    
    return true;
}

bool Point::isSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D)
{
    float S, T;
    
    if (isLineIntersect(A, B, C, D, &S, &T )&&
       (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f))
    {
        return true;
    }  
    
    return false;
}

Point Point::getIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D)
{
    float S, T;
    
    if (isLineIntersect(A, B, C, D, &S, &T))
    {
        // Point of intersection
        Point P;
        P.x = A.x + S * (B.x - A.x);
        P.y = A.y + S * (B.y - A.y);
        return P;
    }
    
    return Point::ZERO;
}

const Point Point::ZERO = Point(0, 0);

// implementation of Size

Size::Size(void) : width(0), height(0)
{
}

Size::Size(float w, float h) : width(w), height(h)
{
}

Size::Size(const Size& other) : width(other.width), height(other.height)
{
}

Size::Size(const Point& point) : width(point.x), height(point.y)
{
}

Size& Size::operator= (const Size& other)
{
    setSize(other.width, other.height);
    return *this;
}

Size& Size::operator= (const Point& point)
{
    setSize(point.x, point.y);
    return *this;
}

Size Size::operator+(const Size& right) const
{
    return Size(this->width + right.width, this->height + right.height);
}

Size Size::operator-(const Size& right) const
{
    return Size(this->width - right.width, this->height - right.height);
}

Size Size::operator*(float a) const
{
    return Size(this->width * a, this->height * a);
}

Size Size::operator/(float a) const
{
	CCASSERT(a!=0, "CCSize division by 0.");
    return Size(this->width / a, this->height / a);
}

void Size::setSize(float w, float h)
{
    this->width = w;
    this->height = h;
}

bool Size::equals(const Size& target) const
{
    return (fabs(this->width  - target.width)  < FLT_EPSILON)
        && (fabs(this->height - target.height) < FLT_EPSILON);
}

const Size Size::ZERO = Size(0, 0);

// implementation of Rect

Rect::Rect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}

Rect::Rect(const Rect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

Rect& Rect::operator= (const Rect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void Rect::setRect(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCASSERT(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool Rect::equals(const Rect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
}

float Rect::getMaxX() const
{
    return (float)(origin.x + size.width);
}

float Rect::getMidX() const
{
    return (float)(origin.x + size.width / 2.0);
}

float Rect::getMinX() const
{
    return origin.x;
}

float Rect::getMaxY() const
{
    return origin.y + size.height;
}

float Rect::getMidY() const
{
    return (float)(origin.y + size.height / 2.0);
}

float Rect::getMinY() const
{
    return origin.y;
}

bool Rect::containsPoint(const Point& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool Rect::intersectsRect(const Rect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

Rect Rect::unionWithRect(const Rect & rect) const
{
    float thisLeftX = origin.x;
    float thisRightX = origin.x + size.width;
    float thisTopY = origin.y + size.height;
    float thisBottomY = origin.y;
    
    if (thisRightX < thisLeftX)
    {
        std::swap(thisRightX, thisLeftX);   // This rect has negative width
    }
    
    if (thisTopY < thisBottomY)
    {
        std::swap(thisTopY, thisBottomY);   // This rect has negative height
    }
    
    float otherLeftX = rect.origin.x;
    float otherRightX = rect.origin.x + rect.size.width;
    float otherTopY = rect.origin.y + rect.size.height;
    float otherBottomY = rect.origin.y;
    
    if (otherRightX < otherLeftX)
    {
        std::swap(otherRightX, otherLeftX);   // Other rect has negative width
    }
    
    if (otherTopY < otherBottomY)
    {
        std::swap(otherTopY, otherBottomY);   // Other rect has negative height
    }
    
    float combinedLeftX = std::min(thisLeftX, otherLeftX);
    float combinedRightX = std::max(thisRightX, otherRightX);
    float combinedTopY = std::max(thisTopY, otherTopY);
    float combinedBottomY = std::min(thisBottomY, otherBottomY);
    
    return Rect(combinedLeftX, combinedBottomY, combinedRightX - combinedLeftX, combinedTopY - combinedBottomY);
}

const Rect Rect::ZERO = Rect(0, 0, 0, 0);

NS_CC_END
