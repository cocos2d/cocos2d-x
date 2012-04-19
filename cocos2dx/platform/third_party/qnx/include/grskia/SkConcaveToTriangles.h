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

#ifndef SkConcaveToTriangles_DEFINED
#define SkConcaveToTriangles_DEFINED

#include "SkPoint.h"
#include "SkTDArray.h"


// Triangulate a polygon.
// The polygon can be convex or concave, and can have holes or multiple contours
// of arbitrary recursion.
// The holes must have opposite orientation of the outer contours, whereas
// islands within the holes must have the same orientation as the outer contour.
// Contours should be joined by zero-thickness double-edges, to mimic a single
// polygon.  The polygon should not be self-intersecting.
// Currently, the outer contour must be right-handed, i.e. it should be oriented
// in the direction that rotates the X-axis to the Y-axis.
bool SkConcaveToTriangles(size_t count,
                          const SkPoint pts[],
                          SkTDArray<SkPoint> *triangles);


#endif  // SkConcaveToTriangles_DEFINED
