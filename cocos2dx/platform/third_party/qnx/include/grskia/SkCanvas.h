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

#ifndef SkCanvas_DEFINED
#define SkCanvas_DEFINED

#include "SkTypes.h"
#include "SkBitmap.h"
#include "SkDeque.h"
#include "SkClipStack.h"
#include "SkPaint.h"
#include "SkRefCnt.h"
#include "SkPath.h"
#include "SkRegion.h"
#include "SkScalarCompare.h"
#include "SkXfermode.h"

class SkBounder;
class SkDevice;
class SkDeviceFactory;
class SkDraw;
class SkDrawFilter;
class SkPicture;

/** \class SkCanvas

    A Canvas encapsulates all of the state about drawing into a device (bitmap).
    This includes a reference to the device itself, and a stack of matrix/clip
    values. For any given draw call (e.g. drawRect), the geometry of the object
    being drawn is transformed by the concatenation of all the matrices in the
    stack. The transformed geometry is clipped by the intersection of all of
    the clips in the stack.

    While the Canvas holds the state of the drawing device, the state (style)
    of the object being drawn is held by the Paint, which is provided as a
    parameter to each of the draw() methods. The Paint holds attributes such as
    color, typeface, textSize, strokeWidth, shader (e.g. gradients, patterns),
    etc.
*/
class SK_API SkCanvas : public SkRefCnt {
public:
    /**
        DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice

        Construct a canvas with the given device factory.
        @param factory  Specify the factory for generating additional devices.
                        The factory may be null, in which case
                        SkRasterDeviceFactory will be used.
    */
    explicit SkCanvas(SkDeviceFactory* factory = NULL);

    /** Construct a canvas with the specified device to draw into.  The device
        factory will be retrieved from the passed device.

        @param device   Specifies a device for the canvas to draw into.
    */
    explicit SkCanvas(SkDevice* device);

    /** Deprecated - Construct a canvas with the specified bitmap to draw into.
        @param bitmap   Specifies a bitmap for the canvas to draw into. Its
                        structure are copied to the canvas.
    */
    explicit SkCanvas(const SkBitmap& bitmap);
    virtual ~SkCanvas();

    ///////////////////////////////////////////////////////////////////////////

    /** Return the canvas' device object, which may be null. The device holds
        the bitmap of the pixels that the canvas draws into. The reference count
        of the returned device is not changed by this call.
    */
    SkDevice* getDevice() const;

    /** Specify a device for this canvas to draw into. If it is not null, its
        reference count is incremented. If the canvas was already holding a
        device, its reference count is decremented. The new device is returned.
    */
    SkDevice* setDevice(SkDevice* device);

    /**
     *  saveLayer() can create another device (which is later drawn onto
     *  the previous device). getTopDevice() returns the top-most device current
     *  installed. Note that this can change on other calls like save/restore,
     *  so do not access this device after subsequent canvas calls.
     *  The reference count of the device is not changed.
     */
    SkDevice* getTopDevice() const;

    /**
     *  Create a new raster device and make it current. This also returns
     *  the new device.
     */
    SkDevice* setBitmapDevice(const SkBitmap& bitmap);

    /**
     * DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice
     *
     *  Return the current device factory, or NULL. The reference count of
     *  the returned factory is not changed.
     */
    SkDeviceFactory* getDeviceFactory() const { return fDeviceFactory; }

    /**
     *  DEPRECATED: Will be replaced by SkDevice::createCompatibleDevice
     *
     *  Replace any existing factory with the specified factory, unrefing the
     *  previous (if any), and refing the new one (if any). For convenience,
     *  the factory parameter is also returned.
     */
    SkDeviceFactory* setDeviceFactory(SkDeviceFactory*);

    /**
     * Shortcut for getDevice()->createCompatibleDevice(...)
     */
    SkDevice* createCompatibleDevice(SkBitmap::Config config, 
                                    int width, int height,
                                    bool isOpaque);

    ///////////////////////////////////////////////////////////////////////////

    /**
     *  Copy the pixels from the device into bitmap. Returns true on success.
     *  If false is returned, then the bitmap parameter is left unchanged.
     *  The bitmap parameter is treated as output-only, and will be completely
     *  overwritten (if the method returns true).
     */
    bool readPixels(const SkIRect& srcRect, SkBitmap* bitmap);
    bool readPixels(SkBitmap* bitmap);

