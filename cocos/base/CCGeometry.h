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

#include "base/CCPlatformMacros.h"
#include "2d/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN

USING_NS_CC_MATH;

/**
 * @addtogroup data_structures
 * @{
 */

// for Vector2 assignement operator and copy constructor
class CC_DLL Size;

CC_DEPRECATED_ATTRIBUTE typedef Vector2 Point;

class CC_DLL Size
{
public:
    float width;
    float height;
public:
    operator Vector2() const
    {
        return Vector2(width, height);
    }

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
    explicit Size(const Vector2& point);
    /**
     * @js NA
     * @lua NA
     */
    Size& operator= (const Size& other);
    /**
     * @js NA
     * @lua NA
     */
    Size& operator= (const Vector2& point);
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
    Vector2 origin;
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
    bool containsPoint(const Vector2& point) const;
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
