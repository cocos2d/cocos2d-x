#ifndef SkProxyCanvas_DEFINED
#define SkProxyCanvas_DEFINED

#include "SkCanvas.h"

/** This class overrides all virtual methods on SkCanvas, and redirects them
    to a "proxy", another SkCanvas instance. It can be the basis for
    intercepting (and possibly modifying) calls to a canvas.
 
    There must be a proxy installed before the proxycanvas can be used (i.e.
    before its virtual methods can be called).
 */
class SkProxyCanvas : public SkCanvas {
public:
    SkProxyCanvas() : fProxy(NULL) {}
    SkProxyCanvas(SkCanvas* proxy);
    virtual ~SkProxyCanvas();
    
    SkCanvas*   getProxy() const { return fProxy; }
    void        setProxy(SkCanvas* proxy);
    
    // overrides from SkCanvas

    virtual int save(SaveFlags flags = kMatrixClip_SaveFlag);
    virtual int saveLayer(const SkRect* bounds, const SkPaint* paint,
                          SaveFlags flags = kARGB_ClipLayer_SaveFlag);
    virtual void restore();

    virtual bool translate(SkScalar dx, SkScalar dy);
    virtual bool scale(SkScalar sx, SkScalar sy);
    virtual bool rotate(SkScalar degrees);
    virtual bool skew(SkScalar sx, SkScalar sy);
    virtual bool concat(const SkMatrix& matrix);
    virtual void setMatrix(const SkMatrix& matrix);
    
    virtual bool clipRect(const SkRect& rect,
                          SkRegion::Op op = SkRegion::kIntersect_Op);
    virtual bool clipPath(const SkPath& path,
                          SkRegion::Op op = SkRegion::kIntersect_Op);
    virtual bool clipRegion(const SkRegion& deviceRgn,
                            SkRegion::Op op = SkRegion::kIntersect_Op);

    virtual void drawPaint(const SkPaint& paint);
    virtual void drawPoints(PointMode mode, size_t count, const SkPoint pts[],
                            const SkPaint& paint);
    virtual void drawRect(const SkRect& rect, const SkPaint& paint);
    virtual void drawPath(const SkPath& path, const SkPaint& paint);
    virtual void drawBitmap(const SkBitmap& bitmap, SkScalar left, SkScalar top,
                            const SkPaint* paint = NULL);
    virtual void drawBitmapRect(const SkBitmap& bitmap, const SkIRect* src,
                                const SkRect& dst, const SkPaint* paint = NULL);
    virtual void drawBitmapMatrix(const SkBitmap& bitmap, const SkMatrix& m,
                                  const SkPaint* paint = NULL);
    virtual void drawSprite(const SkBitmap& bitmap, int left, int top,
                            const SkPaint* paint = NULL);
    virtual void drawText(const void* text, size_t byteLength, SkScalar x,
                          SkScalar y, const SkPaint& paint);
    virtual void drawPosText(const void* text, size_t byteLength,
                             const SkPoint pos[], const SkPaint& paint);
    virtual void drawPosTextH(const void* text, size_t byteLength,
                              const SkScalar xpos[], SkScalar constY,
                              const SkPaint& paint);
    virtual void drawTextOnPath(const void* text, size_t byteLength,
                                const SkPath& path, const SkMatrix* matrix,
                                const SkPaint& paint);
    virtual void drawPicture(SkPicture&);
    virtual void drawVertices(VertexMode vmode, int vertexCount,
                              const SkPoint vertices[], const SkPoint texs[],
                              const SkColor colors[], SkXfermode* xmode,
                              const uint16_t indices[], int indexCount,
                              const SkPaint& paint);
    virtual void drawData(const void* data, size_t length);

    virtual SkBounder* setBounder(SkBounder* bounder);
    virtual SkDrawFilter* setDrawFilter(SkDrawFilter* filter);

private:
    SkCanvas*   fProxy;
    
    typedef SkCanvas INHERITED;
};

#endif
