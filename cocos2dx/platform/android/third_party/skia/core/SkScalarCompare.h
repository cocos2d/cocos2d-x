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

#ifndef SkScalarCompare_DEFINED
#define SkScalarCompare_DEFINED

#include "SkFloatBits.h"
#include "SkRect.h"

/** Skia can spend a lot of time just comparing scalars (e.g. quickReject).
    When scalar==fixed, this is very fast, and when scalar==hardware-float, this
    is also reasonable, but if scalar==software-float, then each compare can be
    a function call and take real time. To account for that, we have the flag
    SK_SCALAR_SLOW_COMPARES.

    If this is defined, we have a special trick where we quickly convert floats
    to a 2's compliment form, and then treat them as signed 32bit integers. In
    this form we lose a few subtlties (e.g. NaNs always comparing false) but
    we gain the speed of integer compares.
 */

#ifdef SK_SCALAR_SLOW_COMPARES
    typedef int32_t SkScalarCompareType;
    typedef SkIRect SkRectCompareType;
    #define SkScalarToCompareType(x)    SkScalarAs2sCompliment(x)
#else
    typedef SkScalar SkScalarCompareType;
    typedef SkRect SkRectCompareType;
    #define SkScalarToCompareType(x)    (x)
#endif

#endif

