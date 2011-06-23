/*
 * Copyright (C) 2005 The Android Open Source Project
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

#ifndef SkRegion_DEFINED
#define SkRegion_DEFINED

#include "SkRect.h"

class SkPath;
class SkRgnBuilder;

namespace android {
    class Region;
}

#define SkRegion_gEmptyRunHeadPtr   ((SkRegion::RunHead*)-1)
#define SkRegion_gRectRunHeadPtr    0

/** \class SkRegion

    The SkRegion class encapsulates the geometric region used to specify
    clipping areas for drawing.
*/
class SkRegion {
public:
    typedef int32_t RunType;
    enum {
        kRunTypeSentinel = 0x7FFFFFFF
    };
    
    SkRegion();
    SkRegion(const SkRegion&);
    explicit SkRegion(const SkIRect&);
    ~SkRegion();

    SkRegion& operator=(const SkRegion&);
    
    friend int operator==(const SkRegion& a, const SkRegion& b);
    friend int operator!=(const SkRegion& a, const SkRegion& b) {
        return !(a == b);
    }
    
    /** Replace this region with the specified region, and return true if the
        resulting region is non-empty.
    */
    bool set(const SkRegion& src) {
        SkASSERT(&src);
        *this = src;
        return !this->isEmpty();
    }

    /** Swap the contents of this and the specified region. This operation
        is gauarenteed to never fail.
    */
    void    swap(SkRegion&);

    /** Return true if this region is empty */
    bool    isEmpty() const { return fRunHead == SkRegion_gEmptyRunHeadPtr; }
    /** Return true if this region is a single, non-empty rectangle */
    bool    isRect() const { return fRunHead == SkRegion_gRectRunHeadPtr; }
    /** Return true if this region consists of more than 1 rectangular area */
    bool    isComplex() const { return !this->isEmpty() && !this->isRect(); }
    /** Return the bounds of this region. If the region is empty, returns an
        empty rectangle.
    */
    const SkIRect& getBounds() const { return fBounds; }

    /** Returns true if the region is non-empty, and if so, sets the specified
        path to the boundary(s) of the region.
    */
    bool getBoundaryPath(SkPath* path) const;

    /** Set the region to be empty, and return false, since the resulting
        region is empty
    */
    bool    setEmpty();

    /** If rect is non-empty, set this region to that rectangle and return true,
        otherwise set this region to empty and return false.
    */
    bool    setRect(const SkIRect&);

    /** If left < right and top < bottom, set this region to that rectangle and
        return true, otherwise set this region to empty and return false.
    */
    bool    setRect(int32_t left, int32_t top, int32_t right, int32_t bottom);

    /** Set this region to the specified region, and return true if it is
        non-empty. */
    bool    setRegion(const SkRegion&);

    /** Set this region to the area described by the path, clipped.
        Return true if the resulting region is non-empty.
        This produces a region that is identical to the pixels that would be
        drawn by the path (with no antialiasing) with the specified clip.
    */
    bool    setPath(const SkPath&, const SkRegion& clip);
    
    /** Returns true if the specified rectangle has a non-empty intersection
        with this region.
    */
    bool    intersects(const SkIRect&) const;
    
    /** Returns true if the specified region has a non-empty intersection
        with this region.
    */
    bool    intersects(const SkRegion&) const;

    /** Return true if the specified x,y coordinate is inside the region.
    */
    bool    contains(int32_t x, int32_t y) const;

    /** Return true if the specified rectangle is completely inside the region.
        This works for simple (rectangular) and complex regions, and always
        returns the correct result. Note: if either this region or the rectangle
        is empty, contains() returns false.
    */
    bool    contains(const SkIRect&) const;

    /** Return true if the specified region is completely inside the region.
        This works for simple (rectangular) and complex regions, and always
        returns the correct result. Note: if either region is empty, contains()
        returns false.
    */
    bool    contains(const SkRegion&) const;

    /** Return true if this region is a single rectangle (not complex) and the
        specified rectangle is contained by this region. Returning false is not
        a guarantee that the rectangle is not contained by this region, but
        return true is a guarantee that the rectangle is contained by this region.
    */
    bool quickContains(const SkIRect& r) const {
        return this->quickContains(r.fLeft, r.fTop, r.fRight, r.fBottom);
    }

    /** Return true if this region is a single rectangle (not complex) and the
        specified rectangle is contained by this region. Returning false is not
        a guarantee that the rectangle is not contained by this region, but
        return true is a guarantee that the rectangle is contained by this
        region.
    */
    bool quickContains(int32_t left, int32_t top, int32_t right,
                       int32_t bottom) const {
        SkASSERT(this->isEmpty() == fBounds.isEmpty()); // valid region
        
        return left < right && top < bottom &&
               fRunHead == SkRegion_gRectRunHeadPtr &&  // this->isRect()
               /* fBounds.contains(left, top, right, bottom); */
               fBounds.fLeft <= left && fBounds.fTop <= top &&
               fBounds.fRight >= right && fBounds.fBottom >= bottom;
    }
    
    /** Return true if this region is empty, or if the specified rectangle does
        not intersect the region. Returning false is not a guarantee that they
        intersect, but returning true is a guarantee that they do not.
    */
    bool quickReject(const SkIRect& rect) const
    {
        return this->isEmpty() || rect.isEmpty() ||
                !SkIRect::Intersects(fBounds, rect);
    }

    /** Return true if this region, or rgn, is empty, or if their bounds do not
        intersect. Returning false is not a guarantee that they intersect, but
        returning true is a guarantee that they do not.
    */
    bool quickReject(const SkRegion& rgn) const {
        return this->isEmpty() || rgn.isEmpty() ||
               !SkIRect::Intersects(fBounds, rgn.fBounds);
    }

