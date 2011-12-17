/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef SkPageFlipper_DEFINED
#define SkPageFlipper_DEFINED

#include "SkRegion.h"

/** SkPageFlipper manages alternating inval/dirty regions for a rectangular area
    (like a bitmap). You call inval() to accumulate inval areas, and then when
    you're ready to "flip" pages (i.e. draw into the one you've been
    invalidating) you call update, which swaps the inval regions, and returns
    two things to you: 1) the final inval region to be drawn into, and 2) the
    region of pixels that should be copied from the "front" page onto the one
    you're about to draw into. This copyBits region will be disjoint from the
    inval region, so both need to be handled.
 */
class SkPageFlipper {
public:
    SkPageFlipper();
    SkPageFlipper(int width, int height);
    
    int width() const { return fWidth; }
    int height() const { return fHeight; }

    void resize(int width, int height);

    bool isDirty() const { return !fDirty1->isEmpty(); }
    const SkRegion& dirtyRgn() const { return *fDirty1; }

    void inval();
    void inval(const SkIRect&);
    void inval(const SkRegion&);
    void inval(const SkRect&, bool antialias);

    /** When you're ready to write to the back page, call update. The returned
        region is the invalidate are that needs to be drawn to. The copyBits
        region (provided by the caller) is the area that should be copied from
        the front page to the back page (will not intersect with the returned
        inval region.
     
        Once this is called, the two internal regions are swapped, so the *new*
        back inval region is ready to receive new inval calls.
     */
    const SkRegion& update(SkRegion* copyBits);

private:
    SkRegion*   fDirty0;
    SkRegion*   fDirty1;
    SkRegion    fDirty0Storage;
    SkRegion    fDirty1Storage;
    int         fWidth;
    int         fHeight;
};

#endif

