/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef SkColorPriv_DEFINED
#define SkColorPriv_DEFINED

// turn this own for extra debug checking when blending onto 565
#ifdef SK_DEBUG
    #define CHECK_FOR_565_OVERFLOW
#endif

#include "SkColor.h"
#include "SkMath.h"

/** Turn 0..255 into 0..256 by adding 1 at the half-way point. Used to turn a
    byte into a scale value, so that we can say scale * value >> 8 instead of
    alpha * value / 255.

    In debugging, asserts that alpha is 0..255
*/
static inline unsigned SkAlpha255To256(U8CPU alpha) {
    SkASSERT(SkToU8(alpha) == alpha);
    // this one assues that blending on top of an opaque dst keeps it that way
    // even though it is less accurate than a+(a>>7) for non-opaque dsts
    return alpha + 1;
}

/** Multiplify value by 0..256, and shift the result down 8
    (i.e. return (value * alpha256) >> 8)
 */
#define SkAlphaMul(value, alpha256)     (SkMulS16(value, alpha256) >> 8)

//  The caller may want negative values, so keep all params signed (int)
//  so we don't accidentally slip into unsigned math and lose the sign
//  extension when we shift (in SkAlphaMul)
static inline int SkAlphaBlend(int src, int dst, int scale256) {
    SkASSERT((unsigned)scale256 <= 256);
    return dst + SkAlphaMul(src - dst, scale256);
}

#define SK_R16_BITS     5
#define SK_G16_BITS     6
#define SK_B16_BITS     5

#define SK_R16_SHIFT    (SK_B16_BITS + SK_G16_BITS)
#define SK_G16_SHIFT    (SK_B16_BITS)
#define SK_B16_SHIFT    0

#define SK_R16_MASK     ((1 << SK_R16_BITS) - 1)
#define SK_G16_MASK     ((1 << SK_G16_BITS) - 1)
#define SK_B16_MASK     ((1 << SK_B16_BITS) - 1)

#define SkGetPackedR16(color)   (((unsigned)(color) >> SK_R16_SHIFT) & SK_R16_MASK)
#define SkGetPackedG16(color)   (((unsigned)(color) >> SK_G16_SHIFT) & SK_G16_MASK)
#define SkGetPackedB16(color)   (((unsigned)(color) >> SK_B16_SHIFT) & SK_B16_MASK)

#define SkR16Assert(r)  SkASSERT((unsigned)(r) <= SK_R16_MASK)
#define SkG16Assert(g)  SkASSERT((unsigned)(g) <= SK_G16_MASK)
#define SkB16Assert(b)  SkASSERT((unsigned)(b) <= SK_B16_MASK)

static inline uint16_t SkPackRGB16(unsigned r, unsigned g, unsigned b) {
    SkASSERT(r <= SK_R16_MASK);
    SkASSERT(g <= SK_G16_MASK);
    SkASSERT(b <= SK_B16_MASK);

    return SkToU16((r << SK_R16_SHIFT) | (g << SK_G16_SHIFT) | (b << SK_B16_SHIFT));
}

#define SK_R16_MASK_IN_PLACE        (SK_R16_MASK << SK_R16_SHIFT)
#define SK_G16_MASK_IN_PLACE        (SK_G16_MASK << SK_G16_SHIFT)
#define SK_B16_MASK_IN_PLACE        (SK_B16_MASK << SK_B16_SHIFT)

/** Expand the 16bit color into a 32bit value that can be scaled all at once
    by a value up to 32. Used in conjunction with SkCompact_rgb_16.
*/
static inline uint32_t SkExpand_rgb_16(U16CPU c) {
    SkASSERT(c == (uint16_t)c);

    return ((c & SK_G16_MASK_IN_PLACE) << 16) | (c & ~SK_G16_MASK_IN_PLACE);
}

