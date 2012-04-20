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

#ifndef SkBitmapCache_DEFINED
#define SkBitmapCache_DEFINED

#include "SkBitmap.h"

class SkBitmapCache : SkNoncopyable {
public:
    SkBitmapCache(int maxEntries);
    ~SkBitmapCache();

    bool find(const void* buffer, size_t len, SkBitmap*) const;
    void add(const void* buffer, size_t len, const SkBitmap&);

private:
    int fEntryCount;
    const int fMaxEntries;

    struct Entry;
    mutable Entry*  fHead;
    mutable Entry*  fTail;

    inline Entry* detach(Entry*) const;
    inline void attachToHead(Entry*) const;

#ifdef SK_DEBUG
    void validate() const;
#else
    void validate() const {}
#endif

    class AutoValidate : SkNoncopyable {
    public:
        AutoValidate(const SkBitmapCache* bc) : fBC(bc) { bc->validate(); }
        ~AutoValidate() { fBC->validate(); }
    private:
        const SkBitmapCache* fBC;
    };
};

#endif

