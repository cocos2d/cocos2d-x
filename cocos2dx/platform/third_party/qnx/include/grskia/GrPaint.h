/*
    Copyright 2011 Google Inc.

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

#ifndef GrPaint_DEFINED
#define GrPaint_DEFINED

#include "GrTexture.h"
#include "GrColor.h"
#include "GrSamplerState.h"

#include "SkXfermode.h"

/**
 * The paint describes how pixels are colored when the context draws to
 * them. TODO: Make this a "real" class with getters and setters, default
 * values, and documentation.
 */
class GrPaint {
public:
    enum {
        kMaxTextures = 1,
        kMaxMasks    = 1,
    };

    // All the paint fields are public except textures/samplers
    GrBlendCoeff                fSrcBlendCoeff;
    GrBlendCoeff                fDstBlendCoeff;
    bool                        fAntiAlias;
    bool                        fDither;
    bool                        fFallback;

    GrColor                     fColor;

    GrColor                     fColorFilterColor;
    SkXfermode::Mode            fColorFilterXfermode;

    void setTexture(int i, GrTexture* texture) {
        GrAssert((unsigned)i < kMaxTextures);
        GrSafeRef(texture);
        GrSafeUnref(fTextures[i]);
        fTextures[i] = texture;
    }

    GrTexture* getTexture(int i) const { 
        GrAssert((unsigned)i < kMaxTextures);
        return fTextures[i]; 
    }

    GrSamplerState* getTextureSampler(int i) {
        GrAssert((unsigned)i < kMaxTextures);
        return fTextureSamplers + i;
    }

    const GrSamplerState* getTextureSampler(int i) const {
        GrAssert((unsigned)i < kMaxTextures);
        return fTextureSamplers + i;
    }

    // The mask can be alpha-only or per channel. It is applied
    // after the colorfilter
    void setMask(int i, GrTexture* mask) {
        GrAssert((unsigned)i < kMaxMasks);
        GrSafeRef(mask);
        GrSafeUnref(fMaskTextures[i]);
        fMaskTextures[i] = mask;
    }

    GrTexture* getMask(int i) const { 
        GrAssert((unsigned)i < kMaxMasks);
        return fMaskTextures[i]; 
    }

    // mask's sampler matrix is always applied to the positions
    // (i.e. no explicit texture coordinates)
    GrSamplerState* getMaskSampler(int i) {
        GrAssert((unsigned)i < kMaxMasks);
        return fMaskSamplers + i;
    }

    const GrSamplerState* getMaskSampler(int i) const {
        GrAssert((unsigned)i < kMaxMasks);
        return fMaskSamplers + i;
    }

    // pre-concats sampler matrices for non-NULL textures and masks
    void preConcatActiveSamplerMatrices(const GrMatrix& matrix) {
        for (int i = 0; i < kMaxTextures; ++i) {
            fTextureSamplers[i].preConcatMatrix(matrix);
        }
        for (int i = 0; i < kMaxMasks; ++i) {
            fMaskSamplers[i].preConcatMatrix(matrix);
        }
    }

    // uninitialized
    GrPaint() {
        for (int i = 0; i < kMaxTextures; ++i) {
            fTextures[i] = NULL;
        }
        for (int i = 0; i < kMaxMasks; ++i) {
            fMaskTextures[i] = NULL;
        }

        fFallback = false;
    }

    GrPaint(const GrPaint& paint) {
        fSrcBlendCoeff = paint.fSrcBlendCoeff;
        fDstBlendCoeff = paint.fDstBlendCoeff;
        fAntiAlias = paint.fAntiAlias;
        fDither = paint.fDither;

        fColor = paint.fColor;

        fColorFilterColor = paint.fColorFilterColor;
        fColorFilterXfermode = paint.fColorFilterXfermode;

        for (int i = 0; i < kMaxTextures; ++i) {
            fTextureSamplers[i] = paint.fTextureSamplers[i];
            fTextures[i] = paint.fTextures[i];
            GrSafeRef(fTextures[i]);
        }
        for (int i = 0; i < kMaxMasks; ++i) {
            fMaskSamplers[i] = paint.fMaskSamplers[i];
            fMaskTextures[i] = paint.fMaskTextures[i];
            GrSafeRef(fMaskTextures[i]);
        }

        fFallback = false;
    }

    ~GrPaint() {
        for (int i = 0; i < kMaxTextures; ++i) {
            GrSafeUnref(fTextures[i]);
        }
        for (int i = 0; i < kMaxMasks; ++i) {
            GrSafeUnref(fMaskTextures[i]);
        }
    }

    // sets paint to src-over, solid white, no texture, no mask
    void reset() {
        this->resetBlend();
        this->resetOptions();
        this->resetColor();
        this->resetTextures();
        this->resetColorFilter();
        this->resetMasks();
    }

    void resetColorFilter() {
        fColorFilterXfermode = SkXfermode::kDst_Mode;
        fColorFilterColor = GrColorPackRGBA(0xff, 0xff, 0xff, 0xff);
    }

    bool hasTexture() const {
        return 0 != this->getActiveTextureStageMask();
    }

    bool hasMask() const {
        return 0 != this->getActiveMaskStageMask();
    }

    bool hasTextureOrMask() const {
        return this->hasTexture() || this->hasMask();
    }

    // helpers for GrContext, GrTextContext
    int getActiveTextureStageMask() const {
        int mask = 0;
        for (int i = 0; i < kMaxTextures; ++i) {
            if (NULL != fTextures[i]) {
                mask |= 1 << (i + kFirstTextureStage);
            }
        }
        return mask;
    }

    int getActiveMaskStageMask() const {
        int mask = 0;
        for (int i = 0; i < kMaxMasks; ++i) {
            if (NULL != fMaskTextures[i]) {
                mask |= 1 << (i + kFirstMaskStage);
            }
        }
        return mask;
    }
    
    int getActiveStageMask() const {
        return this->getActiveTextureStageMask() |
                this->getActiveMaskStageMask();
    }

    // internal use
    // GrPaint's textures and masks map to the first N stages
    // of GrDrawTarget in that order (textures followed by masks)
    enum {
        kFirstTextureStage = 0,
        kFirstMaskStage = kMaxTextures,
        kTotalStages = kMaxTextures + kMaxMasks,
    };

private:

    GrSamplerState              fTextureSamplers[kMaxTextures];
    GrSamplerState              fMaskSamplers[kMaxMasks];

    GrTexture*      fTextures[kMaxTextures];
    GrTexture*      fMaskTextures[kMaxMasks];

    void resetBlend() {
        fSrcBlendCoeff = kOne_BlendCoeff;
        fDstBlendCoeff = kZero_BlendCoeff;
    }

    void resetOptions() {
        fAntiAlias = false;
        fDither = false;
    }

    void resetColor() {
        fColor = GrColorPackRGBA(0xff, 0xff, 0xff, 0xff);
    }

    void resetTextures() {
        for (int i = 0; i < kMaxTextures; ++i) {
            this->setTexture(i, NULL);
            fTextureSamplers[i].setClampNoFilter();
        }
    }

    void resetMasks() {
        for (int i = 0; i < kMaxMasks; ++i) {
            this->setMask(i, NULL);
            fMaskSamplers[i].setClampNoFilter();
        }
    }
};

#endif
