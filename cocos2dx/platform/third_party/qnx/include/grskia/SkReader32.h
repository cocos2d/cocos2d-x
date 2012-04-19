/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef SkReader32_DEFINED
#define SkReader32_DEFINED

#include "SkScalar.h"
#include "SkPoint.h"
#include "SkRect.h"

class SkString;

class SkReader32 : SkNoncopyable {
public:
    SkReader32() : fCurr(NULL), fStop(NULL), fBase(NULL) {}
    SkReader32(const void* data, size_t size)  {
        this->setMemory(data, size);
    }

    void setMemory(const void* data, size_t size) {
        SkASSERT(ptr_align_4(data));
        SkASSERT(SkAlign4(size) == size);
        
        fBase = fCurr = (const char*)data;
        fStop = (const char*)data + size;
    }
    
    uint32_t size() const { return fStop - fBase; }
    uint32_t offset() const { return fCurr - fBase; }
    bool eof() const { return fCurr >= fStop; }
    const void* base() const { return fBase; }
    const void* peek() const { return fCurr; }

    uint32_t available() const { return fStop - fCurr; }
    bool isAvailable(uint32_t size) const { return fCurr + size <= fStop; }
    
    void rewind() { fCurr = fBase; }

    void setOffset(size_t offset) {
        SkASSERT(SkAlign4(offset) == offset);
        SkASSERT(offset <= this->size());
        fCurr = fBase + offset;
    }
    
    bool readBool() { return this->readInt() != 0; }
    
    int32_t readInt() {
        SkASSERT(ptr_align_4(fCurr));
        int32_t value = *(const int32_t*)fCurr;
        fCurr += sizeof(value);
        SkASSERT(fCurr <= fStop);
        return value;
    }
    
    SkScalar readScalar() {
        SkASSERT(ptr_align_4(fCurr));
        SkScalar value = *(const SkScalar*)fCurr;
        fCurr += sizeof(value);
        SkASSERT(fCurr <= fStop);
        return value;
    }
    
    const SkPoint* skipPoint() {
        return (const SkPoint*)this->skip(sizeof(SkPoint));
    }
    
    const SkRect* skipRect() {
        return (const SkRect*)this->skip(sizeof(SkRect));
    }

    const void* skip(size_t size) {
        SkASSERT(ptr_align_4(fCurr));
        const void* addr = fCurr;
        fCurr += SkAlign4(size);
        SkASSERT(fCurr <= fStop);
        return addr;
    }
    
    void read(void* dst, size_t size) {
        SkASSERT(0 == size || dst != NULL);
        SkASSERT(ptr_align_4(fCurr));
        memcpy(dst, fCurr, size);
        fCurr += SkAlign4(size);
        SkASSERT(fCurr <= fStop);
    }
    
    uint8_t readU8() { return (uint8_t)this->readInt(); }
    uint16_t readU16() { return (uint16_t)this->readInt(); }
    int32_t readS32() { return this->readInt(); }
    uint32_t readU32() { return this->readInt(); }

    /**
     *  Read the length of a string (written by SkWriter32::writeString) into
     *  len (if len is not NULL) and return the null-ternimated address of the
     *  string within the reader's buffer.
     */
    const char* readString(size_t* len = NULL);

    /**
     *  Read the string (written by SkWriter32::writeString) and return it in
     *  copy (if copy is not null). Return the length of the string.
     */
    size_t readIntoString(SkString* copy);

private:
    // these are always 4-byte aligned
    const char* fCurr;  // current position within buffer
    const char* fStop;  // end of buffer
    const char* fBase;  // beginning of buffer
    
#ifdef SK_DEBUG
    static bool ptr_align_4(const void* ptr)
    {
        return (((const char*)ptr - (const char*)NULL) & 3) == 0;
    }
#endif
};

#endif
