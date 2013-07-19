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

#ifndef __CCGEMETRY_H__
#define __CCGEMETRY_H__

#include <math.h>
#include <functional>

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"
#include "ccMacros.h"

NS_CC_BEGIN

/** Clamp a value between from and to.
 @since v0.99.1
 */
inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive) {
        CC_SWAP(min_inclusive, max_inclusive, float);
    }
    return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
}

/**
 * @addtogroup data_structures
 * @{
 */

// for Point assignement operator and copy constructor
class CC_DLL Size;

class CC_DLL Point
{
public:
    float x;
    float y;

public:
    Point();
    Point(float x, float y);
    Point(const Point& other);
    Point(const Size& size);
    Point& operator= (const Point& other);
    Point& operator= (const Size& size);
    Point operator+(const Point& right) const;
    Point operator-(const Point& right) const;
    Point operator-() const;
    Point operator*(float a) const;
    Point operator/(float a) const;
    void setPoint(float x, float y);
    bool equals(const Point& target) const;
    
    /** @returns if points have fuzzy equality which means equal with some degree of variance.
     @since v2.1.4
     */
    bool fuzzyEquals(const Point& target, float variance) const;

    /** Calculates distance between point an origin
     @return float
     @since v2.1.4
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** Calculates the square length of a Point (not calling sqrt() )
     @return float
     @since v2.1.4
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** Calculates the square distance between two points (not calling sqrt() )
     @return float
     @since v2.1.4
    */
    inline float getDistanceSq(const Point& other) const {
        return (*this - other).getLengthSq();
    };

    /** Calculates the distance between two points
     @return float
     @since v2.1.4
     */
    inline float getDistance(const Point& other) const {
        return (*this - other).getLength();
    };

    /** @returns the angle in radians between this vector and the x axis
     @since v2.1.4
    */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns the angle in radians between two vector directions
     @since v2.1.4
    */
    float getAngle(const Point& other) const;

    /** Calculates dot product of two points.
     @return float
     @since v2.1.4
     */
    inline float dot(const Point& other) const {
        return x*other.x + y*other.y;
    };

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     */
    inline float cross(const Point& other) const {
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return Point
     @since v2.1.4
     */
    inline Point getPerp() const {
        return Point(-y, x);
    };
    
    /** Calculates midpoint between two points.
     @return Point
     @since v3.0
     */
    inline Point getMidpoint(const Point& other) const
    {
        return Point((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** Clamp a point between from and to.
     @since v3.0
     */
    inline Point getClampPoint(const Point& min_inclusive, const Point& max_inclusive) const
    {
        return Point(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** Run a math operation function on each point component
     * absf, fllorf, ceilf, roundf
     * any function that has the signature: float func(float);
     * For example: let's try to take the floor of x,y
     * p.compOp(floorf);
     @since v3.0
     */
    inline Point compOp(std::function<float(float)> function) const
    {
        return Point(function(x), function(y));
    }

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return Point
     @since v2.1.4
     */
    inline Point getRPerp() const {
        return Point(y, -x);
    };

    /** Calculates the projection of this over other.
     @return Point
     @since v2.1.4
     */
    inline Point project(const Point& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return Point vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline Point rotate(const Point& other) const {
        return Point(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return Point vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline Point unrotate(const Point& other) const {
        return Point(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Returns point multiplied to a length of 1.
     * If the point is 0, it returns (1, 0)
     @return Point
     @since v2.1.4
     */
    inline Point normalize() const {
        float length = getLength();
        if(length == 0.) return Point(1.f, 0);
        return *this / getLength();
    };

    /** Linear Interpolation between two points a and b
     @returns
        alpha == 0 ? a
        alpha == 1 ? b
        otherwise a value between a..b
     @since v2.1.4
     */
    inline Point lerp(const Point& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     */
    Point rotateByAngle(const Point& pivot, float angle) const;

    static inline Point forAngle(const float a)
    {
    	return Point(cosf(a), sinf(a));
    }
    
    /** A general line-line intersection test
     @param p1
     is the startpoint for the first line P1 = (p1 - p2)
     @param p2
     is the endpoint for the first line P1 = (p1 - p2)
     @param p3
     is the startpoint for the second line P2 = (p3 - p4)
     @param p4
     is the endpoint for the second line P2 = (p3 - p4)
     @param s
     is the range for a hitpoint in P1 (pa = p1 + s*(p2 - p1))
     @param t
     is the range for a hitpoint in P3 (pa = p2 + t*(p4 - p3))
     @return bool
     indicating successful intersection of a line
     note that to truly test intersection for segments we have to make
     sure that s & t lie within [0..1] and for rays, make sure s & t > 0
     the hit point is        p3 + t * (p4 - p3);
     the hit point also is    p1 + s * (p2 - p1);
     @since 3.0
     */
    static bool isLineIntersect(const Point& A, const Point& B,
                                 const Point& C, const Point& D,
                                 float *S, float *T);
    
    /*
     returns YES if Segment A-B intersects with segment C-D
     @since v3.0
     */
    static bool isSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D);
    
    /*
     returns the intersection point of line A-B, C-D
     @since v3.0
     */
    static Point getIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D);
    
    static const Point ZERO;
};

class CC_DLL Size
{
public:
    float width;
    float height;

public:
    Size();
    Size(float width, float height);
    Size(const Size& other);
    Size(const Point& point);
    Size& operator= (const Size& other);
    Size& operator= (const Point& point);
    Size operator+(const Size& right) const;
    Size operator-(const Size& right) const;
    Size operator*(float a) const;
    Size operator/(float a) const;
    void setSize(float width, float height);
    bool equals(const Size& target) const;
    
    static const Size ZERO;
};

class CC_DLL Rect
{
public:
    Point origin;
    Size  size;

public:
    Rect();
    Rect(float x, float y, float width, float height);
    Rect(const Rect& other);
    Rect& operator= (const Rect& other);
    void setRect(float x, float y, float width, float height);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect
    bool equals(const Rect& rect) const;   
    bool containsPoint(const Point& point) const;
    bool intersectsRect(const Rect& rect) const;
    Rect unionWithRect(const Rect & rect) const;
    
    static const Rect ZERO;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCGEMETRY_H__
