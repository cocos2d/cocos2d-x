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

#ifndef SkTDStack_DEFINED
#define SkTDStack_DEFINED

#include "SkTypes.h"

template <typename T> class SkTDStack : SkNoncopyable {
public:
    SkTDStack() : fCount(0), fTotalCount(0) {
        fInitialRec.fNext = NULL;
        fRec = &fInitialRec;

    //  fCount = kSlotCount;
    }

    ~SkTDStack() {
        Rec* rec = fRec;
        while (rec != &fInitialRec) {
            Rec* next = rec->fNext;
            sk_free(rec);
            rec = next;
        }
    }

    int count() const { return fTotalCount; }
    int depth() const { return fTotalCount; }
    bool empty() const { return fTotalCount == 0; }

    T* push() {
        SkASSERT(fCount <= kSlotCount);
        if (fCount == kSlotCount) {
            Rec* rec = (Rec*)sk_malloc_throw(sizeof(Rec));
            rec->fNext = fRec;
            fRec = rec;
            fCount = 0;
        }
        ++fTotalCount;
        return &fRec->fSlots[fCount++];
    }

    void push(const T& elem) { *this->push() = elem; }

    const T& index(int idx) const {
        SkASSERT(fRec && fCount > idx);
        return fRec->fSlots[fCount - idx - 1];
    }

    T& index(int idx) {
        SkASSERT(fRec && fCount > idx);
        return fRec->fSlots[fCount - idx - 1];
    }

    const T& top() const {
        SkASSERT(fRec && fCount > 0);
        return fRec->fSlots[fCount - 1];
    }

    T& top() {
        SkASSERT(fRec && fCount > 0);
        return fRec->fSlots[fCount - 1];
    }

    void pop(T* elem) {
        if (elem) {
            *elem = fRec->fSlots[fCount - 1];
        }
        this->pop();
    }

    void pop() {
        SkASSERT(fCount > 0 && fRec);
        --fTotalCount;
        if (--fCount == 0) {
            if (fRec != &fInitialRec) {
                Rec* rec = fRec->fNext;
                sk_free(fRec);
                fCount = kSlotCount;
                fRec = rec;
            } else {
                SkASSERT(fTotalCount == 0);
            }
        }
    }

private:
    enum {
        kSlotCount  = 8
    };

    struct Rec;
    friend struct Rec;

    struct Rec {
        Rec* fNext;
        T    fSlots[kSlotCount];
    };
    Rec     fInitialRec;
    Rec*    fRec;
    int     fCount, fTotalCount;
};

#endif

