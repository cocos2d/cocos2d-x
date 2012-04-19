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

#ifndef SkDeque_DEFINED
#define SkDeque_DEFINED

#include "SkTypes.h"

class SK_API SkDeque : SkNoncopyable {
public:
    explicit SkDeque(size_t elemSize);
    SkDeque(size_t elemSize, void* storage, size_t storageSize);
    ~SkDeque();

    bool    empty() const { return 0 == fCount; }
    int     count() const { return fCount; }
    size_t  elemSize() const { return fElemSize; }

    const void* front() const;
    const void* back() const;

    void* front() {
        return (void*)((const SkDeque*)this)->front();
    }

    void* back() {
        return (void*)((const SkDeque*)this)->back();
    }

    void* push_front();
    void* push_back();

    void pop_front();
    void pop_back();

private:
    struct Head;

public:
    class F2BIter {
    public:
        /**
         * Creates an uninitialized iterator. Must be reset()
         */
        F2BIter();

        F2BIter(const SkDeque& d);
        void* next();

        void reset(const SkDeque& d);

    private:
        SkDeque::Head*  fHead;
        char*           fPos;
        size_t          fElemSize;
    };

private:
    Head*   fFront;
    Head*   fBack;
    size_t  fElemSize;
    void*   fInitialStorage;
    int     fCount;

    friend class Iter;
};

#endif
