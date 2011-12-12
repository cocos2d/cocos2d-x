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

#ifndef SkPath_DEFINED
#define SkPath_DEFINED

#include "SkMatrix.h"
#include "SkTDArray.h"

#ifdef ANDROID
#define GEN_ID_INC              fGenerationID++
#define GEN_ID_PTR_INC(ptr)     ptr->fGenerationID++
#else
#define GEN_ID_INC
#define GEN_ID_PTR_INC(ptr)
#endif

class SkReader32;
class SkWriter32;
class SkAutoPathBoundsUpdate;
class SkString;

/** \class SkPath

    The SkPath class encapsulates compound (multiple contour) geometric paths
    consisting of straight line segments, quadratic curves, and cubic curves.
*/
class SK_API SkPath {
public:
    SkPath();
    SkPath(const SkPath&);
    ~SkPath();

    SkPath& operator=(const SkPath&);
    
    friend bool operator==(const SkPath&, const SkPath&);
    friend bool operator!=(const SkPath& a, const SkPath& b) {
        return !(a == b);
    }

    enum FillType {
        /** Specifies that "inside" is computed by a non-zero sum of signed
            edge crossings
        */
        kWinding_FillType,
        /** Specifies that "inside" is computed by an odd number of edge
            crossings
        */
        kEvenOdd_FillType,
        /** Same as Winding, but draws outside of the path, rather than inside
        */
        kInverseWinding_FillType,
        /** Same as EvenOdd, but draws outside of the path, rather than inside
         */
        kInverseEvenOdd_FillType
    };

    /** Return the path's fill type. This is used to define how "inside" is
        computed. The default value is kWinding_FillType.

        @return the path's fill type
    */
    FillType getFillType() const { return (FillType)fFillType; }

    /** Set the path's fill type. This is used to define how "inside" is
        computed. The default value is kWinding_FillType.
     
        @param ft The new fill type for this path
    */
    void setFillType(FillType ft) {
        fFillType = SkToU8(ft);
        GEN_ID_INC;
    }

    /** Returns true if the filltype is one of the Inverse variants */
    bool isInverseFillType() const { return (fFillType & 2) != 0; }

    /**
     *  Toggle between inverse and normal filltypes. This reverse the return
     *  value of isInverseFillType()
     */
    void toggleInverseFillType() {
        fFillType ^= 2;
        GEN_ID_INC;
     }

    enum Convexity {
        kUnknown_Convexity,
        kConvex_Convexity,
        kConcave_Convexity
    };

    /**
     *  Return the path's convexity, as stored in the path. If it is currently
     *  unknown, and the computeIfUnknown bool is true, then this will first
     *  call ComputeConvexity() and then return that (cached) value.
     */
    Convexity getConvexity() const {
        if (kUnknown_Convexity == fConvexity) {
            fConvexity = (uint8_t)ComputeConvexity(*this);
        }
        return (Convexity)fConvexity;
    }

    /**
     *  Return the currently cached value for convexity, even if that is set to
     *  kUnknown_Convexity. Note: getConvexity() will automatically call
     *  ComputeConvexity and cache its return value if the current setting is
     *  kUnknown.
     */
    Convexity getConvexityOrUnknown() const { return (Convexity)fConvexity; }

    /**
     *  Store a convexity setting in the path. There is no automatic check to
     *  see if this value actually agress with the return value from
     *  ComputeConvexity().
     *
     *  Note: even if this is set to a "known" value, if the path is later
     *  changed (e.g. lineTo(), addRect(), etc.) then the cached value will be
     *  reset to kUnknown_Convexity.
     */
    void setConvexity(Convexity);

    /**
     *  Compute the convexity of the specified path. This does not look at the
     *  value stored in the path, but computes it directly from the path's data.
     *
     *  This never returns kUnknown_Convexity.
     *
     *  If there is more than one contour, this returns kConcave_Convexity.
     *  If the contour is degenerate (e.g. there are fewer than 3 non-degenerate
     *  segments), then this returns kConvex_Convexity.
     *  The contour is treated as if it were closed, even if there is no kClose
     *  verb.
     */
    static Convexity ComputeConvexity(const SkPath&);

    /**
     *  DEPRECATED: use getConvexity()
     *  Returns true if the path is flagged as being convex. This is not a
     *  confirmed by any analysis, it is just the value set earlier.
     */
    bool isConvex() const {
        return kConvex_Convexity == this->getConvexity();
    }

