/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifdef __arm__
#ifdef ANDROID
    #include <machine/cpu-features.h>
#endif
#endif

#include "SkColorPriv.h"

/*
    Filter_32_opaque
    
    There is no hard-n-fast rule that the filtering must produce
    exact results for the color components, but if the 4 incoming colors are
    all opaque, then the output color must also be opaque. Subsequent parts of
    the drawing pipeline may rely on this (e.g. which blitrow proc to use).
 */

#if defined(__ARM_HAVE_NEON) && !defined(SK_CPU_BENDIAN)
static inline void Filter_32_opaque_neon(unsigned x, unsigned y, 
                                    SkPMColor a00, SkPMColor a01,
                                    SkPMColor a10, SkPMColor a11,
                                    SkPMColor *dst) {
    asm volatile(
                 "vdup.8         d0, %[y]                \n\t"   // duplicate y into d0
                 "vmov.u8        d16, #16                \n\t"   // set up constant in d16
                 "vsub.u8        d1, d16, d0             \n\t"   // d1 = 16-y
                 
                 "vdup.32        d4, %[a00]              \n\t"   // duplicate a00 into d4
                 "vdup.32        d5, %[a10]              \n\t"   // duplicate a10 into d5
                 "vmov.32        d4[1], %[a01]           \n\t"   // set top of d4 to a01
                 "vmov.32        d5[1], %[a11]           \n\t"   // set top of d5 to a11
                 
                 "vmull.u8       q3, d4, d1              \n\t"   // q3 = [a01|a00] * (16-y)
                 "vmull.u8       q0, d5, d0              \n\t"   // q0 = [a11|a10] * y
                 
                 "vdup.16        d5, %[x]                \n\t"   // duplicate x into d5
                 "vmov.u16       d16, #16                \n\t"   // set up constant in d16
                 "vsub.u16       d3, d16, d5             \n\t"   // d3 = 16-x
                 
                 "vmul.i16       d4, d7, d5              \n\t"   // d4  = a01 * x
                 "vmla.i16       d4, d1, d5              \n\t"   // d4 += a11 * x
                 "vmla.i16       d4, d6, d3              \n\t"   // d4 += a00 * (16-x)
                 "vmla.i16       d4, d0, d3              \n\t"   // d4 += a10 * (16-x)
                 "vshrn.i16      d0, q2, #8              \n\t"   // shift down result by 8
                 "vst1.32        {d0[0]}, [%[dst]]       \n\t"   // store result
                 :
                 : [x] "r" (x), [y] "r" (y), [a00] "r" (a00), [a01] "r" (a01), [a10] "r" (a10), [a11] "r" (a11), [dst] "r" (dst)
                 : "cc", "memory", "r4", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d16"
                 );
}

