/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef SkTextFormatParams_DEFINES
#define SkTextFormatParams_DEFINES

#include "SkScalar.h"
#include "SkTypes.h"

// Fraction of the text size to lower a strike through line below the baseline.
#define kStdStrikeThru_Offset       (-SK_Scalar1 * 6 / 21)
// Fraction of the text size to lower a underline below the baseline.
#define kStdUnderline_Offset        (SK_Scalar1 / 9)
// Fraction of the text size to use for a strike through or under-line.
#define kStdUnderline_Thickness     (SK_Scalar1 / 18)

// The fraction of text size to embolden fake bold text scales with text size.
// At 9 points or below, the stroke width is increased by text size / 24.
// At 36 points and above, it is increased by text size / 32.  In between,
// it is interpolated between those values.
static const SkScalar kStdFakeBoldInterpKeys[] = {
    SkIntToScalar(9),
    SkIntToScalar(36)
};
static const SkScalar kStdFakeBoldInterpValues[] = {
    SK_Scalar1/24,
    SK_Scalar1/32
};
SK_COMPILE_ASSERT(SK_ARRAY_COUNT(kStdFakeBoldInterpKeys) ==
                  SK_ARRAY_COUNT(kStdFakeBoldInterpValues),
                  mismatched_array_size);
static const int kStdFakeBoldInterpLength =
    SK_ARRAY_COUNT(kStdFakeBoldInterpKeys);

#endif  //SkTextFormatParams_DEFINES