/** Compress an expanded value (from SkExpand_rgb_16) back down to a 16bit
    color value. The computation yields only 16bits of valid data, but we claim
    to return 32bits, so that the compiler won't generate extra instructions to
    "clean" the top 16bits. However, the top 16 can contain garbage, so it is
    up to the caller to safely ignore them.
*/
static inline U16CPU SkCompact_rgb_16(uint32_t c) {
    return ((c >> 16) & SK_G16_MASK_IN_PLACE) | (c & ~SK_G16_MASK_IN_PLACE);
}

/** Scale the 16bit color value by the 0..256 scale parameter.
    The computation yields only 16bits of valid data, but we claim
    to return 32bits, so that the compiler won't generate extra instructions to
    "clean" the top 16bits.
*/
static inline U16CPU SkAlphaMulRGB16(U16CPU c, unsigned scale) {
    return SkCompact_rgb_16(SkExpand_rgb_16(c) * (scale >> 3) >> 5);
}

// this helper explicitly returns a clean 16bit value (but slower)
#define SkAlphaMulRGB16_ToU16(c, s)  (uint16_t)SkAlphaMulRGB16(c, s)

/** Blend src and dst 16bit colors by the 0..256 scale parameter.
    The computation yields only 16bits of valid data, but we claim
    to return 32bits, so that the compiler won't generate extra instructions to
    "clean" the top 16bits.
*/
static inline U16CPU SkBlendRGB16(U16CPU src, U16CPU dst, int srcScale) {
    SkASSERT((unsigned)srcScale <= 256);

    srcScale >>= 3;

    uint32_t src32 = SkExpand_rgb_16(src);
    uint32_t dst32 = SkExpand_rgb_16(dst);
    return SkCompact_rgb_16(dst32 + ((src32 - dst32) * srcScale >> 5));
}

static inline void SkBlendRGB16(const uint16_t src[], uint16_t dst[],
                                int srcScale, int count) {
    SkASSERT(count > 0);
    SkASSERT((unsigned)srcScale <= 256);

    srcScale >>= 3;

    do {
        uint32_t src32 = SkExpand_rgb_16(*src++);
        uint32_t dst32 = SkExpand_rgb_16(*dst);
        *dst++ = SkCompact_rgb_16(dst32 + ((src32 - dst32) * srcScale >> 5));
    } while (--count > 0);
}

#ifdef SK_DEBUG
    static inline U16CPU SkRGB16Add(U16CPU a, U16CPU b) {
        SkASSERT(SkGetPackedR16(a) + SkGetPackedR16(b) <= SK_R16_MASK);
        SkASSERT(SkGetPackedG16(a) + SkGetPackedG16(b) <= SK_G16_MASK);
        SkASSERT(SkGetPackedB16(a) + SkGetPackedB16(b) <= SK_B16_MASK);

        return a + b;
    }
#else
    #define SkRGB16Add(a, b)  ((a) + (b))
#endif

///////////////////////////////////////////////////////////////////////////////

#define SK_A32_BITS     8
#define SK_R32_BITS     8
#define SK_G32_BITS     8
#define SK_B32_BITS     8

#define SK_A32_MASK     ((1 << SK_A32_BITS) - 1)
#define SK_R32_MASK     ((1 << SK_R32_BITS) - 1)
#define SK_G32_MASK     ((1 << SK_G32_BITS) - 1)
#define SK_B32_MASK     ((1 << SK_B32_BITS) - 1)

#define SkGetPackedA32(packed)      ((uint32_t)((packed) << (24 - SK_A32_SHIFT)) >> 24)
#define SkGetPackedR32(packed)      ((uint32_t)((packed) << (24 - SK_R32_SHIFT)) >> 24)
#define SkGetPackedG32(packed)      ((uint32_t)((packed) << (24 - SK_G32_SHIFT)) >> 24)
#define SkGetPackedB32(packed)      ((uint32_t)((packed) << (24 - SK_B32_SHIFT)) >> 24)