    /**
     *  DEPRECATED: use setConvexity()
     *  Set the isConvex flag to true or false. Convex paths may draw faster if
     *  this flag is set, though setting this to true on a path that is in fact
     *  not convex can give undefined results when drawn. Paths default to
     *  isConvex == false
     */
    void setIsConvex(bool isConvex) {
        this->setConvexity(isConvex ? kConvex_Convexity : kConcave_Convexity);
    }

    /** Clear any lines and curves from the path, making it empty. This frees up
        internal storage associated with those segments.
        This does NOT change the fill-type setting nor isConvex
    */
    void reset();
    
    /** Similar to reset(), in that all lines and curves are removed from the
        path. However, any internal storage for those lines/curves is retained,
        making reuse of the path potentially faster.
        This does NOT change the fill-type setting nor isConvex
    */
    void rewind();

    /** Returns true if the path is empty (contains no lines or curves)

        @return true if the path is empty (contains no lines or curves)
    */
    bool isEmpty() const;

    /** Returns true if the path specifies a rectangle. If so, and if rect is
        not null, set rect to the bounds of the path. If the path does not
        specify a rectangle, return false and ignore rect.
     
        @param rect If not null, returns the bounds of the path if it specifies
                    a rectangle
        @return true if the path specifies a rectangle
    */
    bool isRect(SkRect* rect) const;

    /** Return the number of points in the path
     */
    int countPoints() const {
        return this->getPoints(NULL, 0);
    }

    /** Return the point at the specified index. If the index is out of range
         (i.e. is not 0 <= index < countPoints()) then the returned coordinates
         will be (0,0)
     */
    SkPoint getPoint(int index) const;

    /** Returns the number of points in the path. Up to max points are copied.
     
        @param points If not null, receives up to max points
        @param max The maximum number of points to copy into points
        @return the actual number of points in the path
    */
    int getPoints(SkPoint points[], int max) const;

    //! Swap contents of this and other. Guaranteed not to throw
    void swap(SkPath& other);

    /** Returns the bounds of the path's points. If the path contains 0 or 1
        points, the bounds is set to (0,0,0,0), and isEmpty() will return true.
        Note: this bounds may be larger than the actual shape, since curves
        do not extend as far as their control points.
    */
    const SkRect& getBounds() const {
        if (fBoundsIsDirty) {
            this->computeBounds();
        }
        return fBounds;
    }

    /** Calling this will, if the internal cache of the bounds is out of date,
        update it so that subsequent calls to getBounds will be instanteous.
        This also means that any copies or simple transformations of the path
        will inherit the cached bounds.
     */
    void updateBoundsCache() const {
        // for now, just calling getBounds() is sufficient
        this->getBounds();
    }

    //  Construction methods

    /** Hint to the path to prepare for adding more points. This can allow the
        path to more efficiently grow its storage.
    
        @param extraPtCount The number of extra points the path should
                            preallocate for.
    */
    void incReserve(unsigned extraPtCount);

    /** Set the beginning of the next contour to the point (x,y).
     
        @param x    The x-coordinate of the start of a new contour
        @param y    The y-coordinate of the start of a new contour
    */
    void moveTo(SkScalar x, SkScalar y);

    /** Set the beginning of the next contour to the point
     
        @param p    The start of a new contour
    */
    void moveTo(const SkPoint& p) {
        this->moveTo(p.fX, p.fY);
    }

    /** Set the beginning of the next contour relative to the last point on the
        previous contour. If there is no previous contour, this is treated the
        same as moveTo().
     
        @param dx   The amount to add to the x-coordinate of the end of the
                    previous contour, to specify the start of a new contour
        @param dy   The amount to add to the y-coordinate of the end of the
                    previous contour, to specify the start of a new contour
    */
    void rMoveTo(SkScalar dx, SkScalar dy);

    /** Add a line from the last point to the specified point (x,y). If no
        moveTo() call has been made for this contour, the first point is
        automatically set to (0,0).

        @param x    The x-coordinate of the end of a line
        @param y    The y-coordinate of the end of a line
    */
    void lineTo(SkScalar x, SkScalar y);

    /** Add a line from the last point to the specified point. If no moveTo()
        call has been made for this contour, the first point is automatically
        set to (0,0).

        @param p    The end of a line
    */
    void lineTo(const SkPoint& p) {
        this->lineTo(p.fX, p.fY);
    }

    /** Same as lineTo, but the coordinates are considered relative to the last
        point on this contour. If there is no previous point, then a moveTo(0,0)
        is inserted automatically.
     
        @param dx   The amount to add to the x-coordinate of the previous point
                    on this contour, to specify a line
        @param dy   The amount to add to the y-coordinate of the previous point
                    on this contour, to specify a line
    */
    void rLineTo(SkScalar dx, SkScalar dy);

