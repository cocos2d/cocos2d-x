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

#ifndef SkStroke_DEFINED
#define SkStroke_DEFINED

#include "SkPoint.h"
#include "SkPaint.h"

struct SkRect;
class SkPath;

#define SK_DefaultStrokeWidth       SK_Scalar1
#define SK_DefaultMiterLimit        SkIntToScalar(4)


/** \class SkStroke
    SkStroke is the utility class that constructs paths by stroking
    geometries (lines, rects, ovals, roundrects, paths). This is
    invoked when a geometry or text is drawn in a canvas with the
    kStroke_Mask bit set in the paint.
*/
class SkStroke {
public:
    SkStroke();
    SkStroke(const SkPaint&);
    SkStroke(const SkPaint&, SkScalar width);   // width overrides paint.getStrokeWidth()

    SkPaint::Cap    getCap() const { return (SkPaint::Cap)fCap; }
    void        setCap(SkPaint::Cap);

    SkPaint::Join   getJoin() const { return (SkPaint::Join)fJoin; }
    void        setJoin(SkPaint::Join);

    void    setMiterLimit(SkScalar);
    void    setWidth(SkScalar);

    bool    getDoFill() const { return SkToBool(fDoFill); }
    void    setDoFill(bool doFill) { fDoFill = SkToU8(doFill); }

    void    strokeLine(const SkPoint& start, const SkPoint& end, SkPath*) const;
    void    strokeRect(const SkRect& rect, SkPath*) const;
    void    strokeOval(const SkRect& oval, SkPath*) const;
    void    strokeRRect(const SkRect& rect, SkScalar rx, SkScalar ry, SkPath*) const;
    void    strokePath(const SkPath& path, SkPath*) const;

    ////////////////////////////////////////////////////////////////

private:
    SkScalar    fWidth, fMiterLimit;
    uint8_t     fCap, fJoin;
    SkBool8     fDoFill;

    friend class SkPaint;
};

#endif

