#ifndef SkPictureFlat_DEFINED
#define SkPictureFlat_DEFINED

#include "SkChunkAlloc.h"
#include "SkBitmap.h"
#include "SkPicture.h"
#include "SkMatrix.h"
#include "SkPaint.h"
#include "SkPath.h"
#include "SkRegion.h"

enum DrawType {
    UNUSED,
    CLIP_PATH,
    CLIP_REGION,
    CLIP_RECT,
    CONCAT,
    DRAW_BITMAP,
    DRAW_BITMAP_MATRIX,
    DRAW_BITMAP_RECT,
    DRAW_CLEAR,
    DRAW_DATA,
    DRAW_PAINT,
    DRAW_PATH,
    DRAW_PICTURE,
    DRAW_POINTS,
    DRAW_POS_TEXT,
    DRAW_POS_TEXT_H,
    DRAW_POS_TEXT_H_TOP_BOTTOM, // fast variant of DRAW_POS_TEXT_H
    DRAW_RECT,
    DRAW_SPRITE,
    DRAW_TEXT,
    DRAW_TEXT_ON_PATH,
    DRAW_TEXT_TOP_BOTTOM,   // fast variant of DRAW_TEXT
    DRAW_VERTICES,
    RESTORE,
    ROTATE,
    SAVE,
    SAVE_LAYER,
    SCALE,
    SET_MATRIX,
    SKEW,
    TRANSLATE
};

enum DrawVertexFlags {
    DRAW_VERTICES_HAS_TEXS    = 0x01,
    DRAW_VERTICES_HAS_COLORS  = 0x02,
    DRAW_VERTICES_HAS_INDICES = 0x04
};

class SkRefCntPlayback {
public:
    SkRefCntPlayback();
    virtual ~SkRefCntPlayback();
    
    int count() const { return fCount; }
    
    void reset(const SkRefCntSet*);

    void setCount(int count);
    SkRefCnt* set(int index, SkRefCnt*);

    virtual void setupBuffer(SkFlattenableReadBuffer& buffer) const {
        buffer.setRefCntArray(fArray, fCount);
    }
    
protected:
    int fCount;
    SkRefCnt** fArray;
};

class SkTypefacePlayback : public SkRefCntPlayback {
public:
    virtual void setupBuffer(SkFlattenableReadBuffer& buffer) const {
        buffer.setTypefaceArray((SkTypeface**)fArray, fCount);
    }
};

class SkFactoryPlayback {
public:
    SkFactoryPlayback(int count) : fCount(count) {
        fArray = SkNEW_ARRAY(SkFlattenable::Factory, count);
    }

    ~SkFactoryPlayback() {
        SkDELETE_ARRAY(fArray);
    }
    
    SkFlattenable::Factory* base() const { return fArray; }

    void setupBuffer(SkFlattenableReadBuffer& buffer) const {
        buffer.setFactoryPlayback(fArray, fCount);
    }
    
private:
    int fCount;
    SkFlattenable::Factory* fArray;
};

class SkFlatData {
public:
    static int Compare(const SkFlatData* a, const SkFlatData* b) {
        return memcmp(&a->fAllocSize, &b->fAllocSize, a->fAllocSize);
    }
    
    int index() const { return fIndex; }
    
#ifdef SK_DEBUG_SIZE
    size_t size() const { return sizeof(fIndex) + fAllocSize; }
#endif

protected:
    static SkFlatData* Alloc(SkChunkAlloc* heap, int32_t size, int index);
    
    int fIndex;
    int32_t fAllocSize;
};

class SkFlatBitmap : public SkFlatData {
public:
    static SkFlatBitmap* Flatten(SkChunkAlloc*, const SkBitmap&, int index,
                                 SkRefCntSet*);

    void unflatten(SkBitmap* bitmap, SkRefCntPlayback* rcp) const {
        SkFlattenableReadBuffer buffer(fBitmapData);
        if (rcp) {
            rcp->setupBuffer(buffer);
        }
        bitmap->unflatten(buffer);
    }

#ifdef SK_DEBUG_VALIDATE
    void validate() const {
        // to be written
    }
#endif

private:
    char fBitmapData[1];
    typedef SkFlatData INHERITED;
};

class SkFlatMatrix : public SkFlatData {
public:
    static SkFlatMatrix* Flatten(SkChunkAlloc* heap, const SkMatrix& matrix, int index);

    void unflatten(SkMatrix* result) const {
        result->unflatten(fMatrixData);
    }

#ifdef SK_DEBUG_DUMP
    void dump() const;
#endif

#ifdef SK_DEBUG_VALIDATE
    void validate() const {
        // to be written
    }
#endif

private:
    char fMatrixData[1];
    typedef SkFlatData INHERITED;
};

class SkFlatPaint : public SkFlatData {
public:
    static SkFlatPaint* Flatten(SkChunkAlloc* heap, const SkPaint& paint,
                                int index, SkRefCntSet*,
                                SkRefCntSet* faceRecorder);
    
    void unflatten(SkPaint* result, SkRefCntPlayback* rcp,
                   SkTypefacePlayback* facePlayback) const {
        Read(fPaintData, result, rcp, facePlayback);
    }
    
    static void Read(const void* storage, SkPaint* paint, SkRefCntPlayback*,
                     SkTypefacePlayback* facePlayback);

#ifdef SK_DEBUG_DUMP
    void dump() const;
#endif
    
private:
    char fPaintData[1];
    typedef SkFlatData INHERITED;
};

class SkFlatRegion : public SkFlatData {
public:
    static SkFlatRegion* Flatten(SkChunkAlloc* heap, const SkRegion& region, int index);
    
    void unflatten(SkRegion* result) const {
        result->unflatten(fRegionData);
    }

#ifdef SK_DEBUG_VALIDATE
    void validate() const {
        // to be written
    }
#endif

private:
    char fRegionData[1];
    typedef SkFlatData INHERITED;
};

#endif
