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

#ifndef SkEdgeClipper_DEFINED
#define SkEdgeClipper_DEFINED

#include "SkPath.h"

/** This is basically an iterator. It is initialized with an edge and a clip,
    and then next() is called until it returns kDone_Verb.
 */
class SkEdgeClipper {
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
