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

#ifndef SkUtils_DEFINED
#define SkUtils_DEFINED

#include "SkTypes.h"

///////////////////////////////////////////////////////////////////////////////

/** Similar to memset(), but it assigns a 16bit value into the buffer.
    @param buffer   The memory to have value copied into it
    @param value    The 16bit value to be copied into buffer
    @param count    The number of times value should be copied into the buffer.
*/
void sk_memset16_portable(uint16_t dst[], uint16_t value, int count);
typedef void (*SkMemset16Proc)(uint16_t dst[], uint16_t value, int count);
SkMemset16Proc SkMemset16GetPlatformProc();

/** Similar to memset(), but it assigns a 32bit value into the buffer.
    @param buffer   The memory to have value copied into it
    @param value    The 32bit value to be copied into buffer
    @param count    The number of times value should be copied into the buffer.
*/
void sk_memset32_portable(uint32_t dst[], uint32_t value, int count);
typedef void (*SkMemset32Proc)(uint32_t dst[], uint32_t value, int count);
SkMemset32Proc SkMemset32GetPlatformProc();

#if defined(ANDROID) && !defined(SK_BUILD_FOR_ANDROID_NDK)
    #include "cutils/memory.h"
    
    #define sk_memset16(dst, value, count)    android_memset16(dst, value, (count) << 1)
    #define sk_memset32(dst, value, count)    android_memset32(dst, value, (count) << 2)
#endif

#ifndef sk_memset16
extern SkMemset16Proc sk_memset16;
#endif

#ifndef sk_memset32
extern SkMemset32Proc sk_memset32;
#endif

///////////////////////////////////////////////////////////////////////////////

#define kMaxBytesInUTF8Sequence     4

#ifdef SK_DEBUG
    int SkUTF8_LeadByteToCount(unsigned c);
#else
    #define SkUTF8_LeadByteToCount(c)   ((((0xE5 << 24) >> ((unsigned)c >> 4 << 1)) & 3) + 1)
#endif

inline int SkUTF8_CountUTF8Bytes(const char utf8[]) {
    SkASSERT(utf8);
    return SkUTF8_LeadByteToCount(*(const uint8_t*)utf8);
}

int         SkUTF8_CountUnichars(const char utf8[]);
int         SkUTF8_CountUnichars(const char utf8[], size_t byteLength);
SkUnichar   SkUTF8_ToUnichar(const char utf8[]);
SkUnichar   SkUTF8_NextUnichar(const char**);
SkUnichar   SkUTF8_PrevUnichar(const char**);

/** Return the number of bytes need to convert a unichar
    into a utf8 sequence. Will be 1..kMaxBytesInUTF8Sequence,
    or 0 if uni is illegal.
*/
size_t      SkUTF8_FromUnichar(SkUnichar uni, char utf8[] = NULL);

///////////////////////////////////////////////////////////////////////////////

#define SkUTF16_IsHighSurrogate(c)  (((c) & 0xFC00) == 0xD800)
#define SkUTF16_IsLowSurrogate(c)   (((c) & 0xFC00) == 0xDC00)

int SkUTF16_CountUnichars(const uint16_t utf16[]);
int SkUTF16_CountUnichars(const uint16_t utf16[],
                                  int numberOf16BitValues);
// returns the current unichar and then moves past it (*p++)
SkUnichar SkUTF16_NextUnichar(const uint16_t**);
// this guy backs up to the previus unichar value, and returns it (*--p)
SkUnichar SkUTF16_PrevUnichar(const uint16_t**);
size_t SkUTF16_FromUnichar(SkUnichar uni, uint16_t utf16[] = NULL);

SK_API size_t SkUTF16_ToUTF8(const uint16_t utf16[], int numberOf16BitValues,
                           char utf8[] = NULL);

///////////////////////////////////////////////////////////////////////////////

class SkAutoTrace {
public:
    /** NOTE: label contents are not copied, just the ptr is
        retained, so DON'T DELETE IT.
    */
    SkAutoTrace(const char label[]) : fLabel(label) {
        SkDebugf("--- trace: %s Enter\n", fLabel);
    }
    ~SkAutoTrace() {
        SkDebugf("--- trace: %s Leave\n", fLabel);
    }
private:
    const char* fLabel;
};

///////////////////////////////////////////////////////////////////////////////

class SkAutoMemoryUsageProbe {
public:
    /** Record memory usage in constructor, and dump the result
        (delta and current total) in the destructor, with the optional
        label. NOTE: label contents are not copied, just the ptr is
        retained, so DON'T DELETE IT.
    */
    SkAutoMemoryUsageProbe(const char label[]);
    ~SkAutoMemoryUsageProbe();
private:
    const char* fLabel;
    size_t      fBytesAllocated;
};

#endif

