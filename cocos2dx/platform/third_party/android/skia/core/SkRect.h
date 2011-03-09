/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkRect_DEFINED
#define SkRect_DEFINED

#include "SkPoint.h"

/** \struct SkIRect

    SkIRect holds four 32 bit integer coordinates for a rectangle
*/
struct SkIRect {
    int32_t fLeft, fTop, fRight, fBottom;

    /** Return true if the rectangle's width or height are <= 0
    */
    bool isEmpty() const { return fLeft >= fRight || fTop >= fBottom; }

    /** Returns the rectangle's width. This does not check for a valid rectangle (i.e. left <= right)
        so the result may be negative.
    */
    int width() const { return fRight - fLeft; }

    /** Returns the rectangle's height. This does not check for a valid rectangle (i.e. top <= bottom)
        so the result may be negative.
    */
    int height() const { return fBottom - fTop; }

    friend int operator==(const SkIRect& a, const SkIRect& b)
    {
        return !memcmp(&a, &b, sizeof(a));
    }
    friend int operator!=(const SkIRect& a, const SkIRect& b)
    {
        return memcmp(&a, &b, sizeof(a));
    }

    /** Set the rectangle to (0,0,0,0)
    */
    void setEmpty() { memset(this, 0, sizeof(*this)); }

    void set(int32_t left, int32_t top, int32_t right, int32_t bottom)
    {
        fLeft   = left;
        fTop    = top;
        fRight  = right;
        fBottom = bottom;
    }

    /** Offset set the rectangle by adding dx to its left and right,
        and adding dy to its top and bottom.
    */
    void offset(int32_t dx, int32_t dy)
    {
        fLeft   += dx;
        fTop    += dy;
        fRight  += dx;
        fBottom += dy;
    }

    /** Inset the rectangle by (dx,dy). If dx is positive, then the sides are moved inwards,
        making the rectangle narrower. If dx is negative, then the sides are moved outwards,
        making the rectangle wider. The same hods true for dy and the top and bottom.
    */
    void inset(int32_t dx, int32_t dy)
    {
        fLeft   += dx;
        fTop    += dy;
        fRight  -= dx;
        fBottom -= dy;
    }
    /** Returns true if (x,y) is inside the rectangle and the rectangle is not
        empty. The left and top are considered to be inside, while the right
        and bottom are not. Thus for the rectangle (0, 0, 5, 10), the
        points (0,0) and (0,9) are inside, while (-1,0) and (5,9) are not.
    */
    bool contains(int32_t x, int32_t y) const
    {
        return  (unsigned)(x - fLeft) < (unsigned)(fRight - fLeft) &&
                (unsigned)(y - fTop) < (unsigned)(fBottom - fTop);
    }

    /** Returns true if the 4 specified sides of a rectangle are inside or equal to this rectangle.
        If either rectangle is empty, contains() returns false.
    */
    bool contains(int32_t left, int32_t top, int32_t right, int32_t bottom) const
    {
        return  left < right && top < bottom && !this->isEmpty() && // check for empties
                fLeft <= left && fTop <= top &&
                fRight >= right && fBottom >= bottom;
    }

    /** Returns true if the specified rectangle r is inside or equal to this rectangle.
    */
    bool contains(const SkIRect& r) const
    {
        return  !r.isEmpty() && !this->isEmpty() &&     // check for empties
                fLeft <= r.fLeft && fTop <= r.fTop &&
                fRight >= r.fRight && fBottom >= r.fBottom;
    }

    /** Return true if this rectangle contains the specified rectangle.
		For speed, this method does not check if either this or the specified
		rectangles are empty, and if either is, its return value is undefined.
		In the debugging build however, we assert that both this and the
		specified rectangles are non-empty.
    */
    bool containsNoEmptyCheck(int32_t left, int32_t top,
							  int32_t right, int32_t bottom) const
    {
		SkASSERT(fLeft < fRight && fTop < fBottom);
        SkASSERT(left < right && top < bottom);

        return fLeft <= left && fTop <= top &&
			   fRight >= right && fBottom >= bottom;
    }
    
    /** If r intersects this rectangle, return true and set this rectangle to that
        intersection, otherwise return false and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(const SkIRect& r)
    {
        SkASSERT(&r);
        return this->intersect(r.fLeft, r.fTop, r.fRight, r.fBottom);
    }

    /** If rectangles a and b intersect, return true and set this rectangle to
        that intersection, otherwise return false and do not change this
        rectangle. If either rectangle is empty, do nothing and return false.
    */
    bool intersect(const SkIRect& a, const SkIRect& b)
    {
        SkASSERT(&a && &b);
        
        if (!a.isEmpty() && !b.isEmpty() &&
            a.fLeft < b.fRight && b.fLeft < a.fRight &&
            a.fTop < b.fBottom && b.fTop < a.fBottom)
        {
            fLeft   = SkMax32(a.fLeft,   b.fLeft);
            fTop    = SkMax32(a.fTop,    b.fTop);
            fRight  = SkMin32(a.fRight,  b.fRight);
            fBottom = SkMin32(a.fBottom, b.fBottom);
            return true;
        }
        return false;
    }
    