    /**
     *  Similar to draw sprite, this method will copy the pixels in bitmap onto
     *  the device, with the top/left corner specified by (x, y). The pixel
     *  values in the device are completely replaced: there is no blending.
     */
    void writePixels(const SkBitmap& bitmap, int x, int y);

    ///////////////////////////////////////////////////////////////////////////

    enum SaveFlags {
        /** save the matrix state, restoring it on restore() */
        kMatrix_SaveFlag            = 0x01,
        /** save the clip state, restoring it on restore() */
        kClip_SaveFlag              = 0x02,
        /** the layer needs to support per-pixel alpha */
        kHasAlphaLayer_SaveFlag     = 0x04,
        /** the layer needs to support 8-bits per color component */
        kFullColorLayer_SaveFlag    = 0x08,
        /** the layer should clip against the bounds argument */
        kClipToLayer_SaveFlag       = 0x10,

        // helper masks for common choices
        kMatrixClip_SaveFlag        = 0x03,
        kARGB_NoClipLayer_SaveFlag  = 0x0F,
        kARGB_ClipLayer_SaveFlag    = 0x1F
    };

    /** This call saves the current matrix, clip, and drawFilter, and pushes a
        copy onto a private stack. Subsequent calls to translate, scale,
        rotate, skew, concat or clipRect, clipPath, and setDrawFilter all
        operate on this copy.
        When the balancing call to restore() is made, the previous matrix, clip,
        and drawFilter are restored.
        @return The value to pass to restoreToCount() to balance this save()
    */
    virtual int save(SaveFlags flags = kMatrixClip_SaveFlag);

    /** This behaves the same as save(), but in addition it allocates an
        offscreen bitmap. All drawing calls are directed there, and only when
        the balancing call to restore() is made is that offscreen transfered to
        the canvas (or the previous layer).
        @param bounds (may be null) This rect, if non-null, is used as a hint to
                      limit the size of the offscreen, and thus drawing may be
                      clipped to it, though that clipping is not guaranteed to
                      happen. If exact clipping is desired, use clipRect().
        @param paint (may be null) This is copied, and is applied to the
                     offscreen when restore() is called
        @param flags  LayerFlags
        @return The value to pass to restoreToCount() to balance this save()
    */
    virtual int saveLayer(const SkRect* bounds, const SkPaint* paint,
                          SaveFlags flags = kARGB_ClipLayer_SaveFlag);

    /** This behaves the same as save(), but in addition it allocates an
        offscreen bitmap. All drawing calls are directed there, and only when
        the balancing call to restore() is made is that offscreen transfered to
        the canvas (or the previous layer).
        @param bounds (may be null) This rect, if non-null, is used as a hint to
                      limit the size of the offscreen, and thus drawing may be
                      clipped to it, though that clipping is not guaranteed to
                      happen. If exact clipping is desired, use clipRect().
        @param alpha  This is applied to the offscreen when restore() is called.
        @param flags  LayerFlags
        @return The value to pass to restoreToCount() to balance this save()
    */
    int saveLayerAlpha(const SkRect* bounds, U8CPU alpha,
                       SaveFlags flags = kARGB_ClipLayer_SaveFlag);

    /** This call balances a previous call to save(), and is used to remove all
        modifications to the matrix/clip/drawFilter state since the last save
        call.
        It is an error to call restore() more times than save() was called.
    */
    virtual void restore();

    /** Returns the number of matrix/clip states on the SkCanvas' private stack.
        This will equal # save() calls - # restore() calls.
    */
    int getSaveCount() const;

    /** Efficient way to pop any calls to save() that happened after the save
        count reached saveCount. It is an error for saveCount to be less than
        getSaveCount()
        @param saveCount    The number of save() levels to restore from
    */
    void restoreToCount(int saveCount);

    /** Preconcat the current matrix with the specified translation
        @param dx   The distance to translate in X
        @param dy   The distance to translate in Y
        returns true if the operation succeeded (e.g. did not overflow)
    */
    virtual bool translate(SkScalar dx, SkScalar dy);

    /** Preconcat the current matrix with the specified scale.
        @param sx   The amount to scale in X
        @param sy   The amount to scale in Y
        returns true if the operation succeeded (e.g. did not overflow)
    */
    virtual bool scale(SkScalar sx, SkScalar sy);

    /** Preconcat the current matrix with the specified rotation.
        @param degrees  The amount to rotate, in degrees
        returns true if the operation succeeded (e.g. did not overflow)
    */
    virtual bool rotate(SkScalar degrees);

