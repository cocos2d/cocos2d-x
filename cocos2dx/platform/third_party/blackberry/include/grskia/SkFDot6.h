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

#ifndef SkFDot6_DEFINED
#define SkFDot6_DEFINED

#include "SkMath.h"

typedef int32_t SkFDot6;

#define SK_FDot6One         (64)
#define SK_FDot6Half        (32)

#ifdef SK_DEBUG
    inline SkFDot6 SkIntToFDot6(S16CPU x) {
        SkASSERT(SkToS16(x) == x);
        return x << 6;
    }
#else
    #define SkIntToFDot6(x) ((x) << 6)
#endif

#define SkFDot6Floor(x)     ((x) >> 6)
#define SkFDot6Ceil(x)      (((x) + 63) >> 6)
#define SkFDot6Round(x)     (((x) + 32) >> 6)

#define SkFixedToFDot6(x)   ((x) >> 10)

inline SkFixed SkFDot6ToFixed(SkFDot6 x) {
    SkASSERT((x << 10 >> 10) == x);

    return x << 10;
}

#ifdef SK_SCALAR_IS_FLOAT
    #define SkScalarToFDot6(x)  (SkFDot6)((x) * 64)
#else
    #define SkScalarToFDot6(x)  ((x) >> 10)
#endif

inline SkFixed SkFDot6Div(SkFDot6 a, SkFDot6 b) {
    SkASSERT(b != 0);

    if (a == (int16_t)a) {
        return (a << 16) / b;
    } else {
        return SkFixedDiv(a, b);
    }
}

#endif

