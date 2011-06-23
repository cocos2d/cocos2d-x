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

#ifndef SkFlipPixelRef_DEFINED
#define SkFlipPixelRef_DEFINED

#include "SkBitmap.h"
#include "SkPageFlipper.h"
#include "SkPixelRef.h"
#include "SkThread.h"

class SkRegion;

class SkFlipPixelRef : public SkPixelRef {
public:
            SkFlipPixelRef(SkBitmap::Config, int width, int height);
    virtual ~SkFlipPixelRef();
    
    bool isDirty() const { return fFlipper.isDirty(); }
    const SkRegion& dirtyRgn() const { return fFlipper.dirtyRgn(); }

    void inval() { fFlipper.inval(); }
    void inval(const SkIRect& rect) { fFlipper.inval(rect); }
    void inval(const SkRegion& rgn) { fFlipper.inval(rgn); }
    void inval(const SkRect& r, bool doAA) { fFlipper.inval(r, doAA); }

    const SkRegion& beginUpdate(SkBitmap* device);
    void endUpdate();
    
private:
    void getFrontBack(const void** front, void** back) const {
        if (front) {
            *front = fPage0;
        }
        if (back) {
            *back = fPage1;
        }
    }

    void    swapPages();

    // Helper to copy pixels from srcAddr to the dst bitmap, clipped to clip.
    // srcAddr points to memory with the same config as dst.
    static void CopyBitsFromAddr(const SkBitmap& dst, const SkRegion& clip,
                                 const void* srcAddr);

    // serialization

public:
    virtual Factory getFactory() const { return Create; }
    virtual void flatten(SkFlattenableWriteBuffer&) const;
    static SkPixelRef* Create(SkFlattenableReadBuffer& buffer);
    
protected:
    virtual void* onLockPixels(SkColorTable**);
    virtual void onUnlockPixels();

    SkFlipPixelRef(SkFlattenableReadBuffer&);

private:
    SkMutex         fMutex;
    SkPageFlipper   fFlipper;
    
    void*           fStorage;
    void*           fPage0; // points into fStorage;
    void*           fPage1; // points into fStorage;
    size_t          fSize;  // size of 1 page. fStorage holds 2 pages
    SkBitmap::Config fConfig;

    typedef SkPixelRef INHERITED;
};

class SkAutoFlipUpdate : SkNoncopyable {
public:
    SkAutoFlipUpdate(SkFlipPixelRef* ref) : fRef(ref) {
        fDirty = &ref->beginUpdate(&fBitmap);
    }
    ~SkAutoFlipUpdate() {
        if (fRef) {
            fRef->endUpdate();
        }
    }
    
    const SkBitmap& bitmap() const { return fBitmap; }
    const SkRegion& dirty() const { return *fDirty; }
    
    // optional. This gets automatically called in the destructor (only once)
    void endUpdate() {
        if (fRef) {
            fRef->endUpdate();
            fRef = NULL;
        }
    }

private:
    SkFlipPixelRef* fRef;
    SkBitmap        fBitmap;
    const SkRegion* fDirty;
};

#endif
