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

#ifndef SkDevice_DEFINED
#define SkDevice_DEFINED

#include "SkRefCnt.h"
#include "SkBitmap.h"
#include "SkCanvas.h"
#include "SkColor.h"

class SkDraw;
struct SkIRect;
class SkMatrix;
class SkRegion;

class SkDevice : public SkRefCnt {
public:
    SkDevice();
    /** Construct a new device, extracting the width/height/config/isOpaque values from
        the bitmap. If transferPixelOwnership is true, and the bitmap claims to own its
        own pixels (getOwnsPixels() == true), then transfer this responsibility to the
        device, and call setOwnsPixels(false) on the bitmap.
        
        Subclasses may override the destructor, which is virtual, even though this class
        doesn't have one. SkRefCnt does.
    
        @param bitmap   A copy of this bitmap is made and stored in the device
    */
    SkDevice(const SkBitmap& bitmap);

    /** Return the width of the device (in pixels).
    */
    int width() const { return fBitmap.width(); }
    /** Return the height of the device (in pixels).
    */
    int height() const { return fBitmap.height(); }
    /** Return the bitmap config of the device's pixels
    */
    SkBitmap::Config config() const { return fBitmap.getConfig(); }
    /** Returns true if the device's bitmap's config treats every pixels as
        implicitly opaque.
    */
    bool isOpaque() const { return fBitmap.isOpaque(); }
    
    /** Return the bounds of the device
    */
    void getBounds(SkIRect* bounds) const;
    
    /** Return true if the specified rectangle intersects the bounds of the
        device. If sect is not NULL and there is an intersection, sect returns
        the intersection.
    */
    bool intersects(const SkIRect& r, SkIRect* sect = NULL) const;

    /** Return the bitmap associated with this device. Call this each time you need
        to access the bitmap, as it notifies the subclass to perform any flushing
        etc. before you examine the pixels.
        @param changePixels set to true if the caller plans to change the pixels
        @return the device's bitmap
    */
    const SkBitmap& accessBitmap(bool changePixels);

    /** Helper to erase the entire device to the specified color (including
        alpha).
    */
    void eraseColor(SkColor eraseColor);

    /** Called when this device is installed into a Canvas. Balanaced by a call
        to unlockPixels() when the device is removed from a Canvas.
    */
    virtual void lockPixels();
    virtual void unlockPixels();

    /** Called with the correct matrix and clip before this device is drawn
        to using those settings. If your subclass overrides this, be sure to
        call through to the base class as well.
    */
    virtual void setMatrixClip(const SkMatrix&, const SkRegion&);

    /** Called when this device gains focus (i.e becomes the current device
        for drawing).
    */
    virtual void gainFocus(SkCanvas*) {}

    /** These are called inside the per-device-layer loop for each draw call.
     When these are called, we have already applied any saveLayer operations,
     and are handling any looping from the paint, and any effects from the
     DrawFilter.
     */
    virtual void drawPaint(const SkDraw&, const SkPaint& paint);
    virtual void drawPoints(const SkDraw&, SkCanvas::PointMode mode, size_t count,
                            const SkPoint[], const SkPaint& paint);
    virtual void drawRect(const SkDraw&, const SkRect& r,
                          const SkPaint& paint);
    virtual void drawPath(const SkDraw&, const SkPath& path,
                          const SkPaint& paint);
    virtual void drawBitmap(const SkDraw&, const SkBitmap& bitmap,
                            const SkMatrix& matrix, const SkPaint& paint);
    virtual void drawSprite(const SkDraw&, const SkBitmap& bitmap,
                            int x, int y, const SkPaint& paint);
    virtual void drawText(const SkDraw&, const void* text, size_t len,
                          SkScalar x, SkScalar y, const SkPaint& paint);
    virtual void drawPosText(const SkDraw&, const void* text, size_t len,
                             const SkScalar pos[], SkScalar constY,
                             int scalarsPerPos, const SkPaint& paint);
    virtual void drawTextOnPath(const SkDraw&, const void* text, size_t len,
                                const SkPath& path, const SkMatrix* matrix,
                                const SkPaint& paint);
    virtual void drawVertices(const SkDraw&, SkCanvas::VertexMode, int vertexCount,
                              const SkPoint verts[], const SkPoint texs[],
                              const SkColor colors[], SkXfermode* xmode,
                              const uint16_t indices[], int indexCount,
                              const SkPaint& paint);
    virtual void drawDevice(const SkDraw&, SkDevice*, int x, int y,
                            const SkPaint&);

protected:
    /** Update as needed the pixel value in the bitmap, so that the caller can access
        the pixels directly. Note: only the pixels field should be altered. The config/width/height/rowbytes
        must remain unchanged.
    */
    virtual void onAccessBitmap(SkBitmap*);

private:
    SkBitmap fBitmap;
};

#endif