    /** Preconcat the current matrix with the specified skew.
        @param sx   The amount to skew in X
        @param sy   The amount to skew in Y
        returns true if the operation succeeded (e.g. did not overflow)
    */
    virtual bool skew(SkScalar sx, SkScalar sy);

    /** Preconcat the current matrix with the specified matrix.
        @param matrix   The matrix to preconcatenate with the current matrix
        @return true if the operation succeeded (e.g. did not overflow)
    */
    virtual bool concat(const SkMatrix& matrix);

    /** Replace the current matrix with a copy of the specified matrix.
        @param matrix The matrix that will be copied into the current matrix.
    */
    virtual void setMatrix(const SkMatrix& matrix);

    /** Helper for setMatrix(identity). Sets the current matrix to identity.
    */
    void resetMatrix();

    /** Modify the current clip with the specified rectangle.
        @param rect The rect to intersect with the current clip
        @param op The region op to apply to the current clip
        @return true if the canvas' clip is non-empty
    */
    virtual bool clipRect(const SkRect& rect,
                          SkRegion::Op op = SkRegion::kIntersect_Op);

    /** Modify the current clip with the specified path.
        @param path The path to apply to the current clip
        @param op The region op to apply to the current clip
        @return true if the canvas' new clip is non-empty
    */
    virtual bool clipPath(const SkPath& path,
                          SkRegion::Op op = SkRegion::kIntersect_Op);

    /** Modify the current clip with the specified region. Note that unlike
        clipRect() and clipPath() which transform their arguments by the current
        matrix, clipRegion() assumes its argument is already in device
        coordinates, and so no transformation is performed.
        @param deviceRgn    The region to apply to the current clip
        @param op The region op to apply to the current clip
        @return true if the canvas' new clip is non-empty
    */
    virtual bool clipRegion(const SkRegion& deviceRgn,
                            SkRegion::Op op = SkRegion::kIntersect_Op);

    /** Helper for clipRegion(rgn, kReplace_Op). Sets the current clip to the
        specified region. This does not intersect or in any other way account
        for the existing clip region.
        @param deviceRgn The region to copy into the current clip.
        @return true if the new clip region is non-empty
    */
    bool setClipRegion(const SkRegion& deviceRgn) {
        return this->clipRegion(deviceRgn, SkRegion::kReplace_Op);
    }

    /** Enum describing how to treat edges when performing quick-reject tests
        of a geometry against the current clip. Treating them as antialiased
        (kAA_EdgeType) will take into account the extra pixels that may be drawn
        if the edge does not lie exactly on a device pixel boundary (after being
        transformed by the current matrix).
    */
    enum EdgeType {
        /** Treat the edges as B&W (not antialiased) for the purposes of testing
            against the current clip
        */
        kBW_EdgeType,
        /** Treat the edges as antialiased for the purposes of testing
            against the current clip
        */
        kAA_EdgeType
    };

    /** Return true if the specified rectangle, after being transformed by the
        current matrix, would lie completely outside of the current clip. Call
        this to check if an area you intend to draw into is clipped out (and
        therefore you can skip making the draw calls).
        @param rect the rect to compare with the current clip
        @param et  specifies how to treat the edges (see EdgeType)
        @return true if the rect (transformed by the canvas' matrix) does not
                     intersect with the canvas' clip
    */
    bool quickReject(const SkRect& rect, EdgeType et) const;

    /** Return true if the specified path, after being transformed by the
        current matrix, would lie completely outside of the current clip. Call
        this to check if an area you intend to draw into is clipped out (and
        therefore you can skip making the draw calls). Note, for speed it may
        return false even if the path itself might not intersect the clip
        (i.e. the bounds of the path intersects, but the path does not).
        @param path The path to compare with the current clip
        @param et  specifies how to treat the edges (see EdgeType)
        @return true if the path (transformed by the canvas' matrix) does not
                     intersect with the canvas' clip
    */
    bool quickReject(const SkPath& path, EdgeType et) const;

    /** Return true if the horizontal band specified by top and bottom is
        completely clipped out. This is a conservative calculation, meaning
        that it is possible that if the method returns false, the band may still
        in fact be clipped out, but the converse is not true. If this method
        returns true, then the band is guaranteed to be clipped out.
        @param top  The top of the horizontal band to compare with the clip
        @param bottom The bottom of the horizontal and to compare with the clip
        @return true if the horizontal band is completely clipped out (i.e. does
                     not intersect the current clip)
    */
    bool quickRejectY(SkScalar top, SkScalar bottom, EdgeType et) const;

