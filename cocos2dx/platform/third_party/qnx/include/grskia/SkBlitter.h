/* libs/graphics/sgl/SkBlitter.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkBlitter_DEFINED
#define SkBlitter_DEFINED

#include "SkBitmap.h"
#include "SkMatrix.h"
#include "SkPaint.h"
#include "SkRefCnt.h"
#include "SkRegion.h"
#include "SkMask.h"

class SkBlitter {
public:
    virtual ~SkBlitter();

    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha* antialias,
                           const int16_t* runs);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect& clip);

    /*  If the blitter just sets a single value for each pixel, return the
        bitmap it draws into, and assign value. If not, return NULL and ignore
        the value parameter.
    */
    virtual const SkBitmap* justAnOpaqueColor(uint32_t* value);

    // not virtual, just helpers
    void blitMaskRegion(const SkMask& mask, const SkRegion& clip);
    void blitRectRegion(const SkIRect& rect, const SkRegion& clip);
    void blitRegion(const SkRegion& clip);

    // factories
    static SkBlitter* Choose(const SkBitmap& device,
                             const SkMatrix& matrix,
                             const SkPaint& paint) {
        return Choose(device, matrix, paint, NULL, 0);
    }

    static SkBlitter* Choose(const SkBitmap& device,
                             const SkMatrix& matrix,
                             const SkPaint& paint,
                             void* storage, size_t storageSize);

    static SkBlitter* ChooseSprite(const SkBitmap& device,
                                   const SkPaint&,
                                   const SkBitmap& src,
                                   int left, int top,
                                   void* storage, size_t storageSize);

private:
};

/** This blitter silently never draws anything.
*/
class SkNullBlitter : public SkBlitter {
public:
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha[], const int16_t runs[]);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect& clip);
    virtual const SkBitmap* justAnOpaqueColor(uint32_t* value);
};

/** Wraps another (real) blitter, and ensures that the real blitter is only
    called with coordinates that have been clipped by the specified clipRect.
    This means the caller need not perform the clipping ahead of time.
*/
class SkRectClipBlitter : public SkBlitter {
public:
    void init(SkBlitter* blitter, const SkIRect& clipRect) {
        SkASSERT(!clipRect.isEmpty());
        fBlitter = blitter;
        fClipRect = clipRect;
    }

    // overrides
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha[], const int16_t runs[]);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect& clip);
    virtual const SkBitmap* justAnOpaqueColor(uint32_t* value);

private:
    SkBlitter*  fBlitter;
    SkIRect     fClipRect;
};

/** Wraps another (real) blitter, and ensures that the real blitter is only
called with coordinates that have been clipped by the specified clipRgn.
This means the caller need not perform the clipping ahead of time.
*/
class SkRgnClipBlitter : public SkBlitter {
public:
    void init(SkBlitter* blitter, const SkRegion* clipRgn) {
        SkASSERT(clipRgn && !clipRgn->isEmpty());
        fBlitter = blitter;
        fRgn = clipRgn;
    }

    // overrides
    virtual void blitH(int x, int y, int width);
    virtual void blitAntiH(int x, int y, const SkAlpha[], const int16_t runs[]);
    virtual void blitV(int x, int y, int height, SkAlpha alpha);
    virtual void blitRect(int x, int y, int width, int height);
    virtual void blitMask(const SkMask&, const SkIRect& clip);
    virtual const SkBitmap* justAnOpaqueColor(uint32_t* value);

private:
    SkBlitter*      fBlitter;
    const SkRegion* fRgn;
};

class SkBlitterClipper {
public:
    SkBlitter*  apply(SkBlitter* blitter, const SkRegion* clip,
                      const SkIRect* bounds = NULL);

private:
    SkNullBlitter       fNullBlitter;
    SkRectClipBlitter   fRectBlitter;
    SkRgnClipBlitter    fRgnBlitter;
};

#endif
