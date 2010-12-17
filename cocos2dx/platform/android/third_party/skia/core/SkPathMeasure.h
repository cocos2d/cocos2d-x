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

#ifndef SkPathMeasure_DEFINED
#define SkPathMeasure_DEFINED

#include "SkPath.h"
#include "SkTDArray.h"

class SkPathMeasure : SkNoncopyable {
public:
    SkPathMeasure();
    /** Initialize the pathmeasure with the specified path. The path must remain valid
        for the lifetime of the measure object, or until setPath() is called with
        a different path (or null), since the measure object keeps a pointer to the
        path object (does not copy its data).
    */
    SkPathMeasure(const SkPath& path, bool forceClosed);
    ~SkPathMeasure();

    /** Reset the pathmeasure with the specified path. The path must remain valid
        for the lifetime of the measure object, or until setPath() is called with
        a different path (or null), since the measure object keeps a pointer to the
        path object (does not copy its data).
    */
    void    setPath(const SkPath*, bool forceClosed);

    /** Return the total length of the current contour, or 0 if no path
        is associated (e.g. resetPath(null))
    */
    SkScalar getLength();

    /** Pins distance to 0 <= distance <= getLength(), and then computes
        the corresponding position and tangent.
        Returns false if there is no path, or a zero-length path was specified, in which case
        position and tangent are unchanged.
    */
    bool getPosTan(SkScalar distance, SkPoint* position, SkVector* tangent);

    enum MatrixFlags {
        kGetPosition_MatrixFlag     = 0x01,
        kGetTangent_MatrixFlag      = 0x02,
        kGetPosAndTan_MatrixFlag    = kGetPosition_MatrixFlag | kGetTangent_MatrixFlag
    };
    /** Pins distance to 0 <= distance <= getLength(), and then computes
        the corresponding matrix (by calling getPosTan).
        Returns false if there is no path, or a zero-length path was specified, in which case
        matrix is unchanged.
    */
    bool getMatrix(SkScalar distance, SkMatrix* matrix, MatrixFlags flags = kGetPosAndTan_MatrixFlag);
    /** Given a start and stop distance, return in dst the intervening segment(s).
        If the segment is zero-length, return false, else return true.
        startD and stopD are pinned to legal values (0..getLength()). If startD <= stopD
        then return false (and leave dst untouched).
        Begin the segment with a moveTo if startWithMoveTo is true
    */
    bool getSegment(SkScalar startD, SkScalar stopD, SkPath* dst, bool startWithMoveTo);

    /** Return true if the current contour is closed()
    */
    bool isClosed();

    /** Move to the next contour in the path. Return true if one exists, or false if
        we're done with the path.
    */
    bool nextContour();

#ifdef SK_DEBUG
    void    dump();
#endif

private:
    SkPath::Iter    fIter;
    const SkPath*   fPath;
    SkScalar        fLength;            // relative to the current contour
    int             fFirstPtIndex;      // relative to the current contour
    bool            fIsClosed;          // relative to the current contour
    bool            fForceClosed;

    struct Segment {
        SkScalar    fDistance;  // total distance up to this point
        unsigned    fPtIndex : 15;
        unsigned    fTValue : 15;
        unsigned    fType : 2;

        SkScalar getScalarT() const;
    };
    SkTDArray<Segment>  fSegments;

    static const Segment* NextSegment(const Segment*);

    void     buildSegments();
    SkScalar compute_quad_segs(const SkPoint pts[3], SkScalar distance,
                                int mint, int maxt, int ptIndex);
    SkScalar compute_cubic_segs(const SkPoint pts[3], SkScalar distance,
                                int mint, int maxt, int ptIndex);
    const Segment* distanceToSegment(SkScalar distance, SkScalar* t);
};

#endif

