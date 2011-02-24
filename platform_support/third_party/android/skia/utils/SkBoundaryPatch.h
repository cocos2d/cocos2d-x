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

#ifndef SkBoundaryPatch_DEFINED
#define SkBoundaryPatch_DEFINED

#include "SkPoint.h"
#include "SkRefCnt.h"

class SkBoundary : public SkRefCnt {
public:
    // These must be 0, 1, 2, 3 for efficiency in the subclass implementations
    enum Edge {
        kTop    = 0,
        kRight  = 1,
        kBottom = 2,
        kLeft   = 3
    };
    // Edge index goes clockwise around the boundary, beginning at the "top"
    virtual SkPoint eval(Edge, SkScalar unitInterval) = 0;
};

class SkBoundaryPatch {
public:
    SkBoundaryPatch();
    ~SkBoundaryPatch();

    SkBoundary* getBoundary() const { return fBoundary; }
    SkBoundary* setBoundary(SkBoundary*);

    SkPoint eval(SkScalar unitU, SkScalar unitV);
    bool evalPatch(SkPoint verts[], int rows, int cols);

private:
    SkBoundary* fBoundary;
};

////////////////////////////////////////////////////////////////////////

class SkLineBoundary : public SkBoundary {
public:
    SkPoint fPts[4];

    // override
    virtual SkPoint eval(Edge, SkScalar);
};

class SkCubicBoundary : public SkBoundary {
public:
    // the caller sets the first 12 entries. The 13th is used by the impl.
    SkPoint fPts[13];

    // override
    virtual SkPoint eval(Edge, SkScalar);
};

#endif

