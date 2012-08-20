/*
 * Copyright (C) 2010 The Android Open Source Project
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

class SkClipStack;
class SkDevice;
class SkDraw;
struct SkIRect;
class SkMatrix;
class SkMetaData;
class SkRegion;

/** \class SkDeviceFactory

    DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice

    Devices that extend SkDevice should also provide a SkDeviceFactory class
    to pass into SkCanvas.  Doing so will eliminate the need to extend
    SkCanvas as well.
*/
class SK_API SkDeviceFactory : public SkRefCnt {
public:
    SkDeviceFactory();
    virtual ~SkDeviceFactory();
    virtual SkDevice* newDevice(SkCanvas*, SkBitmap::Config, int width,
                                int height, bool isOpaque, bool isLayer) = 0;
};

class SK_API SkRasterDeviceFactory : public SkDeviceFactory {
public:
    virtual SkDevice* newDevice(SkCanvas*, SkBitmap::Config, int width,
                                int height, bool isOpaque, bool isLayer);
};

class SK_API SkDevice : public SkRefCnt {
public:
//    SkDevice();

    /**
     *  Construct a new device with the specified bitmap as its backend. It is
     *  valid for the bitmap to have no pixels associated with it. In that case,
     *  any drawing to this device will have no effect.
    */
    SkDevice(const SkBitmap& bitmap);

    /**
     *  Create a new raster device and have the pixels be automatically
     *  allocated. The rowBytes of the device will be computed automatically
     *  based on the config and the width.
     *
     *  @param config   The desired config for the pixels. If the request cannot
     *                  be met, the closest matching support config will be used.
     *  @param width    width (in pixels) of the device
     *  @param height   height (in pixels) of the device
     *  @param isOpaque Set to true if it is known that all of the pixels will
     *                  be drawn to opaquely. Used as an accelerator when drawing
     *                  these pixels to another device.
     */
    SkDevice(SkBitmap::Config config, int width, int height, bool isOpaque = false);

    virtual ~SkDevice();

    /**
     *  DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice
     *
     *  Return the factory that will create this subclass of SkDevice.
     *  The returned factory is cached by the device, and so its reference count
     *  is not changed by this call.
     */
    SkDeviceFactory* getDeviceFactory();

    /**
     *  Creates a device that is of the same type as this device (e.g. SW-raster,
     *  GPU, or PDF). The backing store for this device is created automatically
     *  (e.g. offscreen pixels or FBO or whatever is appropriate).
     *
     *  @param width    width of the device to create
     *  @param height   height of the device to create
     *  @param isOpaque performance hint, set to true if you know that you will
     *                  draw into this device such that all of the pixels will
     *                  be opaque.
     */
    SkDevice* createCompatibleDevice(SkBitmap::Config config, 
                                     int width, int height,
                                     bool isOpaque);

    enum Capabilities {
        kGL_Capability     = 0x1,  //!< mask indicating GL support
        kVector_Capability = 0x2,  //!< mask indicating a vector representation
        kAll_Capabilities  = 0x3
    };
    virtual uint32_t getDeviceCapabilities() { return 0; }

    /** Return the width of the device (in pixels).
    */
    virtual int width() const { return fBitmap.width(); }
    /** Return the height of the device (in pixels).
    */
    virtual int height() const { return fBitmap.height(); }

    /**
     *  Return the device's origin: its offset in device coordinates from
     *  the default origin in its canvas' matrix/clip
     */
    const SkIPoint& getOrigin() const { return fOrigin; }

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

    /** Clears the entire device to the specified color (including alpha).
     *  Ignores the clip.
     */
    virtual void clear(SkColor color);

    /**
     * Deprecated name for clear.
     */
    void eraseColor(SkColor eraseColor) { this->clear(eraseColor); }

    /** Called when this device is installed into a Canvas. Balanaced by a call
        to unlockPixels() when the device is removed from a Canvas.
    */
    virtual void lockPixels();
    virtual void unlockPixels();

    /** Return the device's associated texture, or NULL. If returned, it may be
        drawn into another device
     */
    virtual SkGpuTexture* accessTexture() { return NULL; }

    /**
     *  Called with the correct matrix and clip before this device is drawn
     *  to using those settings. If your subclass overrides this, be sure to
     *  call through to the base class as well.
     *
     *  The clipstack is another view of the clip. It records the actual
     *  geometry that went into building the region. It is present for devices
     *  that want to parse it, but is not required: the region is a complete
     *  picture of the current clip. (i.e. if you regionize all of the geometry
     *  in the clipstack, you will arrive at an equivalent region to the one
     *  passed in).
    */
    virtual void setMatrixClip(const SkMatrix&, const SkRegion&,
                               const SkClipStack&);

