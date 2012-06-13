#ifndef SkPictureRecord_DEFINED
#define SkPictureRecord_DEFINED

#include "SkCanvas.h"
#include "SkFlattenable.h"
#include "SkPathHeap.h"
#include "SkPicture.h"
#include "SkPictureFlat.h"
#include "SkTemplates.h"
#include "SkWriter32.h"

class SkPictureRecord : public SkCanvas {
public:
    SkPictureRecord(uint32_t recordFlags);
    virtual ~SkPictureRecord();

    // overrides from SkCanvas
    virtual int save(SaveFlags);
    virtual int saveLayer(const SkRect* bounds, const SkPaint*, SaveFlags);
    virtual void restore();
    virtual bool translate(SkScalar dx, SkScalar dy);
    virtual bool scale(SkScalar sx, SkScalar sy);
    virtual bool rotate(SkScalar degrees);
    virtual bool skew(SkScalar sx, SkScalar sy);
    virtual bool concat(const SkMatrix& matrix);
    virtual void setMatrix(const SkMatrix& matrix);
    virtual bool clipRect(const SkRect& rect, SkRegion::Op op);
    virtual bool clipPath(const SkPath& path, SkRegion::Op op);
    virtual bool clipRegion(const SkRegion& region, SkRegion::Op op);
    virtual void clear(SkColor);
    virtual void drawPaint(const SkPaint& paint);
    virtual void drawPoints(PointMode, size_t count, const SkPoint pts[],
                            const SkPaint&);
    virtual void drawRect(const SkRect& rect, const SkPaint&);
    virtual void drawPath(const SkPath& path, const SkPaint&);
    virtual void drawBitmap(const SkBitmap&, SkScalar left, SkScalar top,
                            const SkPaint*);
    virtual void drawBitmapRect(const SkBitmap&, const SkIRect* src,
                                const SkRect& dst, const SkPaint*);
    virtual void drawBitmapMatrix(const SkBitmap&, const SkMatrix&,
                                  const SkPaint*);
    virtual void drawSprite(const SkBitmap&, int left, int top,
                            const SkPaint*);
    virtual void drawText(const void* text, size_t byteLength, SkScalar x, 
                          SkScalar y, const SkPaint&);
    virtual void drawPosText(const void* text, size_t byteLength, 
                             const SkPoint pos[], const SkPaint&);
    virtual void drawPosTextH(const void* text, size_t byteLength,
                      const SkScalar xpos[], SkScalar constY, const SkPaint&);
    virtual void drawTextOnPath(const void* text, size_t byteLength, 
                            const SkPath& path, const SkMatrix* matrix, 
                                const SkPaint&);
    virtual void drawPicture(SkPicture& picture);
    virtual void drawVertices(VertexMode, int vertexCount,
                          const SkPoint vertices[], const SkPoint texs[],
                          const SkColor colors[], SkXfermode*,
                          const uint16_t indices[], int indexCount,
                              const SkPaint&);
    virtual void drawData(const void*, size_t);

    void addFontMetricsTopBottom(const SkPaint& paint, SkScalar baselineY);
    
    const SkTDArray<const SkFlatBitmap* >& getBitmaps() const {
        return fBitmaps;
    }
    const SkTDArray<const SkFlatMatrix* >& getMatrices() const {
        return fMatrices;
    }
    const SkTDArray<const SkFlatPaint* >& getPaints() const {
        return fPaints;
    }
    const SkTDArray<SkPicture* >& getPictureRefs() const {
        return fPictureRefs;
    }
    const SkTDArray<const SkFlatRegion* >& getRegions() const {
        return fRegions;
    }
    
    void reset();

    const SkWriter32& writeStream() const {
        return fWriter;
    }

private:
    SkTDArray<uint32_t> fRestoreOffsetStack;

    void addDraw(DrawType drawType) {
#ifdef SK_DEBUG_TRACE
        SkDebugf("add %s\n", DrawTypeToString(drawType));
#endif
        fWriter.writeInt(drawType);
    }    
    void addInt(int value) {
        fWriter.writeInt(value);
    }
    void addScalar(SkScalar scalar) {
        fWriter.writeScalar(scalar);
    }
    
    void addBitmap(const SkBitmap& bitmap);
    void addMatrix(const SkMatrix& matrix);
    void addMatrixPtr(const SkMatrix* matrix);
    void addPaint(const SkPaint& paint);
    void addPaintPtr(const SkPaint* paint);
    void addPath(const SkPath& path);
    void addPicture(SkPicture& picture);
    void addPoint(const SkPoint& point);
    void addPoints(const SkPoint pts[], int count);
    void addRect(const SkRect& rect);
    void addRectPtr(const SkRect* rect);
    void addIRectPtr(const SkIRect* rect);
    void addRegion(const SkRegion& region);
    void addText(const void* text, size_t byteLength);

    int find(SkTDArray<const SkFlatBitmap* >& bitmaps,
                   const SkBitmap& bitmap);
    int find(SkTDArray<const SkFlatMatrix* >& matrices,
                   const SkMatrix* matrix);
    int find(SkTDArray<const SkFlatPaint* >& paints, const SkPaint* paint);
    int find(SkTDArray<const SkFlatRegion* >& regions, const SkRegion& region);

#ifdef SK_DEBUG_DUMP
public:
    void dumpMatrices();
    void dumpPaints();
#endif

#ifdef SK_DEBUG_SIZE
public:
    size_t size() const;    
    int bitmaps(size_t* size) const;
    int matrices(size_t* size) const;
    int paints(size_t* size) const;
    int paths(size_t* size) const;
    int regions(size_t* size) const;
    size_t streamlen() const;
    
    size_t fPointBytes, fRectBytes, fTextBytes;
    int fPointWrites, fRectWrites, fTextWrites;
#endif

#ifdef SK_DEBUG_VALIDATE
public:
    void validate() const;
private:
    void validateBitmaps() const;
    void validateMatrices() const;
    void validatePaints() const;
    void validatePaths() const;
    void validateRegions() const;
#else
public:
    void validate() const {}
#endif

private:
    SkChunkAlloc fHeap;
    int fBitmapIndex;
    SkTDArray<const SkFlatBitmap* > fBitmaps;
    int fMatrixIndex;
    SkTDArray<const SkFlatMatrix* > fMatrices;
    int fPaintIndex;
    SkTDArray<const SkFlatPaint* > fPaints;
    int fRegionIndex;
    SkTDArray<const SkFlatRegion* > fRegions;
    SkPathHeap* fPathHeap;  // reference counted
    SkWriter32 fWriter;

    // we ref each item in these arrays
    SkTDArray<SkPicture*> fPictureRefs;

    SkRefCntSet fRCSet;
    SkRefCntSet fTFSet;
    
    uint32_t fRecordFlags;

    friend class SkPicturePlayback;

    typedef SkCanvas INHERITED;
};

#endif
