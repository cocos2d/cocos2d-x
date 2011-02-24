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

#ifndef SkDither_DEFINED
#define SkDither_DEFINED

#include "SkColorPriv.h"

#define SK_DitherValueMax4444   15
#define SK_DitherValueMax565    7

/*  need to use macros for bit-counts for each component, and then
    move these into SkColorPriv.h
*/

#define SkDITHER_R32_FOR_565_MACRO(r, d)    (r + d - (r >> 5))
#define SkDITHER_G32_FOR_565_MACRO(g, d)    (g + (d >> 1) - (g >> 6))
#define SkDITHER_B32_FOR_565_MACRO(b, d)    (b + d - (b >> 5))

#define SkDITHER_A32_FOR_4444_MACRO(a, d)    (a + 15 - (a >> 4))
#define SkDITHER_R32_FOR_4444_MACRO(r, d)    (r + d - (r >> 4))
#define SkDITHER_G32_FOR_4444_MACRO(g, d)    (g + d - (g >> 4))
#define SkDITHER_B32_FOR_4444_MACRO(b, d)    (b + d - (b >> 4))

#ifdef SK_DEBUG
    inline unsigned SkDITHER_R32_FOR_565(unsigned r, unsigned d)
    {
        SkASSERT(d <= SK_DitherValueMax565);
        SkA32Assert(r);
        r = SkDITHER_R32_FOR_565_MACRO(r, d);
        SkA32Assert(r);
        return r;
    }
    inline unsigned SkDITHER_G32_FOR_565(unsigned g, unsigned d)
    {
        SkASSERT(d <= SK_DitherValueMax565);
        SkG32Assert(g);
        g = SkDITHER_G32_FOR_565_MACRO(g, d);
        SkG32Assert(g);
        return g;
    }
    inline unsigned SkDITHER_B32_FOR_565(unsigned b, unsigned d)
    {
        SkASSERT(d <= SK_DitherValueMax565);
        SkB32Assert(b);
        b = SkDITHER_B32_FOR_565_MACRO(b, d);
        SkB32Assert(b);
        return b;
    }
#else
    #define SkDITHER_R32_FOR_565(r, d)  SkDITHER_R32_FOR_565_MACRO(r, d)
    #define SkDITHER_G32_FOR_565(g, d)  SkDITHER_G32_FOR_565_MACRO(g, d)
    #define SkDITHER_B32_FOR_565(b, d)  SkDITHER_B32_FOR_565_MACRO(b, d)
#endif

#define SkDITHER_R32To565(r, d)  SkR32ToR16(SkDITHER_R32_FOR_565(r, d))
#define SkDITHER_G32To565(g, d)  SkG32ToG16(SkDITHER_G32_FOR_565(g, d))
#define SkDITHER_B32To565(b, d)  SkB32ToB16(SkDITHER_B32_FOR_565(b, d))

#define SkDITHER_A32To4444(a, d)  SkA32To4444(SkDITHER_A32_FOR_4444_MACRO(a, d))
#define SkDITHER_R32To4444(r, d)  SkR32To4444(SkDITHER_R32_FOR_4444_MACRO(r, d))
#define SkDITHER_G32To4444(g, d)  SkG32To4444(SkDITHER_G32_FOR_4444_MACRO(g, d))
#define SkDITHER_B32To4444(b, d)  SkB32To4444(SkDITHER_B32_FOR_4444_MACRO(b, d))

static inline SkPMColor SkDitherARGB32For565(SkPMColor c, unsigned dither)
{
    SkASSERT(dither <= SK_DitherValueMax565);
    
    unsigned sa = SkGetPackedA32(c);
    dither = SkAlphaMul(dither, SkAlpha255To256(sa));

    unsigned sr = SkGetPackedR32(c);
    unsigned sg = SkGetPackedG32(c);
    unsigned sb = SkGetPackedB32(c);
    sr = SkDITHER_R32_FOR_565(sr, dither);
    sg = SkDITHER_G32_FOR_565(sg, dither);
    sb = SkDITHER_B32_FOR_565(sb, dither);
    
    return SkPackARGB32(sa, sr, sg, sb);
}

static inline SkPMColor SkDitherRGB32For565(SkPMColor c, unsigned dither)
{
    SkASSERT(dither <= SK_DitherValueMax565);
    
    unsigned sr = SkGetPackedR32(c);
    unsigned sg = SkGetPackedG32(c);
    unsigned sb = SkGetPackedB32(c);
    sr = SkDITHER_R32_FOR_565(sr, dither);
    sg = SkDITHER_G32_FOR_565(sg, dither);
    sb = SkDITHER_B32_FOR_565(sb, dither);
    
    return SkPackARGB32(0xFF, sr, sg, sb);
}

