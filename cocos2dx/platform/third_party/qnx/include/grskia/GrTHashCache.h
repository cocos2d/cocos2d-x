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


#ifndef GrTHashCache_DEFINED
#define GrTHashCache_DEFINED

#include "GrTDArray.h"

/**
 *  Key needs
 *      static bool EQ(const Entry&, const HashKey&);
 *      static bool LT(const Entry&, const HashKey&);
 *      uint32_t getHash() const;
 *
 *  Allows duplicate key entries but on find you may get
 *  any of the duplicate entries returned.
 */
template <typename T, typename Key, size_t kHashBits> class GrTHashTable {
public:
    GrTHashTable() { Gr_bzero(fHash, sizeof(fHash)); }
    ~GrTHashTable() {}

    int count() const { return fSorted.count(); }
    T*  find(const Key&) const;
    // return true if key was unique when inserted.
    bool insert(const Key&, T*);
    void remove(const Key&, const T*);
    T* removeAt(int index, uint32_t hash);
    void removeAll();
    void deleteAll();
    void unrefAll();

    /**
     *  Return the index for the element, using a linear search.
     */
    int slowFindIndex(T* elem) const { return fSorted.find(elem); }

#if GR_DEBUG
    void validate() const;
    bool contains(T*) const;
#endif

    // testing
    const GrTDArray<T*>& getArray() const { return fSorted; }
private:
    enum {
        kHashCount = 1 << kHashBits,
        kHashMask  = kHashCount - 1
    };
    static unsigned hash2Index(uint32_t hash) {
        hash ^= hash >> 16;
        if (kHashBits <= 8) {
            hash ^= hash >> 8;
        }
        return hash & kHashMask;
    }

    mutable T* fHash[kHashCount];
    GrTDArray<T*> fSorted;

    // search fSorted, and return the found index, or ~index of where it
    // should be inserted
    int searchArray(const Key&) const;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Key, size_t kHashBits>
int GrTHashTable<T, Key, kHashBits>::searchArray(const Key& key) const {
    int count = fSorted.count();
    if (0 == count) {
        // we should insert it at 0
        return ~0;
    }

    const T* const* array = fSorted.begin();
    int high = count - 1;
    int low = 0;
    while (high > low) {
        int index = (low + high) >> 1;
        if (Key::LT(*array[index], key)) {
            low = index + 1;
        } else {
            high = index;
        }
    }

    // check if we found it
    if (Key::EQ(*array[high], key)) {
        // above search should have found the first occurrence if there
        // are multiple.
        GrAssert(0 == high || Key::LT(*array[high - 1], key));
        return high;
    }

    // now return the ~ of where we should insert it
    if (Key::LT(*array[high], key)) {
        high += 1;
    }
    return ~high;
}

template <typename T, typename Key, size_t kHashBits>
T* GrTHashTable<T, Key, kHashBits>::find(const Key& key) const {
    int hashIndex = hash2Index(key.getHash());
    T* elem = fHash[hashIndex];

    if (NULL == elem || !Key::EQ(*elem, key)) {
        // bsearch for the key in our sorted array
        int index = this->searchArray(key);
        if (index < 0) {
            return NULL;
        }
        elem = fSorted[index];
        // update the hash
        fHash[hashIndex] = elem;
    }
    return elem;
}

template <typename T, typename Key, size_t kHashBits>
bool GrTHashTable<T, Key, kHashBits>::insert(const Key& key, T* elem) {
    int index = this->searchArray(key);
    bool first = index < 0;
    if (first) {
        // turn it into the actual index
        index = ~index;
    }
    // add it to our array
    *fSorted.insert(index) = elem;
    // update our hash table (overwrites any dupe's position in the hash)
    fHash[hash2Index(key.getHash())] = elem;
    return first;
}

template <typename T, typename Key, size_t kHashBits>
void GrTHashTable<T, Key, kHashBits>::remove(const Key& key, const T* elem) {
    int index = hash2Index(key.getHash());
    if (fHash[index] == elem) {
        fHash[index] = NULL;
    }

    // remove from our sorted array
    index = this->searchArray(key);
    GrAssert(index >= 0);
    // if there are multiple matches searchArray will give us the first match
    // march forward until we find elem.
    while (elem != fSorted[index]) {
        ++index;
        GrAssert(index < fSorted.count());
    }
    GrAssert(elem == fSorted[index]);
    fSorted.remove(index);
}

template <typename T, typename Key, size_t kHashBits>
T* GrTHashTable<T, Key, kHashBits>::removeAt(int elemIndex, uint32_t hash) {
    int hashIndex = hash2Index(hash);
    if (fHash[hashIndex] == fSorted[elemIndex]) {
        fHash[hashIndex] = NULL;
    }
    // remove from our sorted array
    T* elem = fSorted[elemIndex];
    fSorted.remove(elemIndex);
    return elem;
}

template <typename T, typename Key, size_t kHashBits>
void GrTHashTable<T, Key, kHashBits>::removeAll() {
    fSorted.reset();
    Gr_bzero(fHash, sizeof(fHash));
}

template <typename T, typename Key, size_t kHashBits>
void GrTHashTable<T, Key, kHashBits>::deleteAll() {
    fSorted.deleteAll();
    Gr_bzero(fHash, sizeof(fHash));
}

template <typename T, typename Key, size_t kHashBits>
void GrTHashTable<T, Key, kHashBits>::unrefAll() {
    fSorted.unrefAll();
    Gr_bzero(fHash, sizeof(fHash));
}

#if GR_DEBUG
template <typename T, typename Key, size_t kHashBits>
void GrTHashTable<T, Key, kHashBits>::validate() const {
    for (size_t i = 0; i < GR_ARRAY_COUNT(fHash); i++) {
        if (fHash[i]) {
            unsigned hashIndex = hash2Index(Key::GetHash(*fHash[i]));
            GrAssert(hashIndex == i);
        }
    }

    int count = fSorted.count();
    for (int i = 1; i < count; i++) {
        GrAssert(Key::LT(*fSorted[i - 1], *fSorted[i]) ||
                 Key::EQ(*fSorted[i - 1], *fSorted[i]));
    }
}

template <typename T, typename Key, size_t kHashBits>
bool GrTHashTable<T, Key, kHashBits>::contains(T* elem) const {
    int index = fSorted.find(elem);
    return index >= 0;
}

#endif

#endif

