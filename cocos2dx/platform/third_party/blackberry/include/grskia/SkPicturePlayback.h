#ifndef SkPicturePlayback_DEFINED
#define SkPicturePlayback_DEFINED

#include "SkPicture.h"
#include "SkReader32.h"

#include "SkBitmap.h"
#include "SkMatrix.h"
#include "SkPaint.h"
#include "SkPath.h"
#include "SkPathHeap.h"
#include "SkRegion.h"
#include "SkPictureFlat.h"

#ifdef ANDROID
#include "SkThread.h"
#endif

class SkPictureRecord;
class SkStream;
class SkWStream;

class SkPicturePlayback {
public:
    SkPicturePlayback();
    SkPicturePlayback(const SkPicturePlayback& src);
    explicit SkPicturePlayback(const SkPictureRecord& record);
    explicit SkPicturePlayback(SkStream*);

    virtual ~SkPicturePlayback();

    void draw(SkCanvas& canvas);

    void serialize(SkWStream*) const;

    void dumpSize() const;
    
    // Can be called in the middle of playback (the draw() call). WIll abort the
    // drawing and return from draw() after the "current" op code is done
    void abort();

private:

    class TextContainer {
    public:
        size_t length() { return fByteLength; }
        const void* text() { return (const void*) fText; }
        size_t fByteLength;
        const char* fText;
    };

    const SkBitmap& getBitmap() {
        int index = getInt();
        SkASSERT(index > 0);
        return fBitmaps[index - 1];
    }

    int getIndex() { return fReader.readInt(); }
    int getInt() { return fReader.readInt(); }

    const SkMatrix* getMatrix() {
        int index = getInt();
        if (index == 0) {
            return NULL;
        }
        SkASSERT(index > 0 && index <= fMatrixCount);
        return &fMatrices[index - 1];
    }

    const SkPath& getPath() {
        return (*fPathHeap)[getInt() - 1];
    }

    SkPicture& getPicture() {
        int index = getInt();
        SkASSERT(index > 0 && index <= fPictureCount);
        return *fPictureRefs[index - 1];
    }
    
    const SkPaint* getPaint() {
        int index = getInt();
        if (index == 0) {
            return NULL;
        }
        SkASSERT(index > 0 && index <= fPaintCount);
        return &fPaints[index - 1];
    }

    const SkRect* getRectPtr() {
        if (fReader.readBool()) {
            return fReader.skipRect();
        } else {
            return NULL;
        }
    }

    const SkIRect* getIRectPtr() {
        if (fReader.readBool()) {
            return (const SkIRect*)fReader.skip(sizeof(SkIRect));
        } else {
            return NULL;
        }
    }

    const SkRegion& getRegion() {
        int index = getInt();
        SkASSERT(index > 0);
        return fRegions[index - 1];
    }

    SkScalar getScalar() { return fReader.readScalar(); }

    void getText(TextContainer* text) {
        size_t length = text->fByteLength = getInt();
        text->fText = (const char*)fReader.skip(length);
    }

    void init();

#ifdef SK_DEBUG_SIZE
public:
    int size(size_t* sizePtr);
    int bitmaps(size_t* size);
    int paints(size_t* size);
    int paths(size_t* size);
    int regions(size_t* size);
#endif

#ifdef SK_DEBUG_DUMP
private:
    void dumpBitmap(const SkBitmap& bitmap) const;
    void dumpMatrix(const SkMatrix& matrix) const;
    void dumpPaint(const SkPaint& paint) const;
    void dumpPath(const SkPath& path) const;
    void dumpPicture(const SkPicture& picture) const;
    void dumpRegion(const SkRegion& region) const;
    int dumpDrawType(char* bufferPtr, char* buffer, DrawType drawType);
    int dumpInt(char* bufferPtr, char* buffer, char* name);
    int dumpRect(char* bufferPtr, char* buffer, char* name);
    int dumpPoint(char* bufferPtr, char* buffer, char* name);
    void dumpPointArray(char** bufferPtrPtr, char* buffer, int count);
    int dumpPtr(char* bufferPtr, char* buffer, char* name, void* ptr);
    int dumpRectPtr(char* bufferPtr, char* buffer, char* name);
    int dumpScalar(char* bufferPtr, char* buffer, char* name);
    void dumpText(char** bufferPtrPtr, char* buffer);
    void dumpStream();

public:
    void dump() const;
#endif

private:
    SkPathHeap* fPathHeap;  // reference counted
    SkBitmap* fBitmaps;
    int fBitmapCount;
    SkMatrix* fMatrices;
    int fMatrixCount;
    SkPaint* fPaints;
    int fPaintCount;
    SkRegion* fRegions;
    int fRegionCount;
    mutable SkFlattenableReadBuffer fReader;

    SkPicture** fPictureRefs;
    int fPictureCount;

    SkRefCntPlayback fRCPlayback;
    SkTypefacePlayback fTFPlayback;
    SkFactoryPlayback*   fFactoryPlayback;
#ifdef ANDROID
    SkMutex fDrawMutex;
#endif
};

#endif
