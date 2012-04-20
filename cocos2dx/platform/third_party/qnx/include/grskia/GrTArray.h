/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrTArray_DEFINED
#define GrTArray_DEFINED

#include <new>
#include "GrTypes.h"
#include "GrTemplates.h"

// DATA_TYPE indicates that T has a trivial cons, destructor
// and can be shallow-copied
template <typename T, bool DATA_TYPE = false> class GrTArray {
public:
    GrTArray() {
        fCount = 0;
        fReserveCount = MIN_ALLOC_COUNT;
        fAllocCount = 0;
        fMemArray = NULL;
        fPreAllocMemArray = NULL;
    }

    explicit GrTArray(int reserveCount) {
        GrAssert(reserveCount >= 0);
        fCount = 0;
        fReserveCount = reserveCount > MIN_ALLOC_COUNT ? reserveCount :
                                                         MIN_ALLOC_COUNT;
        fAllocCount = fReserveCount;
        fMemArray = GrMalloc(sizeof(T) * fReserveCount);
        fPreAllocMemArray = NULL;
    }

    template <int N>
    GrTArray(GrAlignedSTStorage<N,T>* storage) {
        GrAssert(N > 0);
        fCount              = 0;
        fReserveCount       = N;
        fAllocCount         = N;
        fMemArray           = storage->get();
        fPreAllocMemArray   = storage->get();
    }

    GrTArray(void* preAllocStorage, int preAllocCount) {
        GrAssert(preAllocCount >= 0);
        // we allow NULL,0 args and revert to the default cons. behavior
        // this makes it possible for a owner-object to use same constructor
        // to get either prealloc or nonprealloc behavior based using same line
        GrAssert((NULL == preAllocStorage) == !preAllocCount);

        fCount              = 0;
        fReserveCount       = preAllocCount > 0 ? preAllocCount :
                                                  MIN_ALLOC_COUNT;
        fAllocCount         = preAllocCount;
        fMemArray           = preAllocStorage;
        fPreAllocMemArray   = preAllocStorage;
    }

    explicit GrTArray(const GrTArray& array) {
        fCount              = array.count();
        fReserveCount       = MIN_ALLOC_COUNT;
        fAllocCount         = GrMax(fReserveCount, fCount);
        fMemArray           = GrMalloc(sizeof(T) * fAllocCount);
        fPreAllocMemArray   = NULL;

        if (DATA_TYPE) {
            memcpy(fMemArray, array.fMemArray, sizeof(T) * fCount);
        } else {
            for (int i = 0; i < fCount; ++i) {
                new (fItemArray + i) T(array[i]);
            }
        }
    }

    GrTArray(const T* array, int count) {
        GrAssert(count >= 0);
        fCount              = count;
        fReserveCount       = MIN_ALLOC_COUNT;
        fAllocCount         = GrMax(fReserveCount, fCount);
        fMemArray           = GrMalloc(sizeof(T) * fAllocCount);
        fPreAllocMemArray   = NULL;
        if (DATA_TYPE) {
            memcpy(fMemArray, array, sizeof(T) * fCount);
        } else {
            for (int i = 0; i < fCount; ++i) {
                new (fItemArray + i) T(array[i]);
            }
        }
    }

    GrTArray(const GrTArray& array,
             void* preAllocStorage, int preAllocCount) {

        GrAssert(preAllocCount >= 0);

        // for same reason as non-copying cons we allow NULL, 0 for prealloc
        GrAssert((NULL == preAllocStorage) == !preAllocCount);

        fCount              = array.count();
        fReserveCount       = preAllocCount > 0 ? preAllocCount :
                                                  MIN_ALLOC_COUNT;
        fPreAllocMemArray   = preAllocStorage;

        if (fReserveCount >= fCount && preAllocCount) {
            fAllocCount = fReserveCount;
            fMemArray = preAllocStorage;
        } else {
            fAllocCount = GrMax(fCount, fReserveCount);
            fMemArray = GrMalloc(fAllocCount * sizeof(T));
        }

        if (DATA_TYPE) {
            memcpy(fMemArray, array.fMemArray, sizeof(T) * fCount);
        } else {
            for (int i = 0; i < fCount; ++i) {
                new (fItemArray + i) T(array[i]);
            }
        }
    }

    GrTArray(const T* array, int count,
             void* preAllocStorage, int preAllocCount) {

        GrAssert(count >= 0);
        GrAssert(preAllocCount >= 0);

        // for same reason as non-copying cons we allow NULL, 0 for prealloc
        GrAssert((NULL == preAllocStorage) == !preAllocCount);

        fCount              = count;
        fReserveCount       = (preAllocCount > 0) ? preAllocCount :
                                                    MIN_ALLOC_COUNT;
        fPreAllocMemArray   = preAllocStorage;

        if (fReserveCount >= fCount && preAllocCount) {
            fAllocCount = fReserveCount;
            fMemArray = preAllocStorage;
        } else {
            fAllocCount = GrMax(fCount, fReserveCount);
            fMemArray = GrMalloc(fAllocCount * sizeof(T));
        }

        if (DATA_TYPE) {
            memcpy(fMemArray, array, sizeof(T) * fCount);
        } else {
            for (int i = 0; i < fCount; ++i) {
                new (fItemArray + i) T(array[i]);
            }
        }
    }

    GrTArray& operator =(const GrTArray& array) {
        for (int i = 0; i < fCount; ++i) {
            fItemArray[i].~T();
        }
        fCount = 0;
        checkRealloc((int)array.count());
        fCount = array.count();
        if (DATA_TYPE) {
            memcpy(fMemArray, array.fMemArray, sizeof(T) * fCount);
        } else {
            for (int i = 0; i < fCount; ++i) {
                new (fItemArray + i) T(array[i]);
            }
        }
        return *this;
    }

    ~GrTArray() {
        for (int i = 0; i < fCount; ++i) {
            fItemArray[i].~T();
        }
        if (fMemArray != fPreAllocMemArray) {
            GrFree(fMemArray);
        }
    }

    void reset() { this->pop_back_n(fCount); }

    int count() const { return fCount; }

    bool empty() const { return !fCount; }

    T& push_back() {
        checkRealloc(1);
        new ((char*)fMemArray+sizeof(T)*fCount) T;
        ++fCount;
        return fItemArray[fCount-1];
    }

    void push_back_n(int n) {
        GrAssert(n >= 0);
        checkRealloc(n);
        for (int i = 0; i < n; ++i) {
            new (fItemArray + fCount + i) T;
        }
        fCount += n;
    }

    void pop_back() {
        GrAssert(fCount > 0);
        --fCount;
        fItemArray[fCount].~T();
        checkRealloc(0);
    }

    void pop_back_n(int n) {
        GrAssert(n >= 0);
        GrAssert(fCount >= n);
        fCount -= n;
        for (int i = 0; i < n; ++i) {
            fItemArray[i].~T();
        }
        checkRealloc(0);
    }

    // pushes or pops from the back to resize
    void resize_back(int newCount) {
        GrAssert(newCount >= 0);

        if (newCount > fCount) {
            push_back_n(newCount - fCount);
        } else if (newCount < fCount) {
            pop_back_n(fCount - newCount);
        }
    }

    T& operator[] (int i) {
        GrAssert(i < fCount);
        GrAssert(i >= 0);
        return fItemArray[i];
    }

    const T& operator[] (int i) const {
        GrAssert(i < fCount);
        GrAssert(i >= 0);
        return fItemArray[i];
    }

    T& front() { GrAssert(fCount > 0); return fItemArray[0];}

    const T& front() const { GrAssert(fCount > 0); return fItemArray[0];}

    T& back() { GrAssert(fCount); return fItemArray[fCount - 1];}

    const T& back() const { GrAssert(fCount > 0); return fItemArray[fCount - 1];}

    T& fromBack(int i) {
        GrAssert(i >= 0);
        GrAssert(i < fCount);
        return fItemArray[fCount - i - 1];
    }

    const T& fromBack(int i) const {
        GrAssert(i >= 0);
        GrAssert(i < fCount);
        return fItemArray[fCount - i - 1];
    }

private:

    static const int MIN_ALLOC_COUNT = 8;

    inline void checkRealloc(int delta) {
        GrAssert(fCount >= 0);
        GrAssert(fAllocCount >= 0);

        GrAssert(-delta <= fCount);

        int newCount = fCount + delta;
        int fNewAllocCount = fAllocCount;

        if (newCount > fAllocCount) {
            fNewAllocCount = GrMax(newCount + ((newCount + 1) >> 1),
                                   fReserveCount);
        } else if (newCount < fAllocCount / 3) {
            fNewAllocCount = GrMax(fAllocCount / 2, fReserveCount);
        }

        if (fNewAllocCount != fAllocCount) {

            fAllocCount = fNewAllocCount;
            char* fNewMemArray;

            if (fAllocCount == fReserveCount && NULL != fPreAllocMemArray) {
                fNewMemArray = (char*) fPreAllocMemArray;
            } else {
                fNewMemArray = (char*) GrMalloc(fAllocCount*sizeof(T));
            }

            if (DATA_TYPE) {
                memcpy(fNewMemArray, fMemArray, fCount * sizeof(T));
            } else {
                for (int i = 0; i < fCount; ++i) {
                    new (fNewMemArray + sizeof(T) * i) T(fItemArray[i]);
                    fItemArray[i].~T();
                }
            }

            if (fMemArray != fPreAllocMemArray) {
                GrFree(fMemArray);
            }
            fMemArray = fNewMemArray;
        }
    }

    int fReserveCount;
    int fCount;
    int fAllocCount;
    void*    fPreAllocMemArray;
    union {
        T*       fItemArray;
        void*    fMemArray;
    };
};

#endif