    /** Return the bounds of the current clip (in local coordinates) in the
        bounds parameter, and return true if it is non-empty. This can be useful
        in a way similar to quickReject, in that it tells you that drawing
        outside of these bounds will be clipped out.
    */
    bool getClipBounds(SkRect* bounds, EdgeType et = kAA_EdgeType) const;

    /** Fill the entire canvas' bitmap (restricted to the current clip) with the
        specified ARGB color, using the specified mode.
        @param a    the alpha component (0..255) of the color to fill the canvas
        @param r    the red component (0..255) of the color to fill the canvas
        @param g    the green component (0..255) of the color to fill the canvas
        @param b    the blue component (0..255) of the color to fill the canvas
        @param mode the mode to apply the color in (defaults to SrcOver)
    */
    void drawARGB(U8CPU a, U8CPU r, U8CPU g, U8CPU b,
                  SkXfermode::Mode mode = SkXfermode::kSrcOver_Mode);

    /** Fill the entire canvas' bitmap (restricted to the current clip) with the
        specified color and mode.
        @param color    the color to draw with
        @param mode the mode to apply the color in (defaults to SrcOver)
    */
    void drawColor(SkColor color,
                   SkXfermode::Mode mode = SkXfermode::kSrcOver_Mode);

    /**
     *  This erases the entire drawing surface to the specified color,
     *  irrespective of the clip. It does not blend with the previous pixels,
     *  but always overwrites them.
     *
     *  It is roughly equivalent to the following:
     *      canvas.save();
     *      canvas.clipRect(hugeRect, kReplace_Op);
     *      paint.setColor(color);
     *      paint.setXfermodeMode(kSrc_Mode);
     *      canvas.drawPaint(paint);
     *      canvas.restore();
     *  though it is almost always much more efficient.
     */
    virtual void clear(SkColor);

    /**
     *  Fill the entire canvas' bitmap (restricted to the current clip) with the
     *  specified paint.
     *  @param paint    The paint used to fill the canvas
     */
    virtual void drawPaint(const SkPaint& paint);

    enum PointMode {
        /** drawPoints draws each point separately */
        kPoints_PointMode,
        /** drawPoints draws each pair of points as a line segment */
        kLines_PointMode,
        /** drawPoints draws the array of points as a polygon */
        kPolygon_PointMode
    };

    /** Draw a series of points, interpreted based on the PointMode mode. For
        all modes, the count parameter is interpreted as the total number of
        points. For kLine mode, count/2 line segments are drawn.
        For kPoint mode, each point is drawn centered at its coordinate, and its
        size is specified by the paint's stroke-width. It draws as a square,
        unless the paint's cap-type is round, in which the points are drawn as
        circles.
        For kLine mode, each pair of points is drawn as a line segment,
        respecting the paint's settings for cap/join/width.
        For kPolygon mode, the entire array is drawn as a series of connected
        line segments.
        Note that, while similar, kLine and kPolygon modes draw slightly
        differently than the equivalent path built with a series of moveto,
        lineto calls, in that the path will draw all of its contours at once,
        with no interactions if contours intersect each other (think XOR
        xfermode). drawPoints always draws each element one at a time.
        @param mode     PointMode specifying how to draw the array of points.
        @param count    The number of points in the array
        @param pts      Array of points to draw
        @param paint    The paint used to draw the points
    */
    virtual void drawPoints(PointMode mode, size_t count, const SkPoint pts[],
                            const SkPaint& paint);

    /** Helper method for drawing a single point. See drawPoints() for a more
        details.
    */
    void drawPoint(SkScalar x, SkScalar y, const SkPaint& paint);

    /** Draws a single pixel in the specified color.
        @param x        The X coordinate of which pixel to draw
        @param y        The Y coordiante of which pixel to draw
        @param color    The color to draw
    */
    void drawPoint(SkScalar x, SkScalar y, SkColor color);

    /** Draw a line segment with the specified start and stop x,y coordinates,
        using the specified paint. NOTE: since a line is always "framed", the
        paint's Style is ignored.
        @param x0    The x-coordinate of the start point of the line
        @param y0    The y-coordinate of the start point of the line
        @param x1    The x-coordinate of the end point of the line
        @param y1    The y-coordinate of the end point of the line
        @param paint The paint used to draw the line
    */
    void drawLine(SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1,
                  const SkPaint& paint);