static inline void Filter_32_alpha_neon(unsigned x, unsigned y,
                                          SkPMColor a00, SkPMColor a01,
                                          SkPMColor a10, SkPMColor a11,
                                          SkPMColor *dst, uint16_t scale) {
    asm volatile(
                 "vdup.8         d0, %[y]                \n\t"   // duplicate y into d0
                 "vmov.u8        d16, #16                \n\t"   // set up constant in d16
                 "vsub.u8        d1, d16, d0             \n\t"   // d1 = 16-y
                 
                 "vdup.32        d4, %[a00]              \n\t"   // duplicate a00 into d4
                 "vdup.32        d5, %[a10]              \n\t"   // duplicate a10 into d5
                 "vmov.32        d4[1], %[a01]           \n\t"   // set top of d4 to a01
                 "vmov.32        d5[1], %[a11]           \n\t"   // set top of d5 to a11
                 
                 "vmull.u8       q3, d4, d1              \n\t"   // q3 = [a01|a00] * (16-y)
                 "vmull.u8       q0, d5, d0              \n\t"   // q0 = [a11|a10] * y
                 
                 "vdup.16        d5, %[x]                \n\t"   // duplicate x into d5
                 "vmov.u16       d16, #16                \n\t"   // set up constant in d16
                 "vsub.u16       d3, d16, d5             \n\t"   // d3 = 16-x
                 
                 "vmul.i16       d4, d7, d5              \n\t"   // d4  = a01 * x
                 "vmla.i16       d4, d1, d5              \n\t"   // d4 += a11 * x
                 "vmla.i16       d4, d6, d3              \n\t"   // d4 += a00 * (16-x)
                 "vmla.i16       d4, d0, d3              \n\t"   // d4 += a10 * (16-x)
                 "vdup.16        d3, %[scale]            \n\t"   // duplicate scale into d3
                 "vshr.u16       d4, d4, #8              \n\t"   // shift down result by 8
                 "vmul.i16       d4, d4, d3              \n\t"   // multiply result by scale
                 "vshrn.i16      d0, q2, #8              \n\t"   // shift down result by 8
                 "vst1.32        {d0[0]}, [%[dst]]       \n\t"   // store result
                 :
                 : [x] "r" (x), [y] "r" (y), [a00] "r" (a00), [a01] "r" (a01), [a10] "r" (a10), [a11] "r" (a11), [dst] "r" (dst), [scale] "r" (scale)
                 : "cc", "memory", "r4", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d16"
                 );
}
#define Filter_32_opaque    Filter_32_opaque_neon
#define Filter_32_alpha     Filter_32_alpha_neon
#else
static inline void Filter_32_opaque_portable(unsigned x, unsigned y,
                                             SkPMColor a00, SkPMColor a01,
                                             SkPMColor a10, SkPMColor a11,
                                             SkPMColor* dstColor) {
    SkASSERT((unsigned)x <= 0xF);
    SkASSERT((unsigned)y <= 0xF);
    
    int xy = x * y;
    static const uint32_t mask = gMask_00FF00FF; //0xFF00FF;
    
    int scale = 256 - 16*y - 16*x + xy;
    uint32_t lo = (a00 & mask) * scale;
    uint32_t hi = ((a00 >> 8) & mask) * scale;
    
    scale = 16*x - xy;
    lo += (a01 & mask) * scale;
    hi += ((a01 >> 8) & mask) * scale;
    
    scale = 16*y - xy;
    lo += (a10 & mask) * scale;
    hi += ((a10 >> 8) & mask) * scale;
    
    lo += (a11 & mask) * xy;
    hi += ((a11 >> 8) & mask) * xy;
    
    *dstColor = ((lo >> 8) & mask) | (hi & ~mask);
}

static inline void Filter_32_alpha_portable(unsigned x, unsigned y,
                                            SkPMColor a00, SkPMColor a01,
                                            SkPMColor a10, SkPMColor a11,
                                            SkPMColor* dstColor,
                                            unsigned alphaScale) {
    SkASSERT((unsigned)x <= 0xF);
    SkASSERT((unsigned)y <= 0xF);
    SkASSERT(alphaScale <= 256);
    
    int xy = x * y;
    static const uint32_t mask = gMask_00FF00FF; //0xFF00FF;
    
    int scale = 256 - 16*y - 16*x + xy;
    uint32_t lo = (a00 & mask) * scale;
    uint32_t hi = ((a00 >> 8) & mask) * scale;
    
    scale = 16*x - xy;
    lo += (a01 & mask) * scale;
    hi += ((a01 >> 8) & mask) * scale;
    
    scale = 16*y - xy;
    lo += (a10 & mask) * scale;
    hi += ((a10 >> 8) & mask) * scale;
    
    lo += (a11 & mask) * xy;
    hi += ((a11 >> 8) & mask) * xy;

    lo = ((lo >> 8) & mask) * alphaScale;
    hi = ((hi >> 8) & mask) * alphaScale;

    *dstColor = ((lo >> 8) & mask) | (hi & ~mask);
}
#define Filter_32_opaque    Filter_32_opaque_portable
#define Filter_32_alpha     Filter_32_alpha_portable
#endif