    /** Called when this device gains focus (i.e becomes the current device
        for drawing).
    */
    virtual void gainFocus(SkCanvas*, const SkMatrix&, const SkRegion&,
                           const SkClipStack&) {}

    /** Causes any deferred drawing to the device to be completed.
     */
    virtual void flush() {}

    /**
     *  Copy the pixels from the device into bitmap. Returns true on success.
     *  If false is returned, then the bitmap parameter is left unchanged.
     *  The bitmap parameter is treated as output-only, and will be completely
     *  overwritten (if the method returns true).
     */
    virtual bool readPixels(const SkIRect& srcRect, SkBitmap* bitmap);

    /**
     *  Similar to draw sprite, this method will copy the pixels in bitmap onto
     *  the device, with the top/left corner specified by (x, y). The pixel
     *  values in the device are completely replaced: there is no blending.
     */
    virtual void writePixels(const SkBitmap& bitmap, int x, int y);

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
    /**
     *  If pathIsMutable, then the implementation is allowed to cast path to a
     *  non-const pointer and modify it in place (as an optimization). Canvas
     *  may do this to implement helpers such as drawOval, by placing a temp
     *  path on the stack to hold the representation of the oval.
     *
     *  If prePathMatrix is not null, it should logically be applied before any
     *  stroking or other effects. If there are no effects on the paint that
     *  affect the geometry/rasterization, then the pre matrix can just be
     *  pre-concated with the current matrix.
     */
    virtual void drawPath(const SkDraw&, const SkPath& path,
                          const SkPaint& paint,
                          const SkMatrix* prePathMatrix = NULL,
                          bool pathIsMutable = false);
    virtual void drawBitmap(const SkDraw&, const SkBitmap& bitmap,
                            const SkIRect* srcRectOrNull,
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
#ifdef ANDROID
    virtual void drawPosTextOnPath(const SkDraw& draw, const void* text, size_t len,
                                   const SkPoint pos[], const SkPaint& paint,
                                   const SkPath& path, const SkMatrix* matrix);
#endif
    virtual void drawVertices(const SkDraw&, SkCanvas::VertexMode, int vertexCount,
                              const SkPoint verts[], const SkPoint texs[],
                              const SkColor colors[], SkXfermode* xmode,
                              const uint16_t indices[], int indexCount,
                              const SkPaint& paint);
    virtual void drawDevice(const SkDraw&, SkDevice*, int x, int y,
                            const SkPaint&);

    ///////////////////////////////////////////////////////////////////////////

    SkMetaData& getMetaData();

    struct TextFlags {
        uint32_t            fFlags;     // SkPaint::getFlags()
        SkPaint::Hinting    fHinting;
    };

    /**
     *  Device may filter the text flags for drawing text here. If it wants to
     *  make a change to the specified values, it should write them into the
     *  textflags parameter (output) and return true. If the paint is fine as
     *  is, then ignore the textflags parameter and return false.
     *
     *  The baseclass SkDevice filters based on its depth and blitters.
     */
    virtual bool filterTextFlags(const SkPaint& paint, TextFlags*);

protected:
    /**
     *  DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice
     *
     *  subclasses can override this to return a new (or ref'd) instance of
     *  a device factory that will create this subclass of device. This value
     *  is cached, so it should get called at most once for a given instance.
     *
     *  If not overriden then createCompatibleDevice will be used by canvas.
     */
    virtual SkDeviceFactory* onNewDeviceFactory();

    /** Update as needed the pixel value in the bitmap, so that the caller can access
        the pixels directly. Note: only the pixels field should be altered. The config/width/height/rowbytes
        must remain unchanged.
    */
    virtual void onAccessBitmap(SkBitmap*);

    enum Usage {
       kGeneral_Usage,
       kSaveLayer_Usage, // <! internal use only
    };
    /**
     * subclasses should override this to implement createCompatibleDevice.
     */
    virtual SkDevice* onCreateCompatibleDevice(SkBitmap::Config config, 
                                               int width, int height, 
                                               bool isOpaque,
                                               Usage usage);

    SkPixelRef* getPixelRef() const { return fBitmap.pixelRef(); }
    // just for subclasses, to assign a custom pixelref
    SkPixelRef* setPixelRef(SkPixelRef* pr, size_t offset) {
        fBitmap.setPixelRef(pr, offset);
        return pr;
    }

private:
    friend class SkCanvas;
    // just called by SkCanvas when built as a layer
    void setOrigin(int x, int y) { fOrigin.set(x, y); }
    // just called by SkCanvas for saveLayer
    SkDevice* createCompatibleDeviceForSaveLayer(SkBitmap::Config config, 
                                                 int width, int height,
                                                 bool isOpaque);

    SkBitmap    fBitmap;
    SkIPoint    fOrigin;
    SkMetaData* fMetaData;

    SkDeviceFactory* fCachedDeviceFactory;
};

#endif