    /** Draw the specified rectangle using the specified paint. The rectangle
        will be filled or stroked based on the Style in the paint.
        @param rect     The rect to be drawn
        @param paint    The paint used to draw the rect
    */
    virtual void drawRect(const SkRect& rect, const SkPaint& paint);

    /** Draw the specified rectangle using the specified paint. The rectangle
        will be filled or framed based on the Style in the paint.
        @param rect     The rect to be drawn
        @param paint    The paint used to draw the rect
    */
    void drawIRect(const SkIRect& rect, const SkPaint& paint)
    {
        SkRect r;
        r.set(rect);    // promotes the ints to scalars
        this->drawRect(r, paint);
    }

    /** Draw the specified rectangle using the specified paint. The rectangle
        will be filled or framed based on the Style in the paint.
        @param left     The left side of the rectangle to be drawn
        @param top      The top side of the rectangle to be drawn
        @param right    The right side of the rectangle to be drawn
        @param bottom   The bottom side of the rectangle to be drawn
        @param paint    The paint used to draw the rect
    */
    void drawRectCoords(SkScalar left, SkScalar top, SkScalar right,
                        SkScalar bottom, const SkPaint& paint);

    /** Draw the specified oval using the specified paint. The oval will be
        filled or framed based on the Style in the paint.
        @param oval     The rectangle bounds of the oval to be drawn
        @param paint    The paint used to draw the oval
    */
    void drawOval(const SkRect& oval, const SkPaint&);

    /** Draw the specified circle using the specified paint. If radius is <= 0,
        then nothing will be drawn. The circle will be filled
        or framed based on the Style in the paint.
        @param cx       The x-coordinate of the center of the cirle to be drawn
        @param cy       The y-coordinate of the center of the cirle to be drawn
        @param radius   The radius of the cirle to be drawn
        @param paint    The paint used to draw the circle
    */
    void drawCircle(SkScalar cx, SkScalar cy, SkScalar radius,
                    const SkPaint& paint);

    /** Draw the specified arc, which will be scaled to fit inside the
        specified oval. If the sweep angle is >= 360, then the oval is drawn
        completely. Note that this differs slightly from SkPath::arcTo, which
        treats the sweep angle mod 360.
        @param oval The bounds of oval used to define the shape of the arc
        @param startAngle Starting angle (in degrees) where the arc begins
        @param sweepAngle Sweep angle (in degrees) measured clockwise
        @param useCenter true means include the center of the oval. For filling
                         this will draw a wedge. False means just use the arc.
        @param paint    The paint used to draw the arc
    */
    void drawArc(const SkRect& oval, SkScalar startAngle, SkScalar sweepAngle,
                 bool useCenter, const SkPaint& paint);

    /** Draw the specified round-rect using the specified paint. The round-rect
        will be filled or framed based on the Style in the paint.
        @param rect     The rectangular bounds of the roundRect to be drawn
        @param rx       The x-radius of the oval used to round the corners
        @param ry       The y-radius of the oval used to round the corners
        @param paint    The paint used to draw the roundRect
    */
    void drawRoundRect(const SkRect& rect, SkScalar rx, SkScalar ry,
                       const SkPaint& paint);

    /** Draw the specified path using the specified paint. The path will be
        filled or framed based on the Style in the paint.
        @param path     The path to be drawn
        @param paint    The paint used to draw the path
    */
    virtual void drawPath(const SkPath& path, const SkPaint& paint);

    /** Draw the specified bitmap, with its top/left corner at (x,y), using the
        specified paint, transformed by the current matrix. Note: if the paint
        contains a maskfilter that generates a mask which extends beyond the
        bitmap's original width/height, then the bitmap will be drawn as if it
        were in a Shader with CLAMP mode. Thus the color outside of the original
        width/height will be the edge color replicated.
        @param bitmap   The bitmap to be drawn
        @param left     The position of the left side of the bitmap being drawn
        @param top      The position of the top side of the bitmap being drawn
        @param paint    The paint used to draw the bitmap, or NULL
    */
    virtual void drawBitmap(const SkBitmap& bitmap, SkScalar left, SkScalar top,
                            const SkPaint* paint = NULL);

    /** Draw the specified bitmap, with the specified matrix applied (before the
        canvas' matrix is applied).
        @param bitmap   The bitmap to be drawn
        @param src      Optional: specify the subset of the bitmap to be drawn
        @param dst      The destination rectangle where the scaled/translated
                        image will be drawn
        @param paint    The paint used to draw the bitmap, or NULL
    */
    virtual void drawBitmapRect(const SkBitmap& bitmap, const SkIRect* src,
                                const SkRect& dst, const SkPaint* paint = NULL);