#define SkA32Assert(a)  SkASSERT((unsigned)(a) <= SK_A32_MASK)
#define SkR32Assert(r)  SkASSERT((unsigned)(r) <= SK_R32_MASK)
#define SkG32Assert(g)  SkASSERT((unsigned)(g) <= SK_G32_MASK)
#define SkB32Assert(b)  SkASSERT((unsigned)(b) <= SK_B32_MASK)

#ifdef SK_DEBUG
    static inline void SkPMColorAssert(SkPMColor c) {
        unsigned a = SkGetPackedA32(c);
        unsigned r = SkGetPackedR32(c);
        unsigned g = SkGetPackedG32(c);
        unsigned b = SkGetPackedB32(c);

        SkA32Assert(a);
        SkASSERT(r <= a);
        SkASSERT(g <= a);
        SkASSERT(b <= a);
    }
#else
    #define SkPMColorAssert(c)
#endif

/**
 *  Pack the components into a SkPMColor, checking (in the debug version) that
 *  the components are 0..255, and are already premultiplied (i.e. alpha >= color)
 */
static inline SkPMColor SkPackARGB32(U8CPU a, U8CPU r, U8CPU g, U8CPU b) {
    SkA32Assert(a);
    SkASSERT(r <= a);
    SkASSERT(g <= a);
    SkASSERT(b <= a);

    return (a << SK_A32_SHIFT) | (r << SK_R32_SHIFT) |
           (g << SK_G32_SHIFT) | (b << SK_B32_SHIFT);
}

/**
 *  Same as SkPackARGB32, but this version guarantees to not check that the
 *  values are premultiplied in the debug version.
 */
static inline SkPMColor SkPackARGB32NoCheck(U8CPU a, U8CPU r, U8CPU g, U8CPU b) {
    return (a << SK_A32_SHIFT) | (r << SK_R32_SHIFT) |
           (g << SK_G32_SHIFT) | (b << SK_B32_SHIFT);
}

SK_API extern const uint32_t gMask_00FF00FF;

static inline uint32_t SkAlphaMulQ(uint32_t c, unsigned scale) {
    uint32_t mask = gMask_00FF00FF;
//    uint32_t mask = 0xFF00FF;

    uint32_t rb = ((c & mask) * scale) >> 8;
    uint32_t ag = ((c >> 8) & mask) * scale;
    return (rb & mask) | (ag & ~mask);
}

static inline SkPMColor SkPMSrcOver(SkPMColor src, SkPMColor dst) {
    return src + SkAlphaMulQ(dst, SkAlpha255To256(255 - SkGetPackedA32(src)));
}

static inline SkPMColor SkBlendARGB32(SkPMColor src, SkPMColor dst, U8CPU aa) {
    SkASSERT((unsigned)aa <= 255);

    unsigned src_scale = SkAlpha255To256(aa);
    unsigned dst_scale = SkAlpha255To256(255 - SkAlphaMul(SkGetPackedA32(src), src_scale));

    return SkAlphaMulQ(src, src_scale) + SkAlphaMulQ(dst, dst_scale);
}

////////////////////////////////////////////////////////////////////////////////////////////
// Convert a 32bit pixel to a 16bit pixel (no dither)

#define SkR32ToR16_MACRO(r)   ((unsigned)(r) >> (SK_R32_BITS - SK_R16_BITS))
#define SkG32ToG16_MACRO(g)   ((unsigned)(g) >> (SK_G32_BITS - SK_G16_BITS))
#define SkB32ToB16_MACRO(b)   ((unsigned)(b) >> (SK_B32_BITS - SK_B16_BITS))

#ifdef SK_DEBUG
    static inline unsigned SkR32ToR16(unsigned r) {
        SkR32Assert(r);
        return SkR32ToR16_MACRO(r);
    }
    static inline unsigned SkG32ToG16(unsigned g) {
        SkG32Assert(g);
        return SkG32ToG16_MACRO(g);
    }
    static inline unsigned SkB32ToB16(unsigned b) {
        SkB32Assert(b);
        return SkB32ToB16_MACRO(b);
    }
