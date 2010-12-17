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

#ifndef SkDrawFilter_DEFINED
#define SkDrawFilter_DEFINED

#include "SkRefCnt.h"

////////////////// EXPERIMENTAL //////////////////////////

class SkCanvas;
class SkPaint;

/** Right before something is being draw, filter() is called with the
    current canvas and paint. If it returns true, then drawing proceeds
    with the (possibly modified) canvas/paint, and then restore() is called
    to restore the canvas/paint to their state before filter() was called.
    If filter returns false, canvas/paint should not have been changed, and
    restore() will not be called.
*/
class SkDrawFilter : public SkRefCnt {
public:
    enum Type {
        kPaint_Type,
        kPoint_Type,
        kLine_Type,
        kBitmap_Type,
        kRect_Type,
        kPath_Type,
        kText_Type
    };

    /** Return true to allow the draw to continue (with possibly modified
        canvas/paint). If true is returned, then restore() will be called.
    */
    virtual bool filter(SkCanvas*, SkPaint*, Type) = 0;
    /** If filter() returned true, then restore() will be called to restore the
        canvas/paint to their previous states
    */
    virtual void restore(SkCanvas*, SkPaint*, Type) = 0;
};

#endif
