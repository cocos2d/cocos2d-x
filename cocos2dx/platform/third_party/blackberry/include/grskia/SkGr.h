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


#ifndef SkGr_DEFINED
#define SkGr_DEFINED

#include <stddef.h>

// Gr headers
#include "GrConfig.h"
#include "GrContext.h"
#include "GrFontScaler.h"
#include "GrClipIterator.h"
#include "GrPath.h"

// skia headers
#include "SkBitmap.h"
#include "SkPath.h"
#include "SkPoint.h"
#include "SkRegion.h"
#include "SkShader.h"
#include "SkClipStack.h"

#if (GR_DEBUG && defined(SK_RELEASE)) || (GR_RELEASE && defined(SK_DEBUG))
//    #error "inconsistent GR_DEBUG and SK_DEBUG"
#endif

#if GR_SCALAR_IS_FIXED
    #ifdef SK_SCALAR_IS_FIXED
        #define SK_SCALAR_IS_GR_SCALAR  1
    #else
        #define SK_SCALAR_IS_GR_SCALAR  0
    #endif
    #define SkScalarToGrScalar(x)       SkScalarToFixed(x)

#elif GR_SCALAR_IS_FLOAT

    #ifdef SK_SCALAR_IS_FLOAT
        #define SK_SCALAR_IS_GR_SCALAR  1
    #else
        #define SK_SCALAR_IS_GR_SCALAR  0
    #endif
    #define SkScalarToGrScalar(x)       SkScalarToFloat(x)

#else
    #error "Ganesh scalar type not defined"
#endif

////////////////////////////////////////////////////////////////////////////////
// Sk to Gr Type conversions

// Verify that SkPoint and GrPoint are compatible if using the same scalar type
#if 0/*SK_SCALAR_IS_GR_SCALAR*/
    GR_STATIC_ASSERT(sizeof(SkPoint) == sizeof(GrPoint));
    GR_STATIC_ASSERT(offsetof(SkPoint,fX) == offsetof(GrPoint,fX)));
    GR_STATIC_ASSERT(offsetof(SkPoint,fY) == offsetof(GrPoint,fY)));
#endif

GR_STATIC_ASSERT((int)GrSamplerState::kClamp_WrapMode == (int)SkShader::kClamp_TileMode);
GR_STATIC_ASSERT((int)GrSamplerState::kRepeat_WrapMode ==(
                 int)SkShader::kRepeat_TileMode);
GR_STATIC_ASSERT((int)GrSamplerState::kMirror_WrapMode ==
                 (int)SkShader::kMirror_TileMode);

#define sk_tile_mode_to_grwrap(X) ((GrSamplerState::WrapMode)(X))

GR_STATIC_ASSERT((int)kZero_BlendCoeff == (int)SkXfermode::kZero_Coeff);
GR_STATIC_ASSERT((int)kOne_BlendCoeff  == (int)SkXfermode::kOne_Coeff);
GR_STATIC_ASSERT((int)kSC_BlendCoeff   == (int)SkXfermode::kSC_Coeff);
GR_STATIC_ASSERT((int)kISC_BlendCoeff  == (int)SkXfermode::kISC_Coeff);
GR_STATIC_ASSERT((int)kDC_BlendCoeff   == (int)SkXfermode::kDC_Coeff);
GR_STATIC_ASSERT((int)kIDC_BlendCoeff  == (int)SkXfermode::kIDC_Coeff);
GR_STATIC_ASSERT((int)kSA_BlendCoeff   == (int)SkXfermode::kSA_Coeff);
GR_STATIC_ASSERT((int)kISA_BlendCoeff  == (int)SkXfermode::kISA_Coeff);
GR_STATIC_ASSERT((int)kDA_BlendCoeff   == (int)SkXfermode::kDA_Coeff);
GR_STATIC_ASSERT((int)kIDA_BlendCoeff  == (int)SkXfermode::kIDA_Coeff);

#define sk_blend_to_grblend(X) ((GrBlendCoeff)(X))

GR_STATIC_ASSERT((int)SkPath::kMove_Verb  == (int)kMove_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kLine_Verb  == (int)kLine_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kQuad_Verb  == (int)kQuadratic_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kCubic_Verb == (int)kCubic_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kClose_Verb == (int)kClose_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kDone_Verb  == (int)kEnd_PathCmd);

#define sk_path_verb_to_gr_path_command(X) ((GrPathCmd)(X))