#else
    #define SkR32ToR16(r)   SkR32ToR16_MACRO(r)
    #define SkG32ToG16(g)   SkG32ToG16_MACRO(g)
    #define SkB32ToB16(b)   SkB32ToB16_MACRO(b)
#endif

#define SkPacked32ToR16(c)  (((unsigned)(c) >> (SK_R32_SHIFT + SK_R32_BITS - SK_R16_BITS)) & SK_R16_MASK)
#define SkPacked32ToG16(c)  (((unsigned)(c) >> (SK_G32_SHIFT + SK_G32_BITS - SK_G16_BITS)) & SK_G16_MASK)
#define SkPacked32ToB16(c)  (((unsigned)(c) >> (SK_B32_SHIFT + SK_B32_BITS - SK_B16_BITS)) & SK_B16_MASK)

static inline U16CPU SkPixel32ToPixel16(SkPMColor c) {
    unsigned r = ((c >> (SK_R32_SHIFT + (8 - SK_R16_BITS))) & SK_R16_MASK) << SK_R16_SHIFT;
    unsigned g = ((c >> (SK_G32_SHIFT + (8 - SK_G16_BITS))) & SK_G16_MASK) << SK_G16_SHIFT;
    unsigned b = ((c >> (SK_B32_SHIFT + (8 - SK_B16_BITS))) & SK_B16_MASK) << SK_B16_SHIFT;
    return r | g | b;
}

static inline U16CPU SkPack888ToRGB16(U8CPU r, U8CPU g, U8CPU b) {
    return  (SkR32ToR16(r) << SK_R16_SHIFT) |
            (SkG32ToG16(g) << SK_G16_SHIFT) |
            (SkB32ToB16(b) << SK_B16_SHIFT);
}

#define SkPixel32ToPixel16_ToU16(src)   SkToU16(SkPixel32ToPixel16(src))

/////////////////////////////////////////////////////////////////////////////////////////
// Fast dither from 32->16

#define SkShouldDitherXY(x, y)  (((x) ^ (y)) & 1)

static inline uint16_t SkDitherPack888ToRGB16(U8CPU r, U8CPU g, U8CPU b) {
    r = ((r << 1) - ((r >> (8 - SK_R16_BITS) << (8 - SK_R16_BITS)) | (r >> SK_R16_BITS))) >> (8 - SK_R16_BITS);
    g = ((g << 1) - ((g >> (8 - SK_G16_BITS) << (8 - SK_G16_BITS)) | (g >> SK_G16_BITS))) >> (8 - SK_G16_BITS);
    b = ((b << 1) - ((b >> (8 - SK_B16_BITS) << (8 - SK_B16_BITS)) | (b >> SK_B16_BITS))) >> (8 - SK_B16_BITS);

    return SkPackRGB16(r, g, b);
}

static inline uint16_t SkDitherPixel32ToPixel16(SkPMColor c) {
    return SkDitherPack888ToRGB16(SkGetPackedR32(c), SkGetPackedG32(c), SkGetPackedB32(c));
}

/*  Return c in expanded_rgb_16 format, but also scaled up by 32 (5 bits)
    It is now suitable for combining with a scaled expanded_rgb_16 color
    as in SkSrcOver32To16().
    We must do this 565 high-bit replication, in order for the subsequent add
    to saturate properly (and not overflow). If we take the 8 bits as is, it is
    possible to overflow.
*/
static inline uint32_t SkPMColorToExpanded16x5(SkPMColor c) {
    unsigned sr = SkPacked32ToR16(c);
    unsigned sg = SkPacked32ToG16(c);
    unsigned sb = SkPacked32ToB16(c);

    sr = (sr << 5) | sr;
    sg = (sg << 5) | (sg >> 1);
    sb = (sb << 5) | sb;
    return (sr << 11) | (sg << 21) | (sb << 0);
}

