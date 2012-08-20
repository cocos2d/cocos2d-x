#ifndef SkImageRef_ashmem_DEFINED
#define SkImageRef_ashmem_DEFINED

#include "SkImageRef.h"

struct SkAshmemRec {
    int     fFD;
    void*   fAddr;
    size_t  fSize;
    bool    fPinned;
};

class SkImageRef_ashmem : public SkImageRef {
public:
    SkImageRef_ashmem(SkStream*, SkBitmap::Config, int sampleSize = 1);
    virtual ~SkImageRef_ashmem();
    
    // overrides
    virtual void flatten(SkFlattenableWriteBuffer&) const;
    virtual Factory getFactory() const {
        return Create;
    }
    static SkPixelRef* Create(SkFlattenableReadBuffer&);

protected:
    virtual bool onDecode(SkImageDecoder* codec, SkStream* stream,
                          SkBitmap* bitmap, SkBitmap::Config config,
                          SkImageDecoder::Mode mode);
    
    virtual void* onLockPixels(SkColorTable**);
    virtual void onUnlockPixels();
    
private:
    SkImageRef_ashmem(SkFlattenableReadBuffer&);
    void closeFD();

    SkColorTable* fCT;
    SkAshmemRec fRec;

    typedef SkImageRef INHERITED;
};

#endif