    /** Add a quadratic bezier from the last point, approaching control point
        (x1,y1), and ending at (x2,y2). If no moveTo() call has been made for
        this contour, the first point is automatically set to (0,0).
     
        @param x1   The x-coordinate of the control point on a quadratic curve
        @param y1   The y-coordinate of the control point on a quadratic curve
        @param x2   The x-coordinate of the end point on a quadratic curve
        @param y2   The y-coordinate of the end point on a quadratic curve
    */
    void quadTo(SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2);

    /** Add a quadratic bezier from the last point, approaching control point
        p1, and ending at p2. If no moveTo() call has been made for this
        contour, the first point is automatically set to (0,0).
     
        @param p1   The control point on a quadratic curve
        @param p2   The end point on a quadratic curve
    */
    void quadTo(const SkPoint& p1, const SkPoint& p2) {
        this->quadTo(p1.fX, p1.fY, p2.fX, p2.fY);
    }

    /** Same as quadTo, but the coordinates are considered relative to the last
        point on this contour. If there is no previous point, then a moveTo(0,0)
        is inserted automatically.

        @param dx1   The amount to add to the x-coordinate of the last point on
                this contour, to specify the control point of a quadratic curve
        @param dy1   The amount to add to the y-coordinate of the last point on
                this contour, to specify the control point of a quadratic curve
        @param dx2   The amount to add to the x-coordinate of the last point on
                     this contour, to specify the end point of a quadratic curve
        @param dy2   The amount to add to the y-coordinate of the last point on
                     this contour, to specify the end point of a quadratic curve
    */
    void rQuadTo(SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2);

    /** Add a cubic bezier from the last point, approaching control points
        (x1,y1) and (x2,y2), and ending at (x3,y3). If no moveTo() call has been
        made for this contour, the first point is automatically set to (0,0).
     
        @param x1   The x-coordinate of the 1st control point on a cubic curve
        @param y1   The y-coordinate of the 1st control point on a cubic curve
        @param x2   The x-coordinate of the 2nd control point on a cubic curve
        @param y2   The y-coordinate of the 2nd control point on a cubic curve
        @param x3   The x-coordinate of the end point on a cubic curve
        @param y3   The y-coordinate of the end point on a cubic curve
    */
    void cubicTo(SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2,
                 SkScalar x3, SkScalar y3);

    /** Add a cubic bezier from the last point, approaching control points p1
        and p2, and ending at p3. If no moveTo() call has been made for this
        contour, the first point is automatically set to (0,0).
     
        @param p1   The 1st control point on a cubic curve
        @param p2   The 2nd control point on a cubic curve
        @param p3   The end point on a cubic curve
    */
    void cubicTo(const SkPoint& p1, const SkPoint& p2, const SkPoint& p3) {
        this->cubicTo(p1.fX, p1.fY, p2.fX, p2.fY, p3.fX, p3.fY);
    }

    /** Same as cubicTo, but the coordinates are considered relative to the
        current point on this contour. If there is no previous point, then a
        moveTo(0,0) is inserted automatically.
     
        @param dx1   The amount to add to the x-coordinate of the last point on
                this contour, to specify the 1st control point of a cubic curve
        @param dy1   The amount to add to the y-coordinate of the last point on
                this contour, to specify the 1st control point of a cubic curve
        @param dx2   The amount to add to the x-coordinate of the last point on
                this contour, to specify the 2nd control point of a cubic curve
        @param dy2   The amount to add to the y-coordinate of the last point on
                this contour, to specify the 2nd control point of a cubic curve
        @param dx3   The amount to add to the x-coordinate of the last point on
                     this contour, to specify the end point of a cubic curve
        @param dy3   The amount to add to the y-coordinate of the last point on
                     this contour, to specify the end point of a cubic curve
    */
    void    rCubicTo(SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2,
                     SkScalar x3, SkScalar y3);

    /** Append the specified arc to the path as a new contour. If the start of
        the path is different from the path's current last point, then an
        automatic lineTo() is added to connect the current contour to the start
        of the arc. However, if the path is empty, then we call moveTo() with
        the first point of the arc. The sweep angle is treated mod 360.
     
        @param oval The bounding oval defining the shape and size of the arc
        @param startAngle Starting angle (in degrees) where the arc begins
        @param sweepAngle Sweep angle (in degrees) measured clockwise. This is
                          treated mod 360.
        @param forceMoveTo If true, always begin a new contour with the arc
    */
    void    arcTo(const SkRect& oval, SkScalar startAngle, SkScalar sweepAngle,
                  bool forceMoveTo);

