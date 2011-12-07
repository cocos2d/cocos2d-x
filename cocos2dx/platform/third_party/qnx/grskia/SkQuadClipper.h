/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifndef SkQuadClipper_DEFINED
#define SkQuadClipper_DEFINED

#include "SkPath.h"

/** This class is initialized with a clip rectangle, and then can be fed quads,
    which must already be monotonic in Y.
 
    In the future, it might return a series of segments, allowing it to clip
    also in X, to ensure that all segments fit in a finite coordinate system.
 */
class SkQuadClipper {
public:
    SkQuadClipper();
    
    void setClip(const SkIRect& clip);
    
    bool clipQuad(const SkPoint src[3], SkPoint dst[3]);

private:
    SkRect      fClip;
};

/** Iterator that returns the clipped segements of a quad clipped to a rect.
    The segments will be either lines or quads (based on SkPath::Verb), and
    will all be monotonic in Y
 */
class SkQuadClipper2 {
public:
    bool clipQuad(const SkPoint pts[3], const SkRect& clip);
    bool clipCubic(const SkPoint pts[4], const SkRect& clip);

    SkPath::Verb next(SkPoint pts[]);
    
private:
    SkPoint*        fCurrPoint;
    SkPath::Verb*   fCurrVerb;
    
    enum {
        kMaxVerbs = 13,
        kMaxPoints = 32
    };
    SkPoint         fPoints[kMaxPoints];
    SkPath::Verb    fVerbs[kMaxVerbs];

    void clipMonoQuad(const SkPoint srcPts[3], const SkRect& clip);
    void clipMonoCubic(const SkPoint srcPts[4], const SkRect& clip);
    void appendVLine(SkScalar x, SkScalar y0, SkScalar y1, bool reverse);
    void appendQuad(const SkPoint pts[3], bool reverse);
    void appendCubic(const SkPoint pts[4], bool reverse);
};

#ifdef SK_DEBUG
    void sk_assert_monotonic_x(const SkPoint pts[], int count);
    void sk_assert_monotonic_y(const SkPoint pts[], int count);
#else
    #define sk_assert_monotonic_x(pts, count)
    #define sk_assert_monotonic_y(pts, count)
#endif

#endif
