/*
    Copyright 2011 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#ifndef SkClampRange_DEFINED
#define SkClampRange_DEFINED

#include "SkFixed.h"

/**
 *  Iteration fixed fx by dx, clamping as you go to [0..0xFFFF], this class
 *  computes the (up to) 3 spans there are:
 *
 *  range0: use constant value V0
 *  range1: iterate as usual fx += dx
 *  range2: use constant value V1
 */
struct SkClampRange {
    int fCount0;    // count for fV0
    int fCount1;    // count for interpolating (fV0...fV1)
    int fCount2;    // count for fV1
    SkFixed fFx1;   // initial fx value for the fCount1 range.
                    // only valid if fCount1 > 0
    int fV0, fV1;
    bool fOverflowed;   // true if we had to clamp due to numerical overflow

    void init(SkFixed fx, SkFixed dx, int count, int v0, int v1);

private:
    void initFor1(SkFixed fx);
};

#endif