static inline uint16_t SkDitherRGBTo565(U8CPU r, U8CPU g, U8CPU b,
                                              unsigned dither)
{
    SkASSERT(dither <= SK_DitherValueMax565);
    r = SkDITHER_R32To565(r, dither);
    g = SkDITHER_G32To565(g, dither);
    b = SkDITHER_B32To565(b, dither);
    return SkPackRGB16(r, g, b);
}

static inline uint16_t SkDitherRGB32To565(SkPMColor c, unsigned dither)
{
    SkASSERT(dither <= SK_DitherValueMax565);
    
    unsigned sr = SkGetPackedR32(c);
    unsigned sg = SkGetPackedG32(c);
    unsigned sb = SkGetPackedB32(c);
    sr = SkDITHER_R32To565(sr, dither);
    sg = SkDITHER_G32To565(sg, dither);
    sb = SkDITHER_B32To565(sb, dither);
    
    return SkPackRGB16(sr, sg, sb);
}

static inline uint16_t SkDitherARGB32To565(U8CPU sa, SkPMColor c, unsigned dither)
{
    SkASSERT(dither <= SK_DitherValueMax565);    
    dither = SkAlphaMul(dither, SkAlpha255To256(sa));
    
    unsigned sr = SkGetPackedR32(c);
    unsigned sg = SkGetPackedG32(c);
    unsigned sb = SkGetPackedB32(c);
    sr = SkDITHER_R32To565(sr, dither);
    sg = SkDITHER_G32To565(sg, dither);
    sb = SkDITHER_B32To565(sb, dither);
    
    return SkPackRGB16(sr, sg, sb);
}

///////////////////////// 4444

static inline SkPMColor16 SkDitherARGB32To4444(U8CPU a, U8CPU r, U8CPU g,
                                               U8CPU b, unsigned dither)
{
    dither = SkAlphaMul(dither, SkAlpha255To256(a));

    a = SkDITHER_A32To4444(a, dither);
    r = SkDITHER_R32To4444(r, dither);
    g = SkDITHER_G32To4444(g, dither);
    b = SkDITHER_B32To4444(b, dither);
    
    return SkPackARGB4444(a, r, g, b);
}

static inline SkPMColor16 SkDitherARGB32To4444(SkPMColor c, unsigned dither)
{
    unsigned a = SkGetPackedA32(c);
    unsigned r = SkGetPackedR32(c);
    unsigned g = SkGetPackedG32(c);
    unsigned b = SkGetPackedB32(c);

    dither = SkAlphaMul(dither, SkAlpha255To256(a));

    a = SkDITHER_A32To4444(a, dither);
    r = SkDITHER_R32To4444(r, dither);
    g = SkDITHER_G32To4444(g, dither);
    b = SkDITHER_B32To4444(b, dither);
    
    return SkPackARGB4444(a, r, g, b);
}

// TODO: need dither routines for 565 -> 4444

// this toggles between a 4x4 and a 1x4 array
//#define ENABLE_DITHER_MATRIX_4X4

#ifdef ENABLE_DITHER_MATRIX_4X4
    extern const uint8_t gDitherMatrix_4Bit_4X4[4][4];
    extern const uint8_t gDitherMatrix_3Bit_4X4[4][4];

    #define DITHER_4444_SCAN(y) const uint8_t* dither_scan = gDitherMatrix_4Bit_4X4[(y) & 3]
    #define DITHER_565_SCAN(y)  const uint8_t* dither_scan = gDitherMatrix_3Bit_4X4[(y) & 3]

    #define DITHER_VALUE(x) dither_scan[(x) & 3]
#else
    extern const uint16_t gDitherMatrix_4Bit_16[4];
    extern const uint16_t gDitherMatrix_3Bit_16[4];

    #define DITHER_4444_SCAN(y) const uint16_t dither_scan = gDitherMatrix_4Bit_16[(y) & 3]
    #define DITHER_565_SCAN(y)  const uint16_t dither_scan = gDitherMatrix_3Bit_16[(y) & 3]

    #define DITHER_VALUE(x) ((dither_scan >> (((x) & 3) << 2)) & 0xF)
#endif

#define DITHER_INC_X(x) ++(x)

#endif