/*  SrcOver the 32bit src color with the 16bit dst, returning a 16bit value
    (with dirt in the high 16bits, so caller beware).
*/
static inline U16CPU SkSrcOver32To16(SkPMColor src, uint16_t dst) {
    unsigned sr = SkGetPackedR32(src);
    unsigned sg = SkGetPackedG32(src);
    unsigned sb = SkGetPackedB32(src);

    unsigned dr = SkGetPackedR16(dst);
    unsigned dg = SkGetPackedG16(dst);
    unsigned db = SkGetPackedB16(dst);

    unsigned isa = 255 - SkGetPackedA32(src);

    dr = (sr + SkMul16ShiftRound(dr, isa, SK_R16_BITS)) >> (8 - SK_R16_BITS);
    dg = (sg + SkMul16ShiftRound(dg, isa, SK_G16_BITS)) >> (8 - SK_G16_BITS);
    db = (sb + SkMul16ShiftRound(db, isa, SK_B16_BITS)) >> (8 - SK_B16_BITS);

    return SkPackRGB16(dr, dg, db);
}

////////////////////////////////////////////////////////////////////////////////////////////
// Convert a 16bit pixel to a 32bit pixel

static inline unsigned SkR16ToR32(unsigned r) {
    return (r << (8 - SK_R16_BITS)) | (r >> (2 * SK_R16_BITS - 8));
}

static inline unsigned SkG16ToG32(unsigned g) {
    return (g << (8 - SK_G16_BITS)) | (g >> (2 * SK_G16_BITS - 8));
}

static inline unsigned SkB16ToB32(unsigned b) {
    return (b << (8 - SK_B16_BITS)) | (b >> (2 * SK_B16_BITS - 8));
}

#define SkPacked16ToR32(c)      SkR16ToR32(SkGetPackedR16(c))
#define SkPacked16ToG32(c)      SkG16ToG32(SkGetPackedG16(c))
#define SkPacked16ToB32(c)      SkB16ToB32(SkGetPackedB16(c))

static inline SkPMColor SkPixel16ToPixel32(U16CPU src) {
    SkASSERT(src == SkToU16(src));

    unsigned    r = SkPacked16ToR32(src);
    unsigned    g = SkPacked16ToG32(src);
    unsigned    b = SkPacked16ToB32(src);

    SkASSERT((r >> (8 - SK_R16_BITS)) == SkGetPackedR16(src));
    SkASSERT((g >> (8 - SK_G16_BITS)) == SkGetPackedG16(src));
    SkASSERT((b >> (8 - SK_B16_BITS)) == SkGetPackedB16(src));

    return SkPackARGB32(0xFF, r, g, b);
}

// similar to SkPixel16ToPixel32, but returns SkColor instead of SkPMColor
static inline SkColor SkPixel16ToColor(U16CPU src) {
    SkASSERT(src == SkToU16(src));

    unsigned    r = SkPacked16ToR32(src);
    unsigned    g = SkPacked16ToG32(src);
    unsigned    b = SkPacked16ToB32(src);

    SkASSERT((r >> (8 - SK_R16_BITS)) == SkGetPackedR16(src));
    SkASSERT((g >> (8 - SK_G16_BITS)) == SkGetPackedG16(src));
    SkASSERT((b >> (8 - SK_B16_BITS)) == SkGetPackedB16(src));

    return SkColorSetRGB(r, g, b);
}

///////////////////////////////////////////////////////////////////////////////

typedef uint16_t SkPMColor16;

// Put in OpenGL order (r g b a)
#define SK_A4444_SHIFT    0
#define SK_R4444_SHIFT    12
#define SK_G4444_SHIFT    8
#define SK_B4444_SHIFT    4