    /** If rectangles a and b intersect, return true and set this rectangle to
        that intersection, otherwise return false and do not change this
        rectangle. For speed, no check to see if a or b are empty is performed.
        If either is, then the return result is undefined. In the debug build,
        we assert that both rectangles are non-empty.
    */
    bool intersectNoEmptyCheck(const SkIRect& a, const SkIRect& b)
    {
        SkASSERT(&a && &b);
        SkASSERT(!a.isEmpty() && !b.isEmpty());
        
        if (a.fLeft < b.fRight && b.fLeft < a.fRight &&
            a.fTop < b.fBottom && b.fTop < a.fBottom)
        {
            fLeft   = SkMax32(a.fLeft,   b.fLeft);
            fTop    = SkMax32(a.fTop,    b.fTop);
            fRight  = SkMin32(a.fRight,  b.fRight);
            fBottom = SkMin32(a.fBottom, b.fBottom);
            return true;
        }
        return false;
    }

    /** If the rectangle specified by left,top,right,bottom intersects this rectangle,
        return true and set this rectangle to that intersection,
        otherwise return false and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(int32_t left, int32_t top, int32_t right, int32_t bottom)
    {
        if (left < right && top < bottom && !this->isEmpty() &&
            fLeft < right && left < fRight && fTop < bottom && top < fBottom)
        {
            if (fLeft < left) fLeft = left;
            if (fTop < top) fTop = top;
            if (fRight > right) fRight = right;
            if (fBottom > bottom) fBottom = bottom;
            return true;
        }
        return false;
    }
    
    /** Returns true if a and b are not empty, and they intersect
    */
    static bool Intersects(const SkIRect& a, const SkIRect& b)
    {
        return  !a.isEmpty() && !b.isEmpty() &&              // check for empties
                a.fLeft < b.fRight && b.fLeft < a.fRight &&
                a.fTop < b.fBottom && b.fTop < a.fBottom;
    }
    
    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(int32_t left, int32_t top, int32_t right, int32_t bottom);

    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(const SkIRect& r)
    {
        this->join(r.fLeft, r.fTop, r.fRight, r.fBottom);
    }

    /** Swap top/bottom or left/right if there are flipped.
        This can be called if the edges are computed separately,
        and may have crossed over each other.
        When this returns, left <= right && top <= bottom
    */
    void sort();
};

/** \struct SkRect
*/
struct SkRect {
    SkScalar    fLeft, fTop, fRight, fBottom;

    /** Return true if the rectangle's width or height are <= 0
    */
    bool        isEmpty() const { return fLeft >= fRight || fTop >= fBottom; }
    SkScalar    width() const { return fRight - fLeft; }
    SkScalar    height() const { return fBottom - fTop; }
    SkScalar    centerX() const { return SkScalarHalf(fLeft + fRight); }
    SkScalar    centerY() const { return SkScalarHalf(fTop + fBottom); }

    friend int operator==(const SkRect& a, const SkRect& b)
    {
        return !memcmp(&a, &b, sizeof(a));
    }
    friend int operator!=(const SkRect& a, const SkRect& b)
    {
        return memcmp(&a, &b, sizeof(a));
    }

    /** return the 4 points that enclose the rectangle
    */
    void toQuad(SkPoint quad[4]) const;

    /** Set this rectangle to the empty rectangle (0,0,0,0)
    */
    void setEmpty() { memset(this, 0, sizeof(*this)); }

    void set(const SkIRect& src)
    {
        fLeft   = SkIntToScalar(src.fLeft);
        fTop    = SkIntToScalar(src.fTop);
        fRight  = SkIntToScalar(src.fRight);
        fBottom = SkIntToScalar(src.fBottom);
    }

    void set(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom)
    {
        fLeft   = left;
        fTop    = top;
        fRight  = right;
        fBottom = bottom;
    }
    
    /** Initialize the rect with the 4 specified integers. The routine handles
        converting them to scalars (by calling SkIntToScalar)
     */
    void iset(int left, int top, int right, int bottom) {
        fLeft   = SkIntToScalar(left);
        fTop    = SkIntToScalar(top);
        fRight  = SkIntToScalar(right);
        fBottom = SkIntToScalar(bottom);
    }

