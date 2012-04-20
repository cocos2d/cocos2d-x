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

#ifndef SkTemplates_DEFINED
#define SkTemplates_DEFINED

#include "SkTypes.h"

/** \file SkTemplates.h

    This file contains light-weight template classes for type-safe and exception-safe
    resource management.
*/

/** \class SkAutoTCallVProc

    Call a function when this goes out of scope. The template uses two
    parameters, the object, and a function that is to be called in the destructor.
    If detach() is called, the object reference is set to null. If the object
    reference is null when the destructor is called, we do not call the
    function.
*/
template <typename T, void (*P)(T*)> class SkAutoTCallVProc : SkNoncopyable {
public:
    SkAutoTCallVProc(T* obj): fObj(obj) {}
    ~SkAutoTCallVProc() { if (fObj) P(fObj); }
    T* detach() { T* obj = fObj; fObj = NULL; return obj; }
private:
    T* fObj;
};

/** \class SkAutoTCallIProc

Call a function when this goes out of scope. The template uses two
parameters, the object, and a function that is to be called in the destructor.
If detach() is called, the object reference is set to null. If the object
reference is null when the destructor is called, we do not call the
function.
*/
template <typename T, int (*P)(T*)> class SkAutoTCallIProc : SkNoncopyable {
public:
    SkAutoTCallIProc(T* obj): fObj(obj) {}
    ~SkAutoTCallIProc() { if (fObj) P(fObj); }
    T* detach() { T* obj = fObj; fObj = NULL; return obj; }
private:
    T* fObj;
};

// See also SkTScopedPtr.
template <typename T> class SkAutoTDelete : SkNoncopyable {
public:
    SkAutoTDelete(T* obj, bool deleteWhenDone = true) : fObj(obj) {
        fDeleteWhenDone = deleteWhenDone;
    }
    ~SkAutoTDelete() { if (fDeleteWhenDone) delete fObj; }

    T*      get() const { return fObj; }
    void    free() { delete fObj; fObj = NULL; }
    T*      detach() { T* obj = fObj; fObj = NULL; return obj; }

private:
    T*  fObj;
    bool fDeleteWhenDone;
};

template <typename T> class SkAutoTDeleteArray : SkNoncopyable {
public:
    SkAutoTDeleteArray(T array[]) : fArray(array) {}
    ~SkAutoTDeleteArray() { delete[] fArray; }

    T*      get() const { return fArray; }
    void    free() { delete[] fArray; fArray = NULL; }
    T*      detach() { T* array = fArray; fArray = NULL; return array; }

private:
    T*  fArray;
};

/** Allocate an array of T elements, and free the array in the destructor
 */
template <typename T> class SkAutoTArray : SkNoncopyable {
public:
    /** Allocate count number of T elements
     */
    SkAutoTArray(size_t count) {
        fArray = NULL;
        if (count) {
            fArray = new T[count];
        }
        SkDEBUGCODE(fCount = count;)
    }

    ~SkAutoTArray() {
        delete[] fArray;
    }

    /** Return the array of T elements. Will be NULL if count == 0
     */
    T* get() const { return fArray; }
    
    /** Return the nth element in the array
     */
    T&  operator[](int index) const {
        SkASSERT((unsigned)index < fCount);
        return fArray[index];
    }

private:
    T*  fArray;
    SkDEBUGCODE(size_t fCount;)
};

/** Wraps SkAutoTArray, with room for up to N elements preallocated
 */
template <size_t N, typename T> class SkAutoSTArray : SkNoncopyable {
public:
    /** Allocate count number of T elements
     */
    SkAutoSTArray(size_t count) {
        if (count > N) {
            fArray = new T[count];
        } else if (count) {
            fArray = new (fStorage) T[count];
        } else {
            fArray = NULL;
        }
        fCount = count;
    }
    
    ~SkAutoSTArray() {
        if (fCount > N) {
            delete[] fArray;
        } else {
            T* start = fArray;
            T* iter = start + fCount;
            while (iter > start) {
                (--iter)->~T();
            }
        }
    }
    
    /** Return the number of T elements in the array
     */
    size_t count() const { return fCount; }
    
    /** Return the array of T elements. Will be NULL if count == 0
     */
    T* get() const { return fArray; }
    
    /** Return the nth element in the array
     */
    T&  operator[](int index) const {
        SkASSERT((unsigned)index < fCount);
        return fArray[index];
    }
    
private:
    size_t  fCount;
    T*      fArray;
    // since we come right after fArray, fStorage should be properly aligned
    char    fStorage[N * sizeof(T)];
};

/** Allocate a temp array on the stack/heap.
    Does NOT call any constructors/destructors on T (i.e. T must be POD)
*/
template <typename T> class SkAutoTMalloc : SkNoncopyable {
public:
    SkAutoTMalloc(size_t count)
    {
        fPtr = (T*)sk_malloc_flags(count * sizeof(T), SK_MALLOC_THROW | SK_MALLOC_TEMP);
    }
    ~SkAutoTMalloc()
    {
        sk_free(fPtr);
    }
    T* get() const { return fPtr; }

private:
    T*  fPtr;
};

template <size_t N, typename T> class SkAutoSTMalloc : SkNoncopyable {
public:
    SkAutoSTMalloc(size_t count)
    {
        if (count <= N)
            fPtr = fTStorage;
        else
            fPtr = (T*)sk_malloc_flags(count * sizeof(T), SK_MALLOC_THROW | SK_MALLOC_TEMP);
    }
    ~SkAutoSTMalloc()
    {
        if (fPtr != fTStorage)
            sk_free(fPtr);
    }
    T* get() const { return fPtr; }

private:
    T*          fPtr;
    union {
        uint32_t    fStorage32[(N*sizeof(T) + 3) >> 2];
        T           fTStorage[1];   // do NOT want to invoke T::T()
    };
};

#endif