    virtual void drawBitmapMatrix(const SkBitmap& bitmap, const SkMatrix& m,
                                  const SkPaint* paint = NULL);

    /** Draw the specified bitmap, with its top/left corner at (x,y),
        NOT transformed by the current matrix. Note: if the paint
        contains a maskfilter that generates a mask which extends beyond the
        bitmap's original width/height, then the bitmap will be drawn as if it
        were in a Shader with CLAMP mode. Thus the color outside of the original
        width/height will be the edge color replicated.
        @param bitmap   The bitmap to be drawn
        @param left     The position of the left side of the bitmap being drawn
        @param top      The position of the top side of the bitmap being drawn
        @param paint    The paint used to draw the bitmap, or NULL
    */
    virtual void drawSprite(const SkBitmap& bitmap, int left, int top,
                            const SkPaint* paint = NULL);

    /** Draw the text, with origin at (x,y), using the specified paint.
        The origin is interpreted based on the Align setting in the paint.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param x        The x-coordinate of the origin of the text being drawn
        @param y        The y-coordinate of the origin of the text being drawn
        @param paint    The paint used for the text (e.g. color, size, style)
    */
    virtual void drawText(const void* text, size_t byteLength, SkScalar x,
                          SkScalar y, const SkPaint& paint);

    /** Draw the text, with each character/glyph origin specified by the pos[]
        array. The origin is interpreted by the Align setting in the paint.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param pos      Array of positions, used to position each character
        @param paint    The paint used for the text (e.g. color, size, style)
        */
    virtual void drawPosText(const void* text, size_t byteLength,
                             const SkPoint pos[], const SkPaint& paint);

    /** Draw the text, with each character/glyph origin specified by the x
        coordinate taken from the xpos[] array, and the y from the constY param.
        The origin is interpreted by the Align setting in the paint.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param xpos     Array of x-positions, used to position each character
        @param constY   The shared Y coordinate for all of the positions
        @param paint    The paint used for the text (e.g. color, size, style)
        */
    virtual void drawPosTextH(const void* text, size_t byteLength,
                              const SkScalar xpos[], SkScalar constY,
                              const SkPaint& paint);

    /** Draw the text, with origin at (x,y), using the specified paint, along
        the specified path. The paint's Align setting determins where along the
        path to start the text.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param path         The path the text should follow for its baseline
        @param hOffset      The distance along the path to add to the text's
                            starting position
        @param vOffset      The distance above(-) or below(+) the path to
                            position the text
        @param paint        The paint used for the text
    */
    void drawTextOnPathHV(const void* text, size_t byteLength,
                          const SkPath& path, SkScalar hOffset,
                          SkScalar vOffset, const SkPaint& paint);

    /** Draw the text, with origin at (x,y), using the specified paint, along
        the specified path. The paint's Align setting determins where along the
        path to start the text.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param path         The path the text should follow for its baseline
        @param matrix       (may be null) Applied to the text before it is
                            mapped onto the path
        @param paint        The paint used for the text
        */
    virtual void drawTextOnPath(const void* text, size_t byteLength,
                                const SkPath& path, const SkMatrix* matrix,
                                const SkPaint& paint);

#ifdef ANDROID
    /** Draw the text on path, with each character/glyph origin specified by the pos[]
        array. The origin is interpreted by the Align setting in the paint.
        @param text The text to be drawn
        @param byteLength   The number of bytes to read from the text parameter
        @param pos      Array of positions, used to position each character
        @param paint    The paint used for the text (e.g. color, size, style)
        @param path The path to draw on
        @param matrix The canvas matrix
        */
    void drawPosTextOnPath(const void* text, size_t byteLength,
                           const SkPoint pos[], const SkPaint& paint,
                           const SkPath& path, const SkMatrix* matrix);
#endif

    /** Draw the picture into this canvas. This method effective brackets the
        playback of the picture's draw calls with save/restore, so the state
        of this canvas will be unchanged after this call. This contrasts with
        the more immediate method SkPicture::draw(), which does not bracket
        the canvas with save/restore, thus the canvas may be left in a changed
        state after the call.
        @param picture The recorded drawing commands to playback into this
                       canvas.
    */
    virtual void drawPicture(SkPicture& picture);

