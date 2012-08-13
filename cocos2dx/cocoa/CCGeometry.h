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

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCPoint : public CCObject
{
public:
    float x;
    float y;

public:
    CCPoint();
    CCPoint(float x, float y);
    CCPoint(const CCPoint& other);
    CCPoint& operator= (const CCPoint& other);
    void setPoint(float x, float y);
    virtual CCObject* copyWithZone(CCZone* pZone);
    bool equals(const CCPoint& target) const;

public:
    /** @deprecated use CCPoint::equals(const CCPoint&) instead, like p1.equals(p2)
     */
    CC_DEPRECATED_ATTRIBUTE static bool CCPointEqualToPoint(const CCPoint& point1, const CCPoint& point2);
};

class CC_DLL CCSize : public CCObject
{
public:
    float width;
    float height;

public:
    CCSize();
    CCSize(float width, float height);
    CCSize(const CCSize& other);
    CCSize& operator= (const CCSize& other);
    void setSize(float width, float height);
    virtual CCObject* copyWithZone(CCZone* pZone);
    bool equals(const CCSize& target) const;
    
public:
    /** @deprecated use CCSize::equals(const CCSize&) instead, like size1.equals(size2) */
    CC_DEPRECATED_ATTRIBUTE static bool CCSizeEqualToSize(const CCSize& size1, const CCSize& size2);
};

class CC_DLL CCRect : public CCObject
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
    virtual CCObject* copyWithZone(CCZone* pZone);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect
    bool equals(const CCRect& rect) const;   
    bool containsPoint(const CCPoint& point) const;
    bool intersectsRect(const CCRect& rect) const;
    
public:
    /** @deprecated use CCRect::equals(const CCRect&) instead, like r1.equals(r2) */
    CC_DEPRECATED_ATTRIBUTE static bool CCRectEqualToRect(const CCRect& rect1, const CCRect& rect2);
    /** @deprecated use CCRect::containsPoint(const CCPoint&) instead, like rect.containsPoint(point) */
    CC_DEPRECATED_ATTRIBUTE static bool CCRectContainsPoint(const CCRect& rect, const CCPoint& point);
    /** @deprecated use CCRect::intersectsRect(const CCRect&) instead, like r1.intersectsRect(r2) */
    CC_DEPRECATED_ATTRIBUTE static bool CCRectIntersectsRect(const CCRect& rectA, const CCRect& rectB);
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