#define SkA32To4444(a)  ((unsigned)(a) >> 4)
#define SkR32To4444(r)  ((unsigned)(r) >> 4)
#define SkG32To4444(g)  ((unsigned)(g) >> 4)
#define SkB32To4444(b)  ((unsigned)(b) >> 4)

static inline U8CPU SkReplicateNibble(unsigned nib) {
    SkASSERT(nib <= 0xF);
    return (nib << 4) | nib;
}

#define SkA4444ToA32(a)     SkReplicateNibble(a)
#define SkR4444ToR32(r)     SkReplicateNibble(r)
#define SkG4444ToG32(g)     SkReplicateNibble(g)
#define SkB4444ToB32(b)     SkReplicateNibble(b)

#define SkGetPackedA4444(c)     (((unsigned)(c) >> SK_A4444_SHIFT) & 0xF)
#define SkGetPackedR4444(c)     (((unsigned)(c) >> SK_R4444_SHIFT) & 0xF)
#define SkGetPackedG4444(c)     (((unsigned)(c) >> SK_G4444_SHIFT) & 0xF)
#define SkGetPackedB4444(c)     (((unsigned)(c) >> SK_B4444_SHIFT) & 0xF)

#define SkPacked4444ToA32(c)    SkReplicateNibble(SkGetPackedA4444(c))
#define SkPacked4444ToR32(c)    SkReplicateNibble(SkGetPackedR4444(c))
#define SkPacked4444ToG32(c)    SkReplicateNibble(SkGetPackedG4444(c))
#define SkPacked4444ToB32(c)    SkReplicateNibble(SkGetPackedB4444(c))

#ifdef SK_DEBUG
static inline void SkPMColor16Assert(U16CPU c) {
    unsigned a = SkGetPackedA4444(c);
    unsigned r = SkGetPackedR4444(c);
    unsigned g = SkGetPackedG4444(c);
    unsigned b = SkGetPackedB4444(c);

    SkASSERT(a <= 0xF);
    SkASSERT(r <= a);
    SkASSERT(g <= a);
    SkASSERT(b <= a);
}
#else
#define SkPMColor16Assert(c)
#endif

static inline unsigned SkAlpha15To16(unsigned a) {
    SkASSERT(a <= 0xF);
    return a + (a >> 3);
}

#ifdef SK_DEBUG
    static inline int SkAlphaMul4(int value, int scale) {
        SkASSERT((unsigned)scale <= 0x10);
        return value * scale >> 4;
    }
#else
    #define SkAlphaMul4(value, scale)   ((value) * (scale) >> 4)
#endif

static inline unsigned SkR4444ToR565(unsigned r) {
    SkASSERT(r <= 0xF);
    return (r << (SK_R16_BITS - 4)) | (r >> (8 - SK_R16_BITS));
}

static inline unsigned SkG4444ToG565(unsigned g) {
    SkASSERT(g <= 0xF);
    return (g << (SK_G16_BITS - 4)) | (g >> (8 - SK_G16_BITS));
}

static inline unsigned SkB4444ToB565(unsigned b) {
    SkASSERT(b <= 0xF);
    return (b << (SK_B16_BITS - 4)) | (b >> (8 - SK_B16_BITS));
}

static inline SkPMColor16 SkPackARGB4444(unsigned a, unsigned r,
                                         unsigned g, unsigned b) {
    SkASSERT(a <= 0xF);
    SkASSERT(r <= a);
    SkASSERT(g <= a);
    SkASSERT(b <= a);

    return (SkPMColor16)((a << SK_A4444_SHIFT) | (r << SK_R4444_SHIFT) |
                         (g << SK_G4444_SHIFT) | (b << SK_B4444_SHIFT));
}

extern const uint16_t gMask_0F0F;

