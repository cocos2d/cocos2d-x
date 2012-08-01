#ifndef SkDumpCanvas_DEFINED
#define SkDumpCanvas_DEFINED

#include "SkCanvas.h"

/** This class overrides all the draw methods on SkCanvas, and formats them
    as text, and then sends that to a Dumper helper object.
 
    Typical use might be to dump a display list to a log file to see what is
    being drawn.
 */
class SkDumpCanvas : public SkCanvas {
public:
    class Dumper;

    explicit SkDumpCanvas(Dumper* = 0);
    virtual ~SkDumpCanvas();
    
    enum Verb {
        kNULL_Verb,

        kSave_Verb,
        kRestore_Verb,
        
        kMatrix_Verb,
        
        kClip_Verb,
        
        kDrawPaint_Verb,
        kDrawPoints_Verb,
        kDrawRect_Verb,
        kDrawPath_Verb,
        kDrawBitmap_Verb,
        kDrawText_Verb,
        kDrawPicture_Verb,
        kDrawVertices_Verb,
        kDrawData_Verb
    };
    
    /** Subclasses of this are installed on the DumpCanvas, and then called for
        each drawing command.
     */
    class Dumper : public SkRefCnt {
    public:
        virtual void dump(SkDumpCanvas*, SkDumpCanvas::Verb, const char str[],
                          const SkPaint*) = 0;
    };
        
    Dumper* getDumper() const { return fDumper; }
    void    setDumper(Dumper*);
    
    int getNestLevel() const { return fNestLevel; }
    
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
    virtual void drawData(const void*, size_t);

private:
    Dumper* fDumper;
    int     fNestLevel; // for nesting recursive elements like pictures
    
    void dump(Verb, const SkPaint*, const char format[], ...);

    typedef SkCanvas INHERITED;
};

/** Formats the draw commands, and send them to a function-pointer provided
    by the caller.
 */
class SkFormatDumper : public SkDumpCanvas::Dumper {
public:
    SkFormatDumper(void (*)(const char text[], void* refcon), void* refcon);
    
    // override from baseclass that does the formatting, and in turn calls
    // the function pointer that was passed to the constructor
    virtual void dump(SkDumpCanvas*, SkDumpCanvas::Verb, const char str[],
                      const SkPaint*);
    
private:
    void (*fProc)(const char*, void*);
    void* fRefcon;
    
    typedef SkDumpCanvas::Dumper INHERITED;
};

/** Subclass of Dumper that dumps the drawing command to SkDebugf
 */
class SkDebugfDumper : public SkFormatDumper {
public:
    SkDebugfDumper();

private:
    typedef SkFormatDumper INHERITED;
};

#endif
