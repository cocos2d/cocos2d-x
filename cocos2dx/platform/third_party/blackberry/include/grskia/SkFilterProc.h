/*
 * Copyright (C) 2006-2008 The Android Open Source Project
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

#ifndef SkFilter_DEFINED
#define SkFilter_DEFINED

#include "SkMath.h"
#include "SkFixed.h"

typedef unsigned (*SkFilterProc)(unsigned x00, unsigned x01,
                                 unsigned x10, unsigned x11);

const SkFilterProc* SkGetBilinearFilterProcTable();

inline SkFilterProc SkGetBilinearFilterProc(const SkFilterProc* table,
                                            SkFixed x, SkFixed y)
{
    SkASSERT(table);
    
    // convert to dot 2
    x = (unsigned)(x << 16) >> 30;
    y = (unsigned)(y << 16) >> 30;
    return table[(y << 2) | x];
}

inline SkFilterProc SkGetBilinearFilterProc22(const SkFilterProc* table,
                                              unsigned x, unsigned y)
{
    SkASSERT(table);
    
    // extract low 2 bits
    x = x << 30 >> 30;
    y = y << 30 >> 30;
    return table[(y << 2) | x];
}

inline const SkFilterProc* SkGetBilinearFilterProc22Row(const SkFilterProc* table,
                                                        unsigned y)
{
    SkASSERT(table);
    // extract low 2 bits and shift up 2
    return &table[y << 30 >> 28];
}

inline SkFilterProc SkGetBilinearFilterProc22RowProc(const SkFilterProc* row,
                                                     unsigned x)
{
    SkASSERT(row);    
    // extract low 2 bits
    return row[x << 30 >> 30];
}

///////////////////////////////////////////////////////////////////////////////

typedef unsigned (*SkFilter32Proc)(uint32_t x00, uint32_t x01,
                                   uint32_t x10, uint32_t x11);

const SkFilter32Proc* SkGetFilter32ProcTable();

inline SkFilter32Proc SkGetFilter32Proc22(const SkFilter32Proc* table,
                                          unsigned x, unsigned y)
{
    SkASSERT(table);
    
    // extract low 2 bits
    x = x << 30 >> 30;
    y = y << 30 >> 30;
    return table[(y << 2) | x];
}

inline const SkFilter32Proc* SkGetFilter32Proc22Row(const SkFilter32Proc* table,
                                                    unsigned y)
{
    SkASSERT(table);
    // extract low 2 bits and shift up 2
    return &table[y << 30 >> 28];
}

inline SkFilter32Proc SkGetFilter32Proc22RowProc(const SkFilter32Proc* row,
                                                 unsigned x)
{
    SkASSERT(row);
    // extract low 2 bits
    return row[x << 30 >> 30];
}

///////////////////////////////////////////////////////////////////////////////

/** Special version of SkFilterProc. This takes the address of 4 ints, and combines them a byte at a
    time. AABBCCDD.
*/
typedef uint32_t (*SkFilterPtrProc)(const uint32_t*, const uint32_t*, const uint32_t*, const uint32_t*);

const SkFilterPtrProc* SkGetBilinearFilterPtrProcTable();
inline SkFilterPtrProc SkGetBilinearFilterPtrProc(const SkFilterPtrProc* table, SkFixed x, SkFixed y)
{
    SkASSERT(table);

    // convert to dot 2
    x = (unsigned)(x << 16) >> 30;
    y = (unsigned)(y << 16) >> 30;
    return table[(y << 2) | x];
}

/** Given a Y value, return a subset of the proc table for that value.
    Pass this to SkGetBilinearFilterPtrXProc with the corresponding X value to get the
    correct proc.
*/
inline const SkFilterPtrProc* SkGetBilinearFilterPtrProcYTable(const SkFilterPtrProc* table, SkFixed y)
{
    SkASSERT(table);

    y = (unsigned)(y << 16) >> 30;
    return table + (y << 2);
}

/** Given a subtable returned by SkGetBilinearFilterPtrProcYTable(), return the proc for the
    specified X value.
*/
inline SkFilterPtrProc SkGetBilinearFilterPtrXProc(const SkFilterPtrProc* table, SkFixed x)
{
    SkASSERT(table);

    // convert to dot 2
    x = (unsigned)(x << 16) >> 30;
    return table[x];
}

#endif


