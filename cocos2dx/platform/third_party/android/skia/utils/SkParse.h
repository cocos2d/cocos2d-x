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

#ifndef SkParse_DEFINED
#define SkParse_DEFINED

#include "SkColor.h"
#include "SkMath.h"

class SkParse {
public:
    static int Count(const char str[]); // number of scalars or int values
    static int Count(const char str[], char separator);
    static const char* FindColor(const char str[], SkColor* value);
    static const char* FindHex(const char str[], uint32_t* value);
    static const char* FindMSec(const char str[], SkMSec* value);
    static const char* FindNamedColor(const char str[], size_t len, SkColor* color);
    static const char* FindS32(const char str[], int32_t* value);
    static const char* FindScalar(const char str[], SkScalar* value);
    static const char* FindScalars(const char str[], SkScalar value[], int count);

    static bool FindBool(const char str[], bool* value);
    // return the index of str in list[], or -1 if not found
    static int  FindList(const char str[], const char list[]);
#ifdef SK_SUPPORT_UNITTEST
    static void TestColor();
    static void UnitTest();
#endif
};

#endif