static inline U16CPU SkAlphaMulQ4(U16CPU c, unsigned scale) {
    SkASSERT(scale <= 16);

    const unsigned mask = 0xF0F;    //gMask_0F0F;

#if 0
    unsigned rb = ((c & mask) * scale) >> 4;
    unsigned ag = ((c >> 4) & mask) * scale;
    return (rb & mask) | (ag & ~mask);
#else
    c = (c & mask) | ((c & (mask << 4)) << 12);
    c = c * scale >> 4;
    return (c & mask) | ((c >> 12) & (mask << 4));
#endif
}

/** Expand the SkPMColor16 color into a 32bit value that can be scaled all at
    once by a value up to 16. Used in conjunction with SkCompact_4444.
*/
static inline uint32_t SkExpand_4444(U16CPU c) {
    SkASSERT(c == (uint16_t)c);

    const unsigned mask = 0xF0F;    //gMask_0F0F;
    return (c & mask) | ((c & ~mask) << 12);
}

/** Compress an expanded value (from SkExpand_4444) back down to a SkPMColor16.
    NOTE: this explicitly does not clean the top 16 bits (which may be garbage).
    It does this for speed, since if it is being written directly to 16bits of
    memory, the top 16bits will be ignored. Casting the result to uint16_t here
    would add 2 more instructions, slow us down. It is up to the caller to
    perform the cast if needed.
*/
static inline U16CPU SkCompact_4444(uint32_t c) {
    const unsigned mask = 0xF0F;    //gMask_0F0F;
    return (c & mask) | ((c >> 12) & ~mask);
}

static inline uint16_t SkSrcOver4444To16(SkPMColor16 s, uint16_t d) {
    unsigned sa = SkGetPackedA4444(s);
    unsigned sr = SkR4444ToR565(SkGetPackedR4444(s));
    unsigned sg = SkG4444ToG565(SkGetPackedG4444(s));
    unsigned sb = SkB4444ToB565(SkGetPackedB4444(s));

    // To avoid overflow, we have to clear the low bit of the synthetic sg
    // if the src alpha is <= 7.
    // to see why, try blending 0x4444 on top of 565-white and watch green
    // overflow (sum == 64)
    sg &= ~(~(sa >> 3) & 1);

    unsigned scale = SkAlpha15To16(15 - sa);
    unsigned dr = SkAlphaMul4(SkGetPackedR16(d), scale);
    unsigned dg = SkAlphaMul4(SkGetPackedG16(d), scale);
    unsigned db = SkAlphaMul4(SkGetPackedB16(d), scale);

#if 0
    if (sg + dg > 63) {
        SkDebugf("---- SkSrcOver4444To16 src=%x dst=%x scale=%d, sg=%d dg=%d\n", s, d, scale, sg, dg);
    }
#endif
    return SkPackRGB16(sr + dr, sg + dg, sb + db);
}

static inline uint16_t SkBlend4444To16(SkPMColor16 src, uint16_t dst, int scale16) {
    SkASSERT((unsigned)scale16 <= 16);

    return SkSrcOver4444To16(SkAlphaMulQ4(src, scale16), dst);
}

static inline uint16_t SkBlend4444(SkPMColor16 src, SkPMColor16 dst, int scale16) {
    SkASSERT((unsigned)scale16 <= 16);

    uint32_t src32 = SkExpand_4444(src) * scale16;
    // the scaled srcAlpha is the bottom byte
#ifdef SK_DEBUG
    {
        unsigned srcA = SkGetPackedA4444(src) * scale16;
        SkASSERT(srcA == (src32 & 0xFF));
    }
#endif
    unsigned dstScale = SkAlpha255To256(255 - (src32 & 0xFF)) >> 4;
    uint32_t dst32 = SkExpand_4444(dst) * dstScale;
    return SkCompact_4444((src32 + dst32) >> 4);
}

static inline SkPMColor SkPixel4444ToPixel32(U16CPU c) {
    uint32_t d = (SkGetPackedA4444(c) << SK_A32_SHIFT) |
                 (SkGetPackedR4444(c) << SK_R32_SHIFT) |
                 (SkGetPackedG4444(c) << SK_G32_SHIFT) |
                 (SkGetPackedB4444(c) << SK_B32_SHIFT);
    return d | (d << 4);
}