    /** Append a line and arc to the current path. This is the same as the
        PostScript call "arct".
    */
    void arcTo(SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2,
               SkScalar radius);

    /** Append a line and arc to the current path. This is the same as the
        PostScript call "arct".
    */
    void arcTo(const SkPoint p1, const SkPoint p2, SkScalar radius) {
        this->arcTo(p1.fX, p1.fY, p2.fX, p2.fY, radius);
    }

    /** Close the current contour. If the current point is not equal to the
        first point of the contour, a line segment is automatically added.
    */
    void close();

    enum Direction {
        /** clockwise direction for adding closed contours */
        kCW_Direction,
        /** counter-clockwise direction for adding closed contours */
        kCCW_Direction
    };

    /** Add a closed rectangle contour to the path
        @param rect The rectangle to add as a closed contour to the path
        @param dir  The direction to wind the rectangle's contour
    */
    void    addRect(const SkRect& rect, Direction dir = kCW_Direction);

    /** Add a closed rectangle contour to the path

        @param left     The left side of a rectangle to add as a closed contour
                        to the path
        @param top      The top of a rectangle to add as a closed contour to the
                        path
        @param right    The right side of a rectangle to add as a closed contour
                        to the path
        @param bottom   The bottom of a rectangle to add as a closed contour to
                        the path
        @param dir      The direction to wind the rectangle's contour
    */
    void addRect(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom,
                 Direction dir = kCW_Direction);

    /** Add a closed oval contour to the path

        @param oval The bounding oval to add as a closed contour to the path
        @param dir  The direction to wind the oval's contour
    */
    void addOval(const SkRect& oval, Direction dir = kCW_Direction);

    /** Add a closed circle contour to the path

        @param x        The x-coordinate of the center of a circle to add as a
                        closed contour to the path
        @param y        The y-coordinate of the center of a circle to add as a
                        closed contour to the path
        @param radius   The radius of a circle to add as a closed contour to the
                        path
        @param dir      The direction to wind the circle's contour
    */
    void addCircle(SkScalar x, SkScalar y, SkScalar radius,
                   Direction dir = kCW_Direction);

    /** Add the specified arc to the path as a new contour.
     
        @param oval The bounds of oval used to define the size of the arc
        @param startAngle Starting angle (in degrees) where the arc begins
        @param sweepAngle Sweep angle (in degrees) measured clockwise
    */
    void addArc(const SkRect& oval, SkScalar startAngle, SkScalar sweepAngle);

    /** Add a closed round-rectangle contour to the path
        @param rect The bounds of a round-rectangle to add as a closed contour
        @param rx   The x-radius of the rounded corners on the round-rectangle
        @param ry   The y-radius of the rounded corners on the round-rectangle
        @param dir  The direction to wind the round-rectangle's contour
    */
    void    addRoundRect(const SkRect& rect, SkScalar rx, SkScalar ry,
                         Direction dir = kCW_Direction);

    /** Add a closed round-rectangle contour to the path. Each corner receives
        two radius values [X, Y]. The corners are ordered top-left, top-right,
        bottom-right, bottom-left.
        @param rect The bounds of a round-rectangle to add as a closed contour
        @param radii Array of 8 scalars, 4 [X,Y] pairs for each corner
        @param dir  The direction to wind the round-rectangle's contour
        */
    void addRoundRect(const SkRect& rect, const SkScalar radii[],
                      Direction dir = kCW_Direction);

    /** Add a copy of src to the path, offset by (dx,dy)
        @param src  The path to add as a new contour
        @param dx   The amount to translate the path in X as it is added
        @param dx   The amount to translate the path in Y as it is added
    */
    void    addPath(const SkPath& src, SkScalar dx, SkScalar dy);

    /** Add a copy of src to the path
    */
    void addPath(const SkPath& src) {
        SkMatrix m;
        m.reset();
        this->addPath(src, m);
    }

    /** Add a copy of src to the path, transformed by matrix
        @param src  The path to add as a new contour
    */
    void addPath(const SkPath& src, const SkMatrix& matrix);

    /** Offset the path by (dx,dy), returning true on success
     
        @param dx   The amount in the X direction to offset the entire path 
        @param dy   The amount in the Y direction to offset the entire path 
        @param dst  The translated path is written here
    */
    void offset(SkScalar dx, SkScalar dy, SkPath* dst) const;