    /** Translate the region by the specified (dx, dy) amount.
    */
    void translate(int dx, int dy) { this->translate(dx, dy, this); }

    /** Translate the region by the specified (dx, dy) amount, writing the
        resulting region into dst. Note: it is legal to pass this region as the
        dst parameter, effectively translating the region in place. If dst is
        null, nothing happens.
    */
    void translate(int dx, int dy, SkRegion* dst) const;

    /** The logical operations that can be performed when combining two regions.
    */
    enum Op {
        kDifference_Op, //!< subtract the op region from the first region
        kIntersect_Op,  //!< intersect the two regions
        kUnion_Op,      //!< union (inclusive-or) the two regions
        kXOR_Op,        //!< exclusive-or the two regions
        /** subtract the first region from the op region */
        kReverseDifference_Op,
        kReplace_Op     //!< replace the dst region with the op region
    };
    
    /** Set this region to the result of applying the Op to this region and the
        specified rectangle: this = (this op rect).
        Return true if the resulting region is non-empty.
        */
    bool op(const SkIRect& rect, Op op) { return this->op(*this, rect, op); }
    
    /** Set this region to the result of applying the Op to this region and the
        specified rectangle: this = (this op rect).
        Return true if the resulting region is non-empty.
    */
    bool op(int left, int top, int right, int bottom, Op op) {
        SkIRect rect;
        rect.set(left, top, right, bottom);
        return this->op(*this, rect, op);
    }
    
    /** Set this region to the result of applying the Op to this region and the
        specified region: this = (this op rgn).
        Return true if the resulting region is non-empty.
    */
    bool op(const SkRegion& rgn, Op op) { return this->op(*this, rgn, op); }
    /** Set this region to the result of applying the Op to the specified
        rectangle and region: this = (rect op rgn).
        Return true if the resulting region is non-empty.
    */
    bool op(const SkIRect& rect, const SkRegion& rgn, Op);
    /** Set this region to the result of applying the Op to the specified
        region and rectangle: this = (rgn op rect).
        Return true if the resulting region is non-empty.
    */
    bool op(const SkRegion& rgn, const SkIRect& rect, Op);
    /** Set this region to the result of applying the Op to the specified
        regions: this = (rgna op rgnb).
        Return true if the resulting region is non-empty.
    */
    bool op(const SkRegion& rgna, const SkRegion& rgnb, Op op);

    /** Returns the sequence of rectangles, sorted in Y and X, that make up
        this region.
    */
    class Iterator {
    public:
        Iterator() : fRgn(NULL), fDone(true) {}
        Iterator(const SkRegion&);
        // if we have a region, reset to it and return true, else return false
        bool rewind();
        // reset the iterator, using the new region
        void reset(const SkRegion&);
        bool done() { return fDone; }
        void next();
        const SkIRect& rect() const { return fRect; }

    private:
        const SkRegion* fRgn;
        const RunType*  fRuns;
        SkIRect         fRect;
        bool            fDone;
    };

    /** Returns the sequence of rectangles, sorted in Y and X, that make up
        this region intersected with the specified clip rectangle.
    */
    class Cliperator {
    public:
        Cliperator(const SkRegion&, const SkIRect& clip);
        bool            done() { return fDone; }
        void            next();
        const SkIRect& rect() const { return fRect; }

    private:
        Iterator    fIter;
        SkIRect     fClip;
        SkIRect     fRect;
        bool        fDone;
    };

    /** Returns the sequence of runs that make up this region for the specified
        Y scanline, clipped to the specified left and right X values.
    */
    class Spanerator {
    public:
        Spanerator(const SkRegion&, int y, int left, int right);
        bool    next(int* left, int* right);

    private:
        const SkRegion::RunType* fRuns;
        int     fLeft, fRight;
        bool    fDone;
    };

    /** Write the region to the buffer, and return the number of bytes written.
        If buffer is NULL, it still returns the number of bytes.
    */
    uint32_t flatten(void* buffer) const;
    /** Initialized the region from the buffer, returning the number
        of bytes actually read.
    */
    uint32_t unflatten(const void* buffer);
    
    SkDEBUGCODE(void dump() const;)
    SkDEBUGCODE(void validate() const;)
    SkDEBUGCODE(static void UnitTest();)

    // expose this to allow for regression test on complex regions
    SkDEBUGCODE(bool debugSetRuns(const RunType runs[], int count);)

private:
    enum {
        kOpCount = kReplace_Op + 1
    };

    enum {
        kRectRegionRuns = 6 // need to store a region of a rect [T B L R S S]        
    };

    friend class android::Region;    // needed for marshalling efficiently
    void allocateRuns(int count); // allocate space for count runs

    struct RunHead;

    SkIRect     fBounds;
    RunHead*    fRunHead;

    void            freeRuns();
    const RunType*  getRuns(RunType tmpStorage[], int* count) const;
    bool            setRuns(RunType runs[], int count);

    int count_runtype_values(int* itop, int* ibot) const;
    
    static void BuildRectRuns(const SkIRect& bounds,
                              RunType runs[kRectRegionRuns]);
    // returns true if runs are just a rect
    static bool ComputeRunBounds(const RunType runs[], int count,
                                 SkIRect* bounds);

    friend struct RunHead;
    friend class Iterator;
    friend class Spanerator;
    friend class SkRgnBuilder;
    friend class SkFlatRegion;
};


#endif

