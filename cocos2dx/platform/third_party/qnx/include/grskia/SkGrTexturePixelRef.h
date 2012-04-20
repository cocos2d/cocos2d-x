/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef SkGrTexturePixelRef_DEFINED
#define SkGrTexturePixelRef_DEFINED

#include "SkPixelRef.h"
#include "GrGpu.h"

class SkGrTexturePixelRef : public SkPixelRef {
public:
            SkGrTexturePixelRef(GrTexture*);
    virtual ~SkGrTexturePixelRef();

    // override from SkPixelRef
    virtual SkGpuTexture* getTexture() { return (SkGpuTexture*)fTexture; }

protected:
    // override from SkPixelRef
    virtual void* onLockPixels(SkColorTable** ptr) {
        if (ptr) {
            *ptr = NULL;
        }
        return NULL;
    }

    // override from SkPixelRef
    virtual void onUnlockPixels() {}
    virtual bool onReadPixels(SkBitmap* dst, const SkIRect* subset);

private:
    GrTexture*  fTexture;
    typedef SkPixelRef INHERITED;
};

class SkGrRenderTargetPixelRef : public SkPixelRef {
public:
            SkGrRenderTargetPixelRef(GrRenderTarget* rt);
    virtual ~SkGrRenderTargetPixelRef();

    // override from SkPixelRef
    virtual SkGpuTexture* getTexture();

protected:
    // override from SkPixelRef
    virtual void* onLockPixels(SkColorTable** ptr) {
        if (ptr) {
            *ptr = NULL;
        }
        return NULL;
    }

    // override from SkPixelRef
    virtual void onUnlockPixels() {}
    virtual bool onReadPixels(SkBitmap* dst, const SkIRect* subset);

private:
    GrRenderTarget*  fRenderTarget;
    typedef SkPixelRef INHERITED;
};

#endif

