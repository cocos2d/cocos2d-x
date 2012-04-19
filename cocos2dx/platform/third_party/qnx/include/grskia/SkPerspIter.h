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

#ifndef SkPerspIter_DEFINED
#define SkPerspIter_DEFINED

#include "SkMatrix.h"

class SkPerspIter {
public:
    /** Iterate a line through the matrix [x,y] ... [x+count-1, y].
        @param m    The matrix we will be iterating a line through
        @param x    The initial X coordinate to be mapped through the matrix
        @param y    The initial Y coordinate to be mapped through the matrix
        @param count The number of points (x,y) (x+1,y) (x+2,y) ... we will eventually map
    */
    SkPerspIter(const SkMatrix& m, SkScalar x, SkScalar y, int count);
    
    /** Return the buffer of [x,y] fixed point values we will be filling.
        This always returns the same value, so it can be saved across calls to
        next().
    */
    const SkFixed* getXY() const { return fStorage; }

    /** Return the number of [x,y] pairs that have been filled in the getXY() buffer.
        When this returns 0, the iterator is finished.
    */
    int next();
    
private:
    enum {
        kShift  = 4,
        kCount  = (1 << kShift)
    };
    const SkMatrix& fMatrix;
    SkFixed         fStorage[kCount * 2];
    SkFixed         fX, fY;
    SkScalar        fSX, fSY;
    int             fCount;
};

#endif
