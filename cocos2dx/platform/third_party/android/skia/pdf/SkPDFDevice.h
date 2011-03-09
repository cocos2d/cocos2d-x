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

#ifndef SkPDFDevice_DEFINED
#define SkPDFDevice_DEFINED

#include "SkRefCnt.h"
#include "SkDevice.h"
#include "SkString.h"
#include "SkPaint.h"
#include "SkPath.h"

class SkPDFArray;
class SkPDFDevice;
class SkPDFDict;
class SkPDFFont;
class SkPDFGraphicState;
class SkPDFObject;
class SkPDFStream;

class SkPDFDeviceFactory : public SkDeviceFactory {
    virtual SkDevice* newDevice(SkBitmap::Config config, int width, int height,
                                bool isOpaque, bool isForLayer);
};

/** \class SkPDFDevice

    The drawing context for the PDF backend.
*/
class SkPDFDevice : public SkDevice {
public:
    /** Create a PDF drawing context with the given width and height.
     *  72 points/in means letter paper is 612x792.
     *  @param width  Page width in points.
     *  @param height Page height in points.
     */
    SkPDFDevice(int width, int height);
    virtual ~SkPDFDevice();

    virtual SkDeviceFactory* getDeviceFactory() {
        return SkNEW(SkPDFDeviceFactory);
    }

    virtual uint32_t getDeviceCapabilities() { return kVector_Capability; }

    virtual int width() const { return fWidth; };

    virtual int height() const { return fHeight; };

    /** Called with the correct matrix and clip before this device is drawn
        to using those settings. If your subclass overrides this, be sure to
        call through to the base class as well.
    */
    virtual void setMatrixClip(const SkMatrix&, const SkRegion&);

    /** These are called inside the per-device-layer loop for each draw call.
     When these are called, we have already applied any saveLayer operations,
     and are handling any looping from the paint, and any effects from the
     DrawFilter.
     */
    virtual void drawPaint(const SkDraw&, const SkPaint& paint);
    virtual void drawPoints(const SkDraw&, SkCanvas::PointMode mode,
                            size_t count, const SkPoint[],
                            const SkPaint& paint);
    virtual void drawRect(const SkDraw&, const SkRect& r, const SkPaint& paint);
    virtual void drawPath(const SkDraw&, const SkPath& path,
                          const SkPaint& paint);
    virtual void drawBitmap(const SkDraw&, const SkBitmap& bitmap,
                            const SkMatrix& matrix, const SkPaint& paint);
    virtual void drawSprite(const SkDraw&, const SkBitmap& bitmap, int x, int y,
                            const SkPaint& paint);
    virtual void drawText(const SkDraw&, const void* text, size_t len,
                          SkScalar x, SkScalar y, const SkPaint& paint);
    virtual void drawPosText(const SkDraw&, const void* text, size_t len,
                             const SkScalar pos[], SkScalar constY,
                             int scalarsPerPos, const SkPaint& paint);
    virtual void drawTextOnPath(const SkDraw&, const void* text, size_t len,
                                const SkPath& path, const SkMatrix* matrix,
                                const SkPaint& paint);
    virtual void drawVertices(const SkDraw&, SkCanvas::VertexMode,
                              int vertexCount, const SkPoint verts[],
                              const SkPoint texs[], const SkColor colors[],
                              SkXfermode* xmode, const uint16_t indices[],
                              int indexCount, const SkPaint& paint);
    virtual void drawDevice(const SkDraw&, SkDevice*, int x, int y,
                            const SkPaint&);

    // PDF specific methods.

    /** Returns a reference to the resource dictionary for this device.
     */
    const SkRefPtr<SkPDFDict>& getResourceDict();

    /** Get the list of resources (PDF objects) used on this page.
     *  @param resourceList A list to append the resources to.
     */
    void getResources(SkTDArray<SkPDFObject*>* resourceList) const;

    /** Returns the media box for this device.
     */
    SkRefPtr<SkPDFArray> getMediaBox() const;

    /** Returns a string with the page contents.
     *  @param flipOrigin  Flip the origin between top and bottom.
     */
    SkString content(bool flipOrigin) const;

private:
    int fWidth;
    int fHeight;
    SkRefPtr<SkPDFDict> fResourceDict;

    SkTDArray<SkPDFGraphicState*> fGraphicStateResources;
    SkTDArray<SkPDFObject*> fXObjectResources;
    SkTDArray<SkPDFFont*> fFontResources;

    // In PDF, transforms and clips can only be undone by popping the graphic
    // state to before the transform or clip was applied.  Because it can be
    // a lot of work to reapply a clip and because this class has to apply
    // different transforms to accomplish various operations, the clip is
    // always applied before a transform and always at a different graphic
    // state-stack level than a transform.  This strategy results in the
    // following possible states for the graphic state stack:
    // empty:  (identity transform and clip to page)
    // one entry: a transform
    // one entry: a clip
    // two entries: a clip and then a transform
    struct GraphicStackEntry {
        SkColor fColor;
        SkScalar fTextSize;
        SkScalar fTextScaleX;
        SkPaint::Style fTextFill;
        SkRefPtr<SkPDFFont> fFont;
        SkRefPtr<SkPDFGraphicState> fGraphicState;
        SkRegion fClip;
        SkMatrix fTransform;
    };
    struct GraphicStackEntry fGraphicStack[3];
    int fGraphicStackIndex;

    SkString fContent;

    void updateGSFromPaint(const SkPaint& newPaint, bool forText);
    int getFontResourceIndex(uint32_t fontID);

    void moveTo(SkScalar x, SkScalar y);
    void appendLine(SkScalar x, SkScalar y);
    void appendCubic(SkScalar ctl1X, SkScalar ctl1Y,
                     SkScalar ctl2X, SkScalar ctl2Y,
                     SkScalar dstX, SkScalar dstY);
    void appendRectangle(SkScalar x, SkScalar y, SkScalar w, SkScalar h);
    void emitPath(const SkPath& path);
    void closePath();
    void paintPath(SkPaint::Style style, SkPath::FillType fill);
    void strokePath();
    void pushGS();
    void popGS();
    void setTextTransform(SkScalar x, SkScalar y, SkScalar textSkewX);
    void internalDrawBitmap(const SkMatrix& matrix, const SkBitmap& bitmap,
                            const SkPaint& paint);

    SkMatrix setTransform(const SkMatrix& matrix);
};

#endif
