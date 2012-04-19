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

#ifndef SkBounder_DEFINED
#define SkBounder_DEFINED

#include "SkTypes.h"
#include "SkRefCnt.h"
#include "SkPoint.h"

struct SkGlyph;
struct SkIRect;
struct SkPoint;
struct SkRect;
class SkPaint;
class SkPath;
class SkRegion;

/** \class SkBounder

    Base class for intercepting the device bounds of shapes before they are drawn.
    Install a subclass of this in your canvas.
*/
class SkBounder : public SkRefCnt {
public:
    SkBounder();

    /* Call to perform a clip test before calling onIRect. 
       Returns the result from onIRect.
    */
    bool doIRect(const SkIRect&);
    bool doIRectGlyph(const SkIRect& , int x, int y, const SkGlyph&);

protected:
    /** Override in your subclass. This is called with the device bounds of an
        object (text, geometry, image) just before it is drawn. If your method
        returns false, the drawing for that shape is aborted. If your method
        returns true, drawing continues. The bounds your method receives have already
        been transformed in to device coordinates, and clipped to the current clip.
    */
    virtual bool onIRect(const SkIRect&) {
        return false;
    }

    /** Passed to onIRectGlyph with the information about the current glyph.
        LSB and RSB are fixed-point (16.16) coordinates of the start and end
        of the glyph's advance
     */
    struct GlyphRec {
        SkIPoint    fLSB;   //!< fixed-point left-side-bearing of the glyph
        SkIPoint    fRSB;   //!< fixed-point right-side-bearing of the glyph
        uint16_t    fGlyphID;
        uint16_t    fFlags; //!< currently set to 0
    };

    /** Optionally, override in your subclass to receive the glyph ID when
        text drawing supplies the device bounds of the object.
    */
    virtual bool onIRectGlyph(const SkIRect& r, const GlyphRec&) {
        return onIRect(r);
    }

    /** Called after each shape has been drawn. The default implementation does
        nothing, but your override could use this notification to signal itself
        that the offscreen being rendered into needs to be updated to the screen.
    */
    virtual void commit();

private:
    bool doHairline(const SkPoint&, const SkPoint&, const SkPaint&);
    bool doRect(const SkRect&, const SkPaint&);
    bool doPath(const SkPath&, const SkPaint&, bool doFill);
    void setClip(const SkRegion* clip) { fClip = clip; }

    const SkRegion* fClip;
    friend class SkAutoBounderCommit;
    friend class SkDraw;
    friend class SkDrawIter;
    friend struct Draw1Glyph;
    friend class SkMaskFilter;
};

#endif

