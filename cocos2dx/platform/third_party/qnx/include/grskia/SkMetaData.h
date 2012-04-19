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

#ifndef SkMetaData_DEFINED
#define SkMetaData_DEFINED

#include "SkScalar.h"

class SkRefCnt;

class SK_API SkMetaData {
public:
    /**
     *  Used to manage the life-cycle of a ptr in the metadata. This is option
     *  in setPtr, and is only invoked when either copying one metadata to
     *  another, or when the metadata is destroyed.
     *
     *  setPtr(name, ptr, proc) {
     *      fPtr = proc(ptr, true);
     *  }
     *
     *  copy: A = B {
     *      A.fPtr = B.fProc(B.fPtr, true);
     *  }
     *
     *  ~SkMetaData {
     *      fProc(fPtr, false);
     *  }
     */
    typedef void* (*PtrProc)(void* ptr, bool doRef);

    /**
     *  Implements PtrProc for SkRefCnt pointers
     */
    static void* RefCntProc(void* ptr, bool doRef);

    SkMetaData();
    SkMetaData(const SkMetaData& src);
    ~SkMetaData();

    SkMetaData& operator=(const SkMetaData& src);

    void reset();

    bool findS32(const char name[], int32_t* value = NULL) const;
    bool findScalar(const char name[], SkScalar* value = NULL) const;
    const SkScalar* findScalars(const char name[], int* count,
                                SkScalar values[] = NULL) const;
    const char* findString(const char name[]) const;
    bool findPtr(const char name[], void** value = NULL, PtrProc* = NULL) const;
    bool findBool(const char name[], bool* value = NULL) const;
    const void* findData(const char name[], size_t* byteCount = NULL) const;

    bool hasS32(const char name[], int32_t value) const {
        int32_t v;
        return this->findS32(name, &v) && v == value;
    }
    bool hasScalar(const char name[], SkScalar value) const {
        SkScalar v;
        return this->findScalar(name, &v) && v == value;
    }
    bool hasString(const char name[], const char value[]) const {
        const char* v = this->findString(name);
        return  (v == NULL && value == NULL) ||
                (v != NULL && value != NULL && !strcmp(v, value));
    }
    bool hasPtr(const char name[], void* value) const {
        void* v;
        return this->findPtr(name, &v) && v == value;
    }
    bool hasBool(const char name[], bool value) const {
        bool    v;
        return this->findBool(name, &v) && v == value;
    }
    bool hasData(const char name[], const void* data, size_t byteCount) const {
        size_t len;
        const void* ptr = this->findData(name, &len);
        return NULL != ptr && len == byteCount && !memcmp(ptr, data, len);
    }

    void setS32(const char name[], int32_t value);
    void setScalar(const char name[], SkScalar value);
    SkScalar* setScalars(const char name[], int count, const SkScalar values[] = NULL);
    void setString(const char name[], const char value[]);
    void setPtr(const char name[], void* value, PtrProc proc = NULL);
    void setBool(const char name[], bool value);
    // the data is copied from the input pointer.
    void setData(const char name[], const void* data, size_t byteCount);

    bool removeS32(const char name[]);
    bool removeScalar(const char name[]);
    bool removeString(const char name[]);
    bool removePtr(const char name[]);
    bool removeBool(const char name[]);
    bool removeData(const char name[]);

    // helpers for SkRefCnt
    bool findRefCnt(const char name[], SkRefCnt** ptr = NULL) {
        return this->findPtr(name, reinterpret_cast<void**>(ptr));
    }
    bool hasRefCnt(const char name[], SkRefCnt* ptr) {
        return this->hasPtr(name, ptr);
    }
    void setRefCnt(const char name[], SkRefCnt* ptr) {
        this->setPtr(name, ptr, RefCntProc);
    }
    bool removeRefCnt(const char name[]) {
        return this->removePtr(name);
    }

    enum Type {
        kS32_Type,
        kScalar_Type,
        kString_Type,
        kPtr_Type,
        kBool_Type,
        kData_Type,

        kTypeCount
    };

    struct Rec;
    class Iter;
    friend class Iter;

    class Iter {
    public:
        Iter() : fRec(NULL) {}
        Iter(const SkMetaData&);

        /** Reset the iterator, so that calling next() will return the first
            data element. This is done implicitly in the constructor.
        */
        void reset(const SkMetaData&);

        /** Each time next is called, it returns the name of the next data element,
            or null when there are no more elements. If non-null is returned, then the
            element's type is returned (if not null), and the number of data values
            is returned in count (if not null).
        */
        const char* next(Type*, int* count);

    private:
        Rec* fRec;
    };

public:
    struct Rec {
        Rec*        fNext;
        uint16_t    fDataCount; // number of elements
        uint8_t     fDataLen;   // sizeof a single element
        uint8_t     fType;

        const void* data() const { return (this + 1); }
        void*       data() { return (this + 1); }
        const char* name() const { return (const char*)this->data() + fDataLen * fDataCount; }
        char*       name() { return (char*)this->data() + fDataLen * fDataCount; }

        static Rec* Alloc(size_t);
        static void Free(Rec*);
    };
    Rec*    fRec;

    const Rec* find(const char name[], Type) const;
    void* set(const char name[], const void* data, size_t len, Type, int count);
    bool remove(const char name[], Type);
};

#endif

