/* libs/graphics/animator/SkBase64.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkBase64_DEFINED
#define SkBase64_DEFINED

#include "SkTypes.h"

struct SkBase64 {
public:
    enum Error {
        kNoError,
        kPadError,
        kBadCharError
    };

    SkBase64();
    Error decode(const char* src, size_t length);
    char* getData() { return fData; }
    static size_t Encode(const void* src, size_t length, void* dest);

#ifdef SK_SUPPORT_UNITTEST
    static void UnitTest();
#endif
private:
    Error decode(const void* srcPtr, size_t length, bool writeDestination);

    size_t fLength;
    char* fData;
    friend class SkImage;
};

#endif // SkBase64_DEFINED