    /** Set this rectangle to be the bounds of the array of points.
        If the array is empty (count == 0), then set this rectangle
        to the empty rectangle (0,0,0,0)
    */
    void set(const SkPoint pts[], int count);

    /** Offset set the rectangle by adding dx to its left and right,
        and adding dy to its top and bottom.
    */
    void offset(SkScalar dx, SkScalar dy)
    {
        fLeft   += dx;
        fTop    += dy;
        fRight  += dx;
        fBottom += dy;
    }   

    /** Inset the rectangle by (dx,dy). If dx is positive, then the sides are moved inwards,
        making the rectangle narrower. If dx is negative, then the sides are moved outwards,
        making the rectangle wider. The same hods true for dy and the top and bottom.
    */
    void inset(SkScalar dx, SkScalar dy)
    {
        fLeft   += dx;
        fTop    += dy;
        fRight  -= dx;
        fBottom -= dy;
    }

    /** If this rectangle intersects r, return true and set this rectangle to that
        intersection, otherwise return false and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(const SkRect& r);

    /** If this rectangle intersects the rectangle specified by left, top, right, bottom,
        return true and set this rectangle to that intersection, otherwise return false
        and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom);

    /** Return true if this rectangle is not empty, and the specified sides of
        a rectangle are not empty, and they intersect.
    */
    bool intersects(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom) const
    {
        return // first check that both are not empty
               left < right && top < bottom &&
               fLeft < fRight && fTop < fBottom &&
               // now check for intersection
               fLeft < right && left < fRight &&
               fTop < bottom && top < fBottom;
    }
    
    /** Return true if rectangles a and b are not empty and intersect.
        */
    static bool Intersects(const SkRect& a, const SkRect& b)
    {
        return  !a.isEmpty() && !b.isEmpty() &&             // check for empties
        a.fLeft < b.fRight && b.fLeft < a.fRight &&
        a.fTop < b.fBottom && b.fTop < a.fBottom;
    }
    
    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom);

    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(const SkRect& r)
    {
        this->join(r.fLeft, r.fTop, r.fRight, r.fBottom);
    }
    
    /** Returns true if (p.fX,p.fY) is inside the rectangle. The left and top coordinates of
        the rectangle are considered to be inside, while the right and bottom coordinates
        are not. Thus for the rectangle (0, 0, 5, 10), the points (0,0) and (0,9) are inside,
        while (-1,0) and (5,9) are not.
        If this rectangle is empty, return false.
    */
    bool contains(const SkPoint& p) const
    {
        return  !this->isEmpty() &&
                fLeft <= p.fX && p.fX < fRight &&
                fTop <= p.fY && p.fY < fBottom;
    }

    /** Returns true if (x,y) is inside the rectangle. The left and top coordinates of
        the rectangle are considered to be inside, while the right and bottom coordinates
        are not. Thus for the rectangle (0, 0, 5, 10), the points (0,0) and (0,9) are inside,
        while (-1,0) and (5,9) are not.
        If this rectangle is empty, return false.
    */
    bool contains(SkScalar x, SkScalar y) const
    {
        return  !this->isEmpty() &&
                fLeft <= x && x < fRight &&
                fTop <= y && y < fBottom;
    }

    /** Return true if this rectangle contains r.
        If either rectangle is empty, return false.
    */
    bool contains(const SkRect& r) const
    {
        return  !r.isEmpty() && !this->isEmpty() &&     // check for empties
                fLeft <= r.fLeft && fTop <= r.fTop &&
                fRight >= r.fRight && fBottom >= r.fBottom;
    }

    /** Set the dst integer rectangle by rounding this rectangle's coordinates
        to their nearest integer values.
    */
    void round(SkIRect* dst) const
    {
        SkASSERT(dst);
        dst->set(SkScalarRound(fLeft), SkScalarRound(fTop), SkScalarRound(fRight), SkScalarRound(fBottom));
    }

    /** Set the dst integer rectangle by rounding "out" this rectangle, choosing the floor of top and left,
        and the ceiling of right and bototm.
    */
    void roundOut(SkIRect* dst) const
    {
        SkASSERT(dst);
        dst->set(SkScalarFloor(fLeft), SkScalarFloor(fTop), SkScalarCeil(fRight), SkScalarCeil(fBottom));
    }

    /** Swap top/bottom or left/right if there are flipped.
        This can be called if the edges are computed separately,
        and may have crossed over each other.
        When this returns, left <= right && top <= bottom
    */
    void sort();
};

#endif

