/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#include "CCPlatformMacros.h"
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
    /**
     * @js NA
     */
    Point();
    /**
     * @js NA
     */
    Point(float x, float y);
    /**
     * @js NA
     * @lua NA
     */
    Point(const Point& other);
    /**
     * @js NA
     * @lua NA
     */
    explicit Point(const Size& size);
    /**
     * @js NA
     * @lua NA
     */
    Point& operator= (const Point& other);
    /**
     * @js NA
     * @lua NA
     */
    Point& operator= (const Size& size);
    /**
     * @js NA
     * @lua NA
     */
    Point operator+(const Point& right) const;
    /**
     * @js NA
     * @lua NA
     */
    Point& operator+=(const Point& right);
    /**
     * @js NA
     * @lua NA
     */
    Point operator-(const Point& right) const;
    /**
     * @js NA
     * @lua NA
     */
    Point& operator-=(const Point& right);
    /**
     * @js NA
     * @lua NA
     */
    Point operator-() const;
    /**
     * @js NA
     * @lua NA
     */
    bool operator==(const Point& right);
    /**
     * @js NA
     * @lua NA
     */
    bool operator!=(const Point& right);
    /**
     * @js NA
     * @lua NA
     */
    bool operator==(const Point& right) const;
    /**
     * @js NA
     * @lua NA
     */
    bool operator!=(const Point& right) const;
    /**
     * @js NA
     * @lua NA
     */
    Point operator*(float a) const;
    /**
     * @js NA
     * @lua NA
     */
    Point operator/(float a) const;
    /**
     * @js NA
     * @lua NA
     */
    void setPoint(float x, float y);
    /**
     * @js NA
     */
    bool equals(const Point& target) const;
    
    /** @returns if points have fuzzy equality which means equal with some degree of variance.
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    bool fuzzyEquals(const Point& target, float variance) const;

    /** Calculates distance between point an origin
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** Calculates the square length of a Point (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** Calculates the square distance between two points (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistanceSq(const Point& other) const {
        return (*this - other).getLengthSq();
    };

    /** Calculates the distance between two points
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistance(const Point& other) const {
        return (*this - other).getLength();
    };

    /** @returns the angle in radians between this vector and the x axis
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns the angle in radians between two vector directions
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    float getAngle(const Point& other) const;

    /** Calculates dot product of two points.
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float dot(const Point& other) const {
        return x*other.x + y*other.y;
    };

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float cross(const Point& other) const {
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return Point
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Point getPerp() const {
        return Point(-y, x);
    };
    
    /** Calculates midpoint between two points.
     @return Point
     @since v3.0
     * @js NA
     * @lua NA
     */
    inline Point getMidpoint(const Point& other) const
    {
        return Point((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** Clamp a point between from and to.
     @since v3.0
     * @js NA
     * @lua NA
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
     * @js NA
     * @lua NA
     */
    inline Point compOp(std::function<float(float)> function) const
    {
        return Point(function(x), function(y));
    }

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return Point
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Point getRPerp() const {
        return Point(y, -x);
    };

    /** Calculates the projection of this over other.
     @return Point
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Point project(const Point& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return Point vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Point rotate(const Point& other) const {
        return Point(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return Point vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Point unrotate(const Point& other) const {
        return Point(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Returns point multiplied to a length of 1.
     * If the point is 0, it returns (1, 0)
     @return Point
     @since v2.1.4
     * @js NA
     * @lua NA
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
     * @js NA
     * @lua NA
     */
    inline Point lerp(const Point& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    Point rotateByAngle(const Point& pivot, float angle) const;

    /**
     * @js NA
     * @lua NA
     */
    static inline Point forAngle(const float a)
    {
    	return Point(cosf(a), sinf(a));
    }
    
    /** A general line-line intersection test
     @param A   the startpoint for the first line L1 = (A - B)
     @param B   the endpoint for the first line L1 = (A - B)
     @param C   the startpoint for the second line L2 = (C - D)
     @param D   the endpoint for the second line L2 = (C - D)
     @param S   the range for a hitpoint in L1 (p = A + S*(B - A))
     @param T   the range for a hitpoint in L2 (p = C + T*(D - C))
     @returns   whether these two lines interects.

     Note that to truly test intersection for segments we have to make
     sure that S & T lie within [0..1] and for rays, make sure S & T > 0
     the hit point is        C + T * (D - C);
     the hit point also is   A + S * (B - A);
     @since 3.0
     * @js NA
     * @lua NA
     */
    static bool isLineIntersect(const Point& A, const Point& B,
                                 const Point& C, const Point& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**
     returns true if Line A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineOverlap(const Point& A, const Point& B,
                                const Point& C, const Point& D);
    
    /**
     returns true if Line A-B parallel with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineParallel(const Point& A, const Point& B,
                   const Point& C, const Point& D);
    
    /**
     returns true if Segment A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentOverlap(const Point& A, const Point& B,
                                 const Point& C, const Point& D,
                                 Point* S = nullptr, Point* E = nullptr);
    
    /**
     returns true if Segment A-B intersects with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D);
    
    /**
     returns the intersection point of line A-B, C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static Point getIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D);
    
    /** equals to Point(0,0) */
    static const Point ZERO;
    /** equals to Point(0.5, 0.5) */
    static const Point ANCHOR_MIDDLE;
    /** equals to Point(0, 0) */
    static const Point ANCHOR_BOTTOM_LEFT;
    /** equals to Point(0, 1) */
    static const Point ANCHOR_TOP_LEFT;
    /** equals to Point(1, 0) */
    static const Point ANCHOR_BOTTOM_RIGHT;
    /** equals to Point(1, 1) */
    static const Point ANCHOR_TOP_RIGHT;
    /** equals to Point(1, 0.5) */
    static const Point ANCHOR_MIDDLE_RIGHT;
    /** equals to Point(0, 0.5) */
    static const Point ANCHOR_MIDDLE_LEFT;
    /** equals to Point(0.5, 1) */
    static const Point ANCHOR_MIDDLE_TOP;
    /** equals to Point(0.5, 0) */
    static const Point ANCHOR_MIDDLE_BOTTOM;
    
private:
    // returns true if segment A-B intersects with segment C-D. S->E is the ovderlap part
    static bool isOneDimensionSegmentOverlap(float A, float B, float C, float D, float *S, float * E);
    
    // cross procuct of 2 vector. A->B X C->D
    static float crossProduct2Vector(const Point& A, const Point& B, const Point& C, const Point& D) { return (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y); }
};

class CC_DLL Size
{
public:
    float width;
    float height;

public:
    /**
     * @js NA
     */
    Size();
    /**
     * @js NA
     */
    Size(float width, float height);
    /**
     * @js NA
     * @lua NA
     */
    Size(const Size& other);
    /**
     * @js NA
     * @lua NA
     */
    explicit Size(const Point& point);
    /**
     * @js NA
     * @lua NA
     */
    Size& operator= (const Size& other);
    /**
     * @js NA
     * @lua NA
     */
    Size& operator= (const Point& point);
    /**
     * @js NA
     * @lua NA
     */
    Size operator+(const Size& right) const;
    /**
     * @js NA
     * @lua NA
     */
    Size operator-(const Size& right) const;
    /**
     * @js NA
     * @lua NA
     */
    Size operator*(float a) const;
    /**
     * @js NA
     * @lua NA
     */
    Size operator/(float a) const;
    /**
     * @js NA
     * @lua NA
     */
    void setSize(float width, float height);
    /**
     * @js NA
     */
    bool equals(const Size& target) const;
    
    static const Size ZERO;
};

class CC_DLL Rect
{
public:
    Point origin;
    Size  size;

public:
    /**
     * @js NA
     */
    Rect();
    /**
     * @js NA
     */
    Rect(float x, float y, float width, float height);
    /**
     * @js NA
     * @lua NA
     */
    Rect(const Rect& other);
    /**
     * @js NA
     * @lua NA
     */
    Rect& operator= (const Rect& other);
    /**
     * @js NA
     * @lua NA
     */
    void setRect(float x, float y, float width, float height);
    /**
     * @js NA
     */
    float getMinX() const; /// return the leftmost x-value of current rect
    /**
     * @js NA
     */
    float getMidX() const; /// return the midpoint x-value of current rect
    /**
     * @js NA
     */
    float getMaxX() const; /// return the rightmost x-value of current rect
    /**
     * @js NA
     */
    float getMinY() const; /// return the bottommost y-value of current rect
    /**
     * @js NA
     */
    float getMidY() const; /// return the midpoint y-value of current rect
    /**
     * @js NA
     */
    float getMaxY() const; /// return the topmost y-value of current rect
    /**
     * @js NA
     */
    bool equals(const Rect& rect) const;
    /**
     * @js NA
     */
    bool containsPoint(const Point& point) const;
    /**
     * @js NA
     */
    bool intersectsRect(const Rect& rect) const;
    /**
     * @js NA
     * @lua NA
     */
    Rect unionWithRect(const Rect & rect) const;
    
    static const Rect ZERO;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCGEMETRY_H__