    enum VertexMode {
        kTriangles_VertexMode,
        kTriangleStrip_VertexMode,
        kTriangleFan_VertexMode
    };

    /** Draw the array of vertices, interpreted as triangles (based on mode).
        @param vmode How to interpret the array of vertices
        @param vertexCount The number of points in the vertices array (and
                    corresponding texs and colors arrays if non-null)
        @param vertices Array of vertices for the mesh
        @param texs May be null. If not null, specifies the coordinate
                             in texture space for each vertex.
        @param colors May be null. If not null, specifies a color for each
                      vertex, to be interpolated across the triangle.
        @param xmode Used if both texs and colors are present. In this
                    case the colors are combined with the texture using mode,
                    before being drawn using the paint. If mode is null, then
                    kMultiply_Mode is used.
        @param indices If not null, array of indices to reference into the
                    vertex (texs, colors) array.
        @param indexCount number of entries in the indices array (if not null)
        @param paint Specifies the shader/texture if present.
    */
    virtual void drawVertices(VertexMode vmode, int vertexCount,
                              const SkPoint vertices[], const SkPoint texs[],
                              const SkColor colors[], SkXfermode* xmode,
                              const uint16_t indices[], int indexCount,
                              const SkPaint& paint);

    /** Send a blob of data to the canvas.
        For canvases that draw, this call is effectively a no-op, as the data
        is not parsed, but just ignored. However, this call exists for
        subclasses like SkPicture's recording canvas, that can store the data
        and then play it back later (via another call to drawData).
     */
    virtual void drawData(const void* data, size_t length);

    //////////////////////////////////////////////////////////////////////////

    /** Get the current bounder object.
        The bounder's reference count is unchaged.
        @return the canva's bounder (or NULL).
    */
    SkBounder*  getBounder() const { return fBounder; }

    /** Set a new bounder (or NULL).
        Pass NULL to clear any previous bounder.
        As a convenience, the parameter passed is also returned.
        If a previous bounder exists, its reference count is decremented.
        If bounder is not NULL, its reference count is incremented.
        @param bounder the new bounder (or NULL) to be installed in the canvas
        @return the set bounder object
    */
    virtual SkBounder* setBounder(SkBounder* bounder);

    /** Get the current filter object. The filter's reference count is not
        affected. The filter is saved/restored, just like the matrix and clip.
        @return the canvas' filter (or NULL).
    */
    SkDrawFilter* getDrawFilter() const;

    /** Set the new filter (or NULL). Pass NULL to clear any existing filter.
        As a convenience, the parameter is returned. If an existing filter
        exists, its refcnt is decrement. If the new filter is not null, its
        refcnt is incremented. The filter is saved/restored, just like the
        matrix and clip.
        @param filter the new filter (or NULL)
        @return the new filter
    */
    virtual SkDrawFilter* setDrawFilter(SkDrawFilter* filter);

    //////////////////////////////////////////////////////////////////////////

    /** Return the current matrix on the canvas.
        This does not account for the translate in any of the devices.
        @return The current matrix on the canvas.
    */
    const SkMatrix& getTotalMatrix() const;

    /** Return the current device clip (concatenation of all clip calls).
        This does not account for the translate in any of the devices.
        @return the current device clip (concatenation of all clip calls).
    */
    const SkRegion& getTotalClip() const;

    /**
     *  Return the current clipstack. This mirrors the result in getTotalClip()
     *  but is represented as a stack of geometric clips + region-ops.
     */
    const SkClipStack& getTotalClipStack() const;

    void setExternalMatrix(const SkMatrix* = NULL);

    ///////////////////////////////////////////////////////////////////////////

    /** After calling saveLayer(), there can be any number of devices that make
        up the top-most drawing area. LayerIter can be used to iterate through
        those devices. Note that the iterator is only valid until the next API
        call made on the canvas. Ownership of all pointers in the iterator stays
        with the canvas, so none of them should be modified or deleted.
    */
    class SK_API LayerIter /*: SkNoncopyable*/ {
    public:
        /** Initialize iterator with canvas, and set values for 1st device */
        LayerIter(SkCanvas*, bool skipEmptyClips);
        ~LayerIter();

        /** Return true if the iterator is done */
        bool done() const { return fDone; }
        /** Cycle to the next device */
        void next();

        // These reflect the current device in the iterator

        SkDevice*       device() const;
        const SkMatrix& matrix() const;
        const SkRegion& clip() const;
        const SkPaint&  paint() const;
        int             x() const;
        int             y() const;