    /** Offset the path by (dx,dy), returning true on success
     
        @param dx   The amount in the X direction to offset the entire path 
        @param dy   The amount in the Y direction to offset the entire path 
    */
    void offset(SkScalar dx, SkScalar dy) {
        this->offset(dx, dy, this);
    }

    /** Transform the points in this path by matrix, and write the answer into
        dst.
     
        @param matrix   The matrix to apply to the path
        @param dst      The transformed path is written here
    */
    void transform(const SkMatrix& matrix, SkPath* dst) const;

    /** Transform the points in this path by matrix

        @param matrix The matrix to apply to the path
    */
    void transform(const SkMatrix& matrix) {
        this->transform(matrix, this);
    }

    /** Return the last point on the path. If no points have been added, (0,0)
        is returned.
     
        @param lastPt   The last point on the path is returned here
    */
    void getLastPt(SkPoint* lastPt) const;

    /** Set the last point on the path. If no points have been added,
        moveTo(x,y) is automatically called.
     
        @param x    The new x-coordinate for the last point
        @param y    The new y-coordinate for the last point
    */
    void setLastPt(SkScalar x, SkScalar y);

    /** Set the last point on the path. If no points have been added, moveTo(p)
        is automatically called.

        @param p    The new location for the last point
    */
    void setLastPt(const SkPoint& p) {
        this->setLastPt(p.fX, p.fY);
    }

    enum Verb {
        kMove_Verb,     //!< iter.next returns 1 point
        kLine_Verb,     //!< iter.next returns 2 points
        kQuad_Verb,     //!< iter.next returns 3 points
        kCubic_Verb,    //!< iter.next returns 4 points
        kClose_Verb,    //!< iter.next returns 1 point (the last point)
        kDone_Verb      //!< iter.next returns 0 points
    };

    /** Iterate through all of the segments (lines, quadratics, cubics) of
        each contours in a path.
    */
    class SK_API Iter {
    public:
                Iter();
                Iter(const SkPath&, bool forceClose);

        void setPath(const SkPath&, bool forceClose);

        /** Return the next verb in this iteration of the path. When all
            segments have been visited, return kDone_Verb.
         
            @param  pts The points representing the current verb and/or segment
            @return The verb for the current segment
        */
        Verb next(SkPoint pts[4]);

        /** If next() returns kLine_Verb, then this query returns true if the
            line was the result of a close() command (i.e. the end point is the
            initial moveto for this contour). If next() returned a different
            verb, this returns an undefined value.
         
            @return If the last call to next() returned kLine_Verb, return true
                    if it was the result of an explicit close command.
        */
        bool isCloseLine() const { return SkToBool(fCloseLine); }
        
        /** Returns true if the current contour is closed (has a kClose_Verb)
            @return true if the current contour is closed (has a kClose_Verb)
        */
        bool isClosedContour() const;

    private:
        const SkPoint*  fPts;
        const uint8_t*  fVerbs;
        const uint8_t*  fVerbStop;
        SkPoint         fMoveTo;
        SkPoint         fLastPt;
        SkBool8         fForceClose;
        SkBool8         fNeedClose;
        SkBool8         fNeedMoveTo;
        SkBool8         fCloseLine;

        bool cons_moveTo(SkPoint pts[1]);
        Verb autoClose(SkPoint pts[2]);
    };

    void dump(bool forceClose, const char title[] = NULL) const;
    void dump() const;

    void flatten(SkWriter32&) const;
    void unflatten(SkReader32&);

#ifdef ANDROID
    uint32_t getGenerationID() const;
#endif

    SkDEBUGCODE(void validate() const;)

private:
    SkTDArray<SkPoint>  fPts;
    SkTDArray<uint8_t>  fVerbs;
    mutable SkRect      fBounds;
    mutable uint8_t     fBoundsIsDirty;
    uint8_t             fFillType;
    mutable uint8_t     fConvexity;
#ifdef ANDROID
    uint32_t            fGenerationID;
#endif

    // called, if dirty, by getBounds()
    void computeBounds() const;

    friend class Iter;
    void cons_moveto();

    friend class SkPathStroker;
    /*  Append the first contour of path, ignoring path's initial point. If no
        moveTo() call has been made for this contour, the first point is
        automatically set to (0,0).
    */
    void pathTo(const SkPath& path);

    /*  Append, in reverse order, the first contour of path, ignoring path's
        last point. If no moveTo() call has been made for this contour, the
        first point is automatically set to (0,0).
    */
    void reversePathTo(const SkPath&);

    friend const SkPoint* sk_get_path_points(const SkPath&, int index);
    friend class SkAutoPathBoundsUpdate;
};

#endif

