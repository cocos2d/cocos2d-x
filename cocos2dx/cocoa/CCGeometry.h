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

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"
#include <math.h>

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

// for CCPoint assignement operator and copy constructor
class CC_DLL CCSize;

class CC_DLL CCPoint
{
public:
    float x;
    float y;

public:
    CCPoint();
    CCPoint(float x, float y);
    CCPoint(const CCPoint& other);
    CCPoint(const CCSize& size);
    CCPoint& operator= (const CCPoint& other);
    CCPoint& operator= (const CCSize& size);
    CCPoint operator+(const CCPoint& right) const;
    CCPoint operator-(const CCPoint& right) const;
    CCPoint operator-() const;
    CCPoint operator*(float a) const;
    CCPoint operator/(float a) const;
    void setPoint(float x, float y);
    bool equals(const CCPoint& target) const;
    bool fuzzyEquals(const CCPoint& target, float variance) const;

    inline float length() const {
        return sqrtf(x*x + y*y);
    };

    inline float lengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    inline float angle() const {
        return atan2f(y, x);
    };

    float angle(const CCPoint& other) const;

    inline float dot(const CCPoint& other) const {
        return x*other.x + y*other.y;
    };

    inline float cross(const CCPoint& other) const {
        return x*other.y - y*other.x;
    };

    inline CCPoint perp() const {
        return CCPoint(-y, x);
    };

    inline CCPoint rPerp() const {
        return CCPoint(y, -x);
    };

    inline CCPoint project(const CCPoint& other) const {
        return other * dot(other)/other.dot(other);
    };

    inline CCPoint rotate(const CCPoint& other) const {
        return CCPoint(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    inline CCPoint unrotate(const CCPoint& other) const {
        return CCPoint(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    inline CCPoint normalize() const {
        return *this / length();
    };

    inline CCPoint lerp(const CCPoint& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    CCPoint rotateByAngle(const CCPoint& pivot, float angle) const;

    static inline CCPoint forAngle(const float a)
    {
    	return CCPoint(cosf(a), sinf(a));
    }
};

class CC_DLL CCSize
{
public:
    float width;
    float height;

public:
    CCSize();
    CCSize(float width, float height);
    CCSize(const CCSize& other);
    CCSize(const CCPoint& point);
    CCSize& operator= (const CCSize& other);
    CCSize& operator= (const CCPoint& point);
    CCSize operator+(const CCSize& right) const;
    CCSize operator-(const CCSize& right) const;
    CCSize operator*(float a) const;
    CCSize operator/(float a) const;
    void setSize(float width, float height);
    bool equals(const CCSize& target) const;
};

class CC_DLL CCRect
{
public:
    CCPoint origin;
    CCSize  size;

public:
    CCRect();
    CCRect(float x, float y, float width, float height);
    CCRect(const CCRect& other);
    CCRect& operator= (const CCRect& other);
    void setRect(float x, float y, float width, float height);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect
    bool equals(const CCRect& rect) const;   
    bool containsPoint(const CCPoint& point) const;
    bool intersectsRect(const CCRect& rect) const;
};


#define CCPointMake(x, y) CCPoint((float)(x), (float)(y))
#define CCSizeMake(width, height) CCSize((float)(width), (float)(height))
#define CCRectMake(x, y, width, height) CCRect((float)(x), (float)(y), (float)(width), (float)(height))


const CCPoint CCPointZero = CCPointMake(0,0);

/* The "zero" size -- equivalent to CCSizeMake(0, 0). */ 
const CCSize CCSizeZero = CCSizeMake(0,0);

/* The "zero" rectangle -- equivalent to CCRectMake(0, 0, 0, 0). */ 
const CCRect CCRectZero = CCRectMake(0,0,0,0);

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCGEMETRY_H__