static inline SkPMColor16 SkPixel32ToPixel4444(SkPMColor c) {
    return  (((c >> (SK_A32_SHIFT + 4)) & 0xF) << SK_A4444_SHIFT) |
    (((c >> (SK_R32_SHIFT + 4)) & 0xF) << SK_R4444_SHIFT) |
    (((c >> (SK_G32_SHIFT + 4)) & 0xF) << SK_G4444_SHIFT) |
    (((c >> (SK_B32_SHIFT + 4)) & 0xF) << SK_B4444_SHIFT);
}

// cheap 2x2 dither
static inline SkPMColor16 SkDitherARGB32To4444(U8CPU a, U8CPU r,
                                               U8CPU g, U8CPU b) {
    // to ensure that we stay a legal premultiplied color, we take the max()
    // of the truncated and dithered alpha values. If we didn't, cases like
    // SkDitherARGB32To4444(0x31, 0x2E, ...) would generate SkPackARGB4444(2, 3, ...)
    // which is not legal premultiplied, since a < color
    unsigned dithered_a = ((a << 1) - ((a >> 4 << 4) | (a >> 4))) >> 4;
    a = SkMax32(a >> 4, dithered_a);
    // these we just dither in place
    r = ((r << 1) - ((r >> 4 << 4) | (r >> 4))) >> 4;
    g = ((g << 1) - ((g >> 4 << 4) | (g >> 4))) >> 4;
    b = ((b << 1) - ((b >> 4 << 4) | (b >> 4))) >> 4;

    return SkPackARGB4444(a, r, g, b);
}

static inline SkPMColor16 SkDitherPixel32To4444(SkPMColor c) {
    return SkDitherARGB32To4444(SkGetPackedA32(c), SkGetPackedR32(c),
                                SkGetPackedG32(c), SkGetPackedB32(c));
}

/*  Assumes 16bit is in standard RGBA order.
    Transforms a normal ARGB_8888 into the same byte order as
    expanded ARGB_4444, but keeps each component 8bits
*/
static inline uint32_t SkExpand_8888(SkPMColor c) {
    return  (((c >> SK_R32_SHIFT) & 0xFF) << 24) |
            (((c >> SK_G32_SHIFT) & 0xFF) <<  8) |
            (((c >> SK_B32_SHIFT) & 0xFF) << 16) |
            (((c >> SK_A32_SHIFT) & 0xFF) <<  0);
}

/*  Undo the operation of SkExpand_8888, turning the argument back into
    a SkPMColor.
*/
static inline SkPMColor SkCompact_8888(uint32_t c) {
    return  (((c >> 24) & 0xFF) << SK_R32_SHIFT) |
            (((c >>  8) & 0xFF) << SK_G32_SHIFT) |
            (((c >> 16) & 0xFF) << SK_B32_SHIFT) |
            (((c >>  0) & 0xFF) << SK_A32_SHIFT);
}

/*  Like SkExpand_8888, this transforms a pmcolor into the expanded 4444 format,
    but this routine just keeps the high 4bits of each component in the low
    4bits of the result (just like a newly expanded PMColor16).
*/
static inline uint32_t SkExpand32_4444(SkPMColor c) {
    return  (((c >> (SK_R32_SHIFT + 4)) & 0xF) << 24) |
            (((c >> (SK_G32_SHIFT + 4)) & 0xF) <<  8) |
            (((c >> (SK_B32_SHIFT + 4)) & 0xF) << 16) |
            (((c >> (SK_A32_SHIFT + 4)) & 0xF) <<  0);
}

// takes two values and alternamtes them as part of a memset16
// used for cheap 2x2 dithering when the colors are opaque
void sk_dither_memset16(uint16_t dst[], uint16_t value, uint16_t other, int n);

#endif