///////////////////////////////////////////////////////////////////////////////

#include "SkColorPriv.h"

class SkGr {
public:
    /**
     *  Convert the SkBitmap::Config to the corresponding PixelConfig, or
     *  kUnknown_PixelConfig if the conversion cannot be done.
     */
    static GrPixelConfig BitmapConfig2PixelConfig(SkBitmap::Config,
                                                  bool isOpaque);

    static GrPixelConfig Bitmap2PixelConfig(const SkBitmap& bm) {
        return BitmapConfig2PixelConfig(bm.config(), bm.isOpaque());
    }

    static GrColor SkColor2GrColor(SkColor c) {
        SkPMColor pm = SkPreMultiplyColor(c);
        unsigned r = SkGetPackedR32(pm);
        unsigned g = SkGetPackedG32(pm);
        unsigned b = SkGetPackedB32(pm);
        unsigned a = SkGetPackedA32(pm);
        return GrColorPackRGBA(r, g, b, a);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Classes

class SkGrClipIterator : public GrClipIterator {
public:
    SkGrClipIterator() { fClipStack = NULL;  fCurr = NULL; }
    SkGrClipIterator(const SkClipStack& clipStack) { this->reset(clipStack); }

    void reset(const SkClipStack& clipStack);

    // overrides
    virtual bool isDone() const { return NULL == fCurr; }
    virtual void next() { fCurr = fIter.next(); }
    virtual void rewind() { this->reset(*fClipStack); }
    virtual GrClipType getType() const;

    virtual GrSetOp getOp() const;

    virtual void getRect(GrRect* rect) const {
        if (!fCurr->fRect) {
            rect->setEmpty();
        } else {
            *rect = *fCurr->fRect;
        }
    }

    virtual const GrPath* getPath() {
        return fCurr->fPath;
    }

    virtual GrPathFill getPathFill() const;

private:
    const SkClipStack*                  fClipStack;
    SkClipStack::B2FIter                fIter;
    // SkClipStack's auto advances on each get
    // so we store the current pos here.
    const SkClipStack::B2FIter::Clip*   fCurr;
};

class SkGrRegionIterator : public GrClipIterator {
public:
    SkGrRegionIterator() {}
    SkGrRegionIterator(const SkRegion& region) { this->reset(region); }

    void reset(const SkRegion& region) {
        fRegion = &region;
        fIter.reset(region);
    }

    // overrides
    virtual bool isDone() const { return fIter.done(); }
    virtual void next() { fIter.next(); }
    virtual void rewind() { this->reset(*fRegion); }
    virtual GrClipType getType() const { return kRect_ClipType; }

    virtual GrSetOp getOp() const { return kUnion_SetOp; }

    virtual void getRect(GrRect* rect) const {
        const SkIRect& r = fIter.rect();
        rect->fLeft   = GrIntToScalar(r.fLeft);
        rect->fTop    = GrIntToScalar(r.fTop);
        rect->fRight  = GrIntToScalar(r.fRight);
        rect->fBottom = GrIntToScalar(r.fBottom);
    }

    virtual const GrPath* getPath() {
        SkASSERT(0);
        return NULL;
    }

    virtual GrPathFill getPathFill() const {
        SkASSERT(0);
        return kWinding_PathFill;
    }
private:
    const SkRegion*     fRegion;
    SkRegion::Iterator  fIter;
};

class SkGlyphCache;

class SkGrFontScaler : public GrFontScaler {
public:
    explicit SkGrFontScaler(SkGlyphCache* strike);
    virtual ~SkGrFontScaler();

    // overrides
    virtual const GrKey* getKey();
    virtual GrMaskFormat getMaskFormat();
    virtual bool getPackedGlyphBounds(GrGlyph::PackedID, GrIRect* bounds);
    virtual bool getPackedGlyphImage(GrGlyph::PackedID, int width, int height,
                                     int rowBytes, void* image);
    virtual bool getGlyphPath(uint16_t glyphID, GrPath*);

private:
    SkGlyphCache* fStrike;
    GrKey*  fKey;
//    DECLARE_INSTANCE_COUNTER(SkGrFontScaler);
};

////////////////////////////////////////////////////////////////////////////////
// Helper functions

GrTextureEntry* sk_gr_create_bitmap_texture(GrContext* ctx,
                                            GrTextureKey* key,
                                            const GrSamplerState& sampler,
                                            const SkBitmap& bitmap);


#endif
