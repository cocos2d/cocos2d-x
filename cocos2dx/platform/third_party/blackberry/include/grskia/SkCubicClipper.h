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

#ifndef SkCubicClipper_DEFINED
#define SkCubicClipper_DEFINED

#include "SkPoint.h"
#include "SkRect.h"

/** This class is initialized with a clip rectangle, and then can be fed cubics,
    which must already be monotonic in Y.

    In the future, it might return a series of segments, allowing it to clip
    also in X, to ensure that all segments fit in a finite coordinate system.
 */
class SkCubicClipper {
public:
    SkCubicClipper();

    void setClip(const SkIRect& clip);

    bool clipCubic(const SkPoint src[4], SkPoint dst[4]);

private:
    SkRect      fClip;
};

#endif  // SkCubicClipper_DEFINED