    private:
        // used to embed the SkDrawIter object directly in our instance, w/o
        // having to expose that class def to the public. There is an assert
        // in our constructor to ensure that fStorage is large enough
        // (though needs to be a compile-time-assert!). We use intptr_t to work
        // safely with 32 and 64 bit machines (to ensure the storage is enough)
        intptr_t          fStorage[32];
        class SkDrawIter* fImpl;    // this points at fStorage
        SkPaint           fDefaultPaint;
        bool              fDone;
    };

protected:
    // all of the drawBitmap variants call this guy
    virtual void commonDrawBitmap(const SkBitmap&, const SkIRect*,
                                  const SkMatrix&, const SkPaint& paint);

private:
    class MCRec;

    SkClipStack fClipStack;
    SkDeque     fMCStack;
    // points to top of stack
    MCRec*      fMCRec;
    // the first N recs that can fit here mean we won't call malloc
    uint32_t    fMCRecStorage[32];

    SkBounder*  fBounder;
    SkDevice*   fLastDeviceToGainFocus;
    SkDeviceFactory* fDeviceFactory;

    void prepareForDeviceDraw(SkDevice*, const SkMatrix&, const SkRegion&,
                              const SkClipStack& clipStack);

    bool fDeviceCMDirty;            // cleared by updateDeviceCMCache()
    void updateDeviceCMCache();

    friend class SkDrawIter;    // needs setupDrawForLayerDevice()

    SkDevice* createLayerDevice(SkBitmap::Config, int width, int height, 
                                bool isOpaque);

    SkDevice* init(SkDevice*);
    void internalDrawBitmap(const SkBitmap&, const SkIRect*, const SkMatrix& m,
                                  const SkPaint* paint);
    void drawDevice(SkDevice*, int x, int y, const SkPaint*);
    // shared by save() and saveLayer()
    int internalSave(SaveFlags flags);
    void internalRestore();

    /*  These maintain a cache of the clip bounds in local coordinates,
        (converted to 2s-compliment if floats are slow).
     */
    mutable SkRectCompareType fLocalBoundsCompareType;
    mutable bool              fLocalBoundsCompareTypeDirty;

    mutable SkRectCompareType fLocalBoundsCompareTypeBW;
    mutable bool              fLocalBoundsCompareTypeDirtyBW;

    /* Get the local clip bounds with an anti-aliased edge.
     */
    const SkRectCompareType& getLocalClipBoundsCompareType() const {
        return getLocalClipBoundsCompareType(kAA_EdgeType);
    }

    const SkRectCompareType& getLocalClipBoundsCompareType(EdgeType et) const {
        if (et == kAA_EdgeType) {
            if (fLocalBoundsCompareTypeDirty) {
                this->computeLocalClipBoundsCompareType(et);
                fLocalBoundsCompareTypeDirty = false;
            }
            return fLocalBoundsCompareType;
        } else {
            if (fLocalBoundsCompareTypeDirtyBW) {
                this->computeLocalClipBoundsCompareType(et);
                fLocalBoundsCompareTypeDirtyBW = false;
            }
            return fLocalBoundsCompareTypeBW;
        }
    }
    void computeLocalClipBoundsCompareType(EdgeType et) const;

    SkMatrix    fExternalMatrix, fExternalInverse;
    bool        fUseExternalMatrix;

    class AutoValidateClip : ::SkNoncopyable {
    public:
        explicit AutoValidateClip(SkCanvas* canvas) : fCanvas(canvas) {
            fCanvas->validateClip();
        }
        ~AutoValidateClip() { fCanvas->validateClip(); }

    private:
        const SkCanvas* fCanvas;
    };

#ifdef SK_DEBUG
    void validateClip() const;
#else
    void validateClip() const {}
#endif
};

/** Stack helper class to automatically call restoreToCount() on the canvas
    when this object goes out of scope. Use this to guarantee that the canvas
    is restored to a known state.
*/
class SkAutoCanvasRestore : SkNoncopyable {
public:
    SkAutoCanvasRestore(SkCanvas* canvas, bool doSave) : fCanvas(canvas) {
        SkASSERT(canvas);
        fSaveCount = canvas->getSaveCount();
        if (doSave) {
            canvas->save();
        }
    }
    ~SkAutoCanvasRestore() {
        fCanvas->restoreToCount(fSaveCount);
    }

private:
    SkCanvas*   fCanvas;
    int         fSaveCount;
};

#endif

