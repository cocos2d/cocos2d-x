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

#ifndef SkEndian_DEFINED
#define SkEndian_DEFINED

#include "SkTypes.h"

/** \file SkEndian.h

    Macros and helper functions for handling 16 and 32 bit values in
    big and little endian formats.
*/

#if defined(SK_CPU_LENDIAN) && defined(SK_CPU_BENDIAN)
    #error "can't have both LENDIAN and BENDIAN defined"
#endif

#if !defined(SK_CPU_LENDIAN) && !defined(SK_CPU_BENDIAN)
    #error "need either LENDIAN or BENDIAN defined"
#endif

/** Swap the two bytes in the low 16bits of the parameters.
    e.g. 0x1234 -> 0x3412
*/
static inline uint16_t SkEndianSwap16(U16CPU value) {
    SkASSERT(value == (uint16_t)value);
    return (uint16_t)((value >> 8) | (value << 8));
}

/** Vector version of SkEndianSwap16(), which swaps the
    low two bytes of each value in the array.
*/
static inline void SkEndianSwap16s(uint16_t array[], int count) {
    SkASSERT(count == 0 || array != NULL);

    while (--count >= 0) {
        *array = SkEndianSwap16(*array);
        array += 1;
    }
}

/** Reverse all 4 bytes in a 32bit value.
    e.g. 0x12345678 -> 0x78563412
*/
static inline uint32_t SkEndianSwap32(uint32_t value) {
    return  ((value & 0xFF) << 24) |
            ((value & 0xFF00) << 8) |
            ((value & 0xFF0000) >> 8) |
            (value >> 24);
}

/** Vector version of SkEndianSwap16(), which swaps the
    bytes of each value in the array.
*/
static inline void SkEndianSwap32s(uint32_t array[], int count) {
    SkASSERT(count == 0 || array != NULL);

    while (--count >= 0) {
        *array = SkEndianSwap32(*array);
        array += 1;
    }
}

#ifdef SK_CPU_LENDIAN
    #define SkEndian_SwapBE16(n)    SkEndianSwap16(n)
    #define SkEndian_SwapBE32(n)    SkEndianSwap32(n)
    #define SkEndian_SwapLE16(n)    (n)
    #define SkEndian_SwapLE32(n)    (n)
#else   // SK_CPU_BENDIAN
    #define SkEndian_SwapBE16(n)    (n)
    #define SkEndian_SwapBE32(n)    (n)
    #define SkEndian_SwapLE16(n)    SkEndianSwap16(n)
    #define SkEndian_SwapLE32(n)    SkEndianSwap32(n)
#endif


#endif

